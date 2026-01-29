#include "calculation.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
#include <string>
#include <cstdio>
#include <time.h>
#include <iomanip>
//#include <stdio.h>

using namespace std;

double calculation:: computation(double g_d)
{
	double avg = 0;


	initialize(g_d);

	for (int i = 0; i < Tsteps - 1; i++)
	{
		Density(i);

		velocity(i);

		for (int j = 1; j < x_steps; j++)
		 {
			pmtr.flux[i][j] = pmtr.rho[i][j] * pmtr.v[i][j];

			///cout << "flux = " << pmtr.rho[i][j] * pmtr.v[i][j] << "," << "global density=" << g_d << endl;
		}

	}
	double at = 0;

	for (int i = Tsteps - 201; i < Tsteps - 1; i++)
	 {
		double ax = 0;

		for (int j = 0; j < x_steps; j++)
		{
			ax += pmtr.flux[i][j];

		}
		A_X = ax / x_steps;

		at += A_X;

	}
	A_T = at / 200;

	return A_T;

	//cout << "flux = " << A_T << "," << "global density=" << g_d << endl;

}

void calculation::Density(int i)
{
	for (int j = 0; j < x_steps; j++)
	{
		if (j == x_steps - 1)
		{
			pmtr.rho[i + 1][0] = pmtr.rho[i][0] + ((t_x * pmtr.rho[i][0]) * (pmtr.v[i][0] - pmtr.v[i][x_steps-2])) + (t_xx * pmtr.v[i][0]) * (pmtr.rho[i][0] - pmtr.rho[i][x_steps-2]);
			pmtr.c[i + 1][0] = lamda / pmtr.rho[i + 1][0];
		}
		/*
		else if (j==0) {
			pmtr.rho[i + 1][j] = pmtr.rho[i][j] + (t_x * pmtr.rho[i][j]) * (pmtr.v[i][j] - pmtr.v[i][j + 1]) + (t_xx * pmtr.v[i][j]) * (pmtr.rho[i][j] - pmtr.rho[i][j+1]);
			pmtr.c[i + 1][j] = lamda / pmtr.rho[i + 1][j];
		}*/
		else
		{
			pmtr.rho[i + 1][j] = pmtr.rho[i][j] + (t_x * pmtr.rho[i][j]) * (pmtr.v[i][j] - pmtr.v[i][j + 1]) + (t_xx * pmtr.v[i][j]) * (pmtr.rho[i][j] - pmtr.rho[i][j + 1]);
			pmtr.c[i + 1][j] = lamda / pmtr.rho[i + 1][j];
		}
		//cout << pmtr.rho[i][j] << endl;
	}
}

double calculation::E_v(double rho)
 {
	double l_d = v_max * ((1.0 / (1.0 + exp(((rho / rho_max) - 0.25) / 0.6))) - (3.72e-6));
	return l_d;
}

void calculation::velocity(int i)
{
	for (int j = 0; j < x_steps; j++)
	 {
		if (pmtr.v[i][j]< pmtr.c[i][j])
		{
			if (j == x_steps - 1)
			{
				pmtr.v[i + 1][0] = pmtr.v[i][0] - (t_x * (pmtr.v[i][0] - pmtr.c[i][0]) * (pmtr.v[i][1] - pmtr.v[i][0])) + (a * del_t * E_v(pmtr.rho[i][0])) - (a * del_t * pmtr.v[i][0]) + (((t_xx * pmtr.c[i][0]) / (2 * pmtr.rho[i][0])) * (pmtr.v[i][1] - 2 * pmtr.v[i][0] + pmtr.v[i][x_steps-2]));
			}
			else if (j == 0)
			{
				pmtr.v[i + 1][j] = pmtr.v[i][j] - (t_x * (pmtr.v[i][j] - pmtr.c[i][j]) * (pmtr.v[i][j + 1] - pmtr.v[i][j])) + (a * del_t * E_v(pmtr.rho[i][j])) - (a * del_t * pmtr.v[i][j]) + (((t_xx * pmtr.c[i][j]) / (2 * pmtr.rho[i][j])) * (pmtr.v[i][j + 1] - 2 * pmtr.v[i][j] + pmtr.v[i][x_steps - 2]));
			}
			else pmtr.v[i + 1][j] = pmtr.v[i][j] - (t_x * (pmtr.v[i][j] - pmtr.c[i][j]) * (pmtr.v[i][j + 1] - pmtr.v[i][j])) + (a * del_t * E_v(pmtr.rho[i][j])) - (a * del_t * pmtr.v[i][j]) + (((t_xx * pmtr.c[i][j]) / (2 * pmtr.rho[i][j])) * (pmtr.v[i][j + 1] - 2 * pmtr.v[i][j] + pmtr.v[i][j - 1]));

		}
		else if(pmtr.v[i][j] >= pmtr.c[i][j])
		{
			if (j == x_steps - 1)
			{
				pmtr.v[i + 1][0] = pmtr.v[i][0] - (t_x * (pmtr.v[i][0] - pmtr.c[i][0]) * (pmtr.v[i][0] - pmtr.v[i][x_steps-2])) + (a * del_t * E_v(pmtr.rho[i][0])) - (a * del_t * pmtr.v[i][0]) + (((t_xx * pmtr.c[i][0]) / (2 * pmtr.rho[i][0])) * (pmtr.v[i][1] - 2 * pmtr.v[i][0] + pmtr.v[i][x_steps-2]));
			}
			else if (j == 0)
			{
				pmtr.v[i + 1][j] = pmtr.v[i][j] - (t_x * (pmtr.v[i][j] - pmtr.c[i][j]) * (pmtr.v[i][j] - pmtr.v[i][x_steps-2])) + (a * del_t * E_v(pmtr.rho[i][j])) - (a * del_t * pmtr.v[i][j]) + (((t_xx * pmtr.c[i][j]) / (2 * pmtr.rho[i][j])) * (pmtr.v[i][j + 1] - 2 * pmtr.v[i][j] + pmtr.v[i][x_steps - 2]));
			}
			else pmtr.v[i + 1][j] = pmtr.v[i][j] - (t_x * (pmtr.v[i][j] - pmtr.c[i][j]) * (pmtr.v[i][j] - pmtr.v[i][j-1])) + (a * del_t * E_v(pmtr.rho[i][j])) - (a * del_t * pmtr.v[i][j]) + (((t_xx * pmtr.c[i][j]) / (2 * pmtr.rho[i][j])) * (pmtr.v[i][j + 1] - 2 * pmtr.v[i][j] + pmtr.v[i][j - 1]));
			//cout << pmtr.v[i][j] << endl;

		}

		//cout << pmtr.v[i][j] << endl;

	}
}






