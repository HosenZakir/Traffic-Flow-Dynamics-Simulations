#pragma once
class constant{
public:
	const double  dt = 0.016; // 1.0sec
	const double a = 1;
	const double p = 1.0;
	const double lamda = 0.5;
	const double v_maxf = 30;  //   m/s
	const double v_maxb = 30;//   m/s

	const double v_max = 30;

	const double v_max_L = 30;
	const double v_max_M = 30;
	const double v_max_H = 30;

	const double wL = 0.25;
	const double wM = 0.50;
	const double wH = 0.25;

	const double rho_max = 0.2;  //  veh/m
	//double rho_0 = 0.028;
	double del = 4;
	//double del_rho_0 = del * rho_0;
	double del_x = 100.0;  // meter
	double del_t = 1.0;  // sec

	int L= 32200; //road_length=32.2 km


	double Time = 1000;          // Total running time of the simulation
	
	double t_x = del_t / del_x;
	double t_xx = del_t / (del_x * del_x);
	double x_t = del_x / del_t;
	double A_X = 0;
	double A_T = 0;
};

