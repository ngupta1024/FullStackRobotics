#include <iostream>
#include <memory>

class Shape
{
public:
    Shape()
    {
    }

    virtual ~Shape() {}

    virtual double GetInfo()
    {
        return 0.0;
    }
private:
    std::string m_Name;
};

class Rectangle: public virtual Shape
{
public:

    Rectangle()
    {
        //std::string shapeName= "Rectangle";
        //Shape sh(shapeName);
        m_Length=2.0;
        m_Width=5.0;
    }
    Rectangle(double length,double width)
        :m_Length(length),
         m_Width(width)
    {
    }

    virtual bool isSquare()
    {
        return false;
    }

    virtual double GetInfo()
    {
        std::cout<<"this is a rectangle"<<std::endl;
        return m_Width*m_Length;
    }

protected:
    int m_NumSides=4;
    double m_Length;
    double m_Width;
};


class Square: public virtual Rectangle, public virtual Shape
{
public:
    virtual bool isSquare()
    {
        return true;
    }

    virtual double GetInfo()
    {
        std::cout<<"this is a square"<<std::endl;
        return m_Width*m_Length;
    }
};

int main()
{    
    {
        auto squareObj= std::make_shared<Square>();
        auto rectObj= std::dynamic_pointer_cast<Rectangle>(squareObj);
        if (!rectObj)
        {
            std::cout<<"So, child to parent didn't work"<<'\n';
        }
        else
        {
            std::cout<<rectObj->GetInfo()<<std::endl;
        }

        auto shapeObj = std::dynamic_pointer_cast<Rectangle>(squareObj);
        if (!shapeObj)
        {
            std::cout<<"So, child to parent didn't work"<<'\n';
        }
        else
        {
            std::cout<<shapeObj->GetInfo()<<std::endl;
        }
        auto rectObj_revert = std::dynamic_pointer_cast<Rectangle>(shapeObj);
        if (!squareObj)
        {
            std::cout<<"So, parent to child didn't work"<<'\n';
        }
        else
        {
            std::cout<<rectObj_revert->GetInfo()<<std::endl;
        }
    }
    
    {
        auto shapeObj= std::make_shared<Shape>();
        auto rectObj = std::dynamic_pointer_cast<Rectangle>(shapeObj);
        if (!rectObj)
        {
            std::cout<<"So, parent to child didn't work"<<'\n';
        }
        else
        {
            std::cout<<rectObj->GetInfo()<<std::endl;
        }

    }
   
}
