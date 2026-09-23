#include "Fluid.h"

Fluid::Fluid(double gamma, double piInf) {
	m_gamma = gamma;
	m_piInf = piInf;
}

void Fluid::SetGamma(double gamma) {
	m_gamma = gamma;
	return;
}

void Fluid::SetPiInf(double piInf) {
	m_piInf = piInf;
	return;
}

double Fluid::GetGamma() const noexcept {
	return m_gamma;
}

double Fluid::GetPiInf() const noexcept {
	return m_piInf;
}
