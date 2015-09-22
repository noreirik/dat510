#include "Feistel_cipher.h"

#include <vector>
//#include <algorithm>
#include <bitset>

std::bitset<BLOCK_SIZE/2> copy_bit_pattern(const std::bitset<BLOCK_SIZE/2>& data) {
    return data;
}

// given plain text and key, return cipher text
std::bitset<BLOCK_SIZE> encrypt(const std::bitset<BLOCK_SIZE>& input_text, const std::bitset<INPUT_KEY_SIZE>& input_key) {
	std::bitset<BLOCK_SIZE> cipher_block;	
	// generate initial key	
	std::bitset<KEY_SIZE> initial_key = generate_initial_key(input_key);
	
	// generate round keys
	std::vector<std::bitset<ROUND_KEY_SIZE> > round_keys = generate_round_keys(initial_key);
	
	// split input text into two blocks of 32b
	std::bitset<BLOCK_SIZE/2> lower; // use lower to represent bits [0,BLOCK_SIZE/2), and
	std::bitset<BLOCK_SIZE/2> upper; // user upper to represent bits [BLOCK_SIZE/2,BLOCK_SIZE)
	int mid = input_text.size() / 2;
	for (int i = 0; i < input_text.size(); i++)
		if (i < mid) lower.set(i, input_text.test(i));
		else upper.set(i % mid, input_text.test(i));
	
	std::bitset<BLOCK_SIZE/2> temp; // temporarily hold lower, so that upper can be used in XOR
	
	for (int i = 0; i < ROUND_NUM; ++i) {
		temp = copy_bit_pattern(lower); // hold r_i-1 in temp
		// right = f(right, key); 
		lower ^= upper; // r_i = f(r_i-1,key) xor l_i-1
		upper = copy_bit_pattern(temp); // l_i = r_i-1
	}
	return cipher_block;
}

std::bitset<KEY_SIZE> generate_initial_key(const std::bitset<INPUT_KEY_SIZE>& input_key) {
	// permute using pc_1 table, and return output
	std::bitset<KEY_SIZE> output_key;
	for (int i = 0; i < pc_1.size(); ++i)
		output_key.set(i, input_key.test(pc_1[i]));
	return output_key;
}

std::vector<std::bitset<ROUND_KEY_SIZE> > generate_round_keys(const std::bitset<KEY_SIZE>& key) {
	std::vector<std::bitset<ROUND_KEY_SIZE> > round_keys;
	// split key into lower and upper half, of 28b
	std::bitset<KEY_SIZE/2> lower;
	std::bitset<KEY_SIZE/2> upper;
	int mid = key.size() / 2;
	for (int i = 0; i < key.size(); i++)
		if (i < mid) lower.set(i, key.test(i));
		else upper.set(i % mid, key.test(i));

	for (int i = 0; i < ROUND_NUM; ++i) {
		// left shift using key_schedule
		lower = (lower << key_schedule[i]);
		upper = (upper << key_schedule[i]);
		// permute using pc_2 table
		
		//combine 28b lower and 28b upper for 56b key
		std::bitset<KEY_SIZE> input_key;
		for (i = 0; i < input_key.size(); ++i) {
			if (i < mid) input_key.set(i, lower.test(i));
			else input_key.set(i, upper.test(i % mid));
		}
		
		// permute using pc_2 table
		std::bitset<ROUND_KEY_SIZE> round_key;
		for (int i = 0; i < pc_2.size(); ++i)
			round_key.set(i, input_key[pc_2[i]]);

		round_keys.push_back(round_key);
	}
	
	return round_keys;
}

std::bitset<BLOCK_SIZE/2> perform_round(const std::bitset<BLOCK_SIZE/2>& data, const std::bitset<ROUND_KEY_SIZE>& round_key) {
	// expand/permute data from 32b to 48b using e_table
	std::bitset<48> expansion;
	for (int i = 0; i < e_table.size(); ++i)
		expansion.set(i, data.test(e_table[i]));
	
	expansion ^= round_key;
	// substitute with expansion and s-boxes
	
	// permute/shrink expansion from 48b to 32b using P table
	std::bitset<32> shrinkage;
	for (int i = 0; i < p_table.size(); ++i)
		shrinkage.set(i, expansion.test(p_table[i]));
	
	return shrinkage;
}