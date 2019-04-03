#ifndef TETROMINO_HPP
#define TETROMINO_HPP


#include <array>
#include "fixed_point.hpp"

//class représentant le tetrominos courrant (en chute)
//Avec les méthodes de rotation, translation 
//et de vérification des collisions
//Auteur : Thomas FERRAND
namespace Tetris
{
    class Grid;
    
	//Les coordonnées du tetrominos
    struct Coord
    {
        fixed_point<int8_t, 1> x, y;
    };
	
	//permet l'ajout de coordonnées
    Coord operator+(Coord a, Coord b) noexcept;
	
	//enum indiquant le sens de rotation
    enum class Rotation : uint8_t
    {
        ClockWise = 0, CounterClockWise = 1
    };
    

    class Tetromino
    {
    public:
	//enum indiquant le type du tetrominos
        enum Kind { I, O, J, L, S, Z, T };
		
	//destructeur
        virtual ~Tetromino() = default;
        
	//les methodes de rotation
        bool rotateCW(Grid const& grid);
        bool rotateCCW(Grid const& grid);
		
     //acesseur et tableau des origine des blocks 
	 //par rapport a l'origine du tetrominos
        Coord getOrigin() const { return origin; }
        std::array<Coord, 4> const& getBlocks() const { return blocks; }
		
     //permet de translaté le tetrominos courrant
        bool translate(Grid const& grid, int x, int y);


    protected:
        // Vive le C++ \o/ Cette écriture dégueu déclare wall_kick_offset comme 
        // une méthod virtuelle pure const et noexcept qui renvoie un pointeur vers un tableau 2D de 4 sur 4 de Coord
        virtual Coord (*wall_kick_offsets() const noexcept)[4][4] = 0;

    private:
	//verifie que la case a la coordonée est libre
        static bool is_free(Grid const& grid, Coord coor) noexcept;
	//verifie que le tetrominos rentre dans la grille 
        static bool fit(Grid const& grid, Coord ori, std::array<Coord, 4> const& blcs) noexcept;
     
	//rotation du tetrominos effective du tetrominos si fit retourne vrais
        bool rotate(Grid const& grid, Rotation rot) noexcept;
	//rotation virtuel du tetrominos et retroune les nouvelles coordonnées
        std::array<Coord, 4> base_rotate(Rotation rot) const noexcept;

    protected:
	//origine du tetrominos
        Coord origin = {5, 5};
	//origine des blocks par rapport au tetrominos
        std::array<Coord, 4> blocks;
	//entier representant la valeur de la rotation (tranche de 90 degrer)
        uint8_t rotationState = 0;
    };
    
    //Class tetromino T qui herite de tetrominos
    class T_Tetromino : public Tetromino
    {
    public:
        T_Tetromino();
        
    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };

}


#endif // TETROMINO_HPP
