#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<Windows.h>
//#include<tchar.h>

//#pragma warning(disable:2440)
//#pragma warning(disable:4996)

int sort(int*, int);

int main()
{
	int count = 0;
	int* setArray;
	int inputNo = 0;
	int tea[10];
	scanf_s("%d\n", &count);
	int a = 0;
	while (a < count)
	{
		
		int input_size = 0;
		scanf_s("%d\n", &input_size);
		setArray = (int*)malloc(input_size * sizeof(int));
		/*for (int i = 0; i < input_size; i++)
		{
			scanf_s("%d", &tea[i]);

		}*/
		int i = 0;
		while (i<input_size)
		{
			//printf("%d ", i);
			scanf_s("%d", &tea[i++]);
			
		}

		//sort( setArray, input_size);

		for (int i = 0; i < input_size; i++)
		{
			printf("%d", tea[i]);
		}
		printf("\n");
		free(setArray);

		a++;
	}

	
	return 0;
}


int sort(int*array,int size)
{
	int* Rsort0;
	int* Rsort1;
	Rsort0 = (int*)malloc(size * sizeof(int));
	Rsort1 = (int*)malloc(size * sizeof(int));

	
    int d = 0;
	for (int a=0 ,i=0; a < size; a += 2,i++)
	{	
		Rsort0[i] = array[a];
		
	}
	for (int a=1 ; a < size; a += 2,d++)
	{	
		Rsort1[d] = array[a];
	}
	
	for (int a = 0; a < size; a++)
	{
		if (size % 2 == 0)
		{
			if (a < (size / 2))
			{
				array[a] = Rsort0[a];
			}
			else 
			{
				d--; 
				array[a] = Rsort1[d];				
			}
		}
		else
		{
			if (a <=(size / 2))		
			{
				array[a] = Rsort0[a];
			}
			else		
			{
				d--;
				array[a] = Rsort1[d];	
			}
		}	
	}
	return 0;
}