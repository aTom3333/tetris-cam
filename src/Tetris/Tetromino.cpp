#include <algorithm>
#include "Tetromino.hpp"
#include "Tetris/Grid.hpp"


namespace Tetris
{
    Coord operator+(Coord a, Coord b) noexcept
    {
        return Coord{a.x+b.x, a.y+b.y};
    }
    
    Tetromino::Tetromino(Grid const& grid) :
        origin{}, blocks{}
    {}
    
    std::array<Coord, 4> Tetromino::base_rotate(Rotation rot) const noexcept
    {
        int factor = static_cast<int>(rot) * 2 - 1;
        
        std::array<Coord, 4> ret{};
        std::transform(std::begin(blocks), std::end(blocks), std::begin(ret),
                       [factor](Coord a)
                       {
                           return Coord{-factor * a.y, factor * a.x};
                       });
        
        return ret;
    }

    bool Tetromino::rotateCW(Grid const& grid)
    {
        return rotate(grid, Rotation::ClockWise);
    }

    bool Tetromino::is_free(Grid const& grid, Coord coor) noexcept
    {
        if(coor.x < 0 || coor.x >= grid.width() || coor.y < 0 || coor.y >= grid.height())
            return false;
        return grid(coor.x, coor.y) == 0;
    }

    bool Tetromino::fit(Grid const& grid, Coord ori, std::array<Coord, 4> const& blcs) noexcept
    {
        return std::all_of(std::begin(blcs), std::end(blcs), [&grid, ori](Coord a){ return is_free(grid, ori+a); });
    }

    bool Tetromino::rotate(Grid const& grid, Rotation rot) noexcept
    {
        auto rotated = base_rotate(rot);
        
        if(fit(grid, origin, rotated)) {
            blocks = rotated;
            rotationState = (rotationState + 4 + static_cast<int8_t>(rot) * 2 - 1) % 4;
            return true;
        }
        
        auto wallkicks = wall_kick_offsets();
        
        if(!wallkicks)
            return false;
        
        for(Coord wko : wallkicks[static_cast<uint8_t>(rot)][rotationState])
        {
            if(fit(grid, origin+wko, rotated))
            {
                origin = origin + wko;
                blocks = rotated;
                rotationState = (rotationState + 4 + static_cast<int8_t>(rot) * 2 - 1) % 4;
                return true;
            }
        }
        
        return false;
    }

    bool Tetromino::rotateCCW(Grid const& grid)
    {
        return rotate(grid, Rotation::CounterClockWise);
    }

    bool Tetromino::translate(Grid const& grid, Coord v) noexcept
    {
        if(fit(grid, origin+v, blocks))
        {
            origin = origin + v;
            return true;
        }
        
        return false;
    }

    bool Tetromino::translateLeft(Grid const& grid) noexcept
    {
        return translate(grid, {-1, 0});
    }

    bool Tetromino::translateRight(Grid const& grid) noexcept
    {
        return translate(grid, {1, 0});
    }

    bool Tetromino::translateDown(Grid const& grid) noexcept
    {
        return translate(grid, {0, -1});
    }

    void Tetromino::trans(Grid const& grid, int x, int y)
    {
        translate(grid, Coord{x, y});
    }


    static Coord JLSTZ_wk_off[2][4][4] =
        {
            // Clockwise
            {
                { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} }, // 0 >> 1
                { {1, 0}, {1, -1}, {0, 2}, {1, 2} }, // 1 >> 2
                { {1, 0}, {1, 1}, {0, -2}, {1, -2} }, // 2 >> 3
                { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } // 3 >> 0
            },
            // Counter-clockwise
            {
                { {1, 0}, {1, 1}, {0, -2}, {1, -2} }, // 0 >> 3
                { {1, 0}, {1, -1}, {0, 2}, {1, 2} }, // 1 >> 0
                { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} }, // 2 >> 1
                { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} } // 3 >> 2
            }
        };
    
    static Coord I_wk_off[2][4][4] =
        {
            // Clockwise
            {
                { {-2, 0}, {1, 0}, {-2, -1}, {1, 2} }, // 0 >> 1
                { {-1, 0}, {2, 0}, {-1, 2}, {2, -1} }, // 1 >> 2
                { {2, 0}, {-1, 0}, {2, 1}, {-1, -2} }, // 2 >> 3
                { {1, 0}, {-2, 0}, {1, -2}, {-2, 1} } // 3 >> 0
            },
            // Counter-clockwise
            {
                { {-1, 0}, {2, 0}, {-1, 2}, {2, -1} }, // 0 >> 3
                { {2, 0}, {-1, 0}, {2, 1}, {-1, -2} }, // 1 >> 0
                { {1, 0}, {-2, 0}, {1, -2}, {-1, 1} }, // 2 >> 1
                { {-2, 0}, {1, 0}, {-2, -1}, {1, 2} } // 3 >> 2
            }
        };


    T_Tetromino::T_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {0, 0};
        blocks[1] = {1, 0};
        blocks[2] = {-1, 0};
        blocks[3] = {0, 1};
        
        origin = {grid.width()/2 - 1, grid.height()-2};
    }

    Coord (*T_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return JLSTZ_wk_off;
    }

    J_Tetromino::J_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {0, 0};
        blocks[1] = {1, 0};
        blocks[2] = {-1, 0};
        blocks[3] = {-1, 1};

        origin = {grid.width()/2 - 1, grid.height()-2};
    }

    Coord (*J_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return JLSTZ_wk_off;
    }

    L_Tetromino::L_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {0, 0};
        blocks[1] = {1, 0};
        blocks[2] = {-1, 0};
        blocks[3] = {1, 1};

        origin = {grid.width()/2 - 1, grid.height()-2};
    }

    Coord (*L_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return JLSTZ_wk_off;
    }

    S_Tetromino::S_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {0, 0};
        blocks[1] = {-1, 0};
        blocks[2] = {1, 1};
        blocks[3] = {0, 1};

        origin = {grid.width()/2 - 1, grid.height()-2};
    }

    Coord (*S_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return JLSTZ_wk_off;
    }

    Z_Tetromino::Z_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {0, 0};
        blocks[1] = {1, 0};
        blocks[2] = {-1, 1};
        blocks[3] = {0, 1};

        origin = {grid.width()/2 - 1, grid.height()-2};
    }

    Coord (*Z_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return JLSTZ_wk_off;
    }

    O_Tetromino::O_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {-0.5, 0.5};
        blocks[1] = {-0.5, -0.5};
        blocks[2] = {0.5, -0.5};
        blocks[3] = {0.5, 0.5};

        origin = {grid.width()/2 - 0.5, grid.height() - 1.5};
    }

    Coord (*O_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return nullptr;
    }

    I_Tetromino::I_Tetromino(Grid const& grid) : Tetromino(grid)
    {
        blocks[0] = {-1.5, 0.5};
        blocks[1] = {-0.5, 0.5};
        blocks[2] = {0.5, 0.5};
        blocks[3] = {1.5, 0.5};

        origin = {grid.width()/2 - 0.5, grid.height() - 2.5};
    }

    Coord (*I_Tetromino::wall_kick_offsets() const noexcept)[4][4] {
        return I_wk_off;
    }


    std::unique_ptr<Tetromino> newTetromino(Tetromino::Kind kind, Grid const& grid)
    {
        switch(kind)
        {
            case Tetromino::I:
                return std::make_unique<I_Tetromino>(grid);
            case Tetromino::O:
                return std::make_unique<O_Tetromino>(grid);
            case Tetromino::J:
                return std::make_unique<J_Tetromino>(grid);
            case Tetromino::L:
                return std::make_unique<L_Tetromino>(grid);
            case Tetromino::S:
                return std::make_unique<S_Tetromino>(grid);
            case Tetromino::Z:
                return std::make_unique<Z_Tetromino>(grid);
            case Tetromino::T:
                return std::make_unique<T_Tetromino>(grid);
            default:
                throw std::logic_error("Invalid value of Tetromino::Kind");
        }
    }
}