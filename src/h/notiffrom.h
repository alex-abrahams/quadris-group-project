#ifndef NOTFR_H
#define NOTFR_H
#include "board.h"

enum class Direction;
enum class FromType {Cell, Game, NoOne, Move, Drop};

struct NotifFrom {
  FromType from;
  // for game.
  size_t score, hiscore, level;
  Direction d;
};

#endif
