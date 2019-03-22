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
private:
	std::shared_ptr<double[]> x, y;
	double xmin=0, ymin=0;
	double xmax=0, ymax=0;
	ulong len=0;

public:
	int style;
	int width;
	Fl_Color col;
	PlotData(const ulong len, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	PlotData(const std::vector<double> &x, const std::vector<double> &y, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	~PlotData();

	void getXlim(double & xmin, double & xmax);
	void getYlim(double & ymin, double & ymax);
	void setVal(ulong idx, double nx, double ny);
	void getVal(ulong idx, double & nx, double & ny);

	ulong size() { return this->len; }
};

#endif /* PLOTDATA_H_ */
