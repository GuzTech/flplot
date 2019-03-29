/*
 * GraphWidget.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: deadbeef
 */

#include "GraphWidget.h"

#include <FL/fl_draw.H>
#include <cmath>
#include <cinttypes>
#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>

GraphWidget::GraphWidget(const int x, const int y, const int w, const int h, const std::string cap)
	: Fl_Widget(x, y, w, h, cap.c_str())
	, xlabel("x")
	, ylabel("y")
	, caption(cap)
	, lim({0, (double)w, 0, (double)h})
	, limc(lim)
{
}

GraphWidget::~GraphWidget() {
	// TODO Auto-generated destructor stub
}

bool GraphWidget::getClosestPt(const std::vector<pdptr> &data, datatip &tip, const int mx, const int my, const double wd, const double ht)
{
	double mdist = w() * w() + h() * h();

	for(size_t j = 0; j < data.size(); ++j) {
		const pdptr dat = data[j];
		for(size_t i = 0; i < dat->size(); ++i) {
			double px, py;
			//First get the data
			dat->getVal(i, px, py);
			//Scale and shift
			px = ((px - limc.xl) / wd) * w() + x();
			py = h() - ((py - limc.yl) / ht) * h() + y();

			const double dist = std::max(abs(px - mx), abs(py - my));
			if(dist < mdist) {
				dat->getVal(i, px, py);
				mdist = dist;
				tip.x = px;
				tip.y = py;
				tip.plt = j;
			}
		}
	}
	return mdist <= 10;
}

dtipvec::iterator GraphWidget::getClosestDt(const int mx, const int my, const double wd, const double ht)
{
	dtipvec::iterator it;
	for(it = datatips.begin(); it != datatips.end(); ++it) {
		const double px = ((it->x - limc.xl) / wd) * w() + x();
		const double py = h() - ((it->y - limc.yl) / ht) * h() + y();
		const double dist = std::max(abs(px - mx), abs(py - my));

		//First check if we're close to the data-tip point
		if(dist < 15) {
			break; //No-need to continue further, since we don't care about closer data-tips
		}
	}
	return it;
}
