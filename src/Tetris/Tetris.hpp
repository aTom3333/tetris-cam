#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "Grid.hpp"
#include "Tetromino.hpp"
#include "Bag.hpp"


namespace Tetris
{
    //Class gérant le jeu et faisant le lien entre
    //affichage, grille logique et detection des mains
    //Auteur : Thomas FERRAND
    class Tetris
    {
    public:
        //constructeur
        Tetris();
        
        //methodes pour déplacer le tetrominos
        bool goLeft();
        bool goRight();
        bool goDown();
        bool rotateLeft();
        bool rotateRight();
        
        void fallDown();

        //reinitialise la partie
        void reset();
        
        //acesseur
        Grid const& getGrid() const noexcept { return grid; }
        uint32_t getScore() const noexcept { return score; }
        Tetromino const* getTetromino() const noexcept { return current.get(); }
        
        //verifie la fin de partie
        bool testDefeat() const;
        
    private:
        //transforme le tetrominos courant en block dans la grille au contact du "sol"
        void turnIntoBlock();
        //efface les lignes entieres de la gille
        void clearCompletedLines();
        //fait apparaitre le prochain tetrominos courant
        void spawnNew();
        
    private:
        //grille logique
        Grid grid;
        //class gérant les prochain tetrominos
        Bag bag;
        //tetrominos courant
        std::unique_ptr<Tetromino> current;
        //score de la partie
        uint32_t score = 0;
        //id du tetrominos géneré
        uint32_t currentId = 1;
    };

    std::unique_ptr<Tetromino> makeTetromino(Tetromino::Kind kind, Grid const& grid);

}

#endif // TETRIS_HPP
