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
#include <string>
#include "PlotWidget.h"

class FigureWindow: public Fl_Double_Window {
public:
	static const size_t MAX_ROWS = 5;
	static const size_t MAX_COLS = 10;
private:
	static const int CAP_SPC  = 25;
	static const int XLBL_SPC = 20;
	static const int YLBL_SPC = 20;
	typedef std::shared_ptr<PlotWidget> pwptr;

	size_t rows, cols;

	std::array<pwptr, MAX_ROWS * MAX_COLS> plots;
public:
	FigureWindow(const int         w,
				 const int         h,
				 const std::string lb,
				 const size_t      rows = 1,
				 const size_t 	   cols = 1);
	virtual ~FigureWindow();
	void plot(const std::vector<double> &x,
			  const std::vector<double> &y,
			  const int                 style = FL_SOLID,
			  const int                 width = 1,
			  const Fl_Color            col   = FL_BLACK,
			  const size_t              sbplt = 0);
	inline void plot(const std::vector<double> &x,
					 const std::vector<double> &y,
					 const size_t              sbplt = 0);
	void stem(const std::vector<double> &x,
			  const std::vector<double> &y,
			  const int                 style = FL_SOLID,
			  const int                 width = 1,
			  const Fl_Color            col   = FL_BLACK,
			  const size_t              sbplt = 0);
	inline void stem(const std::vector<double> &x,
					 const std::vector<double> &y,
					 const size_t              sbplt = 0);
	void grid(const bool on = true, const size_t sbplt = 0);
	void xlabel(const std::string &str, const size_t sbplt = 0);
	void ylabel(const std::string &str, const size_t sbplt = 0);
	void caption(const std::string &str, const size_t sbplt = 0);
	void hold(const bool on = true, const size_t sbplt = 0);
};

#endif /* FIGUREWINDOW_H_ */
