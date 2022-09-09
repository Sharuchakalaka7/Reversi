#include <sstream>
#include "graphicsdisplay.h"
#include "subject.h"
using namespace std;

void GraphicsDisplay::drawAxes(int n) {
	for (int i = 0; i < n; ++i) {
		ostringstream os;
		int ip = width/2;
		os << i;
		w.drawString(2*width*(i+1) - ip, ip, os.str());
		w.drawString(ip, 2*width*(i+1) - ip, os.str());
	}
}

void GraphicsDisplay::drawCell(int x, int y, int colour) {
	// Output is inverted, oof
	w.fillRectangle(width*(2*y + 1), width*(2*x + 1), width, width, colour);
}

GraphicsDisplay::GraphicsDisplay(int n) : w(), width{500/(2*n+1)} {
	// only allow up to and excluding 250 cells, each padded
	// with one pixel all around each
	drawAxes(n);
	for (int x = 0; x < n; ++x) {
		for (int y = 0; y < n; ++y) {
			drawCell(x, y, Xwindow::Blue);
		}
	}
}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
	Info info = whoNotified.getInfo();
	int colour;
	switch (info.colour) {
		case Colour::NoColour : colour = Xwindow::Blue;  break;
		case Colour::Black    : colour = Xwindow::Black; break;
		case Colour::White    : colour = Xwindow::White; break;
	}
	drawCell(info.row, info.col, colour);
}
