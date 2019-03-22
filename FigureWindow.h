/*
 * FigureWindow.h
 *
 *  Created on: Mar 19, 2019
 *      Author: deadbeef
 */

#ifndef FIGUREWINDOW_H_
#define FIGUREWINDOW_H_

#include <FL/Fl_Double_Window.H>
#include <array>
#include "PlotWidget.h"

class FigureWindow: public Fl_Double_Window {
public:
	static const size_t MAX_ROWS = 5;
	static const size_t MAX_COLS = 10;
private:
	static const int CAP_SPC = 25;
	static const int XLBL_SPC = 20;
	static const int YLBL_SPC = 20;
	typedef std::shared_ptr<PlotWidget> pwptr;

	size_t rows, cols;

	std::array<std::shared_ptr<PlotWidget>,MAX_ROWS*MAX_COLS> plots;
public:
	FigureWindow(int w, int h, const char * lb, size_t rows = 1,size_t cols = 1);
	virtual ~FigureWindow();
	void plot(size_t len,
			 double * x,
			 double * y,
			 const int style = FL_SOLID,
			 const int width=1,
			 const Fl_Color col = FL_BLACK,
			 const size_t sbplt=0);
	inline void plot(size_t len,
			     double * x,
				 double * y,
				 const size_t sbplt=0);
	void grid(bool on = true, const size_t sbplt=0);
	void xlabel(const char * str = "", const size_t sbplt=0);
	void ylabel(const char * str = "", const size_t sbplt=0);
	void caption(const char * str = "", const size_t sbplt=0);
	void hold(bool on = true, const size_t sbplt=0);
};

//const FigureWindow * gcf();
//bool plot(size_t splot, double * x, double * y, const char * style = "-", const FigureWindow * fig = gcf());

#endif /* FIGUREWINDOW_H_ */
