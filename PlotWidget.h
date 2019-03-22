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
	struct datatip {double x,y;ulong plt;int lx,ly; };
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

	bool getClosestPt(datatip & tip, int mx, int my, double wd, double ht);
	dtipvec::iterator getClosestDt(int mx, int my, double wd, double ht);
public:
	PlotWidget(int x, int y, int w, int h, const char * cap="");
	virtual ~PlotWidget();
	int handle(int event);
	void draw();
	void putData(int len, double * x, double * y, int style = FL_SOLID, int width = 1, Fl_Color col = FL_BLACK);
	inline void setGrid(bool on = true) { grid = on; redraw(); }
	inline void setXLabel(const char * str) { xlabel = str; redraw(); };
	inline void setYLabel(const char * str) { ylabel = str; redraw(); };
	inline void setCaption(const char * str) { caption = str; redraw(); };
	inline void setHold(bool on = true) { hold = on; }
};

#endif /* PLOTWIDGET_H_ */
