/*
 * hash table implemented as array of linked list
 */

#include <iostream>
#include <vector>
#include <forward_list>
#include <list>
#include <functional>
#include <common/common.hpp>

struct Complex
{
    friend std::ostream& operator<<(std::ostream& os, const Complex& num);

    double realcomp;
    double imagcomp;

};
std::ostream& operator<<(std::ostream& os, const Complex& num)
{
    os<<num.realcomp<<"+ i"<<num.imagcomp<<std::flush;
    return os;
}

template<typename KeyT>
struct StdHashing
{
    unsigned long operator()(const KeyT& key, const size_t &tableSize) const
    {
        return reinterpret_cast<unsigned long>(std::hash<KeyT>{}(key)%tableSize);
    }

};

template<typename KeyT, typename ValT>
class HashNode
{
public:
    HashNode(KeyT key, ValT val)
    {
        try
        {
            m_Key=key;
            m_Val=val;
        } 
        catch(...)
        {
            std::cout<<"copy constructor needed"<<std::endl;
            throw;
        }
    }

    KeyT GetKey()
    {
        return m_Key;
    }

    ValT GetValue()
    {
        return m_Val;
    }

private:
    KeyT m_Key;
    ValT m_Val;

};

template<typename KeyT, typename ValT, typename HashFn= StdHashing<KeyT>>
class HashTable
{
public:
    HashTable(size_t size)
    {
       m_HashTable.resize(size); 
    }

    ~HashTable(){}
    
    HashTable GetHashTable()
    {
        return m_HashTable;
    }

    void Insert(KeyT key, ValT val)
    {
        m_HashTable[m_HashFn(key, m_HashTable.size())].push_back(HashNode<KeyT, ValT>{key,val});
    }

    void Print()
    {
        size_t vecCount=0;
        for (auto vecIter: m_HashTable)
        {
            std::cout<<vecCount <<"/"<<m_HashTable.size()<<std::flush;
            for (auto listIter: vecIter)
            {
                std::cout<<"\t["<<listIter.GetKey()<<", "<<listIter.GetValue()<<"]"<<std::flush;
            }
            vecCount++;
            std::cout<<std::endl;
        }
    }

private:
    HashFn m_HashFn; 
    std::vector<std::list<HashNode<KeyT, ValT>>> m_HashTable;

};

