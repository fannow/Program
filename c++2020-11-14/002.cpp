//编写一个程序设计一个汽车类vehicle，
//包含的数据成员有车轮个数wheels和车重weight。
//小车类car是它的派生类其中包含载人数passenger_load。
//卡车类truck是vehicle的派生类其中包含载人数passenger_load
//和载重量payload，每个类都有相关数据的输出方法。
#include<iostream>
using namespace std;
class Vehicle {
private:
	int wheels;
	int weight;
public:
	Vehicle(int w1, int w2) {
		wheels = w1;
		weight = w2;
	}
	void show2(){
			cout << "wheels=" << wheels << ";" << "weight=" << weight << endl;
	}
};
class Car :private Vehicle {
private:
	int passenger_load;
public:
	Car(int w1, int w2, int p) :Vehicle(w1,w2){
		passenger_load = p;
	}
	void show() {
		cout << "the information of car:" << endl;
		show2();
		cout << "passenger_load=" << passenger_load << endl;
	}
};
class Truck :protected Vehicle {
private:
	int passenger_load;
	int payload;
public:
	Truck(int w1,int w2, int p,int pa) :Vehicle(w1, w2) {
		passenger_load = p;
		payload = pa;
	}
	void show1() {
		cout << "the information of truck:" << endl;
		show2();
		cout << "passenger_load =" << passenger_load <<";"<< "pay_load="<< payload<<endl;
	}
};
int main() {
	int a, b, c, d, e,f,g;
	cin >> a >> b >> c >> d >> e>>f>>g;
	Car p1(a, b, c);
	Truck p2(d, e, f, g);
	p1.show();
	p2.show1();
	return 0;
}


