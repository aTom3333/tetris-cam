#ifndef BAG_HPP
#define BAG_HPP

#include <random>
#include "Tetromino.hpp"


namespace Tetris
{

    class Bag
    {
    public:
        Bag();

        explicit Bag(std::seed_seq seed);
        
        Tetromino::Kind getNext();

    private:
        std::mt19937 engine;
        Tetromino::Kind next[7] = {};
        uint8_t remaining = 0;
    };

}


#endif // BAG_HPP