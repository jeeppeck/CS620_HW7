#include <stdio.h>
#include <stdlib.h>

int temp =0;

// void begin(int *);
// void add(int *, int);
// void print(int *);

void begin(int **n)
{
	*n=malloc(sizeof(int));

	if(*n==NULL)
	{
		printf("Malloc of holding array failed");
		return;
	}
	(*n)[0]=0;
	printf("Added %d \n", (*n)[0]);
}

void add(int **n, int adding)
{
	int *tmpInt;
	tmpInt = realloc(*n, (temp+1) * sizeof(int));

	if(tmpInt == NULL)
	{
		printf("Failure during realloc");
		return;
	}
	*n = tmpInt;
	temp;
	(*n)[temp]=adding;
	printf("Added %d \n", (*n)[temp]);
	temp++;
}

void printVals(int *n)
{
	int i=0;
	for(i=0; i<temp; i++)
	{
		printf("%d ", n[i]);
	}
}

int main(int argc, char *argv[])
{
	int *vals = NULL;
	begin(&vals);
	int t;
	int u;
	int v;
	printf("Enter a number: ");
	scanf("%d", &t);
	add(&vals, t);	
	printf("Enter another number: ");
	scanf("%d", &u);
	add(&vals, u);
	printf("Do it again: ");
	scanf("%d", &v);
	add(&vals, v);
	printVals(vals);
	printf("Size %d\n", temp);
	return 0;
}

