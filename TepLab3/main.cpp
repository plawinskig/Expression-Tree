#include "tree.hpp"
#include <iostream>
#include <vector>

int main() 
{

    std::vector<int> vec = { 0,1,2,4,5 };
    vec.insert(vec.begin() + 3, 3);

    // 0 1 2 3 4 5


    for (auto i : vec)
    {
        std::cout << i << "\n";
    }

    return 0;
}