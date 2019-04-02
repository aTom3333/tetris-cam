#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "Grid.hpp"
#include "Tetromino.hpp"
#include "Bag.hpp"


namespace Tetris
{

    class Tetris
    {
    public:
        Tetris();
        
        bool goLeft();
        bool goRight();
        bool goDown();
        
        void fallDown();
        
        Grid const& getGrid() const noexcept { return grid; }
        uint32_t getScore() const noexcept { return score; }
        
        bool testDefeat() const;
        
    private:
        void turnIntoBlock();
        void clearCompletedLines();
        void spawnNew();
        
    private:
        Grid grid;
        Bag bag;
        std::unique_ptr<Tetromino> current;
        uint32_t score = 0;
        uint32_t currentId = 1;
    };

    std::unique_ptr<Tetromino> makeTetromino(Tetromino::Kind kind, Grid const& grid);

}

#endif // TETRIS_HPP