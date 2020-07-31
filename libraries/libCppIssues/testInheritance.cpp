#include <iostream>
#include <memory>

class Shape
{
public:
    Shape()
    {
    }

    ~Shape() {}

    virtual double GetInfo()
    {
        std::cout<<"this is just a shape"<<'\n';
        return 0.0;
    }
};

class Rectangle: public Shape
{
public:
    Rectangle()
    {
        m_Length=2.0;
        m_Width=5.0;
    }

    Rectangle(double length,double width)
        :m_Length(length),
         m_Width(width)
    {
    }

    bool isSquare()
    {
        return false;
    }

    virtual double GetInfo() override
    {
        std::cout<<"this is a rectangle"<<std::endl;
        return m_Width*m_Length;
    }

protected:
    int m_NumSides=4;
    double m_Length;
    double m_Width;
};


class Square: public Rectangle
{
public:

    virtual double GetInfo()
    {
        std::cout<<"this is a square"<<std::endl;
        return m_Width*m_Length;
    }
};

int main()
{    
//    {
//        auto squareObj= std::make_shared<Square>();
//        auto rectObj= std::dynamic_cast<std::shared_ptr<Rectangle>>(squareObj);
//        if (!rectObj)
//        {
//            std::cout<<"So, child to parent didn't work"<<'\n';
//        }
//        else
//        {
//            std::cout<<rectObj->GetInfo()<<std::endl;
//        }
//
//        auto shapeObj = std::dynamic_pointer_cast<Rectangle>(squareObj);
//        if (!shapeObj)
//        {
//            std::cout<<"So, child to parent didn't work"<<'\n';
//        }
//        else
//        {
//            std::cout<<shapeObj->GetInfo()<<std::endl;
//        }
//        auto rectObj_revert = std::dynamic_pointer_cast<Rectangle>(shapeObj);
//        if (!squareObj)
//        {
//            std::cout<<"So, parent to child didn't work"<<'\n';
//        }
//        else
//        {
//            std::cout<<rectObj_revert->GetInfo()<<std::endl;
//        }
//    }
    
    {
        std::shared_ptr<Shape> shapeObj = std::make_shared<Rectangle>(3.0, 4.0);
        //auto rectObj = std::dynamic_pointer_cast<Rectangle>(shapeObj);
        if (!shapeObj)
        {
            std::cout<<"So, parent to child didn't work"<<'\n';
        }
        else
        {
            std::cout<<shapeObj->GetInfo()<<std::endl;
        }
    }
   
}
