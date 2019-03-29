/*
 * PlotWidget2D.h
 *
 *  Created on: Mar 28, 2019
 *      Author: oguz286
 */

#ifndef PLOT2DWIDGET_H_
#define PLOT2DWIDGET_H_

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include "Graph2DWidget.h"
#include <vector>
#include <memory>
#include "PlotData.h"
#include <string>

class Plot2DWidget : public Graph2DWidget
{
public:
	Plot2DWidget(const int x, const int y, const int w, const int h, const std::string cap);
	virtual ~Plot2DWidget();
protected:
	void draw();
};

#endif /* PLOT2DWIDGET_H_ */
