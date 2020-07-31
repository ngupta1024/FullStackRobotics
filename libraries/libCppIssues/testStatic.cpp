#include <eigen3/Eigen/Dense>
#include <iostream>


class Abc
{
    private:
        static Eigen::Vector3d a;
        static int b;
    public:
        Abc()
        {
           a={0,0,0};
           b++;
        }

        void printa()
        {
           std::cout<<a<<std::endl;
        }

        void increaseB()
        {
            b++;
            std::cout<<b<<std::endl;
        }
};

int Abc::b= 1;
Eigen::Vector3d Abc::a{0,0,0};

int main()
{
    Abc abc;
    abc.increaseB();
    abc.printa();
    return 0;
}

