//�������
//������������дһ������
//����������Shape������������5�������ࣺ
//Circle��Բ�Σ���Square�������Σ���Rectangle�����Σ���Trapeziod�����Σ���
//Triangle�������Σ������麯���ֱ���㼸��ͼ�ε������
//�������ǵĺͣ���ź͵ı�������Ϊ��̬��Ա����Ҫ���û���ָ�����飬
//ʹ����ÿһ��Ԫ��ָ��һ�����������
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
//԰
class Circle :public Shape {
public:
	Circle(double ra):Shape(ra,0,0){
	
	}
	virtual void area() {
		double area = PI*getr() * getr();
		cout <<"the area of sphere is:"<< area << endl;
	}
};
//������
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
//����
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
//��
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
//������
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