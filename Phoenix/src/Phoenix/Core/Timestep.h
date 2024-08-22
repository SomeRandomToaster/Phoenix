#pragma once

namespace Phoenix
{
	class Timestep
	{
	public:
		Timestep(float time) { this->time = time; }
		operator float() { return time; }

		float GetSeconds() { return time; }
		float GetMilliseconds() { return time * 1000.f; }
	private:
		float time;
	};
}