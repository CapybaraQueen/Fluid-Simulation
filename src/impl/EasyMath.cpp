#include "EasyMath.h"
#include<numeric>








double EasyMath::VecMult(const std::vector<double>& a, const std::vector<double>& b) {
	return std::inner_product(a.begin(),a.end(),b.begin(),0.0);
}

std::vector<double> EasyMath::IndexVecMult(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp[i] = a[i] * b[i];
	}
	return tmp;
}

std::vector<double> EasyMath::ScalarMult(const double& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < b.size(); i++) {
		tmp[i] = a * b[i];
	}
	return tmp;
}

double EasyMath::VecMag2(const std::vector<double>& a) {
	return std::inner_product(a.begin(),a.end(),a.begin(),0.0);
}

std::vector<double> EasyMath::VecSubtract(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp[i] = a[i] - b[i];
	}
	return tmp;
}

std::vector<double> VecScalarSubtract(const std::vector<double>& a, const double& b) {
	std::vector<double> tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp[i] = a[i] - b;
	}
	return tmp;
}

std::vector<double> ScalarVecSubtract(const double& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < b.size(); i++) {
		tmp[i] = a - b[i];
	}
	return tmp;
}

std::vector<double> EasyMath::VecAdd(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp[i] = a[i] + b[i];
	}
	return tmp;
}

std::vector<double> ScalarAdd(const double& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < b.size(); i++) {
		tmp[i] = a + b[i];
	}
	return tmp;
}

std::vector<double> EasyMath::VecDivide(const std::vector<double>& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp[i] = a[i] / b[i];
	}
	return tmp;
}

std::vector<double> VecScalarDivide(const std::vector<double>& a, const double& b) {
	std::vector<double> tmp;
	for (int i = 0; i < a.size(); i++) {
		tmp[i] = a[i] / b;
	}
	return tmp;
}

std::vector<double> ScalarVecDivide(const double& a, const std::vector<double>& b) {
	std::vector<double> tmp;
	for (int i = 0; i < b.size(); i++) {
		tmp[i] = a / b[i];
	}
	return tmp;
}
