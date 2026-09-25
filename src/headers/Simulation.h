#ifndef SIMULATION_H
#define SIMULATION_H

#include<vector>
#include<memory>

#include "TypeU.h"
#include "InitialConditions.h"
#include "Fluid.h"

class Simulation {
	private:
		// size and indexing information
		int m_nx,m_ny,m_nz;
		int m_nxTot,m_nyTot,m_nzTot;
		double m_gridResolution;

		size_t m_strideY;
		size_t m_strideZ;
		size_t m_N;
		size_t m_NTot;


		// conservative variables structure containing the U vector (of vectors)
		TypeU m_U;

		// pressure vector for ease of use
		std::vector<double> m_pressure;

		// volume fraction vector
		std::vector<double> m_phi;


		// Vector of pointer to all fluid objects (this is basically just how to access the fluids because they are not named in the conventional sense
		std::vector<Fluid> m_fluidList;


		friend class Physics;

	public:
		Simulation(int nx, int ny, int nz, double gridResolution);

		void Initialize(const InitialConditions& ic);

		size_t Index(int i, int j, int k) const noexcept;

		void SetSize(int nx, int ny, int nz, double gridResolution);

		void AddFluid(const double& gamma, const double& piInf);

		TypeU GetU() const noexcept;

		size_t GetSize() const noexcept;
		size_t GetSizeTot() const noexcept;

		int GetNx() const noexcept;
		int GetNy() const noexcept;
		int GetNz() const noexcept;
		int GetNxTot() const noexcept;
		int GetNyTot() const noexcept;
		int GetNzTot() const noexcept;

		double GetGridResolution() const noexcept;

		const Fluid& GetFluid(size_t index) const noexcept;
		const std::vector<Fluid>& GetFluidList() const noexcept;
};

#endif
