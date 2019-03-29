/*
 * Plot2DData.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: oguz286
 */

#include "PlotData.h"
#include "Plot2DData.h"

Plot2DData::Plot2DData(const size_t   len,
				   	   const int      style,
					   const int      width,
					   const Fl_Color col)
	: PlotData(len, style, width, col)
{
}

Plot2DData::Plot2DData(const std::vector<double> &_x,
					   const std::vector<double> &_y,
					   const int 				 style,
					   const int 				 width,
					   const Fl_Color 			 col)
	: PlotData(_x, _y, style, width, col)
{
}

void Plot2DData::getXlim(double &xmin, double &xmax)
{
	xmin = this->xmin;
	xmax = this->xmax;
}
void Plot2DData::getYlim(double &ymin, double &ymax)
{
	ymin = this->ymin;
	ymax = this->ymax;
}
void Plot2DData::setVal(const size_t idx, const double nx, const double ny)
{
	if(idx >= 0 && idx < len)
	{
		x[idx] = nx;
		y[idx] = ny;

		xmin = xmin > nx ? nx : xmin;
		xmax = xmax < nx ? nx : xmax;
		ymin = ymin > ny ? ny : ymin;
		ymax = ymax < ny ? ny : ymax;
	}
}
void Plot2DData::getVal(const size_t idx, double &nx, double &ny)
{
	if(idx >= 0 && idx < len)
	{
		nx = x[idx];
		ny = y[idx];
	}
}
Plot2DData::~Plot2DData() {
	// TODO Auto-generated destructor stub
}
