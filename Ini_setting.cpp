#include "Ini_setting.h"
#include <iostream>
#include <fstream>

using namespace std;
void Ini_setting::initialize (double global_density){
	pmtr.rho = std::vector<std::vector<double>>(Tsteps, std::vector<double>(x_steps, 0));
	pmtr.f_rho = std::vector<std::vector<double>>(Tsteps, std::vector<double>(x_steps, 0));
	pmtr.f_v = std::vector<std::vector<double>>(Tsteps, std::vector<double>(x_steps, 0));
	pmtr.c = std::vector<std::vector<double>>(Tsteps, std::vector<double>(x_steps, 0));
	pmtr.v = std::vector<std::vector<double>>(Tsteps, std::vector<double>(x_steps, 0));
	pmtr.flux = std::vector<std::vector<double>>(Tsteps, std::vector<double>(x_steps, 0));
	double del_rho_0 = global_density * del;
	for (int j = 0; j < x_steps; j++) {
		if (j==x_steps-1) {
			pmtr.rho[0][0] = global_density + del_rho_0 * ((1 / (cosh((160 / L) * (j - ((5 * L) / 16))) * cosh((160 / L) * (j - ((5 * L) / 16))))) - 0.20 * (1 / (cosh((40.0 / L) * (j - ((11.0 * L) / 32))) * cosh((40.0 / L) * (j - ((11.0 * L) / 32))))));
			pmtr.c[0][0] = lamda / pmtr.rho[0][0];
			pmtr.v[0][0] = v_max * ((1.0 / (1.0 + exp(((pmtr.rho[0][j] / rho_max) - 0.25) / 0.6))) - (3.72e-6));


		}
		else {
			pmtr.rho[0][j] = global_density + del_rho_0 * ((1 / (cosh((160 / L) * (j - ((5 * L) / 16))) * cosh((160 / L) * (j - ((5 * L) / 16))))) - 0.20 * (1 / (cosh((40.0 / L) * (j - ((11.0 * L) / 32))) * cosh((40.0 / L) * (j - ((11.0 * L) / 32))))));
			pmtr.c[0][j] = lamda / pmtr.rho[0][j];
			pmtr.v[0][j] = v_max * ((1.0 / (1.0 + exp(((pmtr.rho[0][j] / rho_max) - 0.25) / 0.6))) - (3.72e-6));
		}
//cout << pmtr.rho[0][j]<<","<<pmtr.v[0][j] << endl;

	}


}