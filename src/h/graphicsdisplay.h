#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "observer.h"
#include "window.h"
#include "abstracttetromino.h"
#include "info.h"
#include "notiffrom.h"
#undef None
class Cell;

class GraphicsDisplay: public Observer<Info, NotifFrom> {
	std::vector<std::vector<TetroType>> theDisplay;
  const int gridHeight, gridWidth, winHeight, winWidth, gameWidth;
  Xwindow xw;
  std::shared_ptr<AbstractTetromino> nextTetro;
  
  int score = 0;
  int hiScore = 0;
  int level = 0;	

 public:
  GraphicsDisplay(int gridHeight, int gridWidth, int winHeight, int winWidth);
  
  void setNextTetromino(std::shared_ptr<AbstractTetromino> tetro);

  void notify(Publisher<Info, NotifFrom> &whoNotified) override;
  
  void draw(std::shared_ptr<AbstractTetromino> currentTetromino);
};
#endif

