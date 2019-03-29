/*
 * Graph2DWidget.cpp
 *
 *  Created on: Mar 29, 2019
 *      Author: oguz286
 */

#include "Graph2DWidget.h"

Graph2DWidget::Graph2DWidget(const int x, const int y, const int w, const int h, const std::string cap)
	: GraphWidget(x, y, w, h, cap)
{
}

Graph2DWidget::~Graph2DWidget() {
	// TODO Auto-generated destructor stub
}

int Graph2DWidget::handle(int event)
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
				if(getClosestPt(data, tmp, mx, my, wd, ht)) {
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
					const pdptr dat = data[cdtip->plt];

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

void Graph2DWidget::putData(const std::vector<double> &x,
						    const std::vector<double> &y,
						    const int                 style,
						    const int                 width,
						    const Fl_Color            col)
{
	pdptr data = std::make_shared<Plot2DData>(x, y, style, width, col);

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
	this->data.push_back(data);
}
