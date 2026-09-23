#include<algorithm>
#include<cmath>

#include "Physics.h"
#include "Fluid.h"
#include "Problem.h"

// sets the initial time and time step
Physics::Physics(float dt, float interfaceTol, float epsilon) {
	SetTime(0.00);
	SetTimeStep(dt);
	SetInterfaceTolerance(interfaceTol);
	SetEpsilon(epsilon);
}

void Physics::ApplyBoundary(Problem &problem) {
	// to start let's just set all ghost cell values to be equal to their neighbor
}

// proceeds to the next time, performing all physics necessary to do so
void Physics::Compute(Problem& problem) {
	Physics::InitializeAlgorithm(problem);

	m_time += m_dt;
	return;
}

void Physics::InitializeAlgorithm(Problem& problem) {
	ApplyBoundary(problem);
	double epsilon_h = m_epsilon * problem.m_gridResolution;
	float a = 0.5; // this might need to be changed later. Look at alpha values in paper and decide. Or maybe find best value myself.
	std::vector<double> psi(problem.m_NTot);
	std::vector<double> q(problem.m_NTot);
	std::vector<double> phiNew(problem.m_NTot);
	std::vector<double> rhoNew(problem.m_NTot);
	
	for (;;) {
		for (int k = 1; k < problem.m_nz; ++k) {
			for (int j = 1; j < problem.m_ny; ++j) {
				
				size_t id = problem.Index(1,j,k);

				for (int i = 1; i < problem.m_nx; ++i, ++id) {
					
					const double tmpPhi = std::clamp(problem.m_phi[id], 0.0, 1.0);

					const double tmp1 = std::pow(tmpPhi, a);
					const double tmp2 = std::pow(1.0 - tmpPhi, a);

					psi[id] = tmp1 / (tmp1 + tmp2);
				}
			}
		}

		for (int k = 1; k < problem.m_nz; ++k) {
			for (int j = 1; j < problem.m_ny; ++j) {
				
				size_t id = problem.Index(1,j,k);

				for (int i = 1; i < problem.m_nx; ++i, ++id) {
					
					const double dPsidx = (psi[id + 1] - psi[id - 1]) / (2 * problem.m_gridResolution);
					const double dPsidy = (psi[id + problem.m_strideY] - psi[id - problem.m_strideY]) / (2 * problem.m_gridResolution);
					const double dPsidz = (psi[id + problem.m_strideZ] - psi[id - problem.m_strideZ]) / (2 * problem.m_gridResolution);

					const double gradPsiMag = std::sqrt(dPsidx*dPsidx + dPsidy*dPsidy + dPsidz*dPsidz);

					double normx = 0.0;
					double normy = 0.0;
					double normz = 0.0;

					if (gradPsiMag > epsilon_h) {
						normx = dPsidx / gradPsiMag;
						normy = dPsidy / gradPsiMag;
						normz = dPsidz / gradPsiMag;
					}

					
					const double dRhodx = (problem.m_U.rho[id + 1] - problem.m_U.rho[id - 1]) / (2 * problem.m_gridResolution);
					const double dRhody = (problem.m_U.rho[id + problem.m_strideY] - problem.m_U.rho[id - problem.m_strideY]) / (2 * problem.m_gridResolution);
					const double dRhodz = (problem.m_U.rho[id + problem.m_strideZ] - problem.m_U.rho[id - problem.m_strideZ]) / (2 * problem.m_gridResolution);

					const double normalGradRho = normx*dRhodx + normy*dRhody + normz*dRhodz;

					q[id] = epsilon_h * normalGradRho;
				}
			}
		}

		double maxChange = 0.0;

		for (int k = 1; k < problem.m_nz; ++k) {
			for (int j = 1; j < problem.m_ny; ++j) {
				
				size_t id = problem.Index(1,j,k);

				for (int i = 1; i < problem.m_nx; ++i, ++id) {

					const double tmpPhi = std::clamp(problem.m_phi[id], 0.0, 1.0);
					
					const double dPsidx = (psi[id + 1] - psi[id - 1]) / (2 * problem.m_gridResolution);
					const double dPsidy = (psi[id + problem.m_strideY] - psi[id - problem.m_strideY]) / (2 * problem.m_gridResolution);
					const double dPsidz = (psi[id + problem.m_strideZ] - psi[id - problem.m_strideZ]) / (2 * problem.m_gridResolution);

					const double gradPsiMag = std::sqrt(dPsidx*dPsidx + dPsidy*dPsidy + dPsidz*dPsidz);

					double normx = 0.0;
					double normy = 0.0;
					double normz = 0.0;

					if (gradPsiMag > epsilon_h) {
						normx = dPsidx / gradPsiMag;
						normy = dPsidy / gradPsiMag;
						normz = dPsidz / gradPsiMag;
					}
					
					const double dPhidx = (problem.m_phi[id + 1] - problem.m_phi[id - 1]) / (2 * problem.m_gridResolution);
					const double dPhidy = (problem.m_phi[id + problem.m_strideY] - problem.m_phi[id - problem.m_strideY]) / (2 * problem.m_gridResolution);
					const double dPhidz = (problem.m_phi[id + problem.m_strideZ] - problem.m_phi[id - problem.m_strideZ]) / (2 * problem.m_gridResolution);

					const double gradPhiMag = std::sqrt(dPhidx*dPhidx + dPhidy*dPhidy + dPhidz*dPhidz);

					const double phiSource = epsilon_h * gradPhiMag - tmpPhi * (1.0 - tmpPhi);

					phiNew[id] = std::clamp(tmpPhi + m_dt * phiSource, 0.0, 1.0);
					
					const double dRhodx = (problem.m_U.rho[id + 1] - problem.m_U.rho[id - 1]) / (2 * problem.m_gridResolution);
					const double dRhody = (problem.m_U.rho[id + problem.m_strideY] - problem.m_U.rho[id - problem.m_strideY]) / (2 * problem.m_gridResolution);
					const double dRhodz = (problem.m_U.rho[id + problem.m_strideZ] - problem.m_U.rho[id - problem.m_strideZ]) / (2 * problem.m_gridResolution);

					const double normalGradRho = normx*dRhodx + normy*dRhody + normz*dRhodz;
					
					const double dqdx = (q[id + 1] - q[id - 1]) / (2 * problem.m_gridResolution);
					const double dqdy = (q[id + problem.m_strideY] - q[id - problem.m_strideY]) / (2 * problem.m_gridResolution);
					const double dqdz = (q[id + problem.m_strideZ] - q[id - problem.m_strideZ]) / (2 * problem.m_gridResolution);

					const double normalGradQ = normx*dqdx + normy*dqdy + normz*dqdz;

					const double H = std::tanh(std::pow(tmpPhi * (1.0 - tmpPhi) / 1.0e-2, 2.0));

					const double rhoSource = H * (normalGradQ - (1.0 - 2.0 * tmpPhi) * normalGradRho);

					rhoNew[id] = problem.m_U.rho[id] + m_dt * rhoSource;

					maxChange = std::max(maxChange, std::abs(phiNew[id] - problem.m_phi[id]));

					maxChange = std::max(maxChange, std::abs(rhoNew[id] - problem.m_U.rho[id]));
				}
			}
		}

		problem.m_phi.swap(phiNew);
		problem.m_U.rho.swap(rhoNew);

		if (maxChange < m_interfaceTolerance) {
			break;
		}
	}

	return;
}

void Physics::SetTime(float t) {

	// calculate u,v,w = x,y,zMomentum / rho
	// calculate p = (E - 0.5*(xMomentum*xMomentum + yMomentum*yMomentum + zMomentum*zMomentum) / rho - beta) / alpha
	
	// Interface Sharpening call to update phi and rho
	
	m_time = t;
}

void Physics::SetTimeStep(float dt) {
	m_dt = dt;
}

void Physics::SetInterfaceTolerance(float tol) {
	m_interfaceTolerance = tol;
}

void Physics::SetEpsilon(float epsilon) {
	m_epsilon = epsilon;
}

double Physics::GetTime() {
	return m_time;
}

double Physics::GetDeltaTime() {
	return m_dt;
}

double Physics::GetInterfaceTolerance() {
	return m_interfaceTolerance;
}

double Physics::GetEpsilon() {
	return m_epsilon;
}
