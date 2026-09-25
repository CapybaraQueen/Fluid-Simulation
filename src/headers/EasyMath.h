#ifndef EASYMATH_H
#define EASYMATH_H

#include<vector>

namespace EasyMath {
	double VecMult(const std::vector<double>& a, const std::vector<double>& b);
	std::vector<double> IndexVecMult(const std::vector<double>& a, const std::vector<double>& b);
	std::vector<double> ScalarMult(const double& a, const std::vector<double>& b);
	double VecMag2(const std::vector<double>& a);
	std::vector<double> VecSubtract(const std::vector<double>& a, const std::vector<double>& b);
	std::vector<double> VecScalarSubtract(const std::vector<double>& a, const double& b);
	std::vector<double> ScalarVecSubtract(const double& a, const std::vector<double>& b);
	std::vector<double> VecAdd(const std::vector<double>& a, const std::vector<double>& b);
	std::vector<double> ScalarAdd(const double& a, const std::vector<double>& b);
	std::vector<double> VecDivide(const std::vector<double>& a, const std::vector<double>& b);
	std::vector<double> VecScalarDivide(const std::vector<double>& a, const double& b);
	std::vector<double> ScalarVecDivide(const double& a, const std::vector<double>& b);
}

#endif
