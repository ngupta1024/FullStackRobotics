#include <iostream>

// lesson learnt: an operator overload is needed if you are going to bitwise or a custom type
// overloading | doesn't let |= will work
// at work, this thing got compiled without errors and did not even throw a runtime error
// but DID NOT WORK. IT DID NOTHING.

template<class flagtype>
flagtype GetOR(flagtype a, flagtype b)
{
    a=static_cast<flagtype>(static_cast<uint8_t>(a)|static_cast<uint8_t>(b));
    //a= a|b;
    return a;
}

int main()
{
    enum flag: uint8_t
    {
        ON=3,
        OFF=4
    };

   flag a =flag::OFF;
   flag b =flag::ON;
   std::cout<<(a | b)<<std::endl;
   a=GetOR(a,b);
   std::cout<<static_cast<unsigned int>(a)<<std::endl;
}
