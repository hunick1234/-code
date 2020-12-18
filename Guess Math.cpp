#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int guess(int , int , int );

int main(void) 
{		
	int min = 0;
	int max = 0;
	srand(time(0));
	printf("輸入最小和最大(空白分隔)\n");
	scanf_s("%d %d", &min, &max);


	int x = rand() % max;
	printf("the rand is:?\n");
	
	//printf("%d\n",x);
		 
	guess(min, x, max);
	printf("you did it,the rand is %d\n", x);

    return 0;
}
int guess(int left, int in, int right)
{
	
	int math=0;
	printf("rand at %d~%d\n", left, right);

		while (math != in)
		{
			printf("your math:");
			scanf_s("%d", &math);

			if (math < in)
			{
				//printf("%d<%d\n", math, right);
				guess((math < left ? left:math), in, right);
			}
			if (math > in)
			{
				//printf("%d>%d\n", math, left);
				guess(left, in, (math > right ? right: math));
			}
			break;
			
		}	
	return 0;
}

