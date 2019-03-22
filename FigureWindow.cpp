/*
 * FigureWindow.cpp
 *
 *  Created on: Mar 19, 2019
 *      Author: deadbeef
 */

#include "FigureWindow.h"

//static FigureWindow * cf = nullptr;
//const FigureWindow * gcf() { return cf; }
//bool plot(double * x, double * y, const char * style = "-", const FigureWindow * fig) {
//	if(fig != nullptr) {
//	}
//}

void FigureWindow::plot(
		const std::vector<double> &x,
		const std::vector<double> &y,
		const int style,
		const int width,
		const Fl_Color col,
		const size_t sbplt) {
	if (sbplt < (rows * cols) && sbplt >= 0) {
		plots[sbplt]->putData(x, y, style, width, col);
	}
}

inline void FigureWindow::plot(
			     const std::vector<double> &x,
				 const std::vector<double> &y,
				 const size_t sbplt) {
	plot(x, y, FL_SOLID, 1, FL_BLACK, sbplt);
}

void FigureWindow::grid(bool on, const size_t sbplt) {
	if(sbplt < rows*cols && sbplt >= 0) {
		plots[sbplt]->setGrid(on);
	}
}
void FigureWindow::xlabel(const char * str, const size_t sbplt) {
	if(sbplt < rows*cols && sbplt >= 0) {
		plots[sbplt]->setXLabel(str);
	}
}
void FigureWindow::ylabel(const char * str, const size_t sbplt) {
	if(sbplt < rows*cols && sbplt >= 0) {
		plots[sbplt]->setYLabel(str);
	}
}
void FigureWindow::caption(const char * str, const size_t sbplt) {
	if(sbplt < rows*cols && sbplt >= 0) {
		plots[sbplt]->setCaption(str);
	}
}
void FigureWindow::hold(bool on, const size_t sbplt) {
	if(sbplt < rows*cols && sbplt >= 0) {
		plots[sbplt]->setHold(on);
	}
}
FigureWindow::FigureWindow(int w, int h,
		                   const char * lb, size_t rows,size_t cols) :
						   Fl_Double_Window(w,h,lb)
{
	this->color(FL_WHITE);
	this->rows = rows;
	this->cols = cols;

	int dx = (w - 20)/cols;
	int dy = (h - 20)/rows;
	for(size_t i = 0;i < (rows>MAX_ROWS?MAX_ROWS:rows);i++) {
		int posy = 10 + dy*i;
		for(size_t j = 0;j < (cols>MAX_COLS?MAX_COLS:cols);j++) {
			int posx = 10 + dx*j;
			plots[cols*i + j] =
					std::shared_ptr<PlotWidget>(
							new PlotWidget(posx+YLBL_SPC,posy+CAP_SPC,dx-YLBL_SPC,dy-(CAP_SPC+XLBL_SPC),"Subfig")
												);
		}
	}

	this->resizable(this);
	this->end();
}

FigureWindow::~FigureWindow() {
	// TODO Auto-generated destructor stub
}



