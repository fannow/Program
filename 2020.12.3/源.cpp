#include<iostream>
using namespace std;
class Time {
private:
	int hours;
	int minutes;
	int seconds;
public:
	Time() {}
	Time(int h, int m, int s) {
		hours = h;
		minutes = m;
		seconds = s;
	}
	friend Time operator+(Time p1, Time p2);
	friend ostream& operator<<(ostream& output, Time p);
};
Time operator+(Time p1, Time p2) {
	Time p;
	p.hours = p1.hours + p2.hours;
	p.minutes = p1.minutes + p2.minutes;
	p.seconds = p1.seconds + p2.seconds;
	if (p.seconds > 59) {
		p.seconds -= 59;
		p.minutes += 1;
	}
	if (p.minutes > 59) {
		p.minutes -= 59;
		p.hours += 1;
	}
	return p;
}
ostream& operator<<(ostream& output, Time p) {
	output << p.hours << ":";
	output << p.minutes << ":";
	output << p.seconds << endl;
	return output;
}
int main() {
	int a, b, c;
	cout << "请输入第一个时间的时，分，秒:" << endl;
	cin >> a >> b >> c;
	int x, y, z;
	cout << "请输入第二个时间的时，分，秒:" << endl;
	cin >> x >> y >> z;
	Time q1(a, b, c), q2(x, y, z), q;
	q = q1 + q2;
	cout << "Time one is:" << q1 << endl;
	cout << "Time two is:" << q2 << endl;
	cout << "Two time add is:" << q << endl;
	return 0;
}