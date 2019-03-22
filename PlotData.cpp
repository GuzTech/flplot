/*
 * PlotData.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: deadbeef
 */

#include "PlotData.h"

PlotData::PlotData(const ulong    len,
				   const int      style,
				   const int      width,
				   const Fl_Color col)
	: style(style)
	, width(width)
	, col(col)
	, xmin(0)
	, ymin(0)
	, xmax(0)
	, ymax(0)
	, len(len)
{
	x.reserve(len);
	y.reserve(len);
}

PlotData::PlotData(const std::vector<double> &_x,
				   const std::vector<double> &_y,
				   const int 				 style,
				   const int 				 width,
				   const Fl_Color 			 col)
	: style(style)
	, width(width)
	, col(col)
	, len(_x.size())
{
	if(len >= 1) {
		xmin = _x[0];
		xmax = xmin;
		ymin = _y[0];
		ymax = ymin;

		x = _x;
		y = _y;

		for (ulong i = 1 ; i < len; ++i) {
			xmin = xmin > x[i] ? x[i] : xmin;
			xmax = xmax < x[i] ? x[i] : xmax;
			ymin = ymin > y[i] ? y[i] : ymin;
			ymax = ymax < y[i] ? y[i] : ymax;
		}
	}
}

void PlotData::getXlim(double &xmin, double &xmax)
{
	xmin = this->xmin;
	xmax = this->xmax;
}
void PlotData::getYlim(double &ymin, double &ymax)
{
	ymin = this->ymin;
	ymax = this->ymax;
}
void PlotData::setVal(const ulong idx, const double nx, const double ny)
{
	if(idx >= 0 && idx < len)
	{
		x[idx] = nx;
		y[idx] = ny;
	}
}
void PlotData::getVal(const ulong idx, double &nx, double &ny)
{
	if(idx >= 0 && idx < len)
	{
		nx = x[idx];
		ny = y[idx];
	}
}
PlotData::~PlotData() {
	// TODO Auto-generated destructor stub
}

