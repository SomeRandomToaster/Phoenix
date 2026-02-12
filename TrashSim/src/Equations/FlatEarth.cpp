#include <Equations/FlatEarth.h>
#include <Models/Atmosphere/USSA1976.h>

namespace Equations
{
	std::vector<double> FlatEarth(const std::vector<double>& x, double t, const void* data) {
        /*
        :params:
        x - vector of state variables
        t - time[s]
        model - dictionary of the aircraft' physical characteristics


        : return : derivative of state vector

        Variable naming convention <name>_[reference frame_]<units>
        Reference frame is mandatory for vectors
        reference frames :
            b - body fixed CS
            n - North - East - Down(NED) CS, fixed to the point on the earth surface
        units naming :
            -simplified to kilograms, meters, radians and seconds(in this order)
            - 'p' divides the numerator and the denominator

        Variable names :
            u, v, w - components of velocity
            p, q, r - components of angular velocity
            phi, psi, theta - roll, pitch and yaw relative to NED
        */

        // Answer init
        std::vector<double> dx(x.size());

        // State variables init
        double u_b_mps = x[0];
        double v_b_mps = x[1];
        double w_b_mps = x[2];
        double p_b_rps = x[3];
        double q_b_rps = x[4];
        double r_b_rps = x[5];
        double x_n_m = x[6];
        double y_n_m = x[7];
        double z_n_m = x[8];
        double phi_n_r = x[9];
        double theta_n_r = x[10];
        double psi_n_r = x[11];

        // Euler angles trig functions
        double s_phi = sin(phi_n_r);
        double c_phi = cos(phi_n_r);
        double s_theta = sin(theta_n_r);
        double c_theta = cos(theta_n_r);
        double t_theta = tan(theta_n_r);
        double s_psi = sin(psi_n_r);
        double c_psi = cos(psi_n_r);

        // Vehicle model parameters

        const ModelSet* models = (const ModelSet*)data;
        double m_kg = models->vmod->m_kg;
        double Jx_kgm2 = models->vmod->Jx_kgm2;
        double Jy_kgm2 = models->vmod->Jy_kgm2;
        double Jz_kgm2 = models->vmod->Jz_kgm2;
        double Jxz_kgm2 = models->vmod->Jxz_kgm2;
        double CD_approx = models->vmod->CD_approx;
        double Aref_m2 = models->vmod->Aref_m2;

        double Jden_kg2m4 = Jx_kgm2 * Jz_kgm2 - Jxz_kgm2 * Jxz_kgm2;

        // Gravity
        // double gz_n_mps2 = 9.81;
        double G_m3pkgs2 = 6.6743015e-11;
        double Me_kg = 5.97226e24;
        double R_m = 6378137 - z_n_m;
        double gz_n_mps2 = G_m3pkgs2 * Me_kg / (R_m * R_m);

        double gx_b_mps2 = -s_theta * gz_n_mps2;
        double gy_b_mps2 = s_phi * c_theta * gz_n_mps2;
        double gz_b_mps2 = c_phi * c_theta * gz_n_mps2;

        // Aerodynamics
        //// Atmosphere model
        double h_m = -z_n_m; //Height
        //double rho_kgpm3 = 1.2f;
        double rho_kgpm3 = USSA1976::InterpByTable(models->amod->table["rho_kgpm3"], h_m);

        //// Air data calculation
        double true_airspeed_mps = sqrt(u_b_mps * u_b_mps + v_b_mps * v_b_mps + w_b_mps * w_b_mps);
        double qbar_kgpms2 = 0.5f * rho_kgpm3 * true_airspeed_mps * true_airspeed_mps;

        double w_over_u = 0;
        if(u_b_mps != 0) {
            w_over_u = w_b_mps / u_b_mps;
        }

        double v_over_Vrel = 0;
        if (true_airspeed_mps != 0) {
            v_over_Vrel = v_b_mps / true_airspeed_mps;
        }

        double alpha_r = atan(w_over_u); // Angle of Attack(AoA)
        double beta_r = asin(v_over_Vrel); // Angle of Sideslip(AoS)
        double s_alpha = sin(alpha_r);
        double c_alpha = cos(alpha_r);
        double s_beta = sin(beta_r);
        double c_beta = cos(beta_r);

        //// Aerodynamic forces
        double drag_kgmps2 = 0; //CD_approx * qbar_kgpms2 * Aref_m2;
        double side_kgmps2 = 0;
        double lift_kgmps2 = 0;

        // External forces
        double Fx_b_kgmps2 = -c_alpha * c_beta * drag_kgmps2 + c_alpha * s_beta * side_kgmps2 + s_alpha * lift_kgmps2;
        double Fy_b_kgmps2 = -s_beta * drag_kgmps2 - c_beta * side_kgmps2;
        double Fz_b_kgmps2 = -s_alpha * c_beta * drag_kgmps2 + s_alpha * s_beta * side_kgmps2 - c_alpha * lift_kgmps2;

        // External moments
        double L_b_kgm2ps2 = 0;
        double M_b_kgm2ps2 = 0;
        double N_b_kgm2ps2 = 0;

        // Derivatives
        //// Translation equations
        dx[0] = Fx_b_kgmps2 / m_kg + gx_b_mps2 - w_b_mps * q_b_rps + v_b_mps * r_b_rps;
        dx[1] = Fy_b_kgmps2 / m_kg + gy_b_mps2 - u_b_mps * r_b_rps + w_b_mps * p_b_rps;
        dx[2] = Fz_b_kgmps2 / m_kg + gz_b_mps2 - v_b_mps * p_b_rps + u_b_mps * q_b_rps;
        //// Rotational equations
        dx[3] = (Jxz_kgm2 * (Jx_kgm2 - Jy_kgm2 + Jz_kgm2) * p_b_rps * q_b_rps
            - (Jz_kgm2 * (Jz_kgm2 - Jy_kgm2) + Jxz_kgm2 * Jxz_kgm2) * q_b_rps * r_b_rps
            + Jz_kgm2 * L_b_kgm2ps2 + Jxz_kgm2 * N_b_kgm2ps2) / Jden_kg2m4;
        dx[4] = ((Jz_kgm2 - Jx_kgm2) * p_b_rps * r_b_rps - Jxz_kgm2 * (p_b_rps * p_b_rps - r_b_rps * r_b_rps) + M_b_kgm2ps2) / Jy_kgm2;
        dx[5] = (-Jxz_kgm2 * (Jx_kgm2 - Jy_kgm2 + Jz_kgm2) * q_b_rps * r_b_rps
            + (Jx_kgm2 * (Jx_kgm2 - Jy_kgm2) + Jxz_kgm2 * Jxz_kgm2) * p_b_rps * q_b_rps
            + Jxz_kgm2 * L_b_kgm2ps2 + Jx_kgm2 * N_b_kgm2ps2) / Jden_kg2m4;

        //// Navigational equations
        dx[6] = (c_theta * c_psi * u_b_mps + (-c_phi * s_psi + s_phi * s_theta * c_psi) * v_b_mps
            + (s_phi * s_psi + c_phi * s_theta * c_psi) * w_b_mps);
        dx[7] = (c_theta * s_psi * u_b_mps + (c_phi * c_psi + s_phi * s_theta * s_psi) * v_b_mps
            + (-s_phi * c_psi + c_phi * s_theta * s_psi) * w_b_mps);
        dx[8] = -s_theta * u_b_mps + s_phi * c_theta * v_b_mps + c_phi * c_theta * w_b_mps;
        //// Euler kinematic equations
        dx[9] = p_b_rps + s_phi * c_theta * q_b_rps + c_phi * t_theta * r_b_rps;
        dx[10] = c_phi * q_b_rps - s_phi * r_b_rps;
        dx[11] = (s_phi / c_theta) * q_b_rps + (c_phi / c_theta) * r_b_rps;

        return dx;
	}
}