#include <iostream>
#include "dynamicArray.cpp"
#include "hashTable.cpp"

int main(int argc, char* argv[])
{
    std::cout<<"Test 1"<<std::endl;
    HashTable<std::string, int> ht1(5);
    ht1.Insert("hi", 10320);
    ht1.Insert("abc", 980);
    ht1.Insert("aa", 897);
    ht1.Insert("qs",897);
    ht1.Insert("pl",63);
    ht1.Print();

    std::cout<<"Test 2"<<std::endl;
    HashTable<std::string, Complex> ht2(5);   
    Complex c1{1.2, 2.0};
    ht2.Insert("helloWorld", c1);
    ht2.Print();

    std::cout<<"Test 3"<<std::endl;
    HashTable<std::string, std::vector<Complex>> ht3(5);
    std::vector<Complex> complexVec;
    complexVec.push_back(Complex{1.2,2.0});
    ht3.Insert("helloWorld",complexVec);
    ht3.Print();//you can't print a vector<> without having to implement an overloaded operator

    DynamicArray<int> arr;
    arr.Push(2);
    arr.Push(4);
    arr.Push(3);
    arr[1]=5;
    arr.Pop();
    arr.Pop();
    std::cout<<arr<<std::endl;
    arr[2]=3;
    return 0;

}
