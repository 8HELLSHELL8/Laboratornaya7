# Laboratornaya7
Цели и задачи работы: изучение рекурсивного программирования, методов разработки эффективных алгоритмов.
Задание к работе: написать программу решения задачи в соответствии с индивидуальным вариантом.
Задание 1. Дано число m. Требуется в последовательности цифр 1 2 3 4 … 9 расставить знаки «+» и «-» так, чтобы значением получившегося выражения было число m. Например, m=122. Знаки расставляются как 12+34-5-6+78+9.
Задание 2. Имея входную строку (s) и шаблон (p), реализуйте сопоставление шаблонов с подстановочными знаками с поддержкой '?' и '*' где: '?' соответствует любому одиночному символу, '*' соответствует любой последовательности символов (включая пустую последовательность). Сопоставление должно охватывать всю входную строку (не частичную).
Задание №1
Листинг программы на языке C++:
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

Результат работы программы:
   
Листинг программы на языке Go:
package main
import (
	"fmt"
	"strconv"
	"unicode"
)

// Function to evaluate the expression represented as a string
func evaluate(expr string) int {
	result := 0
	number := 0
	sign := 1

	for i := 0; i < len(expr); i++ {
		if unicode.IsDigit(rune(expr[i])) {
			num, _ := strconv.Atoi(string(expr[i]))
			number = number*10 + num
		} else {
			result += sign * number
			number = 0
			if expr[i] == '+' {
				sign = 1
			} else {
				sign = -1
			}
		}
	}
	result += sign * number
	return result
}

// Recursive function to generate and check all possible expressions
func findExpressions(expr string, digits string, target int, pos int, found *bool) {
	if pos == len(digits) {
		if evaluate(expr) == target {
			fmt.Println(expr)
			*found = true
		}
		return
	}

	// Add digit without sign
	findExpressions(expr+string(digits[pos]), digits, target, pos+1, found)

	// Add digit with '+' sign
	findExpressions(expr+"+"+string(digits[pos]), digits, target, pos+1, found)

	// Add digit with '-' sign
	findExpressions(expr+"-"+string(digits[pos]), digits, target, pos+1, found)
}

func main() {
	var m int
	fmt.Print("Input your number: ")
	fmt.Scan(&m)

	digits := "123456789"
	found := false

	// Start recursion with the first digit
	findExpressions(string(digits[0]), digits, m, 1, &found)

	// If no expression was found, output a message
	if !found {
		fmt.Println("Number cannot be achieved!")
	}
}
Результат работы программы:

      
Задание №2
Листинг программы на языке C++:
#include <iostream>

using namespace std;

// Функция для проверки соответствия строки шаблону
bool Verification(const string str, string templ, int index, bool& rezult) {
    // Если текущий шаблон совпадает со строкой, устанавливаем результат в true и возвращаем true
    if (templ == str) {
        rezult = true;
        return true;
    }
    // Если текущий символ в шаблоне - '*', пробуем все возможные подстроки
    else if (templ[index] == '*') {
        // Проходим по всем возможным длинам подстроки
        for (size_t i = 0; i + templ.size() < str.size() + 1; i++) {
            // Если длина подстроки равна 0, проверяем шаблон без '*'
            if (i == 0) {
                Verification(str, templ.substr(0, index) + templ.substr(index + 1), index, rezult); // нулевая последовательность
            }
            // Формируем подстроку длины i
            string tempStr(str.begin() + index, str.begin() + index + i + 1);
            // Проверяем шаблон с добавленной подстрокой
            int check = Verification(str, templ.substr(0, index) + tempStr + templ.substr(index + 1), index + i, rezult);
            // Если последовательность подобрана успешно, останавливаем цикл
            if (check == 1) {
                break;
            }
        }
    }
    // Если текущий символ в шаблоне - '?', заменяем его соответствующим символом из строки
    else if (templ[index] == '?') {
        Verification(str, templ.substr(0, index) + str[index] + templ.substr(index + 1), index + 1, rezult);
    }
    // Если текущие символы строки и шаблона совпадают, продолжаем проверку
    else if (str[index] == templ[index]) {
        Verification(str, templ, index + 1, rezult);
    }
    return false;
}

int main() {
    // Ввод строки
    cout << "Enter string: ";
    string str;
    cin >> str;

    // Ввод шаблона
    cout << "Enter template: ";
    string templ;
    cin >> templ;

    bool answer = false; // Переменная для хранения результата

    // Вызов функции проверки
    Verification(str, templ, 0, answer);

    // Вывод результата
    cout << boolalpha << answer << endl; // преобразование цифры в булево значение
    return 0;
}
	Результат работы программы:
   
Листинг программы на языке Go:
package main

import (
	"fmt"
)

// Function to check if the string matches the pattern
func Verification(str, templ string, index int, result *bool) bool {
	if templ == str {
		*result = true
		return true
	} else if index < len(templ) && templ[index] == '*' {
		for i := 0; i+len(templ) < len(str)+1; i++ {
			if i == 0 {
				Verification(str, templ[:index]+templ[index+1:], index, result) // zero-length sequence
			}
			tempStr := str[index : index+i+1]
			check := Verification(str, templ[:index]+tempStr+templ[index+1:], index+i, result)
			if check {
				break
			}
		}
	} else if index < len(templ) && templ[index] == '?' {
		if index < len(str) {
			Verification(str, templ[:index]+string(str[index])+templ[index+1:], index+1, result)
		}
	} else if index < len(templ) && index < len(str) && str[index] == templ[index] {
		Verification(str, templ, index+1, result)
	}
	return false
}

func main() {
	var str, templ string

	// Input string
	fmt.Print("Enter string: ")
	fmt.Scan(&str)

	// Input template
	fmt.Print("Enter template: ")
	fmt.Scan(&templ)

	answer := false // Variable to store the result

	// Call the verification function
	Verification(str, templ, 0, &answer)

	// Output the result
	fmt.Println(answer)
}

	Результат работы программы:
   

Вывод
В результате лабораторной работы было изучено рекурсивное программирование, методы разработки эффективных алгоритмов. Каждая программа проверена на представленных в задании исходных данных и выдает ожидаемый результат.

