/*
 * PlotWidget.h
 *
 *  Created on: Mar 18, 2019
 *      Author: deadbeef
 */

#ifndef PLOTWIDGET_H_
#define PLOTWIDGET_H_

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <vector>
#include <memory>
#include "PlotData.h"
#include <string>

class PlotWidget : public Fl_Widget
{
private:
	struct datatip {
		double x,y;
		ulong plt;
		int lx,ly;
	};
	typedef std::shared_ptr<PlotData> pdptr;
	typedef std::vector<datatip> dtipvec;
	std::vector<pdptr> data;
	std::string xlabel, ylabel, caption;
	dtipvec datatips;
	struct { double xl,xr,yl,yr; } lim, limc;

	ulong cur_dtip = 0;
	dtipvec::iterator cdtip;
	bool zooming = false,
		 grid = false,
		 hold = false;
	int zoomx=0, zoomy=0;

	int xngrid = 5, yngrid = 5;

	bool getClosestPt(datatip &tip, const int mx, const int my, const double wd, const double ht);
	dtipvec::iterator getClosestDt(const int mx, const int my, const double wd, const double ht);
public:
	PlotWidget(const int x, const int y, const int w, const int h, const std::string cap);
	virtual ~PlotWidget();
	int handle(const int event);
	void draw();
	void putData(const std::vector<double> &x, const std::vector<double> &y, const int style = FL_SOLID, const int width = 1, const Fl_Color col = FL_BLACK);
	inline void setGrid(const bool on = true) { grid = on; redraw(); }
	inline void setXLabel(const std::string str) { xlabel = str; redraw(); };
	inline void setYLabel(const std::string str) { ylabel = str; redraw(); };
	inline void setCaption(const std::string str) { caption = str; redraw(); };
	inline void setHold(const bool on = true) { hold = on; }
};

#endif /* PLOTWIDGET_H_ */
