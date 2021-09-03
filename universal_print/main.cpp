#include <iostream>
#include "universal_print.hpp"
#include "meta/Tested_structures.h"


void tets_print_strucures()
{

    MyString str{ 15, "hello" };
    tools::universal_print(str);
    std::cout << std::endl;
  
    Vec2 vector_2d{ -0.3f, 3.14f };
    tools::universal_print(vector_2d);

    iVec3 vector_3d{ 10, 3, '+' };
    tools::universal_print(vector_3d);
    std::cout << std::endl;

    Chars chrs{ '0','1','2', '3' };
    tools::universal_print(chrs);
    std::cout << std::endl;

    MySuperException except{ 1000, "Universal print testing" };
    tools::universal_print(except);
    std::cout << std::endl;

    Debug_location location {__FUNCTION__, __FILE__, __LINE__};
    tools::universal_print(location);
    std::cout << std::endl;

}

int main()
{
    tets_print_strucures();
    return 0;
}
