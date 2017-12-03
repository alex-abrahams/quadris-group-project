#ifndef NOTFR_H
#define NOTFR_H

enum class Direction;
enum class FromType {Cell, Game, NoOne, Move, Drop};

struct NotifFrom {
  FromType from;
  // for game.
  size_t rowsScore, blocksClearedScore, hiscore, level;
  Direction d;
};

#endif

