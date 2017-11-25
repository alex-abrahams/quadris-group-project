#ifndef CELL_H
#define CELL_H
#include "info.h"

class Cell : public Publisher<Info> {
    const size_t row, col;
    TetroType type = TetroType::None;
    
    public:
        Cell(size_t row, size_t col);

        // make this cell hold a certain Tetromino type.
        void setType(TetroType type);
        
        Info getInfo() const override;

}

#endif
