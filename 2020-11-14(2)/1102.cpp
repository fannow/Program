//�̵�����ĳһ��Ʒ���̵�ÿ�칫��ͳһ���ۿۣ�ͬʱ����������Ա������ʱ��������ۼۣ��ڴ˻����ϣ���һ�ι�10�������ߣ�����������9.8���Żݡ�����֪����3������Ա���������Ϊ��
//
//����Ա�ţ�num��   ��������(quantity)   ��������(price)
//
//101                                 5                            23.5
//
//102                                12                           24.56
//
//103                                100                         21.5
//
//�����򣬼��㵱�մ���Ʒ�������ۿ�sum�Լ�ÿ����Ʒ��ƽ���ۼۡ�Ҫ���þ�̬���ݳ�Ա�;�̬��Ա������
//
//��ʾ�����ۿ�discout�������ۿ�sum����Ʒ�����ܼ���n����Ϊ��̬���ݳ�Ա���ٶ��徲̬��Ա����average(ƽ���ۼ�)����display(������)
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

