/*
 * Stem2DWidget.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: oguz286
 */

#include "Stem2DWidget.h"

#include <FL/fl_draw.H>
#include <cmath>
#include <cinttypes>
#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>

Stem2DWidget::Stem2DWidget(const int x, const int y, const int w, const int h, const std::string cap)
	: Graph2DWidget(x, y, w, h, cap)
{
}

Stem2DWidget::~Stem2DWidget() {
	// TODO Auto-generated destructor stub
}

void Stem2DWidget::draw()
{
	const double wd = limc.xr - limc.xl;
	const double ht = limc.yr - limc.yl;
	char str[50];

	//Background
	fl_color(FL_WHITE);
	fl_rectf(x(),y(),w(),h());
	fl_color(FL_BLACK);
	fl_line_style(FL_SOLID);
	fl_rect(x(),y(),w(),h());

	//Caption+labels
	fl_font(FL_HELVETICA,12);
	fl_color(FL_BLACK);
	int tw, th;
	fl_measure(caption.c_str(),tw,th);
	fl_draw(caption.c_str(),x()+(w()>>1) - (tw>>1),y()-7);
	fl_measure(xlabel.c_str(),tw,th);
	fl_draw(xlabel.c_str(),x()+(w()>>1) - (tw>>1),y()+h()+12);
	fl_measure(ylabel.c_str(),tw,th);
	fl_draw(90,ylabel.c_str(),x()-5,y()+(h()>>1)+(tw>>1));

	fl_push_clip(x(),y(),w(),h());
	//Proportionally determine tick amount
	xngrid = w()/75;
	yngrid = h()/50;

	//Draw grid lines
	fl_font(FL_HELVETICA,10);
	fl_color(FL_BLACK);
	int dx = w()/(this->xngrid + 1);
	for(int i = 1;i <= this->xngrid;i++) {
		if(grid) {
			fl_color(FL_GRAY);
			fl_line_style(FL_DASH);
			fl_line(x()+dx*i,y(),x()+dx*i,y()+h());
		}
		fl_color(FL_BLACK);
		fl_line_style(FL_SOLID);
		fl_line(x()+dx*i,y(),x()+dx*i,y()+10);
		fl_line(x()+dx*i,y()+h(),x()+dx*i,y()+h()-10);
		snprintf(str,50,"%.2e",i*wd/(this->xngrid+1) + limc.xl);
		fl_draw(str,x()+dx*i+2,y()+h()-5);
	}
	int dy = h()/(this->yngrid + 1);
	for(int i = 1;i <= this->yngrid;i++) {
		if(grid) {
			fl_color(FL_GRAY);
			fl_line_style(FL_DASH);
			fl_line(x(),y() + dy*i,x() + w(),y()+dy*i);
		}
		fl_color(FL_BLACK);
		fl_line_style(FL_SOLID);
		fl_line(x(),y() + dy*i,x()+10,y() + dy*i);
		fl_line(x()+w(),y() + dy*i,x()+w()-10,y() + dy*i);
		snprintf(str,20,"%.2e",i*ht/(this->yngrid+1) + limc.yl);
		fl_draw(str,x()+2,h() + y()-dy*i-5);
	}

	//Plot the data
	for(pdptr &dat : data) {
		fl_color(dat->col);
		fl_line_style(dat->style, dat->width);

		for(size_t i = 0; i < dat->size(); i++)
		{
			fl_begin_line();

			double px, py, p0;
			dat->getVal(i, px, py);

			//Scale and shift
			px = ((px - limc.xl) / wd) * w() + x();
			py = h() - ((py - limc.yl) / ht) * h() + y();
			p0 = h() - (-limc.yl / ht) * h() + y();

			fl_vertex((int)px, p0);
			fl_vertex((int)px, (int)py);
			fl_end_line();

			fl_circle(px, py, 4);
		}
	}


	fl_color(FL_BLACK);
	fl_line_style(FL_SOLID,1);
	//Draw data-tips
	for(datatip & tip : datatips) {
		double px = tip.x,py = tip.y;
		snprintf(str,50,"x: %.2e y: %.2e",px,py);
		px = ((px - limc.xl)/wd)*w() + x();
		py = h() - ((py - limc.yl)/ht)*h() + y();
		if((int)px >= x() && (int)px <= x()+w() &&
			(int)py >= y() && (int)py <= y()+h()) {
			fl_rectf(px-5,py-5,10,10);
			fl_draw(str,px+tip.lx,py+tip.ly);
		}
	}

	//Zoom-box
	if(zooming) {
		const int mx = Fl::event_x();
		const int my = Fl::event_y();
		const int dx = mx - zoomx;
		const int dy = my - zoomy;
		fl_line_style(FL_DASH);
		fl_rect(std::min(zoomx, zoomx + dx), std::min(zoomy, zoomy + dy), abs(dx), abs(dy));
	}

	fl_pop_clip();
}
