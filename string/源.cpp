#include<iostream>
#include<string>
using namespace std;
int main() {
    string str;
    getline(cin, str);
    int count = 0;
    for (int i = 0; i <str.size(); i++) {
        cout << str[i] << endl;
    }
        for (size_t i = str.size()-1; i > 0; i--) {
            if (str[i] != ' ') {
                count++;
            }
            else if (str[i] == ' ') {
                break;
            }
        }
    cout << count << endl;
    return 0;
}