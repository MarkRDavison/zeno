#include <zeno/Core/Mat4x4.hpp>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <string>

int main(int _argc, char** _argv) {
	if (_argc != 2) {
		std::cout << "Please use with a number" << std::endl;
		return EXIT_FAILURE;
	}

	float number;

	try {
		number = std::stof(std::string(_argv[1]));
	} catch (std::out_of_range e) {
		std::cout << "Please use with a valid number" << std::endl;
		return EXIT_FAILURE;
	} catch (std::exception e) {
		std::cout << "Please use with a number" << std::endl;
		return EXIT_FAILURE;
	}

	ze::Mat4x4 mat(number);

	std::cout << mat << std::endl;

	return EXIT_SUCCESS;

}