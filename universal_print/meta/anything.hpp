#pragma once


namespace {
    #include "types_converter.hpp"

    template <typename T>
    struct remove_all_const{
        typedef std::remove_cv_t<T> type;
    };

    template <typename T>
    struct remove_all_const<T*>{
        typedef typename remove_all_const<std::remove_cv_t<T>>::type* type;
    };

    template <typename T>
    struct remove_all_const<T* const>{
        typedef typename remove_all_const<std::remove_cv_t<T>>::type* type;
    };

    template<typename T>
    using remove_all_const_t = typename remove_all_const<T>::type;

} // end anonymous namespace

template <size_t index>
struct Anything
{
    size_t* m_ref;
    constexpr Anything(size_t* _ref) : m_ref(_ref) {};
    Anything() {};
    template <typename T>
    constexpr operator T() const noexcept
    {
        m_ref[index] = type_to_id<remove_all_const_t<T>>::get_id();
        return T{};
    }
};
