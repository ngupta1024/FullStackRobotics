#include <iostream>

constexpr int minCapacity = 0;
constexpr int growthFactor = 2;

template<typename T>
class DynamicArray
{
public:
    DynamicArray()
    {
       m_Capacity= minCapacity;
       m_Size = 0; 
       m_Data = (T*)malloc(m_Capacity * sizeof(*m_Data));
       if (!m_Data)
           throw std::bad_alloc();
    }

    ~DynamicArray()
    {
    }

    void Push(T datum)
    {
        if (m_Size>=m_Capacity)
            Resize();

        *(m_Data+m_Size++) = datum;
        std::cout<<m_Size<<"/"<<m_Capacity<<std::endl;
    }

    T Pop()
    {
        T tmp=*(m_Data+m_Size-1);
        m_Size--;
        return tmp;
    }

    T& operator[](size_t index)
    {
        if (index<m_Size) 
            return *(m_Data+index);
        throw std::runtime_error("accessing elements out of bounds\n");
    }

    T Get(size_t index)
    {
        return *(m_Data+index);
    }

    size_t Size()
    {
        return m_Size;
    }

    size_t Capacity()
    {
        return m_Capacity;
    }

    T operator*()
    {
        return *m_Data;
    }

    T* operator+(size_t rhs)
    {
        return m_Data+rhs;
    }

    template<class U>
    friend std::ostream& operator<< (std::ostream& os, const DynamicArray<U> & arr);
    
private:
    size_t Resize()
    {
        if (m_Capacity==0)
            m_Capacity =1;
        size_t capacity = m_Capacity* growthFactor;
        T* tmp = (T*)realloc(m_Data, capacity*sizeof(*m_Data));
        if (!tmp)
            throw std::bad_alloc();
        m_Data = tmp;
        m_Capacity= capacity;
    }

    size_t m_Size;
    size_t m_Capacity;
    T* m_Data;
};

template<typename T>
std::ostream& operator<< (std::ostream& os, DynamicArray<T> & arr)
{ 
    os<<"[";
    size_t iter=0;
    while (iter<arr.Size()-1)
    {
        os<<*(arr+iter++)<<", ";
    }
    os<<*(arr+iter)<<"]";
    return os;
}

//int main(int argc, char* argv[])
//{
//    DynamicArray<int> arr;
//    arr.Push(2);
//    arr.Push(4);
//    arr.Push(3);
//    arr[1]=5;
//    arr.Pop();
//    arr.Pop();
//    std::cout<<arr<<std::endl;
//    arr[2]=3;
//    return 0;
//}
