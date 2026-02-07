#include <Equations/FlatEarth.h>

namespace Equations
{
	std::vector<float> FlatEarth(const std::vector<float>& x, float t, const ModelSet& models) {
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
        std::vector<float> dx(x.size());

        // State variables init
        float u_b_mps = x[0];
        float v_b_mps = x[1];
        float w_b_mps = x[2];
        float p_b_rps = x[3];
        float q_b_rps = x[4];
        float r_b_rps = x[5];
        float x_n_m = x[6];
        float y_n_m = x[7];
        float z_n_m = x[8];
        float phi_n_r = x[9];
        float theta_n_r = x[10];
        float psi_n_r = x[11];

        // Euler angles trig functions
        float s_phi = sinf(phi_n_r);
        float c_phi = cosf(phi_n_r);
        float s_theta = sinf(theta_n_r);
        float c_theta = cosf(theta_n_r);
        float t_theta = tanf(theta_n_r);
        float s_psi = sinf(psi_n_r);
        float c_psi = cosf(psi_n_r);

        // Vehicle model parameters
        float m_kg = models.vmod->m_kg;
        float Jx_kgm2 = models.vmod->Jx_kgm2;
        float Jy_kgm2 = models.vmod->Jy_kgm2;
        float Jz_kgm2 = models.vmod->Jz_kgm2;
        float Jxz_kgm2 = models.vmod->Jxz_kgm2;
        float CD_approx = models.vmod->CD_approx;
        float Aref_m2 = models.vmod->Aref_m2;

        float Jden_kg2m4 = Jx_kgm2 * Jz_kgm2 - Jxz_kgm2 * Jxz_kgm2;

        // Gravity
        float gz_n_mps2 = 9.81f;

        float gx_b_mps2 = -s_theta * gz_n_mps2;
        float gy_b_mps2 = s_phi * c_theta * gz_n_mps2;
        float gz_b_mps2 = c_phi * c_theta * gz_n_mps2;

        // Aerodynamics
        //// Atmosphere model
        float h_m = -z_n_m; //Height
        float rho_kgpm3 = 1.2f;
        //rho_kgpm3 = interp.atmo_interp(amod['rho'], h_m)

        //// Air data calculation
        float true_airspeed_mps = sqrtf(u_b_mps * u_b_mps + v_b_mps * v_b_mps + w_b_mps * w_b_mps);
        float qbar_kgpms2 = 0.5f * rho_kgpm3 * true_airspeed_mps * true_airspeed_mps;

        float w_over_u = 0;
        if(u_b_mps != 0) {
            w_over_u = w_b_mps / u_b_mps;
        }

        float v_over_Vrel = 0;
        if (true_airspeed_mps != 0) {
            v_over_Vrel = v_b_mps / true_airspeed_mps;
        }

        float alpha_r = atanf(w_over_u); // Angle of Attack(AoA)
        float beta_r = asinf(v_over_Vrel); // Angle of Sideslip(AoS)
        float s_alpha = sinf(alpha_r);
        float c_alpha = cosf(alpha_r);
        float s_beta = sinf(beta_r);
        float c_beta = cosf(beta_r);

        //// Aerodynamic forces
        float drag_kgmps2 = CD_approx * qbar_kgpms2 * Aref_m2;
        float side_kgmps2 = 0;
        float lift_kgmps2 = 0;

        // External forces
        float Fx_b_kgmps2 = -c_alpha * c_beta * drag_kgmps2 + c_alpha * s_beta * side_kgmps2 + s_alpha * lift_kgmps2;
        float Fy_b_kgmps2 = -s_beta * drag_kgmps2 - c_beta * side_kgmps2;
        float Fz_b_kgmps2 = -s_alpha * c_beta * drag_kgmps2 + s_alpha * s_beta * side_kgmps2 - c_alpha * lift_kgmps2;

        // External moments
        float L_b_kgm2ps2 = 0;
        float M_b_kgm2ps2 = 0;
        float N_b_kgm2ps2 = 0;

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