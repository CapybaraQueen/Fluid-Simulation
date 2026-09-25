#ifndef FLUID_H
#define FLUID_H

class Fluid {
	private:
		double m_gamma;
		double m_piInf;

		friend class Physics;
		friend class Simulation;

		Fluid(double gamma, double piInf);

		void SetGamma(double gamma);

		void SetPiInf(double piInf);

	public:

		double GetGamma() const noexcept;

		double GetPiInf() const noexcept;
};
#endif
