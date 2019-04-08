#ifndef BAG_HPP
#define BAG_HPP

#include <random>
#include "Tetromino.hpp"


namespace Tetris
{
    //Class gerant la répartition des type de tetrominos et leur generation.
    //Auteur : Thomas FERRAND
    class Bag
    {
    public:
        //constructeur
        Bag();

        explicit Bag(std::seed_seq seed);
        
        //genere le prochain tetrominos courant
        Tetromino::Kind getNext();

        void reset();

    private:
        //le moteur aleatoire pour la generation
        std::mt19937 engine;
        //les 7 prochains type de tetrominos
        Tetromino::Kind next[7] = {};
        //Le nombre de tetrominos restant avant la prochaine generation
        uint8_t remaining = 0;
    };

}


#endif // BAG_HPP
