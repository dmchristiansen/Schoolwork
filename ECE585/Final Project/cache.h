// Contains cache struct definitions & function prototypes

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define I_OFFSET_BITS  6
#define I_INDEX_BITS   14
#define I_TAG_BITS     12
#define I_ADDRESS_SIZE 32

#define D_OFFSET_BITS  6
#define D_INDEX_BITS   14
#define D_TAG_BITS     12
#define D_ADDRESS_SIZE 32

#define ICS (1 << I_INDEX_BITS) // Instruction cache set count
#define DCS (1 << D_INDEX_BITS) // Data cache set count
#define ICA 2                   // Instruction cache associativity
#define DCA 4                   // Data cache associativity

// Bits masking macros
#define I_INDEX_MASK (0x000FFFC0)
#define I_TAG_MASK   (0xFFF00000)
#define i_index(x) ((x & I_INDEX_MASK) >> I_OFFSET_BITS)
#define i_tag(x)   ((x & I_TAG_MASK) >> (I_OFFSET_BITS + I_INDEX_BITS)
#define d_address(t, i) (((t) << (D_INDEX_BITS + D_OFFSET_BITS)) + ((i) << D_OFFSET_BITS))
#define i_address(t, i) ((t) << ((I_INDEX_BITS + I_OFFSET_BITS)) + ((i) << I_OFFSET_BITS))

#define D_INDEX_MASK (0x000FFFC0)
#define D_TAG_MASK   (0xFFF00000)
#define d_index(x) ((x & D_INDEX_MASK) >> D_OFFSET_BITS)
#define d_tag(x)   ((x & D_TAG_MASK) >> (D_OFFSET_BITS + D_INDEX_BITS))


// Data structure declarations

enum MESI_BITS {
	MODIFIED  = 0, 
	EXCLUSIVE = 1,
	SHARED    = 2,
	INVALID   = 3};

// representation of a single cache line
struct cache_line
{
 	enum MESI_BITS MESI;
	uint8_t LRU;
	uint32_t tag;
};

struct cache_set
{
	struct cache_line* line;
};

// representation of a single cache
struct cache
{
	int hits;
	int misses;
	int reads;
	int writes;
	int associativity;
	int set_count;
	struct cache_set* set;
};

// global cache performance statistics
int hits, misses, reads, writes;

// General cache function prototypes
int allocate_cache(struct cache*, int way_cnt, int set_cnt);
int parse_input(int argc, char* argv[]);
void invalidate_cache(struct cache* cache);
int cache_check(struct cache* cache, int index, int tag);
int update_LRU(struct cache* cache, int index, int tag, int way);
int find_LRU(struct cache* cache, int index);
int find_victim(struct cache* cache, int index);
int display_cache(struct cache* cache);

// Main cache operation functions
int read_data(int address); // returns ???
int read_instruction(int address);
int write_data(int address);
void clear_cache();
void print_contents();

