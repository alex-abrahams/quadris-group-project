#ifndef NOTFR_H
#define NOTFR_H

enum class FromType {Cell, Game, NoOne};

struct NotifFrom {
  FromType from;
  // for game.
  size_t score, hiscore, level;
};

#endif
