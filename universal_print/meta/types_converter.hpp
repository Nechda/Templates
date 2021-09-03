#pragma once

template <typename T>
struct type_to_id
{
    static constexpr size_t get_id()
    {
        return -1;
    }
};

template <size_t>
struct id_to_type
{
    using type = char;
};

template <size_t>
struct id_to_name
{
    static constexpr const char* get_name()
    {
        return "";
    }
};

#define REGISTER_TYPE(id_,type_)\
    template<> struct id_to_type<id_> { using type = type_; };\
    template<> constexpr size_t type_to_id<type_>::get_id() { return id_;};\
    template<> constexpr const char* id_to_name<id_>::get_name() {return #type_;};

template<typename T>
T get_poison(size_t index = 0, size_t dirty_index = 0)
{
    if(dirty_index == -1)
        dirty_index = 0;
    union
    {
        char bytes[sizeof(T)];
        T t;
    }data;
    char BITS = index == dirty_index ? 0xFF : 0x00;
    for (size_t i = 0; i < sizeof(T); i++)
        data.bytes[i] = BITS;
    return data.t;
}

REGISTER_TYPE(1, char)
REGISTER_TYPE(2, unsigned char)
REGISTER_TYPE(3, signed char)
REGISTER_TYPE(4, unsigned short)
REGISTER_TYPE(5, signed short)
REGISTER_TYPE(6, unsigned int)
REGISTER_TYPE(7, signed int)
REGISTER_TYPE(8, unsigned long)
REGISTER_TYPE(9, signed long)
REGISTER_TYPE(10, unsigned long long)
REGISTER_TYPE(11, signed long long)
REGISTER_TYPE(12, float)
REGISTER_TYPE(13, double)
REGISTER_TYPE(14, long double)
REGISTER_TYPE(15, char*)
#undef REGISTER_TYPE