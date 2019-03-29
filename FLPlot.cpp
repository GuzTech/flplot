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

void linspace(vector<double> &arr, const double l, const double r, const size_t len) {
	const double dx = (r - l) / (len - 1);

	// Reserve enough space so that we do not have to reallocate more memory.
	arr.reserve(len);

	for (size_t i = 0; i < len; ++i) {
		arr[i] = l + (i * dx);
	}
}

void meshgrid(vector<vector<double>> &X,
			  vector<vector<double>> &Y,
			  const double xleft,
			  const double xright,
			  const double xstep,
			  const double ydown,
			  const double yup,
			  const double ystep)
{
	const double dx = (xright - xleft) / xstep;
	const double dy = (yup - ydown) / ystep;
	const size_t dxi = abs(dx) + 1;
	const size_t dyi = abs(dy) + 1;

	X.reserve(dyi);
	Y.reserve(dyi);
	X.resize(dyi);
	Y.resize(dyi);

	for (size_t y = 0; y < dyi; ++y) {
		for (size_t x = 0; x < dxi; ++x) {
			X[y].reserve(dxi);
			Y[y].reserve(dxi);
			X[y].resize(dxi);
			Y[y].resize(dxi);

			X[y][x] = xleft + (((double)x) * xstep);
			Y[y][x] = ydown + (((double)y) * ystep);
		}
	}
}

void arrayfun(const vector<double> &in,
			  vector<double> &out,
			  double (*fun)(double))
{
	// Reserve enough space so that we do not have to reallocate
	// more memory while calling push_back over and over again.
	out.reserve(in.size());

	for (size_t i = 0; i < in.size(); ++i)
		out[i] = fun(in[i]);
}

void arrayfun2d(const vector<vector<double>> &in_x,
				const vector<vector<double>> &in_y,
				vector<vector<double>> &out,
				double (*fun)(double, double))
{
	out.reserve(in_x.size());
	out.resize(in_x.size());

	for (size_t i = 0; i < in_x.size(); ++i) {
		out[i].reserve(in_x[i].size());
		out[i].resize(in_x[i].size());

		for (size_t j = 0; j < in_x[i].size(); ++j) {
			out[i][j] = fun(in_x[i][j], in_y[i][j]);
		}
	}
}

void gradient(const vector<vector<double>> &in,
			  vector<vector<double>> &px,
			  vector<vector<double>> &py,
			  const double hx,
			  const double hy)
{
	px.reserve(in.size());
	py.reserve(in.size());
	px.resize(in.size());
	py.resize(in.size());

	// Reserve space
	for (size_t y = 0; y < in.size(); ++y) {
		for (size_t x = 0; x < in[y].size(); ++x) {
			px[y].reserve(in[y].size());
			py[y].reserve(in[y].size());
			px[y].resize(in[y].size());
			py[y].resize(in[y].size());
		}
	}

	// Calculate interior gradients using central difference.
	for (size_t y = 1; y < in.size() - 1; ++y) {
		for (size_t x = 1; x < in[y].size() - 1; ++x) {
			px[y][x] = 0.5 * ((in[y][x + 1] - in[y][x - 1])) / hx;
			py[y][x] = 0.5 * ((in[y + 1][x] - in[y - 1][x])) / hy;
		}
	}

	// Calculate gradients of the edges using single-sided differences.
	for (size_t y = 0; y < in.size(); ++y) {
		const size_t size = in[y].size() - 1;
		px[y][0] = (in[y][1] - in[y][0]) / hx;
		px[y][size] = (in[y][size] - in[y][size - 1]) / hx;
	}
	for (size_t x = 0; x < in[0].size(); ++x) {
		const size_t size = in.size() - 1;
		py[0][x] = (in[1][x] - in[0][x]) / hy;
		py[size][x] = (in[size][x] - in[size - 1][x]) / hy;
	}
}

int main() {
	const size_t N = 1000;
	vector<double> t(N),
				   x(N),
				   y(N);

	linspace(t, 0, 2 * M_PI, N);
	arrayfun(t, x, sin);
	arrayfun(t, y, [](const double x){ return 0.5 - 0.5 * exp(-x); });

	FigureWindow fig(640, 480, "Figure 1", 1, 2);
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
	fig2.stem(t, x, 0);

	vector<vector<double>> X, Y, Z, PX, PY;

	meshgrid(X, Y, -2.0, 2.0, .2, -1.0, 1.0, 0.15);
	arrayfun2d(X, Y, Z, [](const double x, const double y){ return x * exp(-(x * x) - (y * y)); });
	gradient(Z, PX, PY, .2, .2);

	FigureWindow fig3(640, 480, "Figure 3");
	fig3.quiver(X, Y, PX, PY);

	fig.show();
	fig2.show();
	fig3.show();

	return Fl::run();
}
