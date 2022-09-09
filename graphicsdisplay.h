#ifndef GRAPHICSDISPLAY_H
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"
class Cell;

class GraphicsDisplay: public Observer<Info, State> {
  Xwindow w;
  const int width;	// dimensions for each rectangle representing the cells

  void drawAxes(int n);
  void drawCell(int x, int y, int colour);

 public:
  GraphicsDisplay(int n);

  void notify(Subject<Info, State> &whoNotified) override;

  //friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
