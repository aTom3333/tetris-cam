#ifndef FIXED_POINT_HPP
#define FIXED_POINT_HPP


#include <cstdint>


//class représentant un reel a virgule fixe 
//avec toutes les methodes de comparaison et de combinaison
//Role : represente l'origine des tetrominos et les coordonées des blocks par rapport à l'origine
//Exemple : le carré a pour origine une intersection de blocks donc un nombre non-entier
//Auteur : Thomas FERRAND
template<typename T, uint8_t decimals>
class fixed_point
{
public:
	//constructeur
    constexpr fixed_point() noexcept = default;
    constexpr fixed_point(double a) noexcept;
    
    constexpr operator double() const noexcept;
    
	//Methode de combinaison
    constexpr fixed_point& operator+=(fixed_point);
    constexpr fixed_point& operator-=(fixed_point);
    constexpr fixed_point& operator*=(fixed_point);
    constexpr fixed_point& operator/=(fixed_point);

	//Methode de comparaison
    //friend constexpr bool operator==(fixed_point, fixed_point);
    //friend constexpr bool operator<(fixed_point, fixed_point);
    //friend constexpr bool operator>(fixed_point, fixed_point);
    //friend constexpr bool operator<=(fixed_point, fixed_point);
    //friend constexpr bool operator>=(fixed_point, fixed_point);
    
private:
    T underlying;
};

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals>::fixed_point(double a) noexcept :
    underlying(a * (1 << decimals))
{}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals>::operator double() const noexcept
{
    return static_cast<double>(underlying) / (1 << decimals);
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals>& fixed_point<T, decimals>::operator+=(fixed_point other)
{
    underlying += other.underlying;
    return *this;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals>& fixed_point<T, decimals>::operator-=(fixed_point other)
{
    underlying -= other.underlying;
    return *this;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals>& fixed_point<T, decimals>::operator*=(fixed_point other)
{
    underlying = (underlying * other.underlying) >> 2;
    return *this;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals>& fixed_point<T, decimals>::operator/=(fixed_point other)
{
    underlying /= (other.underlying >> decimals);
    return *this;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals> operator+(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
{
    return a+=b;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals> operator-(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
{
    return a-=b;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals> operator*(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
{
    return a*=b;
}

template<typename T, uint8_t decimals>
constexpr fixed_point<T, decimals> operator/(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
{
    return a/=b;
}

//template<typename T, uint8_t decimals>
//constexpr bool operator==(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
//{
//    return a.underlying == b.underlying;
//}
//
//template<typename T, uint8_t decimals>
//constexpr bool operator!=(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
//{
//    return a.underlying != b.underlying;
//}
//
//template<typename T, uint8_t decimals>
//constexpr bool operator<(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
//{
//    return a.underlying < b.underlying;
//}
//
//template<typename T, uint8_t decimals>
//constexpr bool operator<=(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
//{
//    return a.underlying <= b.underlying;
//}
//
//template<typename T, uint8_t decimals>
//constexpr bool operator>(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
//{
//    return a.underlying > b.underlying;
//}
//
//template<typename T, uint8_t decimals>
//constexpr bool operator>=(fixed_point<T, decimals> a, fixed_point<T, decimals> b)
//{
//    return a.underlying >= b.underlying;
//}


#endif // FIXED_POINT_HPP
