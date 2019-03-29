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
	PlotData(const size_t len, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	PlotData(const std::vector<double> &x, const std::vector<double> &y, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	~PlotData();

	void getXlim(double &xmin, double &xmax);
	void getYlim(double &ymin, double &ymax);
	void setVal(const size_t idx, const double nx, const double ny);
	void getVal(const size_t idx, double &nx, double &ny);

	const size_t size() { return this->len; }

public:
	int style;
	int width;
	Fl_Color col;

protected:
	std::vector<double> x, y;
	double xmin, ymin;
	double xmax, ymax;
	size_t len;
};

typedef std::shared_ptr<PlotData> pdptr;

#endif /* PLOTDATA_H_ */
