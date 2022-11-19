#include<stdio.h>
#include<sys/syscall.h>
#include<linux/kernel.h>
#include<unistd.h>
#include<errno.h>
#define ROW_NUM 4
#define COL_NUM 5
int main(){
	float sourceArray[ROW_NUM][COL_NUM] = {{4, 4, 4, 4, 4}, {2, 2, 2, 2, 2}, {3, 3, 3, 3, 3}, {4, 4, 4, 4, 4}};
	float destinationArray[ROW_NUM][COL_NUM];
	long syscall_status = syscall(452, sourceArray, destinationArray, ROW_NUM, COL_NUM);
	for(int i = 0; i<ROW_NUM; i++){
		for(int j = 0; j<COL_NUM; j++){
			printf("%f ", destinationArray[i][j]);
		}
		printf("\n");
	}
}





















