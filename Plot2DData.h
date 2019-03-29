/*
 * Plot2DData.h
 *
 *  Created on: Mar 29, 2019
 *      Author: oguz286
 */

#ifndef PLOT2DDATA_H_
#define PLOT2DDATA_H_

#include <memory>
#include <cinttypes>
#include <FL/fl_draw.H>
#include <vector>
#include "PlotData.h"

class Plot2DData : public PlotData
{
public:
	Plot2DData(const size_t len, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	Plot2DData(const std::vector<double> &x, const std::vector<double> &y, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	~Plot2DData();

	void getXlim(double &xmin, double &xmax);
	void getYlim(double &ymin, double &ymax);
	void setVal(const size_t idx, const double nx, const double ny);
	void getVal(const size_t idx, double &nx, double &ny);

	const size_t size() { return this->len; }

public:
	int style;
	int width;
	Fl_Color col;

private:
	std::array<std::vector<double>, 2> data;
//	std::vector<double> x, y;
//	double xmin, ymin;
//	double xmax, ymax;
//	size_t len;
};

#endif /* PLOT2DDATA_H_ */
