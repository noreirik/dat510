#include "Feistel_cipher.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <bitset>

int main() {
	std::bitset<INPUT_KEY_SIZE> key(std::string("00110011101011011101101010"));
		
	while(true) {
		std::cout << "Enter input text or Q to quit:\t" << std::endl;
		std::string input;
		std::cin >> input;
		if (input == "q") break;
		bool is_valid = true;
		for (int i = 0; i < input.size(); ++i) {
			if (input[i] != '0' && input[i] != '1') {
				std::cout << "Invalid input. Only binary data is allowed." << std::endl;
				is_valid = false;
				break;
			}
		}
		if (!is_valid) continue;
		bool is_encrypt = true;
		std::string mode;
		std::cout << "Enter mode: [1] encryption (Enter) or [2] decryption: ";
		std::cin >> mode;
		if (mode[0] == '2') is_encrypt = false;

		
		std::bitset<64> binary_input(input);		
		if (is_encrypt) {
			std::cout << encrypt(binary_input, key, true) << std::endl;
		}
		else {
			std::cout << encrypt(binary_input, key, false) << std::endl;
		}
		input.clear();
	}
	
	return 0;
}