#include "textdisplay.h"
#include "subject.h"
using namespace std;

TextDisplay::TextDisplay(int n) : theDisplay(n, vector<char>(n, EMPTY)), gridSize{n} {}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
	Info info = whoNotified.getInfo();
	switch (info.colour) {
		case Colour::Black    : theDisplay.at(info.row).at(info.col) = BLACK; break;
		case Colour::White    : theDisplay.at(info.row).at(info.col) = WHITE; break;
		case Colour::NoColour : theDisplay.at(info.row).at(info.col) = EMPTY; break;
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (auto &row : td.theDisplay) {
		for (auto &col : row) {
			out << col;
		}
		out << endl;
	}
	return out;
}
