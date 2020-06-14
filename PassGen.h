/** 
* @file PassGen.h
* @author Сергеев В.Ю.
* @version 1.0
* @date 12.20.2020
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля PassGen
*/
#pragma once
#include <iostream>
#include <cassert>
#include <random>
#include <string>
#include <vector>
#include <cstdlib> // для функций strtol, exit
#include <unistd.h> // для функции getopt
using namespace std;

/** 
* @brief Генератор паролей
* @details В конструкторе передаются аргументы командной строки.
*/
class Opts
{
private:
	
// константы с пределами значений
    static constexpr int minLen = 8;
    static constexpr int maxLen = 40;
    static constexpr int minNum = 1;
    static constexpr int maxNum = 20;
	
	const std::string set_alpha = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
	const std::string set_digit = "0123456789";
	const std::string set_special = ".,<>?!/|\\@#$%^&*()[]";
// атрибуты
    int passLen = minLen; // длина пароля
    int passNum = minNum; // количество паролей
    bool useNums = false; // использовавание цифр
    bool useAlpha = false; // использование букв
    bool useSign = false; // использование знаков
    void usage(const char* progName); //вывод подсказки и останов
public:
    Opts(int argc, char* argv[]); // конструктор
	string text_shuffling(int len, const string &letters);
	vector<string> passgen();
	// "геттеры" с результатами разбора параметров
    int getLen() const{return passLen;}   //длина пароля
    int getNum() const{return passNum;}   //кол-во паролей
    bool isNums() const{return useNums;}	// исп. цифр
    bool isAlpha() const{return useAlpha;}   // исп. букв
    bool isSign() const{return useSign;}   // исп. знаков
};

/** 
* @brief Класс обработки исключений.
*/
class gen_error: public std::invalid_argument
{
public:
	explicit gen_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit gen_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};