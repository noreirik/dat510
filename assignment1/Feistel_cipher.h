#ifndef GUARD_FEISTEL_CIPHER_H
#define GUARD_FEISTEL_CIPHER_H

#include <vector>
#include <bitset>
#include <iostream>

typedef std::vector<int> int_vector;

const int INPUT_KEY_SIZE = 64;
const int KEY_SIZE = 56;
const int ROUND_KEY_SIZE = 48;
const int BLOCK_SIZE = 64;
const int ROUND_NUM = 16;
const int NUM_S_BOXES = 8;

// from the 64b key, extract 56 to be used as key
std::bitset<KEY_SIZE> generate_initial_key(const std::bitset<INPUT_KEY_SIZE>& input_key);
// 
std::vector<std::bitset<ROUND_KEY_SIZE> > generate_round_keys(const std::bitset<KEY_SIZE>& initial_key);
// 
std::bitset<BLOCK_SIZE/2> perform_round(const std::bitset<BLOCK_SIZE/2>& data, const std::bitset<ROUND_KEY_SIZE>& round_key);
// 
std::bitset<BLOCK_SIZE> encrypt(const std::bitset<BLOCK_SIZE>& input_text, const std::bitset<INPUT_KEY_SIZE>& input_key);

// PC1 table is used in generating the 56b initial key from the 64b input key
int pc_1_table[KEY_SIZE] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,14
};
std::vector<int> pc_1(pc_1_table, pc_1_table + KEY_SIZE);

// PC2 table is used in generating the 48b round key from the 56b initial key
int pc_2_table[ROUND_KEY_SIZE] = {
	14,17,11,24,1,5,3,8,
	15,6,21,10,23,19,12,4,
	26,8,16,7,27,20,13,2,
	41,52,31,37,47,55,30,40,
	51,45,33,48,44,49,39,56,
	34,53,46,42,50,36,29,32
};
std::vector<int> pc_2(pc_2_table, pc_2_table + ROUND_KEY_SIZE);

// key shift table is used to determine for a given round how many left shifts
int key_schedule_table[] = {
	1,1,2,2,2,2,2,2,
	1,2,2,2,2,2,2,1
	
};
std::vector<int> key_schedule(key_schedule_table, key_schedule_table + ROUND_NUM);

// p_table is used to shrinking the lower from 48b to 32b to be able to xor left half
int p_table_arr[] = {
	16,1,2,19,7,15,8,13,
	20,23,24,30,21,26,14,6,
	29,5,32,22,12,18,27,11,
	28,31,3,4,17,10,9,25
};
int_vector p_table(p_table_arr, p_table_arr + 32);

int e_table_arr[] = {
	32,4,8,12,16,20,24,28,
	1,5,9,13,17,21,25,29,
	2,6,10,14,18,22,26,30,
	3,7,11,15,19,23,27,31,
	4,8,12,16,20,24,28,32,
	5,9,13,17,21,25,29,1
};
int_vector e_table(e_table_arr, e_table_arr + 48);

int s_boxes[NUM_S_BOXES][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	}, {
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	}, {
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
	}, {
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	}, {
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	}, {
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	}, {
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	}, {
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};

std::bitset<BLOCK_SIZE/2> copy_bit_pattern(const std::bitset<BLOCK_SIZE/2>& data) {
    return data;
}

// given plain text and key, return cipher text
std::bitset<BLOCK_SIZE> encrypt(const std::bitset<BLOCK_SIZE>& input_text, const std::bitset<INPUT_KEY_SIZE>& input_key, bool encrypt) {
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
	
	// if encryption
	if (encrypt) {
		for (int i = 0; i < ROUND_NUM; ++i) {
			//std::cout << "ROUND " << i << "----------------------------------------" << std::endl;
			//std::cout << "Using key " <<  i << ":\t\t" << round_keys[i] << std::endl;
			temp = copy_bit_pattern(lower); // hold r_i-1 in temp
			lower = perform_round(lower, round_keys[i]);
			lower ^= upper; // r_i = f(r_i-1,key) xor l_i-1
			upper = copy_bit_pattern(temp); // l_i = r_i-1
			std::cout << "ROUND " << i << " ENDED" << "----------------------------------" << std::endl;
		}
	} else {
		// if decryption
		for (int i = ROUND_NUM -1; i >= 0; --i) {
			//std::cout << "ROUND " << i << "----------------------------------------" << std::endl;
			//std::cout << "Using key " <<  i << ":\t\t" << round_keys[i] << std::endl;
			temp = copy_bit_pattern(lower); // hold r_i-1 in temp
			lower = perform_round(lower, round_keys[i]);
			lower ^= upper; // r_i = f(r_i-1,key) xor l_i-1
			upper = copy_bit_pattern(temp); // l_i = r_i-1
			//std::cout << "ROUND " << i << " ENDED" << "----------------------------------" << std::endl;
		}
	}
	
	// perform final swap
	for (int i = 0; i < cipher_block.size(); ++i) {
		if (i < mid) cipher_block.set(i, upper.test(i));
		else cipher_block.set(i, lower.test(i % mid));
	}
	
	return cipher_block;
}

std::bitset<KEY_SIZE> generate_initial_key(const std::bitset<INPUT_KEY_SIZE>& input_key) {
	// permute using pc_1 table, and return output
	std::bitset<KEY_SIZE> output_key;
	for (int i = 0; i < pc_1.size(); ++i) {
		output_key.set(i, input_key.test(pc_1[i] - 1));
	}
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

std::bitset<32> perform_sbox_subst(const std::bitset<48>& input) {
    std::bitset<32> output;
    for (int i = 0; i < NUM_S_BOXES; ++i) {
        int row = 0;
        int col = 0;
        //row bits are in bits 0,5
        if (input.test(6*i)) row += 1;
        if (input.test(6*i+5)) row += 2;
        
        //column bits are bits[1,5)
        if (input.test(6*i+1)) col += 1;
        if (input.test(6*i+2)) col += 2;
        if (input.test(6*i+3)) col += 4;
        if (input.test(6*i+4)) col += 8;
        
	// perform substitution for block i using s-box i
        std::bitset<4> sbox_out = s_boxes[i][row][col];
        for (int j = 0; j < 4; ++j) output.set(i*4+j,sbox_out.test(j));
    }
    return output;
}

std::bitset<BLOCK_SIZE/2> perform_round(const std::bitset<BLOCK_SIZE/2>& data, const std::bitset<ROUND_KEY_SIZE>& round_key) {
	// expand/permute data from 32b to 48b using e_table
	std::bitset<48> expansion;
	for (int i = 0; i < e_table.size(); ++i) {
		expansion.set(i, data.test(e_table[i] - 1));
	}
	expansion ^= round_key;

	// perform s-box substitution on expanded data	
	std::bitset<32> s_box_out = perform_sbox_subst(expansion);
	
	// permute using P table
	std::bitset<32> shrinkage;
	for (int i = 0; i < p_table.size(); ++i)
		shrinkage.set(i, expansion.test(p_table[i] - 1));
	return shrinkage;
}

#endif