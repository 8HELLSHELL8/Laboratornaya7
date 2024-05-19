#include <iostream>
#include <string>
using namespace std;

// Функция для выполнения вычисления выражения, записанного в виде строки
int evaluate(const string& expr) {
    int result = 0; // Инициализируем результат
    int number = 0; // Инициализируем текущее число
    int sign = 1;   // 1 для '+' и -1 для '-'

    // Проходим по каждому символу в строке
    for (size_t i = 0; i < expr.size(); ++i) {
        if (isdigit(expr[i])) {
            // Если символ является цифрой, добавляем его к текущему числу
            number = number * 10 + (expr[i] - '0');
        }
        else {
            // Если символ не является цифрой (это знак), добавляем текущее число к результату
            result += sign * number;
            number = 0; // Сбрасываем текущее число
            // Обновляем знак в зависимости от текущего символа
            sign = (expr[i] == '+') ? 1 : -1;
        }
    }
    // Добавляем последнее число к результату
    result += sign * number;

    return result; // Возвращаем результат
}

// Рекурсивная функция для генерации всех возможных выражений и их проверки
void findExpressions(string expr, const string& digits, int target, size_t pos, bool& found) {
    if (pos == digits.size()) {
        // Если достигнут конец строки digits
        if (evaluate(expr) == target) {
            // Если результат выражения равен целевому числу, выводим выражение
            cout << expr << endl;
            found = true; // Обновляем флаг найденного выражения
        }
        return; // Завершаем текущий вызов
    }

    // Добавляем цифру без знака
    findExpressions(expr + digits[pos], digits, target, pos + 1, found);

    // Добавляем цифру со знаком '+'
    findExpressions(expr + '+' + digits[pos], digits, target, pos + 1, found);

    // Добавляем цифру со знаком '-'
    findExpressions(expr + '-' + digits[pos], digits, target, pos + 1, found);
}

int main() {
    int m;
    cout << "Input your number: "; // Запрашиваем у пользователя ввод числа
    cin >> m;

    string digits = "123456789"; // Исходная строка цифр
    bool found = false; // Флаг для отслеживания найденного выражения

    // Начинаем рекурсию с первой цифры
    findExpressions(string(1, digits[0]), digits, m, 1, found);

    // Если ни одно выражение не было найдено, выводим сообщение
    if (!found) {
        cout << "Number cannot be achieved!" << endl;
    }

    return 0;
}
