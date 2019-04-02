#ifndef GRID_HPP
#define GRID_HPP


#include <memory>

namespace Tetris
{

    class Grid
    {
    public:
        Grid(uint32_t width, uint32_t height);

        uint32_t& operator()(uint32_t x, uint32_t y) noexcept;
        uint32_t const& operator()(uint32_t x, uint32_t y) const noexcept;
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;

        uint32_t* ptr_to(uint32_t x, uint32_t y) noexcept;
        uint32_t const* ptr_to(uint32_t x, uint32_t y) const noexcept;

        void clear_line(uint32_t line) noexcept;
        void clear_lines(uint32_t from, uint32_t to) noexcept;

    private:
        uint32_t w;
        uint32_t h;
        std::unique_ptr<uint32_t[]> data_ptr;
    };
    

}

#endif // GRID_HPP