/*
 * Stem2DWidget.h
 *
 *  Created on: Mar 29, 2019
 *      Author: oguz286
 */

#ifndef STEM2DWIDGET_H_
#define STEM2DWIDGET_H_

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include "Graph2DWidget.h"
#include <vector>
#include <memory>
#include "PlotData.h"
#include <string>

class Stem2DWidget : public Graph2DWidget
{
public:
	Stem2DWidget(const int x, const int y, const int w, const int h, const std::string cap);
	virtual ~Stem2DWidget();
protected:
	void draw();
};

#endif /* STEM2DWIDGET_H_ */
