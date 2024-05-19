#include <iostream>

using namespace std;

 Функция для проверки соответствия строки шаблону
bool Verification(const string str, string templ, int index, bool& rezult) {
     Если текущий шаблон совпадает со строкой, устанавливаем результат в true и возвращаем true
    if (templ == str) {
        rezult = true;
        return true;
    }
     Если текущий символ в шаблоне - '*', пробуем все возможные подстроки
    else if (templ[index] == '*') {
         Проходим по всем возможным длинам подстроки
        for (size_t i = 0; i + templ.size() < str.size() + 1; i++) {
             Если длина подстроки равна 0, проверяем шаблон без '*'
            if (i == 0) {
                Verification(str, templ.substr(0, index) + templ.substr(index + 1), index, rezult); // нулевая последовательность
            }
             Формируем подстроку длины i
            string tempStr(str.begin() + index, str.begin() + index + i + 1);
             Проверяем шаблон с добавленной подстрокой
            int check = Verification(str, templ.substr(0, index) + tempStr + templ.substr(index + 1), index + i, rezult);
             Если последовательность подобрана успешно, останавливаем цикл
            if (check == 1) {
                break;
            }
        }
    }
     Если текущий символ в шаблоне - '?', заменяем его соответствующим символом из строки
    else if (templ[index] == '?') {
        Verification(str, templ.substr(0, index) + str[index] + templ.substr(index + 1), index + 1, rezult);
    }
     Если текущие символы строки и шаблона совпадают, продолжаем проверку
    else if (str[index] == templ[index]) {
        Verification(str, templ, index + 1, rezult);
    }
    return false;
}

int main() {
     Ввод строки
    cout << "Enter string: ";
    string str;
    cin >> str;

     Ввод шаблона
    cout << "Enter template: ";
    string templ;
    cin >> templ;

    bool answer = false; // Переменная для хранения результата

     Вызов функции проверки
    Verification(str, templ, 0, answer);

     Вывод результата
    cout << boolalpha << answer << endl; // преобразование цифры в булево значение
    return 0;
}
