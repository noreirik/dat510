#ifndef GUARD_FEISTEL_CIPHER_H
#define GUARD_FEISTEL_CIPHER_H

#include <vector>
#include <bitset>

typedef std::vector<int> int_vector;

const int INPUT_KEY_SIZE = 64;
const int KEY_SIZE = 56;
const int ROUND_KEY_SIZE = 48;
const int BLOCK_SIZE = 64;
const int ROUND_NUM = 16;
const int S_BOXES = 8;

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

#endif