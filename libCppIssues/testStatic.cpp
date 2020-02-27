#include <eigen3/Eigen/Dense>
#include <iostream>


class Abc
{
    private:
    public:
        Eigen::Vector3d a;
        static int b;

        Abc()
        {
           //a={0,0,0};
           //b=1;
        }

        static void printa()
        {
           std::cout<<b<<std::endl;
        }
};

int main()
{
    Abc abc;
    abc.b++;
    abc.printa();
    return 0;
}

