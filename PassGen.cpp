/**
 * @file PassGen.cpp
 */
#include "PassGen.h"
/**
* @brief Конструктор класса Opts.
* @param В конструктор передаются и разбираются все аргументы командной строки.
* @throw gen_error, если произошла ошибка.
*/
Opts::Opts(int argc, char* argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "l:n:0ash")) != -1) {
        switch (opt) {
        case 'l':{ // длина пароля
            passLen = strtol(optarg,nullptr,10);
            if (passLen < minLen || passLen > maxLen) {
				optind = 1;
				throw gen_error(std::string("passLen must be from 8 to 40\n"));
            }
            break;
        }case 'n':{ // кол-во паролей
            passNum = strtol(optarg,nullptr,10);
            if (passNum < minNum || passNum > maxNum) {
				// если ошибка - сообщить и завершить
				optind = 1;			
                throw gen_error(std::string("passNum must be from 1 to 20\n"));
            }
            break;
        }case '0': // исп. цифры
            useNums = true;
            break;
        case 'a': // исп. буквы
            useAlpha = true;
            break;
        case 's': // исп. знаки
            useSign = true;
            break;
        case 'h': // -h help
        case '?': // неверный параметр
			throw gen_error(std::string("invalid argument\n"));
        case ':': // нет значения у параметра
			throw gen_error(std::string("invalid argument\n"));
			//usage(argv[0]); // сообщить и завершить
        }
    }
	if(opt == -1) optind = 1;
	// если не установлено ничего из алфавита - установить все
    if (!useNums && !useAlpha && !useSign) {
        useAlpha = useNums = useSign = true;
    }
}

/**
* @brief Метод text_shuffling.
* @details Перемешивает строку.
* @param len длинна новой строки
* @param letters строка символов из которых будет сгенерирована новая строка.
* @throw client_error, если произошла ошибка.
* @return Возвращет перемешанную строку указанной длины.
*/
std::string Opts::text_shuffling(int len, const std::string &letters) {
	if(letters.empty()) throw gen_error(std::string("empty string for passgen\n"));
	if(len == 0) throw gen_error(std::string("null lenth string\n"));
    assert(letters.length() != 0);
 
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned long> dist(0, letters.length() - 1);
 
    std::string passwd;
    for (int i = 0; i < len; ++i) {
        passwd += letters[dist(gen)];
    }
 
    return passwd;
}

/**
* @brief Метод passgen.
* @details Геренирует вектор с паролями.
* @return Возвращет вектор с паролями.
*/
std::vector<string> Opts::passgen() {
    std::string letters;
 
    if (this->isAlpha()) letters += set_alpha;
    if (this->isNums()) letters += set_digit;
    if (this->isSign()) letters += set_special;
 
    std::vector<std::string> pass_list;
    for (int i = 0; i < this->getNum(); ++i) {
        pass_list.push_back(text_shuffling(this->getLen(), letters));
    } 
    return pass_list;
}
/**
* @brief Метод usage. 
* @details Выводит краткую справку и досрочно завершает программу.
* @return Возвращет вектор с паролями.
*/
void Opts::usage(const char* progName)
{
    cout<<"Usage: "<<progName<<" [-l pass_len] [-n pass_num] [-0] [-a] [-s]\n";
    exit(1);
}