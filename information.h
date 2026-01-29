#pragma once
#include"constant.h"
#include <vector>

class information :public constant {
public:
	double iters = Time / del_t;   // total time steps
	int Tsteps = (int)iters;
	//double tt = 1000.0 * road_length;
	//double L = tt / del_x;
	int x_steps = L/del_x;
	void varidef();
	struct parameter{
		std::vector<std::vector<double>>v;
		std::vector<std::vector<double>>f_v;
		std::vector<std::vector<double>>rho;
		std::vector<std::vector<double>>f_rho;
		std::vector<std::vector<double>>c;
		std::vector<std::vector<double>>flux;
	
	};
	parameter pmtr;
};

