/*
 * PlotData.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: deadbeef
 */

#include "PlotData.h"

PlotData::PlotData(const ulong len,
				   const int style,
				   const int width,
				   const Fl_Color col) {
	this->style = style;
	this->width = width;
	this->col = col;
	this->len = len;
	this->x = std::shared_ptr<double[]>(new double[len]);
	this->y = std::shared_ptr<double[]>(new double[len]);
}

PlotData::PlotData(const std::vector<double> &x,
				   const std::vector<double> &y,
				   const int 				 style,
				   const int 				 width,
				   const Fl_Color 			 col)
	: style(style)
	, width(width)
	, col(col)
	, len(x.size())
{
	this->x = std::shared_ptr<double[]>(new double[len]);
	this->y = std::shared_ptr<double[]>(new double[len]);

	if(len >= 1) {
		xmin = x[0];
		xmax = xmin;
		ymin = y[0];
		ymax = ymin;
		this->x[0] = x[0];
		this->y[0] = y[0];

		for (ulong i = 1 ; i < len; ++i) {
			this->x[i] = x[i];
			this->y[i] = y[i];
			xmin = xmin > x[i] ? x[i] : xmin;
			xmax = xmax < x[i] ? x[i] : xmax;
			ymin = ymin > y[i] ? y[i] : ymin;
			ymax = ymax < y[i] ? y[i] : ymax;
		}
	}
}

void PlotData::getXlim(double & xmin, double & xmax)
{
	xmin = this->xmin;
	xmax = this->xmax;
}
void PlotData::getYlim(double & ymin, double & ymax)
{
	ymin = this->ymin;
	ymax = this->ymax;
}
void PlotData::setVal(ulong idx, double nx, double ny)
{
	if(idx >= 0 && idx < len)
	{
		x[idx] = nx;
		y[idx] = ny;
	}
}
void PlotData::getVal(ulong idx, double & nx, double & ny)
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

