//商店销售某一商品，商店每天公布统一的折扣，同时允许销售人员在销售时灵活掌握售价，在此基础上，对一次购10件以上者，还可以享受9.8折优惠。现已知当天3个销售员的销售情况为：
//
//销货员号（num）   销货件数(quantity)   销货单价(price)
//
//101                                 5                            23.5
//
//102                                12                           24.56
//
//103                                100                         21.5
//
//请编程序，计算当日此商品和总销售款sum以及每件商品的平均售价。要求用静态数据成员和静态成员函数。
//
//提示：将折扣discout，总销售款sum和商品销售总件数n声明为静态数据成员，再定义静态成员函数average(平均售价)，和display(输出结果)
#include<iostream>
#include<string>
using namespace std;
class Sales {
private:
	string num;
	int quantity;
	float price;
	static double discout;
	static double sum;
	static int n;
public:
	Sales(string num1, int quantity1, float price1) {
		num = num1;
		quantity = quantity1;
		price = price1;
		if (quantity > 10) {
			sum = sum + quantity * price * discout;
		}
		else {
			sum = sum + quantity * price;
		}
		n = n + quantity;
	}
    static double average() {
		return sum / n;
	}
	static void display() {
		cout << "Average= " << average() << endl;
		cout << "Sum= " << sum << endl;
	}
};
double Sales::discout = 0.98;
double Sales::sum = 0.0;
int Sales::n = 0;
int main() {
	
	Sales p1("101",5,23.5);
	Sales p2("102",12,24.56);
	Sales p3("103",100,21.5);
	Sales::average();
	Sales::display();
	return 0;
}

