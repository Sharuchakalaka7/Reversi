#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  Colour pc = Colour::NoColour;		// player colour
  bool gameStarted = false;
  // End of added code

  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      // Add code here
	  if (!gameStarted && n >= 4 && n % 2 == 0) {
        g.init(n);
		g.setObserver(new GraphicsDisplay(n));
		pc = Colour::Black;
		gameStarted = true;
		cout << g;
	  }
	  // End of added code
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
	  if (gameStarted) {
        try {
        g.setPiece(r, c, pc);
		cout << g;
        pc = (pc == Colour::Black) ? Colour::White : Colour::Black;
		if (g.isFull()) {
          switch (g.whoWon()) {
			case Colour::Black : cout << "Black wins!" << endl; break;
			case Colour::White :
			default            : cout << "White wins!" << endl; break;
          }
		  break;
        }
		}
        catch (...) {}	// Any game semantic failure also quits
	  }
	  // End of added code
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
