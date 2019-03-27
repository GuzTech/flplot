/*
 * FigureWindow.cpp
 *
 *  Created on: Mar 19, 2019
 *      Author: deadbeef
 */

#include "FigureWindow.h"

void FigureWindow::plot(
		const std::vector<double> &x,
		const std::vector<double> &y,
		const int style,
		const int width,
		const Fl_Color col,
		const size_t sbplt) {
	if (sbplt < (rows * cols) && sbplt >= 0) {
		plots[sbplt]->putData(x, y, style, width, col, PlotWidget::PlotType::PLOT);
	}
}

inline void FigureWindow::plot(
			     const std::vector<double> &x,
				 const std::vector<double> &y,
				 const size_t sbplt) {
	plot(x, y, FL_SOLID, 1, FL_BLACK, sbplt);
}

void FigureWindow::stem(
		const std::vector<double> &x,
		const std::vector<double> &y,
		const int style,
		const int width,
		const Fl_Color col,
		const size_t sbplt) {
	if (sbplt < (rows * cols) && sbplt >= 0) {
		plots[sbplt]->putData(x, y, style, width, col, PlotWidget::PlotType::STEM);
	}
}

inline void FigureWindow::stem(
			     const std::vector<double> &x,
				 const std::vector<double> &y,
				 const size_t sbplt) {
	stem(x, y, FL_SOLID, 1, FL_BLACK, sbplt);
}

void FigureWindow::grid(bool on, const size_t sbplt) {
	if(sbplt < rows * cols && sbplt >= 0) {
		plots[sbplt]->setGrid(on);
	}
}

void FigureWindow::xlabel(const std::string &str, const size_t sbplt) {
	if(sbplt < rows * cols && sbplt >= 0) {
		plots[sbplt]->setXLabel(str);
	}
}

void FigureWindow::ylabel(const std::string &str, const size_t sbplt) {
	if(sbplt < rows * cols && sbplt >= 0) {
		plots[sbplt]->setYLabel(str);
	}
}

void FigureWindow::caption(const std::string &str, const size_t sbplt) {
	if(sbplt < rows * cols && sbplt >= 0) {
		plots[sbplt]->setCaption(str);
	}
}

void FigureWindow::hold(bool on, const size_t sbplt) {
	if(sbplt < rows * cols && sbplt >= 0) {
		plots[sbplt]->setHold(on);
	}
}

FigureWindow::FigureWindow(const int    	 w,
						   const int    	 h,
		                   const std::string lb,
						   const size_t 	 rows,
						   const size_t 	 cols)
	: Fl_Double_Window(w, h, strdup(lb.c_str()))
	, rows(rows)
	, cols(cols)
{
	color(FL_WHITE);

	const int dx = (w - 20) / cols;
	const int dy = (h - 20) / rows;

	for(size_t i = 0; i < (rows > MAX_ROWS ? MAX_ROWS : rows); ++i) {
		const int posy = 10 + dy * i;
		for(size_t j = 0; j < (cols > MAX_COLS ? MAX_COLS : cols); ++j) {
			const int posx = 10 + dx * j;
			plots[cols*i + j] = std::make_shared<PlotWidget>(posx + YLBL_SPC,
															 posy + CAP_SPC,
															 dx - YLBL_SPC,
															 dy - (CAP_SPC + XLBL_SPC),
															 std::string("Subfig"));
		}
	}

	resizable(this);
	end();
}

FigureWindow::~FigureWindow() {
	// TODO Auto-generated destructor stub
}



