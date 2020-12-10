//抽象基类
//【问题描述】写一个程序，
//定义抽象基类Shape，由它派生出5个派生类：
//Circle（圆形）、Square（正方形）、Rectangle（矩形）、Trapeziod（梯形）、
//Triangle（三角形）。用虚函数分别计算几种图形的面积，
//并求它们的和（存放和的变量声明为静态成员）。要求用基类指针数组，
//使它的每一个元素指向一个派生类对象。
#include<iostream>
using namespace std;
#define PI 3.14
class Shape {
private:
	double radius;
	double height;
	double hiht;
	static double area1;
public:
	Shape(double ra,double he,double h) {
		radius = ra;
		height = he;
		hiht = h;
	}
	double getr() {
		return radius;
	}
	double geth() {
		return height;
	}
	double gethi() {
		return hiht;
	}
	virtual void area() {
	
	}
	double geta() {
		return area1;
	
	}
};
//园
class Circle :public Shape {
public:
	Circle(double ra):Shape(ra,0,0){
	
	}
	virtual void area() {
		double area = PI*getr() * getr();
		cout <<"the area of sphere is:"<< area << endl;
	}
};
//正方形
class Square :public Shape {
private:

public:
	Square(double ra) :Shape(ra,0,0) {}
	virtual void area() {
		double area = getr() * getr();
		cout << "the area of Square is:"<<area << endl;

	}
	virtual void volume() {
		double volume = 2 * PI * getr() * getr() * geth();
		cout << "the volume of Cylinder is:"<<volume << endl;
	}
};
//矩形
class Rectangle :public Shape {
private:
public:
	Rectangle(double ra, double he): Shape(ra,he,0){
	}
	virtual void area() {
		double area = getr() * geth();
		cout << "the area of Rectangle is:"<<area << endl;
	}
};
//梯
class Trapeziod :public Shape {
private:
public:
	Trapeziod(double ra, double he, double h) : Shape(ra,he,h) {
	}
	virtual void area() {
		double area = 0.5*(getr() + geth())*gethi();
		cout << "the area of Triangle is:" << area << endl;
	}
};
//三角形
class Triangle :public Shape {
private:
public:
	Triangle(double re,double he) : Shape(re, he,0) {
	}
	virtual void area() {
		double area =  0.5*getr() * geth();
		cout << "the area of Triangle is:" << area << endl;
	}
};
int main() {
	double a, b,c;
	cin>>a>>b>>c;
	Circle p1(a);
	Square p2(a);
	Rectangle p3(a,b);
	Trapeziod p4(a,b,c);
	Triangle p5(a,c);
	Shape *p[5] = {&p1,&p2,&p3,&p4,&p5};
	for (int i = 0; i < 5; i++) {
		p[i]->area();
	}
	return 0;
}