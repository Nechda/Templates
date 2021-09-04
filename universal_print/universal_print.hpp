#pragma once
#include "meta/structure_parser.hpp"
#include <iomanip>

namespace tools {

    namespace {

        template<size_t I, size_t N>
        struct print_imp_collection
        {
            template <typename T, typename Tulpe_of_types, size_t N_ = N>
            static void print(const char* addr, Tulpe_of_types tuple, std::array<size_t, N_> offsets)
            {
                typedef typename std::remove_cv<typename std::remove_reference<decltype(std::get<I>(tuple))>::type>::type elem_t;

                std::cout << std::setw(16) << id_to_name< type_to_id<typename remove_all_const<elem_t>::type>::get_id() >::get_name()
                    << " : " << *((elem_t*)(addr + offsets[I])) << std::endl;

                print_imp_collection<I + 1, N>::template print<T, Tulpe_of_types, N_>(addr, tuple, offsets);
            }
        };

        template <size_t I>
        struct print_imp_collection<I, I>
        {
            template <typename T, typename Tulpe_of_types, size_t N_>
            static void print(const char* addr, Tulpe_of_types tuple, std::array<size_t, N_> offsets) {}
        };

    } // end anonymous namespace

    template<typename T>
    void universal_print(const T& value)
    {
        constexpr size_t n_fileds = get_field_number<T>();
        using types_collection = decltype(make_tuple_by_structure<T>());

        std::cout << "Fields number" << " : " << n_fileds << std::endl;
        std::cout << typeid(T).name() << " {" << std::endl;
        std::array<size_t, n_fileds> offsets = get_offsets<T>();
        print_imp_collection<0, n_fileds>::template print<T, types_collection, n_fileds>((const char*)&value, types_collection{}, offsets);
        std::cout << "}" << std::endl;
    }
    
} // end namespace tools