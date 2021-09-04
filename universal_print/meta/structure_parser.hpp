#pragma once
#include <utility>
#include <stdint.h>
#include <tuple>
#include <array>


namespace tools
{
    namespace {
        #include "anything.hpp"
        #include "array_constexpr.hpp"
        #include "types_converter.hpp"
    } // end anonymous namespace

    namespace {

        template <typename T, size_t ... I>
        constexpr Array<size_t, sizeof ... (I)> get_array_of_types(std::index_sequence<I ...>) noexcept
        {
            std::size_t types[sizeof ... (I)]{};
            T obj_for_reading{ Anything<I>(types) ... };
            return Array<size_t, sizeof ... (I)>{types[I] ...};
        }

        template <typename T, size_t ... I>
        constexpr auto make_tuple_by_array(std::index_sequence<I ...>) noexcept
        {
            constexpr Array<size_t, sizeof ... (I)> arr_of_types { get_array_of_types<T>(std::make_index_sequence<sizeof ... (I)>{})[I]... };
            return std::tuple<typename std::remove_reference<typename id_to_type<arr_of_types[I]>::type>::type ...>{};
        }

        template <typename T, size_t ... I>
        constexpr void check_fileds(...) noexcept
        {
        }

        template <typename T, size_t ... I>
        constexpr auto check_fileds(size_t& out, std::index_sequence<I ...>) noexcept
            ->decltype(T{ Anything<I>{}... })
        {
            out = sizeof...(I);
            check_fileds<T>(out, std::make_index_sequence<sizeof ... (I) + 1>{});
            return T{};
        }

        template <typename T>
        constexpr size_t get_field_number() noexcept
        {
            size_t n_fields = 0;
            check_fileds<T>(n_fields, std::make_index_sequence<1>{});
            return n_fields;
        }

    } // end anonymous namespace

    /*
        Generating a tuple with the same fileds as in the given structure
    */
    template<typename T>
    constexpr auto make_tuple_by_structure() noexcept
    {
        constexpr size_t n_fields = get_field_number<T>();
        return make_tuple_by_array<T>(std::make_index_sequence<n_fields>{});
    }

    namespace {

        template <typename T, size_t ... I>
        constexpr auto get_offset(std::index_sequence<I ...>)
        {
            constexpr auto tuple_types = tools::make_tuple_by_array<T>(std::make_index_sequence<sizeof ... (I)>{});
            T tmp{
                get_poison<
                    std::remove_cv_t<
                        std::remove_reference_t<
                            decltype(std::get<I>(tuple_types))
                        >
                    >
                >(I, sizeof ... (I) - 1) ...
            };

            size_t result = 0;
            char* ptr = (char*)&tmp;
            for (result = 0; result < sizeof(T) && !ptr[result]; result++) {;;}
            return result;
        }

        template <typename T, size_t ... I>
        constexpr auto get_offsets_imp(std::index_sequence<I ...>)
        {
            std::array<size_t, sizeof ... (I)> offsets{ get_offset<T>(std::make_index_sequence<I + 1>{}) ... };
            return offsets;
        }

    } // end anonymous namespace

    /* 
        Getting offsets of each structure's field
    */
    template <typename T>
    constexpr auto get_offsets()
    {
        constexpr size_t n_fields = tools::get_field_number<T>();
        return get_offsets_imp<T>(std::make_index_sequence<n_fields>{});
    }
    // =====================
}