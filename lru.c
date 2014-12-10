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
	long frame_num;
};

FRAME *page_table[HASH_SIZE];
FRAME *fm_free_list;
FRAME *fm_lru_head;
FRAME *fm_lru_tail;
int hash_table_size;
int number_of_frames;
int number_of_pages;
int count;
long *vals=NULL;


//initilization function 
//creates a single linked list of FRAME structures

/*
 *init_it - function to initilize the linked list, creates a single linked list of Frame structures
 */
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
			pNew->f_hash_next =NULL;
			pNew->f_hash_prev = NULL;
			pNew->f_free_next = NULL;
			pNew->f_lru_next = NULL;
			pNew->f_lru_prev = NULL;
			pNew->frame_num = i;
			pCurrent = pNew;
			fm_free_list = pNew;
		}
		else
		{
			pNew->page_num = 0;
			pNew->f_hash_next =NULL;
			pNew->f_hash_prev = NULL;
			pNew->f_free_next = NULL;
			pNew->f_lru_next = NULL;
			pNew->f_lru_prev = NULL;
			pNew->frame_num = i;
			pCurrent->f_free_next = pNew;
			pCurrent = pNew;
		}
		pCurrent = pNew;
	}


	// for(j=0; j<=number_of_frames-1; j++)
	// {
	// 	//allocate memory for a structure
	// 	if((lNew = (FRAME*)malloc(sizeof(FRAME))) == NULL)
	// 	{
	// 		perror("Error allocating memory"); 
	// 		exit(1);
	// 	}
	// 	//** Next -- initialize the fields in frame;
	// 	if(j == 0)
	// 	{
	// 		lNew->page_num = 0;
	// 		lNew->f_lru_prev = NULL;
	// 		lNew->f_lru_next = NULL;
	// 		fm_lru_head = lNew;
	// 	}
	// 	else
	// 	{
	// 		lNew->page_num = j;
	// 		lCurrent->f_lru_next = lNew;
	// 		lNew->f_lru_prev = lCurrent;
	// 		lNew->f_lru_next = NULL;
	// 	}
	// 	lCurrent = lNew;
	// }
	// fm_lru_tail = lCurrent;

	for(j=0; j<number_of_pages; j++)
	{
		page_table[j]=NULL;
	}
	fm_lru_head = NULL;
	fm_lru_tail = NULL;
}

/*
 *getFreeFrame - function to get free frame from the fm_free_list. It takes the returns the head
 *from the list and sets the newHead to the next node
 */
FRAME *getFreeFrame()
{
	FRAME *ret;
	ret = fm_free_list;
	fm_free_list = fm_free_list->f_free_next;
	return ret;
}

/*
 *putFrameInMM - function to put frame into the page table, if a frame is already frame at the
 *key in the hash table then it does nothing(*****CHANGE THIS*****). If the spot is free the frame 
 *is added to the index at that key
 */
void putFrameInMM(FRAME *f)
{
	if(spotTaken(hash(f->page_num)))
	{

	}
	else
	{
		page_table[hash(f->page_num)] = f;
		printf("%lu added to page_table\n", f->page_num);
	}
}
/*
 *letsDoIt - goes through the pagenumbers in the vals array to be added to mm.
 */
void letsDoIt()
{
	int i;
	for(i=3; i<count; i++)
	{
		if(isLoadedInMM(vals[i]))
		{
			printf("%lu Is in MM\n", vals[i]);
		}
		else
		{
			printf("%lu Is not in mm\n", vals[i]);
			if(thereIsAFreeFrame())
			{
				FRAME *newFrame = getFreeFrame();
				newFrame->page_num = vals[i];
				putFrameInMM(newFrame);
			}
		}
	}
}

/*
 *thereIsAFreeFrame - is just a function to check if there is already are any Frames left in the 
 *fm_free_list
 */
int thereIsAFreeFrame()
{
	if(fm_free_list == NULL)
	{
		printf("There are no free Frames\n");
		return 0;
	}
	printf("There is a free frame\n");
	return 1;
}






/*
 *spotTaken - takes a key and tells you if there is a frame already in 
 *the page table at that spot
 */
int spotTaken(int i)
{
	if(page_table[i])
	{
		printf("something is already in the table at: %d\n", i);
		return 1;
	}
	return 0;
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
	return (int)(iHashKey % hash_table_size);
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

/*
 *initializeArr - function to initialize dynamic array
 */
void initializeArr(long **n)
{
	*n=malloc(sizeof(long));
	if(*n==NULL)
	{
		printf("Malloc of holding array failed");
		return;
	}
	(*n)[0]=0;
	printf("Added %lu \n", (*n)[0]);
}
void addToPageTable(long i)
{
	page_table[hash(i)]=i;
}
/*
 *addValue - function to add value to dynamic array
 */
void addValue(long **n, long valToAdd)
{
	long *tmpInt;
	tmpInt = realloc(*n, (count+1) * sizeof(long));

	if(tmpInt == NULL)
	{
		printf("Failure during realloc");
		return;
	}
	*n = tmpInt;
	count;
	(*n)[count]=valToAdd;
	printf("Added %lu \n", (*n)[count]);
	count++;
}
/*
 *isLoadedInMM - checks to see if a pageNumber is in the page table(checks for
 *page hit or page fault)
 */
int isLoadedInMM(long pNum)
{
	if(page_table[hash(pNum)])
	{
		return(1);
	}
	return 0;
}
/*
 *printVals - function to printValues from dynamic array
 */
void printVals(long *n)
{
	int i=0;
	for(i=0; i<count; i++)
	{
		printf("%lu ", n[i]);
	}
}

int main(int argc, char *argv[])
{
	FILE *fp1 = stdin;
	char line[128];
	size_t len = 0;
	ssize_t read;
	//long *vals = NULL;
	initializeArr(&vals);

	if(!fp1)
	{
		printf("ERROR Opening file\n");
		exit(0);
	}

	int i=0;
	while(fgets(line, sizeof line, fp1) != NULL)
	{
		long curval = atol(line);
		//printf("Line = %s\n", line);
		addValue(&vals, curval);
		i++;
	}

	hash_table_size = vals[0];
	number_of_frames = vals[1];
	number_of_pages = vals[2];
	printf("%d , %d , %d\n", hash_table_size, number_of_frames, number_of_pages);
	init_it();
	letsDoIt();
	// init_it();
	// printf("tail is: %lu\n", fm_lru_tail->page_num);
	// for(i=3; i<number_of_pages;i++)
	// {
	// 	printf("yo\n");
	// 	if(free_frame() == 1)
	// 	{
	// 		page_table[hash(vals[i])] = fm_free_list;
	// 		fm_lru_head = fm_free_list;
	// 		fm_lru_head->page_num = vals[i];
	// 		fm_free_list = fm_free_list->f_free_next;
	// 	}
	// 	else
	// 	{
	// 		printf("YO-\n");
	// 		add_lru(vals[i]);
	// 	}
	// }

}
