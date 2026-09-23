#ifndef PROBLEM_H
#define PROBLEM_H

#include<vector>
#include "TypeU.h"
#include "InitialConditions.h"

class Problem {
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

		// volume fraction
		std::vector<double> m_phi;

		double m_gamma1;
		double m_gamma2;

		double m_piInf1;
		double m_piInf2;

		friend class Physics;

	public:
		Problem(int nx, int ny, int nz, double gridResolution);

		void Initialize(const InitialConditions& ic, const double& gamma1, const double& piInf1, const double& gamma2 = 0, const double& piInf2 = 0);

		size_t Index(int i, int j, int k) const noexcept;

		void SetSize(int nx, int ny, int nz, double gridResolution);

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
};

#endif
