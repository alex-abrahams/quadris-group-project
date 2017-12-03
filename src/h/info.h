#ifndef __INFO_H__
#define __INFO_H__
#include <string>
#include <cstddef>
#undef None
enum class TetroType {IBlock, JBlock, LBlock, ZeroBlock, SBlock, ZBlock, TBlock, None};



struct Info {
  size_t row, col;
  TetroType type;
};

#endif

