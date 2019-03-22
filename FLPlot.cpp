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

void linspace(vector<double> &arr, const double l, const double r, const ulong len) {
	const double dx = (r - l) / (len - 1);

	// Reserve enough space so that we do not have to reallocate more memory.
	arr.reserve(len);

	for (ulong i = 0; i < len; ++i) {
		arr[i] = l + (i * dx);
	}
}

void arrayfun(const vector<double> &in, vector<double> &out, double (*fun)(double))
{
	// Reserve enough space so that we do not have to reallocate
	// more memory while calling push_back over and over again.
	out.reserve(in.size());

	for (ulong i = 0; i < in.size(); ++i)
		out[i] = fun(in[i]);
}

int main() {
	const ulong N = 1000;
	vector<double> t(N),
				   x(N),
				   y(N);

	linspace(t, 0, 2 * M_PI, N);
	arrayfun(t, x, sin);
	arrayfun(t, y, [](const double x){return 0.5 - 0.5 * exp(-x);});

	FigureWindow fig(640, 480, "Figure 1", 1, 2);
	//fig.plot(N, t.data(), x.data(), FL_SOLID, 2, FL_RED, 0);
	fig.plot(t, x, FL_SOLID, 2, FL_RED, 0);
	fig.hold(true);
	fig.plot(t, y, FL_DASH,  2, FL_BLUE, 0);
	fig.hold(false);
	fig.plot(x, y, FL_SOLID, 2, FL_RED, 1);

	fig.xlabel("Time [s]");
	fig.ylabel("Voltage [V]");
	fig.caption("Voltages vs. time");
	fig.grid(true, 0);

	fig.xlabel("Voltage [V]",1);
	fig.ylabel("Voltage [V]",1);
	fig.caption("Signal 1 vs. signal 2",1);
	fig.grid(true, 1);

	FigureWindow fig2(640, 480, "Figure 2");
	fig2.plot(t, x, 0);

	fig.show();
	fig2.show();

	return Fl::run();
}
