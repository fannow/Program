#include<iostream>
#include<math.h>
using namespace std;
class Point {
private:
	double x;
	double y;
public:
	Point(double x1, double y1) {
		x = x1;
		y = y1;
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
};
double show(Point p1, Point p2) {
	return sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY() - p2.getY()) * (p1.getY() - p2.getY()));
}
int main() {
	double m, n, a, b;
	cout << "请输入第一个点坐标";
	cin >> m >> n;
	cout << "请输入第二个点坐标";
	cin >> a >> b;
	Point p1(m, n);
	Point p2(a, b);
	cout <<"The distance of Point A(" << p1.getX()<<","<<p1.getY() << ") and Point B(" << p2.getX()<<","<< p2.getY() << ") is " << sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) + (p1.getY() - p2.getY()) * (p1.getY() - p2.getY())) << endl;
	return 0;
}

