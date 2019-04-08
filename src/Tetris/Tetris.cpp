#include "Tetris.hpp"
#include <algorithm>


Tetris::Tetris::Tetris() :
    grid(10, 22)
{
    spawnNew();
}

bool Tetris::Tetris::goLeft()
{
    return current->translateLeft(grid);
}

bool Tetris::Tetris::goRight()
{
    return current->translateRight(grid);
}

bool Tetris::Tetris::goDown()
{
    bool result = current->translateDown(grid);
    if(!result)
        turnIntoBlock();
    return result;
}

void Tetris::Tetris::fallDown()
{
    while(goDown());
}

void Tetris::Tetris::reset()
{
    grid.clear_lines(0,21);
    bag.reset();
    spawnNew();
}

void Tetris::Tetris::turnIntoBlock()
{
    Coord o = current->getOrigin();
    for(auto const& b : current->getBlocks())
    {
        Coord c = o + b;
        grid(c.x, c.y) = current->getId();
    }
    
    clearCompletedLines();
    
    if(testDefeat()){
        reset();
    }
    spawnNew();
}

void Tetris::Tetris::spawnNew()
{
    Tetromino::Kind kind = bag.getNext();
    current = std::move(makeTetromino(kind, grid));
    current->setId((currentId << 3) | static_cast<uint8_t>(kind+1));
    ++currentId;
}

void Tetris::Tetris::clearCompletedLines()
{
    for(uint8_t i = 0; i < grid.height(); ++i)
    {
        if(std::all_of(grid.ptr_to(0, i), grid.ptr_to(0, i+1), [](uint32_t val){ return val != 0; }))
        {
            grid.clear_line(i);
            --i;
            score++;
        }
    }
}

bool Tetris::Tetris::testDefeat() const
{
    return std::any_of(grid.ptr_to(0, grid.height()-2), grid.ptr_to(0, grid.height()), [](uint32_t val){ return val != 0; });
}

bool Tetris::Tetris::rotateLeft()
{
    return current->rotateCCW(grid);
}

bool Tetris::Tetris::rotateRight()
{
    return current->rotateCW(grid);
}

std::unique_ptr<Tetris::Tetromino> Tetris::makeTetromino(Tetromino::Kind kind, Grid const& grid)
{
    switch(kind)
    {
        case Tetromino::L:
            return std::make_unique<L_Tetromino>(grid);
        case Tetromino::J:
            return std::make_unique<J_Tetromino>(grid);
        case Tetromino::S:
            return std::make_unique<S_Tetromino>(grid);
        case Tetromino::Z:
            return std::make_unique<Z_Tetromino>(grid);
        case Tetromino::O:
            return std::make_unique<O_Tetromino>(grid);
        case Tetromino::I:
            return std::make_unique<I_Tetromino>(grid);
        case Tetromino::T:
            return std::make_unique<T_Tetromino>(grid);
    }
}
