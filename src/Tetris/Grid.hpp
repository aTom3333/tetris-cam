#ifndef GRID_HPP
#define GRID_HPP


#include <memory>
//class représentant la grille logique du jeux
//
//Role : stock les blocks de tetrominos une fois qu'ils sont fixés
//permet de suprimer une ligne quand elle est pleine
//Auteur : Thomas FERRAND
namespace Tetris
{

    class Grid
    {
    public:
	//constructeur
        Grid(uint32_t width, uint32_t height);
		
	//accesseur
        uint32_t& operator()(uint32_t x, uint32_t y) noexcept;
        uint32_t const& operator()(uint32_t x, uint32_t y) const noexcept;
        
        uint32_t width() const noexcept;
        uint32_t height() const noexcept;

        uint32_t* ptr_to(uint32_t x, uint32_t y) noexcept;
        uint32_t const* ptr_to(uint32_t x, uint32_t y) const noexcept;
	//suprimme une ligne(s)
        void clear_line(uint32_t line) noexcept;
        void clear_lines(uint32_t from, uint32_t to) noexcept;

    private:
	//hauteur, largeur et pointeur vers un tableau d'entier
        uint32_t w;
        uint32_t h;
        std::unique_ptr<uint32_t[]> data_ptr;
    };
    

}

#endif // GRID_HPP