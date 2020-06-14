/** 
* @file main.cpp
* @brief Главный модуль генератора паролей
*/
#include "PassGen.h"

int main(int argc, char* argv[])
{	
	try{		
		Opts op(argc, argv);
		for (const std::string &pass : op.passgen())
			cout << pass << endl;
	}catch (const gen_error & e) {
		std::cerr << e.what() << std::endl;
	}
	
    return 0;
}
