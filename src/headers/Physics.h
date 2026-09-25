#ifndef PHYSICS_H
#define PHYSICS_H

#include "Simulation.h"

class Physics {
	private:
		double m_time;

		// delta time
		double m_dt;

		// tolerance allowed for the interface sharpening algorithm
		double m_interfaceTolerance;

		// scalar dimensionless parameter to be defined for each application, which helps with interface sharpening
		// epsilon_h = epsilon * h, where h is grid-size represents how wide the interface sharpening is
		double m_epsilon;

		void InitializeAlgorithm(Simulation& simulation);
	public:
		Physics(float dt, float interfaceTol, float epsilon);

		void ApplyBoundary(Simulation& simulation);

		void CalculateEOS(Simulation& simulation);

		void Compute(Simulation& simulation);

		void SetTime(float t);

		void SetTimeStep(float dt);

		void SetInterfaceTolerance(float tol);

		void SetEpsilon(float epsilon);

		double GetTime();

		double GetDeltaTime();

		double GetInterfaceTolerance();

		double GetEpsilon();
};

#endif
