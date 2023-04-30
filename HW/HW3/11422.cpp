#include <iostream>
#include <string>
#include <math.h>
namespace oj
{
	class Shape 
	{	
	public:
		double getArea();
		double getPerimeter();
	
	protected:
		void setArea(double a);
		void setPerimeter(double p);
			
	private:
		double area;
		double perimeter;
	};

	class Triangle : public Shape
	{
	public:
		Triangle(double edge1, double edge2, double edge3);
		
	private:
		double edge1;
		double edge2;
		double edge3;
		
	};

	class Rectangle : public Shape
	{
	public:
		Rectangle(double width, double height);
		
	private:
		double width;
		double height;
	};

	class Circle : public Shape
	{
	public:
		Circle(double radius, double pi);
		
	private:
		double radius;
		double pi;
	};
}

using namespace std;

namespace oj
{   
    void Shape::setArea(double a)
    {
        area = a;
    }

    void Shape::setPerimeter(double p)
    {
        perimeter = p;
    }

    double Shape::getArea()
    {
        return area;
    }

    double Shape::getPerimeter()
    {
        return perimeter;
    }
}


int main(void)
{   
    using namespace oj;

    string s;
    double a, b, c;
    double totalArea = 0.0, totalPerimeter = 0.0;

    while(cin >> s) {
        if(s == "Triangle") {
            cin >> a >> b >> c;
            Triangle T(a, b, c);
            totalArea += T.getArea();
            totalPerimeter += T.getPerimeter();
        }
        if(s == "Rectangle") {
            cin >> a >> b;
            Rectangle R(a, b);
            totalArea += R.getArea();
            totalPerimeter += R.getPerimeter();
        }
        if(s == "Circle") {
            cin >> a >> b;
            Circle C(a, b);
            totalArea += C.getArea();
            totalPerimeter += C.getPerimeter();
        }
    }

    cout << totalArea << endl;
    cout << totalPerimeter << endl;


    return 0;
}
using namespace oj;
Triangle::Triangle(double edge1, double edge2, double edge3){
    if(edge1<=0||edge2<=0||edge3<=0||edge1+edge2<=edge3||edge1+edge3<=edge2||edge2+edge3<=edge1){
        this->edge1 = this->edge2 = this->edge3 = 0;
        setArea(0); setPerimeter(0);
    }
    else{
        this->edge1 = edge1;
        this->edge2 = edge2;
        this->edge3 = edge3;
        double s = (edge1+edge2+edge3)/2;
        setArea(sqrt(s*(s-edge1)*(s-edge2)*(s-edge3)));
        setPerimeter(edge1+edge2+edge3);
    }
}

Circle::Circle(double radius, double pi){
    if(radius>0){
        this->radius = radius;
        this->pi = pi;
        setArea(radius*radius*pi);
        setPerimeter(2*radius*pi);
    }
    else{
        this->radius = 0;
        this->pi = pi;
        setArea(0);
        setPerimeter(0);
    }
}

Rectangle::Rectangle(double width, double height){
    if(height<=0||width<=0){
        this->height = this->width = 0;
        setArea(0);
        setPerimeter(0);
    }
    else{
        this->height = height;
        this->width = width;
        setArea(height*width);
        setPerimeter(2*(height+width));
    }
}