#pragma		once

#include <algorithm>

namespace ft
{
//False type -----------------------------------------------------------------//
    template <class T> struct is_integral {static const bool value = false;};

//True type -----------------------------------------------------------------//
    template<> struct is_integral<bool>{static const bool value = true;};
    template<> struct is_integral<char>{static const bool value = true;};
   	//template<> struct is_integral<char16_t>{static const bool value = true;}; //REVIEW - c++11?
   	//template<> struct is_integral<char32_t>{static const bool value = true;}; //REVIEW - c++11?
    template<> struct is_integral<wchar_t>{static const bool value = true;};
    template<> struct is_integral<signed char>{static const bool value = true;};
    template<> struct is_integral<short int>{static const bool value = true;};
    template<> struct is_integral<int>{static const bool value = true;};
    template<> struct is_integral<long int>{static const bool value = true;};
    template<> struct is_integral<long long int>{static const bool value = true;};
    template<> struct is_integral<unsigned char>{static const bool value = true;};
    template<> struct is_integral<unsigned short int>{static const bool value = true;};
    template<> struct is_integral<unsigned int>{static const bool value = true;};
    template<> struct is_integral<unsigned long int>{static const bool value = true;};
    template<> struct is_integral<unsigned long long int>{static const bool value = true;};
}