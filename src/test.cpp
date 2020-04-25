/**
 * 该文件用来测试一些例子的，可随时删除，不影响整个项目
 */

#include <iostream>
struct A
{
    int a;

    A()
    {
        int i[2];
        std::cout << &a << std::endl;
        std::cout << &i[0] << std::endl;
        std::cout  << &i[1] << std::endl;
    }
};


int main()
{

    A a;

    std::cin.get();
    return 0;
}