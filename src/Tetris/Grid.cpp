#include "Grid.hpp"


namespace Tetris
{

    Grid::Grid(uint32_t width, uint32_t height) :
        w{width}, h{height}, data_ptr{new uint32_t[w * h]} 
    {
        std::fill_n(data_ptr.get(), w*h, 0);
    }

    uint32_t& Grid::operator()(uint32_t x, uint32_t y) noexcept
    {
        return *ptr_to(x, y);
    }

    uint32_t const& Grid::operator()(uint32_t x, uint32_t y) const noexcept
    {
        return *ptr_to(x, y);
    }

    uint32_t Grid::width() const noexcept
    {
        return w;
    }

    uint32_t Grid::height() const noexcept
    {
        return h;
    }

    uint32_t* Grid::ptr_to(uint32_t x, uint32_t y) noexcept
    {
        return &data_ptr[y * w + x];
    }

    uint32_t const* Grid::ptr_to(uint32_t x, uint32_t y) const noexcept
    {
        return &data_ptr[y * w + x];
    }

    void Grid::clear_line(uint32_t line) noexcept
    {
        clear_lines(line, line + 1);
    }

    void Grid::clear_lines(uint32_t from, uint32_t to) noexcept
    {
        std::copy(ptr_to(0, to), data_ptr.get() + w * h, ptr_to(0, from));
    }

}