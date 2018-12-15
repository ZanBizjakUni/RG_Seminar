#include "ErrorMsg.h"
#include <iostream>
namespace DEngine {

	void ErrorMsg::message(std::string context) {
		std::cout << "ERROR: " << context << "\n";
		std::cout << "press enter to continue... \n";
		int a;
		std::cin >> a;
	}

} //namespace