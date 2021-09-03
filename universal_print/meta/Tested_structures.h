#pragma once

struct MyString
{
    int size = 0;
    const char* data;
};

struct iVec3
{
    int x;
    unsigned long y;
    char z;
};

struct MySuperException
{
    size_t error_code;
    const char* msg;
};

struct Vec2
{
    float x;
    double y;
};

struct Chars
{
    char first;
    char second;
    char third;
    char last;
};

struct Debug_location
{
    const char* function;
    const char* file;
    unsigned line;
};