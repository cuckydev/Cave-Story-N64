#include "mem.h"

#define MEM_ALIGN(x) (((size_t)x + 0xF) & ~0xF)

typedef struct
{
	void *prev, *next;
	size_t size;
	u32 pad;
} Mem_Header;

#ifdef NEWGCC
	_Static_assert((sizeof(Mem_Header) & 0xF) == 0, "Mem_Header size must be aligned to 16 bytes");
#endif

static Mem_Header *mem = NULL;
static size_t mem_used, mem_size, mem_max;

u8 Mem_Init(void *ptr, size_t size)
{
	//Make sure there's enough space for mem header
	if (size < sizeof(Mem_Header))
		return 1;
	
	//Get mem pointer (16 byte alignment)
	mem = (Mem_Header*)MEM_ALIGN(ptr);
	mem_used = sizeof(Mem_Header);
	mem_size = size - ((size_t)mem - (size_t)ptr);
	mem_max = mem_used;
	
	//Initial mem header
	mem->prev = NULL;
	mem->next = NULL;
	mem->size = mem_size - sizeof(Mem_Header);
	return 0;
}

static Mem_Header *Mem_GetHeader(void *ptr)
{
	if (ptr == NULL)
		return NULL;
	return (Mem_Header*)((size_t)ptr - sizeof(Mem_Header));
}

void *Mem_Alloc(size_t size)
{
	size_t header_size;
	size_t next_pos;
	Mem_Header *new_header;
	void *new_block;
	
	//Get block to allocate in front of
	Mem_Header *header = mem;
	if (header == NULL)
		return NULL;
	
	header_size = 0;
	next_pos = MEM_ALIGN((size_t)header + sizeof(Mem_Header));
	
	while (header != NULL)
	{
		//If there's no block to check up next, compare against the end of the heap
		if (header->next == NULL)
		{
			//Check if there's enough space to allocate
			if ((next_pos + sizeof(Mem_Header) + size) > 
				((size_t)mem + sizeof(Mem_Header) + mem->size))
				return NULL;
			break;
		}
		
		//Check if there's enough space to allocate
		if (((size_t)header->next - sizeof(Mem_Header)) >= (next_pos + sizeof(Mem_Header) + size))
			break;
		
		//Check next block
		if ((header = Mem_GetHeader(header->next)) == NULL)
			return NULL;
		header_size = header->size;
		next_pos = MEM_ALIGN((size_t)header + sizeof(Mem_Header) + header_size);
	}
	
	//Setup header
	new_header = (Mem_Header*)next_pos;
	new_header->size = size;
	
	new_block = (void*)(next_pos + sizeof(Mem_Header));
	
	//Link header to previous and next headers
	new_header->prev = (void*)((size_t)header + sizeof(Mem_Header));
	new_header->next = header->next;
	
	//Link next header to us
	if (header->next != NULL)
		Mem_GetHeader(header->next)->prev = new_block;
	
	//Link previous header to us
	header->next = new_block;
	
	mem_used += new_header->size + sizeof(Mem_Header);
	if (mem_used > mem_max)
		mem_max = mem_used;
	
	return new_block;
}

void Mem_Free(void *ptr)
{
	Mem_Header *header, *header2;
	
	//Get this block's header
	header = Mem_GetHeader(ptr);
	if (header == NULL)
		return;
	
	//Unlink from previous block
	header2 = Mem_GetHeader(header->prev);
	if (header2 != NULL)
		header2->next = header->next;
	
	//Unlink from next block
	header2 = Mem_GetHeader(header->next);
	if (header2 != NULL)
		header2->prev = header->prev;
	
	mem_used -= header->size + sizeof(Mem_Header);
}

void Mem_GetStat(size_t *used, size_t *size, size_t *max)
{
	if (used != NULL)
		*used = mem_used;
	if (size != NULL)
		*size = mem_size;
	if (max != NULL)
		*max = mem_max;
}
