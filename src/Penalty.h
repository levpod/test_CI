#pragma once

#include <string>
#include <functional>
#include <vector>


	class Penalty
	{
	public:
		Penalty();
		~Penalty(){};

		void SetPenaltyMethod(std::string method_to_set);

		void ComputePenalty(const double& E_min, const std::vector<double>& lenghts, const std::vector<double>& radii, const double& multiplier, std::vector<double>& penalty_values);
		double ComputePenaltyAtNode(const double& E_min, const double& l = 0.0, const double& radius = 1.0);

	private:
		double ComputePenalty_E_MIN_L_AVG(const double& E_min, const double& l_avg); // , const double& radius);
		double ComputePenalty_E_MIN_L_AVG_STRONG(const double& E_min, const double& l_avg);
		double ComputePenalty_E_MIN(const double& E_min);
		double ComputePenalty_E_MIN_L_LOCAL(const double& E_min, const double& l_local);
		double ComputePenalty_E_MIN_R_LOCAL(const double& E_min, const double& radius);
		double ComputePenalty_E_MIN_L_R_LOCAL(const double& E_min, const double& l_local, const double& radius);

		double factor;
		std::string method;

		std::function<double(double, double, double)>  penalty_calculator;
	};


