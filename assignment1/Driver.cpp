#include "Binary.h"
#include "Feistel_cipher.h"

#include <string>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	
	// read input
	Binary plain_text = "plaintext";
	std::cout << "Plain text:\t" << plain_text << std::endl;
	
	// read/generate key
	Binary key = "key";
	std::cout << "Key:\t" << key << std::endl;
	
	// convert input into blocks of BLOCK_SIZE, pad with zeros if necessary
	std::vector<Binary> plain_text_blocks;
	typedef std::vector<Binary>::const_iterator Binary_iterator;
	for (Binary_iterator i; i != plain_text.end(); ++i) {
		// TODO: split plain text into blocks of size of BLOCK_SIZE
	}
	
	// encrypt blocks
	std::vector<Binary> cipher_text_blocks;
	for (Binary_iterator i = plain_text_blocks.begin(); i != plain_text_blocks.end(); ++i) {
		Binary c = encrypt(*i, key);
		cipher_text_blocks.append(c);
	}
	
	std::string cipher_text;
	for (Binary_iterator i = cipher_text_blocks.begin(); i != cipher_text_blocks.end(); ++i)
		cipher_text.append(*i)
	
	std::cout << "Cipher text:\t" << cipher_text << std::endl;
	
	return 0;
}