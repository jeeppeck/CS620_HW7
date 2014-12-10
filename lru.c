#include "stdio.h"
#include <stdlib.h>
#define FRAME struct memory_frame
#define HASH_SIZE 1013 //N=41



FRAME{
	FRAME *f_hash_next;
	FRAME *f_hash_prev;
	FRAME *f_free_next;
	FRAME *f_lru_next;
	FRAME *f_lru_prev;
	long page_num;
};

FRAME *page_table[HASH_SIZE];
FRAME *fm_free_list;
FRAME *fm_lru_head;
FRAME *fm_lru_tail;
int hash_table_size;
int number_of_frames;
int number_of_pages;



//initilization function 
//creates a single linked list of FRAME structures
void init_it()
{
	int i, j;
	FRAME *pCurrent, *pNew;
	FRAME *lCurrent, *lNew;

	for(i=0; i<=number_of_frames-1; i++)
	{
		//allocate memory for a structure
		if( (pNew = (FRAME*)malloc(sizeof(FRAME))) == NULL)
		{
			perror("Error allocating memory"); 
			exit(1);
		}
		//** Next -- initialize the fields in frame;
		if(i == 0)
		{
			pNew->page_num = 0;
			fm_free_list = pNew;
		}
		else
		{
			pNew->page_num = i;
			pCurrent->f_free_next = pNew;
		}
		pCurrent = pNew;
	}

	for(j=0; j<=number_of_frames-1; j++)
	{
		//allocate memory for a structure
		if((lNew = (FRAME*)malloc(sizeof(FRAME))) == NULL)
		{
			perror("Error allocating memory"); 
			exit(1);
		}
		//** Next -- initialize the fields in frame;
		if(j == 0)
		{
			lNew->page_num = 0;
			lNew->f_lru_prev = NULL;
			lNew->f_lru_next = NULL;
			fm_lru_head = lNew;
		}
		else
		{
			lNew->page_num = j;
			lCurrent->f_lru_next = lNew;
			lNew->f_lru_prev = lCurrent;
			lNew->f_lru_next = NULL;
		}
		lCurrent = lNew;
	}
	fm_lru_tail = lCurrent;
}

int free_frame()
{
	if(fm_free_list == NULL)
	{
		return 0;
	}
	return 1;
}



// int check_page_table(long page_num, FRAME **p_p_frame_pkt)
// {
// 	return 2;
// }

// void put_pageframe_in_memory(long page_num, FRAME *p_frame_pkt)
// {

// }

int hash(long pageNumber)
{
	long iHashKey;

	iHashKey = pageNumber + 1;
	return(iHashKey % hash_table_size);
}

void add_lru(long l)
{
	printf("HELLO\n");
	FRAME *newHead;
	FRAME *newTail;
	FRAME *newPtr;
	FRAME *second;
	if((newHead = (FRAME*)malloc(sizeof(FRAME))) == NULL)
	{
		perror("Error allocating memory"); 
		exit(1);
	}
	if((newTail = (FRAME*)malloc(sizeof(FRAME))) == NULL)
	{
		perror("Error allocating memory"); 
		exit(1);
	}
	printf("HELLO1\n");
	newPtr=fm_lru_head->f_lru_next;
	printf("HELLO2\n");
	newHead->f_lru_next=newPtr->f_lru_next;
	printf("HELLO3\n");
	newHead->page_num = newPtr->page_num;
	printf("HELLO4\n");
	second = newPtr->f_lru_next;
	second->f_lru_prev = newHead;
	printf("HELLO5\n");
	fm_lru_head = newHead;
	printf("HELLO6\n");
	newTail->page_num = l;
	fm_lru_tail->f_lru_next=newTail;
	newTail->f_lru_prev = fm_lru_tail;
	//printf("?");
	free(newPtr);
}

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char* filename;
	char line[128];
	size_t len = 0;
	ssize_t read;
	int numlines = 1;
	filename = argv[1];
	if(argc <= 1)
	{
		printf("Please provide valid input file\n");
		return 0;
	}
	printf("before\n");
	fp1 = fopen(filename, "r");
	fp2 = fopen(filename, "r");
	//fp2 = fopen(filename, "r");
	printf("after\n");
	if(!fp1 || !fp2)
	{
		printf("ERROR Opening file\n");
		exit(0);
	}
	printf("after2\n");
	int ch;
	while(EOF != (ch = fgetc(fp1)))
	{
		if(ch == '\n')
		{
			numlines++;
		}
	}
	//printf("k is %d\n", k);
	// // printf("after3\n");
	printf("Numlines = %d\n", numlines);
	int vals[numlines];
	int i=0;
	while(fgets(line, sizeof line, fp2) != NULL)
	{
		int curval = atoi(line);
		vals[i] = curval;
		i++;
	}
	hash_table_size = vals[0];
	number_of_frames = vals[1];
	number_of_pages = vals[2];
	printf("%d , %d , %d\n", hash_table_size, number_of_frames, number_of_pages);
	fclose(fp1);
	fclose(fp2);
	init_it();
	printf("tail is: %lu\n", fm_lru_tail->page_num);
	for(i=3; i<number_of_pages;i++)
	{
		printf("yo\n");
		if(free_frame() == 1)
		{
			page_table[hash(vals[i])] = fm_free_list;
			fm_lru_head = fm_free_list;
			fm_lru_head->page_num = vals[i];
			fm_free_list = fm_free_list->f_free_next;
		}
		else
		{
			printf("YO-\n");
			add_lru(vals[i]);
		}
	}

}
