/*
 * PlotWidget.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author: deadbeef
 */

#include "PlotWidget.h"
#include <FL/fl_draw.H>
#include <cmath>
#include <cinttypes>
#include <cstdlib>
#include <memory>
#include <string>
#include <iostream>

PlotWidget::PlotWidget(const int x, const int y, const int w, const int h, const std::string cap)
	: Fl_Widget(x, y, w, h, cap.c_str())
	, xlabel("x")
	, ylabel("y")
	, caption(cap)
	, lim({0, (double)w, 0, (double)h})
	, limc(lim)
{
}

PlotWidget::~PlotWidget() {
	// TODO Auto-generated destructor stub
}

bool PlotWidget::getClosestPt(datatip &tip, const int mx, const int my, const double wd, const double ht) {
	double mdist = w() * w() + h() * h();

	for(size_t j = 0; j < data.size(); ++j) {
		const plot &plt = data[j];
		const pdptr dat = plt.data;
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

PlotWidget::dtipvec::iterator PlotWidget::getClosestDt(const int mx, const int my, const double wd, const double ht) {
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

int PlotWidget::handle(int event)
{
	const int mx = Fl::event_x();
	const int my = Fl::event_y();
	const double wd = limc.xr - limc.xl;
	const double ht = limc.yr - limc.yl;

	switch(event) {
	case FL_PUSH:
		cdtip = getClosestDt(mx, my, wd, ht);
		if(Fl::event_button() == FL_LEFT_MOUSE) {
			//First check if user clicked on a data-tip
			//Find a data-tip point within a neighborhood of the mouse pointer
			if(cdtip == datatips.end()) {
				//User didn't click on an existing datatip
				datatip tmp;
				if(getClosestPt(tmp, mx, my, wd, ht)) {
					tmp.lx = 10;
					tmp.ly = -10;
					datatips.push_back(tmp);
					cdtip = datatips.end() - 1;
				} else {
					zooming = true;
					zoomx = mx;
					zoomy = my;
				}
				redraw();
			}
		} else if(Fl::event_button() == FL_MIDDLE_MOUSE) {
			zoomx = mx;
			zoomy = my;
		} else if (Fl::event_button() == FL_RIGHT_MOUSE) {
			if(cdtip != datatips.end()) {
				datatips.erase(cdtip);
				cdtip = datatips.end();
			} else {
				limc = lim;
			}
			redraw();
		}
		return 1;
	case FL_DRAG:
		if(Fl::event_inside(this)) {
			if(Fl::event_button() == FL_LEFT_MOUSE) {
				if(!zooming && cdtip != datatips.end()) {
					const plot &plt = this->data[cdtip->plt];
					const pdptr dat = plt.data;

					double mdist = w()*w()+h()*h();
					for(size_t i = 0;i < dat->size();i++) {
						double px,py;
						//First get the data
						dat->getVal(i,px,py);
						px = ((px - limc.xl)/wd)*w() + x();
						py = h() - ((py - limc.yl)/ht)*h() + y();

						double dist = std::max(abs(px-mx),abs(py-my));
						if(dist < mdist) {
							dat->getVal(i,px,py);
							mdist = dist;
							cdtip->x = px;
							cdtip->y = py;
						}
					}
				}
			} else if(Fl::event_button() == FL_MIDDLE_MOUSE) {
				if(cdtip != datatips.end()) {
					double px = cdtip->x,py = cdtip->y;
					px = ((px - limc.xl)/wd)*w() + x();
					py = h() - ((py - limc.yl)/ht)*h() + y();

					cdtip->lx = mx-px;
					cdtip->ly = my-py;
				} else {
					double dx = mx-zoomx,
							dy = my-zoomy;
					if(abs(dx) >= 1 || abs(dy) >= 1) {
						dx *= wd/w();
						dy *= ht/h();
						zoomx = mx;
						zoomy = my;
						limc.xl -= dx;
						limc.xr -= dx;
						limc.yl += dy;
						limc.yr += dy;
					}
				}
			}
			redraw();
		}
		return 1;
	case FL_RELEASE:
		if(Fl::event_button() == FL_LEFT_MOUSE) {
			if(zooming) {
				int dx = mx - zoomx;
				int dy = my - zoomy;
				zooming = false;

				//Get rect (lul)
				zoomx = std::min(zoomx, mx);
				zoomy = std::min(zoomy, my);
				dx = abs(dx);
				dy = abs(dy);

				if(dx > 2 || dy > 2) {
					//Clip
					zoomx = std::max(zoomx, x());
					zoomy = std::max(zoomy, y());
					dx = std::min(dx, w() + x() - zoomx);
					dy = std::min(dy, h() + y() - zoomy);

					//Scale+shift
					limc.xl = ((double)(zoomx - x()) / w()) * wd + limc.xl;
					limc.xr = limc.xl + ((double)dx / w()) * wd;
					limc.yl = ((double)(y() + h() - dy - zoomy) / h()) * ht + limc.yl;
					limc.yr = limc.yl + ((double)dy / h()) * ht;
				}
				redraw();
			}
		}
		//cout << "Release at " << Fl::event_x() << " " << Fl::event_y() <<endl;
		return 1;
	case FL_MOUSEWHEEL:
	{
		// Fl::event_dx() gives horizontal scrolling values.
		// Fl::event_dy() gives vertical scrolling values. -1 is zooming in, 1 is zooming out.
		double coefficient = Fl::event_dy() * -0.1;

		// mx, my are in window space
		// x(), y() are in plot widget coordinates
		// w(), h() are the absolute widget sizes
		const double mxx = ((double)(mx - x())) / w() * wd;
		const double myy = ((double)(h() + y() - my)) / h() * ht;

		const double dxr = wd - mxx;
		const double dyr = ht - myy;

		limc.xl = (mxx * coefficient) + limc.xl;
		limc.xr = limc.xr - (dxr * coefficient);
		limc.yl = (myy * coefficient) + limc.yl;
		limc.yr = limc.yr - (dyr * coefficient);

		redraw();

		return 1;
	}
	default:
		return Fl_Widget::handle(event);
	}
	return 0;
}
void PlotWidget::draw()
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
	for(plot &dat : data) {
		fl_color(dat.data->col);
		fl_line_style(dat.data->style, dat.data->width);

		switch(dat.type) {
		case PLOT: {
			fl_begin_line();
			for(size_t i = 0;i < dat.data->size();i++)
			{
				double px,py;
				dat.data->getVal(i,px,py);
				//Scale and shift
				px = ((px - limc.xl)/wd)*w() + x();
				py = h() - ((py - limc.yl)/ht)*h() + y();
				fl_vertex((int)px, (int)py);
			}
			fl_end_line();
		} break;
		case STEM: {
			for(size_t i = 0; i < dat.data->size(); i++)
			{
				fl_begin_line();

				double px, py, p0;
				dat.data->getVal(i, px, py);

				//Scale and shift
				px = ((px - limc.xl) / wd) * w() + x();
				py = h() - ((py - limc.yl) / ht) * h() + y();
				p0 = h() - (-limc.yl / ht) * h() + y();

				fl_vertex((int)px, p0);
				fl_vertex((int)px, (int)py);
				fl_end_line();

				fl_circle(px, py, 4);
			}
		} break;
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

void PlotWidget::putData(const std::vector<double> &x,
						 const std::vector<double> &y,
						 const int                 style,
						 const int                 width,
						 const Fl_Color            col,
						 const PlotType            type)
{
	pdptr data = std::make_shared<PlotData>(x, y, style, width, col);

	double xmin, xmax, ymin, ymax;

	if (!hold)
		this->data.clear();

	data->getXlim(xmin, xmax);
	data->getYlim(ymin, ymax);

	if (this->data.empty())
	{
		lim = {xmin, xmax, ymin, ymax};
		limc = lim;
	}
	else
	{
		lim = { lim.xl > xmin ? xmin : lim.xl,
				lim.xr < xmax ? xmax : lim.xr,
				lim.yl > ymin ? ymin : lim.yl,
				lim.yr < ymax ? ymax : lim.yr
		};
		limc = lim;
	}
	this->data.push_back({data, type});
}
