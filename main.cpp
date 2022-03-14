#include <iostream>
#include <vector>
#include "vector/vector.hpp"


#define LOG(X) std::cout << X << std::endl;
int main( void )
{
    std::vector<int>::iterator sysIt;
    std::vector<int>::iterator sysItEnd;
    std::vector<int>    sysvec;
    // sysvec.reserve(400);
    sysIt = sysvec.begin();
    sysItEnd = sysvec.end();
    sysvec.insert(sysvec.begin(), 12, 1337);
        for (sysIt = sysvec.begin(); sysIt != sysvec.end(); sysIt++)
        std::cout << *sysIt << std::endl;
    std::cout << "sysvec size     => " << sysvec.size() << std::endl;
    std::cout << "sysvec capacity => " << sysvec.capacity() << std::endl;
    // std::cout << "myvec max size => " << sysvec.max_size() << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    vector<int>::iterator it;
    vector<int> myvec;
    // myvec.resize(11, 13);
    // myvec.reserve(400);
    // myvec.assign(10, 13);
    // myvec.push_back(1337);
    // myvec.pop_back();
    myvec.insert(myvec.begin(), 12, 1337);

    for (it = myvec.begin(); it != myvec.end(); it++)
        std::cout << *it << std::endl;
    std::cout << "myvec size     => " << myvec.size() << std::endl;
    std::cout << "myvec capacity => " << myvec.capacity() << std::endl;
    // std::cout << "myvec max size => " << myvec.max_size() << std::endl;
    // std::cout << "myvec.empty() => " << myvec.empty() << std::endl;
}