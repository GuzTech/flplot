/*
 * FigureWindow.cpp
 *
 *  Created on: Mar 19, 2019
 *      Author: deadbeef
 */

#include "FigureWindow.h"
#include "GraphWidget.h"
#include "Plot2DWidget.h"
#include "Stem2DWidget.h"

bool FigureWindow::isSubPlotIdxValid(const size_t sbplt)
{
	return (sbplt < (rows * cols));
}

bool FigureWindow::doesSubPlotExist(const size_t sbplt)
{
	return isSubPlotIdxValid(sbplt) && plots[sbplt];
}

void FigureWindow::createSubPlot(const std::vector<double> &x,
								 const std::vector<double> &y,
								 const int 				   style,
								 const int 				   width,
								 const Fl_Color 		   col,
								 const size_t 			   sbplt,
								 const PlotType            type)
{
	if (sbplt < (rows * cols)) {
		if (plots[sbplt] == nullptr) {
			const size_t row = sbplt / cols;
			const size_t clm = sbplt % cols;
			const int dx = (w() - 20) / cols;
			const int dy = (h() - 20) / rows;
			const int posx = 10 + dx * clm;
			const int posy = 10 + dy * row;

			begin();
			switch (type) {
			case PLOT:
				plots[sbplt] = make_shared<Plot2DWidget>(posx + YLBL_SPC,
												   	     posy + CAP_SPC,
														 dx - YLBL_SPC,
														 dy - (CAP_SPC + XLBL_SPC),
														 std::string("Subfig"));
				plots[sbplt]->putData(x, y, style, width, col);
				break;
			case STEM:
				plots[sbplt] = make_shared<Stem2DWidget>(posx + YLBL_SPC,
												   	     posy + CAP_SPC,
														 dx - YLBL_SPC,
														 dy - (CAP_SPC + XLBL_SPC),
														 std::string("Subfig"));
				plots[sbplt]->putData(x, y, style, width, col);
				break;
			case QUIVER: break;
			default: break;
			}
			end();
		}
	}
}

void FigureWindow::updateSubPlot(const std::vector<double> &x,
							     const std::vector<double> &y,
								 const int 				   style,
								 const int 				   width,
								 const Fl_Color 		   col,
								 const size_t 			   sbplt)
{
	plots[sbplt]->putData(x, y, style, width, col);
}

void FigureWindow::plot(const std::vector<double> &x,
						const std::vector<double> &y,
						const int 				  style,
						const int 				  width,
						const Fl_Color 			  col,
						const size_t 			  sbplt)
{
	if (!doesSubPlotExist(sbplt)) {
		createSubPlot(x, y, style, width, col, sbplt, PlotType::PLOT);
	} else {
		updateSubPlot(x, y, style, width, col, sbplt);
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
		const size_t sbplt)
{
	if (!doesSubPlotExist(sbplt)) {
			createSubPlot(x, y, style, width, col, sbplt, PlotType::STEM);
		} else {
			updateSubPlot(x, y, style, width, col, sbplt);
		}
}

inline void FigureWindow::stem(
			     const std::vector<double> &x,
				 const std::vector<double> &y,
				 const size_t sbplt) {
	stem(x, y, FL_SOLID, 1, FL_BLACK, sbplt);
}

void FigureWindow::quiver(const vector<vector<double>> &x,
						  const vector<vector<double>> &y,
						  const vector<vector<double>> &px,
						  const vector<vector<double>> &py,
						  const int                    style,
						  const int                    width,
						  const Fl_Color               col,
						  const size_t                 sbplt)
{

}

//inline void FigureWindow::quiver(const vector<vector<double>> &x,
//								 const vector<vector<double>> &y,
//								 const vector<vector<double>> &px,
//								 const vector<vector<double>> &py,
//								 const size_t                 sbplt)
//{
//	quiver(x, y, px, py, FL_SOLID, 1, FL_BLACK, sbplt);
//}

void FigureWindow::grid(bool on, const size_t sbplt) {
	if(sbplt < rows * cols && plots[sbplt]) {
		plots[sbplt]->setGrid(on);
	}
}

void FigureWindow::xlabel(const std::string &str, const size_t sbplt) {
	if(sbplt < rows * cols && plots[sbplt]) {
		plots[sbplt]->setXLabel(str);
	}
}

void FigureWindow::ylabel(const std::string &str, const size_t sbplt) {
	if(sbplt < rows * cols && plots[sbplt]) {
		plots[sbplt]->setYLabel(str);
	}
}

void FigureWindow::caption(const std::string &str, const size_t sbplt) {
	if(sbplt < rows * cols && plots[sbplt]) {
		plots[sbplt]->setCaption(str);
	}
}

void FigureWindow::hold(bool on, const size_t sbplt) {
	if(sbplt < rows * cols && plots[sbplt]) {
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

//	const int dx = (w - 20) / cols;
//	const int dy = (h - 20) / rows;
//
//	for(size_t i = 0; i < (rows > MAX_ROWS ? MAX_ROWS : rows); ++i) {
//		const int posy = 10 + dy * i;
//		for(size_t j = 0; j < (cols > MAX_COLS ? MAX_COLS : cols); ++j) {
//			const int posx = 10 + dx * j;
//
//			plots[cols*i + j] = std::make_shared<GraphWidget>(posx + YLBL_SPC,
//															  posy + CAP_SPC,
//															  dx - YLBL_SPC,
//															  dy - (CAP_SPC + XLBL_SPC),
//															  std::string("Subfig"));
//		}
//	}

	resizable(this);
	end();
}

FigureWindow::~FigureWindow() {
	// TODO Auto-generated destructor stub
}



