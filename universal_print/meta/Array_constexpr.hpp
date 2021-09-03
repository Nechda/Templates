#pragma once
#include <initializer_list>
#include <array>


template<typename T,size_t N>
struct Array
{
    T m_data[N];
    constexpr T& operator[](size_t index) noexcept { return m_data[index]; }
    constexpr const T& operator[](size_t index) const noexcept { return m_data[index]; }
};