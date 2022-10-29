#include <utf8_parser.h>
//maps state and transition byte class to new state
static uint8_t transition_table[23][3] = {{0,0,0},{0,2,2},{0,3,3},{0,5,8},{0,6,7},{0,11,6},{0,10,4},{0,4,5},{8,1,3},{7,1,3},{7,7,3},{7,9,3},{6,7,3},{6,9,3},{4,7,2},{5,1,2},{5,9,2},{3,1,2},{3,7,2},{3,9,2},{2,1,0},{2,7,0},{2,9,0}};

//maps tansition byte to byte class
static uint8_t byte_to_class[256] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,10,3,3,3,3,3,3,3,3,3,3,3,3,4,3,3,11,6,6,6,5,8,8,8,8,8,8,8,8,8,8,8};

//returns new state after looking up
//transition table
//if transition does not exist returns -1
static int8_t find_new_state(uint8_t state, uint8_t class)
{
	int ret = -1;
	for(int i =0;i<sizeof(transition_table);i++)
	{
		if(state==transition_table[i][0] && class==transition_table[i][1]) 
			return transition_table[i][2];
	}
	return ret;
}

//returns the index of the end
//of the first valid utf8 sequence found
//in the byte array
//if an invalid sequence is met it returns -1
int8_t utf8_index(const unsigned char * s, uint32_t len)
{
	int8_t state = 0;
	for(int i=0;i<len;i++)
	{
		uint8_t class = byte_to_class[s[i]];
		state = find_new_state(state,class);
		
		//the sequence is invalid because 
		//we stayed stuck in a state
		if(state==-1)
			return -1;
		//we have encountered a complete utf8 sequence
		if(state==0)
			return i;
	}
	//we arrived at the end of the array without
	//a complete utf8 sequence
	return -1;
}
