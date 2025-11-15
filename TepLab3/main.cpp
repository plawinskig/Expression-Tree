#include "tree.hpp"
#include <iostream>
#include <vector>

int main() 
{

    std::vector<int> vec;
    vec.assign(0, 5);

    for (auto i : vec)
    {
        std::cout << ">>> " << i << "\n";
    }

    std::cout << vec.empty();

    return 0;
}