#ifndef TETROMINO_HPP
#define TETROMINO_HPP


#include <array>
#include "fixed_point.hpp"


namespace Tetris
{
    class Grid;
    

    struct Coord
    {
        fixed_point<int8_t, 1> x, y;
    };

    Coord operator+(Coord a, Coord b) noexcept;

    enum class Rotation : uint8_t
    {
        ClockWise = 0, CounterClockWise = 1
    };
    

    class Tetromino
    {
    public:
        enum Kind { I, O, J, L, S, Z, T };

        virtual ~Tetromino() = default;
        
        bool rotateCW(Grid const& grid);
        bool rotateCCW(Grid const& grid);
        
        Coord getOrigin() const { return origin; }
        std::array<Coord, 4> const& getBlocks() const { return blocks; }
        
        bool translate(Grid const& grid, int x, int y);


    protected:
        // Vive le C++ \o/ Cette écriture dégueu déclare wall_kick_offset comme 
        // une méthod virtuelle pure const et noexcept qui renvoie un pointeur vers un tableau 2D de 4 sur 4 de Coord
        virtual Coord (*wall_kick_offsets() const noexcept)[4][4] = 0;

    private:
        static bool is_free(Grid const& grid, Coord coor) noexcept;
        static bool fit(Grid const& grid, Coord ori, std::array<Coord, 4> const& blcs) noexcept;
        
        bool rotate(Grid const& grid, Rotation rot) noexcept;
        std::array<Coord, 4> base_rotate(Rotation rot) const noexcept;

    protected:
        Coord origin = {5, 5};
        std::array<Coord, 4> blocks;
        uint8_t rotationState = 0;
    };
    
    
    class T_Tetromino : public Tetromino
    {
    public:
        T_Tetromino();
        
    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };

}


#endif // TETROMINO_HPP
