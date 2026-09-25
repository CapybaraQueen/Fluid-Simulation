#include "Simulation.h"
#include "TypeU.h"
#include "InitialConditions.h"

// sets the initial volume/grid variables and reserves the conversative variable vectors to the total volume/grid size
Simulation::Simulation(int nx, int ny, int nz, double gridResolution) {
	SetSize(nx, ny, nz, gridResolution);

	// reserves enough space for nx*ny*nz entries to avoid needing to extend the vectors multiple times
	m_U.rho.reserve(m_NTot);
	m_U.xMomentum.reserve(m_NTot);
	m_U.yMomentum.reserve(m_NTot);
	m_U.zMomentum.reserve(m_NTot);
	m_U.E.reserve(m_NTot);
	m_U.alpha.reserve(m_NTot);
	m_U.beta.reserve(m_NTot);
}

// sets the initial conditions of the conservative variable vectors, passed in as the full struct object
void Simulation::Initialize(const InitialConditions& ic) {
	m_U.rho = ic.rho;
	m_U.xMomentum = ic.xMomentum;
	m_U.yMomentum = ic.yMomentum;
	m_U.zMomentum = ic.zMomentum;
	m_U.E = ic.E;
	m_phi = ic.phi;
}

// used for indexing the 1D vector with a 3D structure. Stride is the index jump needed to reach the next Y or Z location
size_t Simulation::Index(int i, int j, int k) const noexcept {
	return static_cast<size_t>(i) + m_strideY*static_cast<size_t>(j) + m_strideZ*static_cast<size_t>(k);
}

void Simulation::SetSize(int nx, int ny, int nz, double gridResolution) {
	m_nx = nx;
	m_ny = ny;
	m_nz = nz;
	m_gridResolution = gridResolution;

	m_nxTot = nx+2;
	m_nyTot = ny+2;
	m_nzTot = nz+2;

	m_N = static_cast<size_t>(nx*ny*nz);

	m_NTot = m_N+2;

	m_strideY = static_cast<size_t>(m_nxTot);
	m_strideZ = static_cast<size_t>(m_nxTot*m_nyTot);
}

void Simulation::AddFluid(const double &gamma, const double &piInf) {
	m_fluidList.push_back(Fluid(gamma,piInf));
}

TypeU Simulation::GetU() const noexcept {
	return m_U;
}

size_t Simulation::GetSize() const noexcept {
	return m_N;
}

size_t Simulation::GetSizeTot() const noexcept {
	return m_NTot;
}

int Simulation::GetNx() const noexcept {
	return m_nx;
}

int Simulation::GetNxTot() const noexcept {
	return m_nxTot;
}

int Simulation::GetNy() const noexcept {
	return m_ny;
}

int Simulation::GetNyTot() const noexcept {
	return m_ny;
}

int Simulation::GetNz() const noexcept {
	return m_nz;
}

int Simulation::GetNzTot() const noexcept {
	return m_nzTot;
}

double Simulation::GetGridResolution() const noexcept {
	return m_gridResolution;
}

const Fluid& Simulation::GetFluid(size_t index) const noexcept {
	return m_fluidList[index];
}

const std::vector<Fluid>& Simulation::GetFluidList() const noexcept {
	return m_fluidList;
}
