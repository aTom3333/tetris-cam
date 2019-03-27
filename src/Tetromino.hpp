#ifndef TETROMINO_HPP
#define TETROMINO_HPP


#include <array>
#include "fixed_point.hpp"


namespace Tetris
{
    class Grid;
    
    namespace 
    {
        struct Coord
        {
            fixed_point<int8_t, 1> x, y;
        };
        
        Coord operator+(Coord a, Coord b) noexcept
        {
            return Coord{a.x+b.x, a.y+b.y};
        }
    }
    
    
    enum class Rotation : uint8_t
    {
        ClockWise = 0, CounterClockWise = 1
    };
    

    class Tetromino
    {
    public:
        explicit Tetromino(Grid const& grid);
        
        enum Kind { I, O, J, L, S, Z, T };

        virtual ~Tetromino() = default;
        
        bool rotateCW(Grid const& grid);
        bool rotateCCW(Grid const& grid);
        
        Coord getOrigin() const { return origin; }
        std::array<Coord, 4> const& getBlocks() const { return blocks; }
        
        // TODO Remove
        void trans(Grid const& grid, int x, int y);
        
        bool translateLeft(Grid const& grid) noexcept;
        bool translateRight(Grid const& grid) noexcept;
        bool translateDown(Grid const& grid) noexcept;
        

    protected:
        // Vive le C++ \o/ Cette écriture dégueu déclare wall_kick_offset comme 
        // une méthod virtuelle pure const et noexcept qui renvoie un pointeur vers un tableau 2D de 4 sur 4 de Coord
        virtual Coord (*wall_kick_offsets() const noexcept)[4][4] = 0;

    private:
        static bool is_free(Grid const& grid, Coord coor) noexcept;
        static bool fit(Grid const& grid, Coord ori, std::array<Coord, 4> const& blcs) noexcept;
        
        bool rotate(Grid const& grid, Rotation rot) noexcept;
        std::array<Coord, 4> base_rotate(Rotation rot) const noexcept;

        bool translate(Grid const& grid, Coord v) noexcept;

    protected:
        Coord origin = {5, 5};
        std::array<Coord, 4> blocks;
        uint8_t rotationState = 0;
    };


    class T_Tetromino : public Tetromino
    {
    public:
        explicit T_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };


    class J_Tetromino : public Tetromino
    {
    public:
        explicit J_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };


    class L_Tetromino : public Tetromino
    {
    public:
        explicit L_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };


    class S_Tetromino : public Tetromino
    {
    public:
        explicit S_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };


    class Z_Tetromino : public Tetromino
    {
    public:
        explicit Z_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };


    class I_Tetromino : public Tetromino
    {
    public:
        explicit I_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };


    class O_Tetromino : public Tetromino
    {
    public:
        explicit O_Tetromino(Grid const& grid);

    protected:
        Coord (*wall_kick_offsets() const noexcept)[4][4];
    };

}


#endif // TETROMINO_HPP