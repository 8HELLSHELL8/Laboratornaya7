#include <iostream>

using namespace std;

 ������� ��� �������� ������������ ������ �������
bool Verification(const string str, string templ, int index, bool& rezult) {
     ���� ������� ������ ��������� �� �������, ������������� ��������� � true � ���������� true
    if (templ == str) {
        rezult = true;
        return true;
    }
     ���� ������� ������ � ������� - '*', ������� ��� ��������� ���������
    else if (templ[index] == '*') {
         �������� �� ���� ��������� ������ ���������
        for (size_t i = 0; i + templ.size() < str.size() + 1; i++) {
             ���� ����� ��������� ����� 0, ��������� ������ ��� '*'
            if (i == 0) {
                Verification(str, templ.substr(0, index) + templ.substr(index + 1), index, rezult); // ������� ������������������
            }
             ��������� ��������� ����� i
            string tempStr(str.begin() + index, str.begin() + index + i + 1);
             ��������� ������ � ����������� ����������
            int check = Verification(str, templ.substr(0, index) + tempStr + templ.substr(index + 1), index + i, rezult);
             ���� ������������������ ��������� �������, ������������� ����
            if (check == 1) {
                break;
            }
        }
    }
     ���� ������� ������ � ������� - '?', �������� ��� ��������������� �������� �� ������
    else if (templ[index] == '?') {
        Verification(str, templ.substr(0, index) + str[index] + templ.substr(index + 1), index + 1, rezult);
    }
     ���� ������� ������� ������ � ������� ���������, ���������� ��������
    else if (str[index] == templ[index]) {
        Verification(str, templ, index + 1, rezult);
    }
    return false;
}

int main() {
     ���� ������
    cout << "Enter string: ";
    string str;
    cin >> str;

     ���� �������
    cout << "Enter template: ";
    string templ;
    cin >> templ;

    bool answer = false; // ���������� ��� �������� ����������

     ����� ������� ��������
    Verification(str, templ, 0, answer);

     ����� ����������
    cout << boolalpha << answer << endl; // �������������� ����� � ������ ��������
    return 0;
}
