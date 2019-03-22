/*
 * PlotData.h
 *
 *  Created on: Mar 18, 2019
 *      Author: deadbeef
 */

#ifndef PLOTDATA_H_
#define PLOTDATA_H_

#include <memory>
#include <cinttypes>
#include <FL/fl_draw.H>
#include <vector>

class PlotData
{
public:
	PlotData(const ulong len, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	PlotData(const std::vector<double> &x, const std::vector<double> &y, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	~PlotData();

	void getXlim(double &xmin, double &xmax);
	void getYlim(double &ymin, double &ymax);
	void setVal(const ulong idx, const double nx, const double ny);
	void getVal(const ulong idx, double &nx, double &ny);

	const ulong size() { return this->len; }

public:
	int style;
	int width;
	Fl_Color col;

private:
	std::vector<double> x, y;
	double xmin, ymin;
	double xmax, ymax;
	ulong len;
};

#endif /* PLOTDATA_H_ */
