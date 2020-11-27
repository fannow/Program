#include<iostream>
#include<string.h>
using namespace std;
class Base {
private:
	string name;
	int age;
public:
	Base(string na, int ag) {
		name = na;
		age = ag;
	}
	void show() {
		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
	}
};
class Leader :virtual public Base {
protected:
	string post;
	string department;
public:
	Leader(string na, int ag, string np, string de):Base(na,ag) {
		post = np;
		department = de;
	}
	void show1() {
		cout << "Leader:" << endl;
		show();
		cout << "post:" << post << endl;
		cout << "department:" << department <<endl;
	}
};
class Engineer :virtual public Base {
protected:
	string nposition;
	string professional;
public:
	Engineer(string na, int ag, string np, string pr):Base(na,ag) {
		professional = pr;
		nposition = np;
	}
	void show2(){
		cout << "Engineer:" << endl;
		show();
		cout << "profession:" << nposition << endl;
		cout << "subject:" << professional << endl;
	}
};
class Chairman :public Leader, public Engineer {
public:
	Chairman(string na, int ag, string as, string pr,string np,string de) :Base(na,ag), Engineer(na, ag,as, pr), Leader(na, ag, np, de) {
	}
	void show3() {
		cout << "Chief Engineer:" << endl;
		show();
		cout << "post:" << post << endl;
		cout << "department:" << department << endl;
		cout << "profession:" << nposition << endl;
		cout << "subject:" << professional << endl;
	}
};
int main() {
	Leader p1("zhangsan",30,"manager","managerdepartment");
	Engineer p2("lisi",25,"Cengineer","Junior engineer");
	Chairman p3("Wangwu",45,"Senior engineer","Building design","President","Chanpinbu");
	p1.show1();
	p2.show2();
	p3.show3();



	return 0;
}