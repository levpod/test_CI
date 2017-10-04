#include "Penalty.h"

#include <vtkDoubleArray.h>


	Penalty::Penalty():
		factor(10.0)
	{
	}


	void Penalty::SetPenaltyMethod(std::string method_to_set)
	{
		method = method_to_set;

		if (method == "STANDARD" || method == "E_MIN_L_AVG")
		{
			penalty_calculator = std::bind(&Penalty::ComputePenalty_E_MIN_L_AVG, this, std::placeholders::_1, std::placeholders::_2);
		}
		else if (method == "STRONG" || method == "E_MIN_L_AVG_STRONG")
		{
			penalty_calculator = std::bind(&Penalty::ComputePenalty_E_MIN_L_AVG_STRONG, this, std::placeholders::_1, std::placeholders::_2);
		}
		else if (method == "E_MIN")
		{
			penalty_calculator = std::bind(&Penalty::ComputePenalty_E_MIN, this, std::placeholders::_1);
		}
		else if (method == "E_MIN_L_LOCAL")
		{
			penalty_calculator = std::bind(&Penalty::ComputePenalty_E_MIN_L_LOCAL, this, std::placeholders::_1, std::placeholders::_2);
		}
		else if (method == "E_MIN_R_LOCAL")
		{
			penalty_calculator = std::bind(&Penalty::ComputePenalty_E_MIN_R_LOCAL, this, std::placeholders::_1, std::placeholders::_3);
		}
		else if (method == "E_MIN_L_R_LOCAL")
		{
			penalty_calculator = std::bind(&Penalty::ComputePenalty_E_MIN_L_R_LOCAL, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		}
	}


	double Penalty::ComputePenalty_E_MIN_L_AVG(const double& E_min, const double& l_avg) 
	{
		return E_min*l_avg;
	}

	double Penalty::ComputePenalty_E_MIN_L_AVG_STRONG(const double& E_min, const double& l_avg)
	{
		return factor*E_min*l_avg;
	}

	double Penalty::ComputePenalty_E_MIN(const double& E_min)
	{
		return E_min;
	}

	double Penalty::ComputePenalty_E_MIN_L_LOCAL(const double& E_min, const double& l_local)
	{
		return E_min*l_local;
	}

	double Penalty::ComputePenalty_E_MIN_R_LOCAL(const double& E_min, const double& radius)
	{
		return E_min*radius;
	}

	double Penalty::ComputePenalty_E_MIN_L_R_LOCAL(const double& E_min, const double& l_local, const double& radius)
	{
		return E_min*l_local*radius;
	}

	double Penalty::ComputePenaltyAtNode(const double& E_min, const double& l, const double& radius)
	{
		return penalty_calculator(E_min, l, radius);
	}

	void Penalty::ComputePenalty(const double& E_min, const std::vector<double>& lenghts, const std::vector<double>& radii, const double& multiplier, std::vector<double>& penalty_values)
	{
		const int nPoints = lenghts.size();

		penalty_values.resize(nPoints);

		for (int node_id = 0; node_id < nPoints; ++node_id)
		{
			penalty_values[node_id] = multiplier * ComputePenaltyAtNode(E_min, lenghts[node_id], radii[node_id]);
		}
	}


