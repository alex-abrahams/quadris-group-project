#ifndef NOTFR_H
#define NOTFR_H

enum class FromType {Cell, Game, NoOne};
enum class Visibility {Hide, Show, Unset};

struct NotifFrom {
  FromType from;

  // for game.
  size_t score, hiscore, level;
  Visibility visibility = Visibility::Unset;
};

#endif
