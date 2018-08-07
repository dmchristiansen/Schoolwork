/*
 * main.c
 *
 * ECE 585 Final Project
 * Authors:
 * Manisha Balakrishna Garade
 * Amruta Kalambkar
 * Rashmi Rajendra Kulkarni
 * Daniel Christiansen
 *
 * Version 0.2
 */

#include <string.h>
#include "cache.h"

// global variables
int mode; // Output mode. 0 = silent, 1 = verbose.
struct cache data_cache, instruction_cache;

// index into cache line like so:
// data_cache.set[i].line[j].LRU, etc

int main(int argc, char* argv[])
{
	unsigned int operation;
	unsigned int address;
	FILE *fp;

	// Allocates caches
	if(allocate_cache(&data_cache, DCA, DCS))
		return -1;
	if(allocate_cache(&instruction_cache, ICA, ICS))
		return -1;

	printf("Allocation successful.\n");

    // Clear caches & reset statistic so that all lines are invalid
    clear_cache();

	printf("Caches cleared.\n");
	
	// set mode and filename globals
	if(parse_input(argc, argv))
		return -1;

	printf("Parsing successful.\n");
	
	fp = fopen(argv[2],"r");
	if(NULL == fp)
	{
		printf("Unable to open file: %s\n", argv[2]);
		return -1;
	}

	printf("File open.\n");

	while(fscanf(fp,"%d",&operation)!=EOF)
	{
		fscanf(fp,"%x",&address);
		printf("operation %d, Address %x\n", operation, address);
		switch(operation) {
			case 0: read_data(address);
					break;
			case 1: write_data(address);
					break;
			case 2: //instruction_read();
					break;
			case 3: //invalidate_line();
					break;
			case 4: //data_req_L2();
					break;
			case 8: clear_cache();
					break;
			case 9: print_contents();
					break;
		}
	}



	// main loop

	return 0;
}

// Parses command line input
// There need to be 
int parse_input(int argc, char* argv[])
{
	if(argc < 2 || argc > 3)
	{
	    printf("Incorrect number of arguments.\n");
		return -1;
    }
   
	printf("Correct number of arguments.\n"); 
    
    if(0 == strcmp(argv[1], "-v"))
        mode = 1;
    else if(0 == strcmp(argv[1], "-s"))
        mode = 0;
    else if(0 == strcmp(argv[1], "--help"))
    {
        printf("\nProgram use:");
        printf("\n\tcachesim -[flag] [filename]");
        printf("\n\t-v\tverbose\t- print read/write operations");
        printf("\n\t-s\tsilent\t- only output information on command\n");
		return -1;
    }
    else
    {
        printf("Invalid argument '%s'.\n", argv[1]);
        return -1;
    }
    
	printf("Mode = %d\n", mode);
	
	return 0;
}

// Reads data cache
int read_data(int address)
{
	// mask tag & index
	// call cache_check
	// if hit, call update_LRU
	// if miss
	//   send read from L2 signal
	//   find line to evict, replace line, update LRU
	//   new line should be in shared state

	int new_index, new_tag, i;
	// mask tag & index
	new_index = d_index(address);
	new_tag = d_tag(address);

	 // call cache_check
	i = cache_check(&data_cache, new_index, new_tag);
	if (i != -1)
		// if hit, update LRU
		update_LRU(&data_cache, new_index, new_tag, i);
	else
	{
		// if miss, find line to evict, replace line, update LRU
		i = find_victim(&data_cache, new_index);
		// Write back only when line is modified
		if((data_cache.set[new_index].line[i].MESI == MODIFIED)
			&& (mode == 1))
			printf("Write to L2 %x\n",
				d_address(data_cache.set[new_index].line[i].tag, new_index));
		data_cache.set[new_index].line[i].tag = new_tag;
		data_cache.set[new_index].line[i].MESI = SHARED;
		update_LRU(&data_cache, new_index, new_tag, i);	
		if(mode == 1)
         	printf("Read from L2 %x\n", address);
	}
}


int write_data(int address)
{
	// mask index & tag bits
	// call cache_check function
	// if hit:
	//   if in shared state, write through, update MESI & LRU
	//   if not, update LRU
	// if miss:
	//   read for ownership from L2
	//   put in modified state
}


int instruction_read(int address)
{
	// same as data_read, mostly
}

// Clears all caches and resets statistics
void clear_cache()
{
	hits = 0;
	misses = 0;
	reads = 0;
	writes = 0;

	invalidate_cache(&data_cache);
	invalidate_cache(&instruction_cache);
}

// Prints cache statistics & valid cache content
void print_contents()
{
	// Global statistics
	printf("\nGlobal cache statistics:\n");
	printf("Reads:\t%d\n", reads);
	printf("Writes:\t%d\n", writes);
 	printf("Hits:\t%d\n", hits);
	printf("Misses\t%d\n", misses);

	// Data cache statistics
	printf("\nData cache statistics:\n");
	printf("Reads:\t%d\n", data_cache.reads);
	printf("Writes:\t%d\n", data_cache.writes);
 	printf("Hits:\t%d\n", data_cache.hits);
	printf("Misses\t%d\n", data_cache.misses);
	printf("\nData ");
	display_cache(&data_cache);	

	// Instruction cache statistics
	printf("\nInstruction cache statistics:\n");
	printf("Reads:\t%d\n", instruction_cache.reads);
	printf("Writes:\t%d\n", instruction_cache.writes);
 	printf("Hits:\t%d\n", instruction_cache.hits);
	printf("Misses\t%d\n", instruction_cache.misses);
	printf("\nInstruction ");
	display_cache(&instruction_cache);
}



