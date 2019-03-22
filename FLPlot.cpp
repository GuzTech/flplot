//============================================================================
// Name        : FLPlot.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <FL/Fl.H>
#include "FigureWindow.h"
#include <cmath>
#include <string>

using namespace std;

void linspace(double * arr, double l, double r, ulong len)
{
	double dx = (r-l)/(len-1);
	for(ulong i = 0;i < len;i++) {
		arr[i] = l + i*dx;
	}
}

void arrayfun(double * in, double * out, double (*fun)(double), ulong len)
{
	for(ulong i = 0;i < len;i++) {
		out[i] = fun(in[i]);
	}
}

int main() {
	ulong N = 1000;
	double t[N],
	       x[N],
		   y[N];

	linspace(t,0,2*M_PI,N);
	arrayfun(t,x,sin,N);
	arrayfun(t,y,[](double x){return 0.5 - 0.5*exp(-x);},N);

	FigureWindow fig(640,480,"Figure 1",1,2);
	fig.plot(N,t,x,FL_SOLID,2,FL_RED,0);
	fig.hold(true);
	fig.plot(N,t,y,FL_DASH,2,FL_BLUE,0);
	fig.hold(false);
	fig.plot(N,x,y,FL_SOLID,2,FL_RED,1);

	fig.xlabel("Time [s]");
	fig.ylabel("Voltage [V]");
	fig.caption("Voltages vs. time");
	fig.grid(true,0);

	fig.xlabel("Voltage [V]",1);
	fig.ylabel("Voltage [V]",1);
	fig.caption("Signal 1 vs. signal 2",1);
	fig.grid(true,1);


	FigureWindow fig2(640,480,"Figure 2");
	fig2.plot(N,t,x,0);

	fig.show();
	fig2.show();

	return Fl::run();
}
