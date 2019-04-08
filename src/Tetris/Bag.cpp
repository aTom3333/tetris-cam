#include "Bag.hpp"
#include <algorithm>
#include <numeric>


Tetris::Bag::Bag(std::seed_seq seed) :
    engine{seed}
{}

Tetris::Bag::Bag() :
    engine{std::random_device{}()}
{}

Tetris::Tetromino::Kind Tetris::Bag::getNext()
{
    if(remaining == 0)
    {
        int init = 0;
        for(auto& k : next)
            k = static_cast<Tetromino::Kind>(init++);
        std::shuffle(std::begin(next), std::end(next), engine);
        remaining = 7;
    }
    
    remaining--;
    return next[remaining];
}

void Tetris::Bag::reset()
{
    int init = 0;
    for(auto& k : next)
        k = static_cast<Tetromino::Kind>(init++);
    std::shuffle(std::begin(next), std::end(next), engine);
    remaining = 7;
}
