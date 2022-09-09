#include "grid.h"
#include "textdisplay.h"
using namespace std;


void Grid::initInfo(size_t n) {
	for (size_t r = 0; r < n; ++r) {
		for (size_t c = 0; c < n; ++c) {
			theGrid.at(r).emplace_back(Cell(r, c));
			theGrid.at(r).at(c).attach(td);
		}
	}
	// Taking advantage of unattached neighbors at this point of
	// intializing - using setPiece() will also change display accordingly
	theGrid.at((n/2)-1).at((n/2)-1).setPiece(Colour::Black);
	theGrid.at((n/2)-1).at((n/2)).setPiece(Colour::White);
	theGrid.at((n/2)).at((n/2)-1).setPiece(Colour::White);
	theGrid.at((n/2)).at((n/2)).setPiece(Colour::Black);

	for (int r = 0; r < (int) n; ++r) {
	for (int c = 0; c < (int) n; ++c) {
	for (int x = r-1; x <= r+1; ++x) {
	for (int y = c-1; y <= c+1; ++y) {
		if (isWithinBounds(x, y) && !(x == r && y == c)) {
			theGrid.at(r).at(c).attach(&(theGrid.at(x).at(y)));
		}
	}}}}
}

bool Grid::isWithinBounds(size_t r, size_t c) {
	return (r >= 0 && r < theGrid.size() && c >= 0 && c < theGrid.size());
}

Grid::~Grid() {
	if (td != nullptr) delete td;
	if (ob != nullptr) delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) {
	if (this->ob == nullptr && ob != nullptr) {
		this->ob = ob;
		// Also need to attach this new observer to the grid cells
		// for its functionality
		for (auto &row : theGrid) {
			for (auto &col : row) {
				col.attach(ob);
				ob->notify(col);
			}
		}
	}
}

bool Grid::isFull() const {
	for (auto &row : theGrid) {
		for (auto &col : row) {
			if (col.getInfo().colour == Colour::NoColour) {
				return false;
			}
		}
	}
	return true;
}

Colour Grid::whoWon() const {
	int b = 0, w = 0;
	for (auto &row : theGrid) {
		for (auto &col : row) {
			switch (col.getInfo().colour) {
				case Colour::NoColour : break;		// This case should not be encountered
				case Colour::Black    : ++b; break;
				case Colour::White    : ++w; break;
			}
		}
	}
	if (b > w) {
		return Colour::Black;
	} else if (b < w) {
		return Colour::White;
	} else {
		return Colour::NoColour;
	}
}

void Grid::init(size_t n) {
	if (td != nullptr) delete td;
	td = new TextDisplay(n);
	ob = nullptr;
	theGrid = vector<vector<Cell>>(n, vector<Cell>());
	// handle detail specific initialization
	initInfo(n);
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
	if (isWithinBounds(r, c) && theGrid.at(r).at(c).getInfo().colour == Colour::NoColour) {
		theGrid.at(r).at(c).setPiece(colour);
	} else {
		throw InvalidMove();
	}
}

void Grid::toggle(size_t r, size_t c) {
	theGrid.at(r).at(c).toggle();
}

ostream &operator<<(ostream &out, const Grid &g) {
	if (g.td != nullptr) out << *(g.td);
	return out;
}
