#pragma once
#include"ini_setting.h"


class calculation:public ini_setting
{
private:

	void Density(int time);
	void velocity(int time);
	double E_v(double rho);

public:

	double computation(double g_d);


};

