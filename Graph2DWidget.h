/*
 * Graph2DWidget.h
 *
 *  Created on: Mar 29, 2019
 *      Author: oguz286
 */

#ifndef GRAPH2DWIDGET_H_
#define GRAPH2DWIDGET_H_

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include "GraphWidget.h"
#include <vector>
#include <memory>
#include "Plot2DData.h"
#include <string>

class Graph2DWidget : public GraphWidget
{
protected:
	std::vector<pdptr> data;
public:
	Graph2DWidget(const int x, const int y, const int w, const int h, const std::string cap);
	virtual ~Graph2DWidget();
	virtual int handle(const int event);
	void putData(const std::vector<double> &x,
				 const std::vector<double> &y,
				 const int                 style = FL_SOLID,
				 const int                 width = 1,
				 const Fl_Color            col   = FL_BLACK);
};

#endif /* GRAPH2DWIDGET_H_ */
