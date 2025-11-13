#include "tree.hpp"
#include <iostream>
#include <vector>

int main() 
{

    std::vector<int> vec = { 0,1,2,4,5 };
    vec.insert(vec.begin() + 3, 3);

    // 0 1 2 3 4 5

    //                  0123456789012
    std::string form = "abc_def_gh_i";

    std::vector<std::string> vecstr = Tree::split(form, "_");

    for (auto i : vecstr)
    {
        std::cout << i << "\n";
    }

    return 0;
}