#include "cell.h"
using namespace std;


Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

Direction Cell::getDirection(int d) const {
	switch (d) {
		case 0: return Direction::NW;
		case 1: return Direction::N;
		case 2: return Direction::NE;
		case 3: return Direction::W;
		case 4: return Direction::E;
		case 5: return Direction::SW;
		case 6: return Direction::S;
		case 7: return Direction::SE;
		default: return Direction::N;
	}
}

void Cell::setPiece(Colour colour) {
	this->colour = colour;
	// Send a signal for each direction, from NW to SE
	for (int d = 0; d <= DIRS; ++d) {
		setState(State{StateType::NewPiece, colour, getDirection(d)});
		notifyObservers();
	}
}

void Cell::toggle() {
	switch (colour) {
		case Colour::NoColour: break;
		case Colour::Black:    colour = Colour::White; break;
		case Colour::White:    colour = Colour::Black; break;
	}
}

void Cell::notify(Subject<Info, State> &whoFrom) {
	Info info = whoFrom.getInfo();
	State state = whoFrom.getState();

	// First, calculate relative direction of whoFrom from this cell
	int dr = (int) (info.row - r);	// delta row number
	int dc = (int) (info.col - c);	// delta column number

	// Calculation that results with 0 <= d <= (DIRS = 7)
	int d = (3 + 3*dr) + (1 + dc);
	d -= (d >= 4) ? 1 : 0;

	Direction dir = getDirection(d);

	// Keep propogating message iff message is coming from correct direction
	if (dir == state.direction) {
		switch (state.type) {
			case StateType::NewPiece:
				// Don't need to relay if no cells of opposite pieces -
				// just satisfied with changing the ordered piece
				switch (colour) {
					case Colour::NoColour : break;
					case Colour::Black :
					case Colour::White :
						if (colour != state.colour) {
							setState(State{StateType::Relay, state.colour, dir});
							notifyObservers();
						}
						break;
				}
				break;
			case StateType::Relay:
				switch (colour) {
					case Colour::NoColour : break;	// break relay - no same colour found
					case Colour::Black :
					case Colour::White :
						// Note: getDirection(DIRS-d) produces the opposite direction
						// Either matching piece is found for reply or keep propogating relay
						if (colour == state.colour) {
							setState(State{StateType::Reply, state.colour, getDirection(DIRS-d)});
						} else {
							setState(State{StateType::Relay, state.colour, dir});
						}
						notifyObservers();
						break;
				}
				break;
			case StateType::Reply:
				// By how Reply is used with State here, state.colour cannot be NoColour,
				// which means we keep replying (and flipping colours throughout) as long
				// as there are cells of the toggled colours

				switch (colour) {
					case Colour::NoColour : break;
					case Colour::Black :
					case Colour::White :
						if (colour != state.colour) {
							toggle();
							setState(State{StateType::Reply, state.colour, dir});
							notifyObservers();
						}
						break;
				}
				break;
		}
	}
}

Info Cell::getInfo() const {
	return Info{r, c, colour};
}
