#include<algorithm>
#include<cmath>
#include<numeric>

#include "Physics.h"
#include "Fluid.h"
#include "Simulation.h"
#include "EasyMath.h"


// sets the initial time and time step
Physics::Physics(float dt, float interfaceTol, float epsilon) {
	SetTime(0.00);
	SetTimeStep(dt);
	SetInterfaceTolerance(interfaceTol);
	SetEpsilon(epsilon);
}

void Physics::ApplyBoundary(Simulation &simulation) {
	// to start let's just set all ghost cell values to be equal to their neighbor
	
	for (int i = 1; i < simulation.GetSizeTot() - 1; i++) {
		for (int j = 1; j < simulation.GetSizeTot() - 1; j++) {
			simulation.m_phi[simulation.Index(i,j,0)] = simulation.m_phi[simulation.Index(i,j,1)];
			simulation.m_phi[simulation.Index(i,0,j)] = simulation.m_phi[simulation.Index(i,1,j)];
			simulation.m_phi[simulation.Index(0,i,j)] = simulation.m_phi[simulation.Index(1,i,j)];
		}
	}
	simulation.m_phi[simulation.Index(0,0,0)] = simulation.m_phi[simulation.Index(1,0,0)];
	simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 1,0,0)] = simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 2,0,0)];

	simulation.m_phi[simulation.Index(0,simulation.GetSizeTot() - 1,0)] = simulation.m_phi[simulation.Index(0,simulation.GetSizeTot() - 2,0)];
	simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 1,0)] =
		simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 2,0)];

	simulation.m_phi[simulation.Index(0,0,simulation.GetSizeTot() - 1)] = simulation.m_phi[simulation.Index(0,0,simulation.GetSizeTot() - 2)];
	simulation.m_phi[simulation.Index(0,simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 1)] =
		simulation.m_phi[simulation.Index(0,simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 2)];

	simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 1,0,simulation.GetSizeTot() - 1)] =
		simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 1,0,simulation.GetSizeTot() - 2)];
	simulation.m_phi[simulation.Index(simulation.GetSizeTot() -1,simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 1)] =
		simulation.m_phi[simulation.Index(simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 1,simulation.GetSizeTot() - 2)];
}

void Physics::CalculateEOS(Simulation &simulation) {

	if (simulation.m_fluidList.size() == 1) {
		for (int k = 1; k < simulation.m_nz; ++k) {
			for (int j = 1; j < simulation.m_ny; ++j) {
				
				size_t id = simulation.Index(1,j,k);

				for (int i = 1; i < simulation.m_nx; ++i, ++id) {
					simulation.m_U.alpha[id] = 1 / (1 - simulation.m_fluidList[0].GetGamma());
					simulation.m_U.beta[id] = simulation.m_fluidList[0].GetPiInf() * simulation.m_fluidList[0].GetGamma()
						/ (1 - simulation.m_fluidList[0].GetGamma());
				}
			}
		}
	}
	else if (simulation.m_fluidList.size() == 2) {
		for (int k = 1; k < simulation.m_nz; ++k) {
			for (int j = 1; j < simulation.m_ny; ++j) {
				
				size_t id = simulation.Index(1,j,k);

				for (int i = 1; i < simulation.m_nx; ++i, ++id) {
					simulation.m_U.alpha[id] =
						simulation.m_phi[id] / (1 - simulation.m_fluidList[0].GetGamma())
						+ (1 - simulation.m_phi[id]) / (1 - simulation.m_fluidList[0].GetGamma());
					simulation.m_U.beta[id] =
						(simulation.m_phi[id] * simulation.m_fluidList[0].GetPiInf() * simulation.m_fluidList[0].GetGamma())
						/ (1 - simulation.m_fluidList[0].GetGamma())
						+ simulation.m_fluidList[1].GetPiInf() * simulation.m_fluidList[1].GetGamma() * (1 - simulation.m_phi[id])
						/ (1 - simulation.m_fluidList[2].GetGamma());
				}
			}
		}
	}
	
}

// proceeds to the next time, performing all physics necessary to do so
void Physics::Compute(Simulation& simulation) {
	ApplyBoundary(simulation);
	CalculateEOS(simulation);
	InitializeAlgorithm(simulation);

	std::vector<double> p = EasyMath::VecDivide(EasyMath::VecSubtract(EasyMath::VecSubtract(simulation.m_U.E,simulation.m_U.beta),
				EasyMath::VecDivide(EasyMath::VecAdd(EasyMath::VecAdd(EasyMath::IndexVecMult(simulation.m_U.xMomentum,simulation.m_U.xMomentum),
						EasyMath::IndexVecMult(simulation.m_U.yMomentum,simulation.m_U.yMomentum)),
						EasyMath::IndexVecMult(simulation.m_U.zMomentum,simulation.m_U.zMomentum)),
					EasyMath::ScalarMult(2.0, simulation.m_U.rho))),
				simulation.m_U.alpha);

	std::vector<double> F[7];
	std::vector<double> G[7];
	std::vector<double> H[7];

	F[0] = simulation.m_U.xMomentum;
	F[1] = EasyMath::VecAdd(EasyMath::VecDivide(EasyMath::IndexVecMult(simulation.m_U.xMomentum,simulation.m_U.xMomentum), simulation.m_U.rho),p);
	F[2] = EasyMath::VecDivide(EasyMath::IndexVecMult(simulation.m_U.xMomentum,simulation.m_U.yMomentum),simulation.m_U.rho);
	F[3] = EasyMath::VecDivide(EasyMath::IndexVecMult(simulation.m_U.xMomentum,simulation.m_U.zMomentum),simulation.m_U.rho);
	F[4] = EasyMath::IndexVecMult(EasyMath::VecAdd(simulation.m_U.E,p),EasyMath::VecDivide(simulation.m_U.yMomentum,simulation.m_U.rho));
	F[5] = simulation.m_U.alpha;
	F[6] = simulation.m_U.beta;


	return;
}

void Physics::InitializeAlgorithm(Simulation& simulation) {
	double epsilon_h = m_epsilon * simulation.m_gridResolution;
	float a = 0.5; // this might need to be changed later. Look at alpha values in paper and decide. Or maybe find best value myself.
	std::vector<double> psi(simulation.m_NTot);
	std::vector<double> q(simulation.m_NTot);
	std::vector<double> phiNew(simulation.m_NTot);
	std::vector<double> rhoNew(simulation.m_NTot);
	double tmpPhi;
	double tmp1,tmp2;
	double dPsidx,dPsidy,dPsidz,gradPsiMag;
	double normx,normy,normz;
	double dRhodx,dRhody,dRhodz,normalGradRho;
	double maxChange;
	double dPhidx,dPhidy,dPhidz,gradPhiMag,phiSource;
	double dqdx,dqdy,dqdz,normalGradQ;
	double H;
	double rhoSource;
	
	for (;;) {
		for (int k = 1; k < simulation.m_nz; ++k) {
			for (int j = 1; j < simulation.m_ny; ++j) {
				
				size_t id = simulation.Index(1,j,k);

				for (int i = 1; i < simulation.m_nx; ++i, ++id) {
					
					tmpPhi = std::clamp(simulation.m_phi[id], 0.0, 1.0);

					tmp1 = std::pow(tmpPhi, a);
					tmp2 = std::pow(1.0 - tmpPhi, a);

					psi[id] = tmp1 / (tmp1 + tmp2);
				}
			}
		}

		for (int k = 1; k < simulation.m_nz; ++k) {
			for (int j = 1; j < simulation.m_ny; ++j) {
				
				size_t id = simulation.Index(1,j,k);

				for (int i = 1; i < simulation.m_nx; ++i, ++id) {
					
					dPsidx = (psi[id + 1] - psi[id - 1]) / (2 * simulation.m_gridResolution);
					dPsidy = (psi[id + simulation.m_strideY] - psi[id - simulation.m_strideY]) / (2 * simulation.m_gridResolution);
					dPsidz = (psi[id + simulation.m_strideZ] - psi[id - simulation.m_strideZ]) / (2 * simulation.m_gridResolution);

					gradPsiMag = std::sqrt(dPsidx*dPsidx + dPsidy*dPsidy + dPsidz*dPsidz);

					normx = 0.0;
					normy = 0.0;
					normz = 0.0;

					if (gradPsiMag > epsilon_h) {
						normx = dPsidx / gradPsiMag;
						normy = dPsidy / gradPsiMag;
						normz = dPsidz / gradPsiMag;
					}

					
					dRhodx = (simulation.m_U.rho[id + 1] - simulation.m_U.rho[id - 1]) / (2 * simulation.m_gridResolution);
					dRhody = (simulation.m_U.rho[id + simulation.m_strideY] - simulation.m_U.rho[id - simulation.m_strideY]) / (2 * simulation.m_gridResolution);
					dRhodz = (simulation.m_U.rho[id + simulation.m_strideZ] - simulation.m_U.rho[id - simulation.m_strideZ]) / (2 * simulation.m_gridResolution);

					normalGradRho = normx*dRhodx + normy*dRhody + normz*dRhodz;

					q[id] = epsilon_h * normalGradRho;
				}
			}
		}

		maxChange = 0.0;

		for (int k = 1; k < simulation.m_nz; ++k) {
			for (int j = 1; j < simulation.m_ny; ++j) {
				
				size_t id = simulation.Index(1,j,k);

				for (int i = 1; i < simulation.m_nx; ++i, ++id) {

					tmpPhi = std::clamp(simulation.m_phi[id], 0.0, 1.0);
					
					dPsidx = (psi[id + 1] - psi[id - 1]) / (2 * simulation.m_gridResolution);
					dPsidy = (psi[id + simulation.m_strideY] - psi[id - simulation.m_strideY]) / (2 * simulation.m_gridResolution);
					dPsidz = (psi[id + simulation.m_strideZ] - psi[id - simulation.m_strideZ]) / (2 * simulation.m_gridResolution);

					gradPsiMag = std::sqrt(dPsidx*dPsidx + dPsidy*dPsidy + dPsidz*dPsidz);

					normx = 0.0;
					normy = 0.0;
					normz = 0.0;

					if (gradPsiMag > epsilon_h) {
						normx = dPsidx / gradPsiMag;
						normy = dPsidy / gradPsiMag;
						normz = dPsidz / gradPsiMag;
					}
					
					dPhidx = (simulation.m_phi[id + 1] - simulation.m_phi[id - 1]) / (2 * simulation.m_gridResolution);
					dPhidy = (simulation.m_phi[id + simulation.m_strideY] - simulation.m_phi[id - simulation.m_strideY]) / (2 * simulation.m_gridResolution);
					dPhidz = (simulation.m_phi[id + simulation.m_strideZ] - simulation.m_phi[id - simulation.m_strideZ]) / (2 * simulation.m_gridResolution);

					gradPhiMag = std::sqrt(dPhidx*dPhidx + dPhidy*dPhidy + dPhidz*dPhidz);

					phiSource = epsilon_h * gradPhiMag - tmpPhi * (1.0 - tmpPhi);

					phiNew[id] = std::clamp(tmpPhi + m_dt * phiSource, 0.0, 1.0);
					
					dRhodx = (simulation.m_U.rho[id + 1] - simulation.m_U.rho[id - 1]) / (2 * simulation.m_gridResolution);
					dRhody = (simulation.m_U.rho[id + simulation.m_strideY] - simulation.m_U.rho[id - simulation.m_strideY]) / (2 * simulation.m_gridResolution);
					dRhodz = (simulation.m_U.rho[id + simulation.m_strideZ] - simulation.m_U.rho[id - simulation.m_strideZ]) / (2 * simulation.m_gridResolution);

					normalGradRho = normx*dRhodx + normy*dRhody + normz*dRhodz;
					
					dqdx = (q[id + 1] - q[id - 1]) / (2 * simulation.m_gridResolution);
					dqdy = (q[id + simulation.m_strideY] - q[id - simulation.m_strideY]) / (2 * simulation.m_gridResolution);
					dqdz = (q[id + simulation.m_strideZ] - q[id - simulation.m_strideZ]) / (2 * simulation.m_gridResolution);

					normalGradQ = normx*dqdx + normy*dqdy + normz*dqdz;

					H = std::tanh(std::pow(tmpPhi * (1.0 - tmpPhi) / 1.0e-2, 2.0));

					rhoSource = H * (normalGradQ - (1.0 - 2.0 * tmpPhi) * normalGradRho);

					rhoNew[id] = simulation.m_U.rho[id] + m_dt * rhoSource;

					maxChange = std::max(maxChange, std::abs(phiNew[id] - simulation.m_phi[id]));

					maxChange = std::max(maxChange, std::abs(rhoNew[id] - simulation.m_U.rho[id]));
				}
			}
		}

		simulation.m_phi.swap(phiNew);
		simulation.m_U.rho.swap(rhoNew);

		if (maxChange < m_interfaceTolerance) {
			break;
		}
	}

	return;
}

void Physics::SetTime(float t) {
	
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
