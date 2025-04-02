#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

#define MAX_CPU_TIME 1; //in seconds

void cpu_limit_exceeded(int signal_num){
	printf("\nCPU time limit exceeded!\n");
	exit(1);
}


void generate_numbers(int min, int max, int *result, int size){
	bool unique;
	int number;
	
	for(int i = 0; i < size; i++){
		do{		
			number = rand() % (max - min +1) + min;
			unique = true;
			for(int j = 0; j < i; j++){
				if(result[j] == number){
					unique = false;
				}
			}
		}while(!unique);

		result[i] = number;
	}

}


void print_results(const int numbers[], int size){
	for(int i = 0; i < size; i++){
		printf("%d, ", numbers[i]);
	}
	printf("\n");

}


int main(){
	struct rlimit cpu_limit;
	cpu_limit.rlim_cur = MAX_CPU_TIME;
	cpu_limit.rlim_max = MAX_CPU_TIME;
	setrlimit(RLIMIT_CPU, &cpu_limit);

	signal(SIGXCPU, cpu_limit_exceeded);

	srand(time(NULL));
	int min = 1;
	int max1 = 49;
	int max2 = 36;
	int size1 = 7;
	int size2 = 6;
	int result1[size1];
	int result2[size2];
	printf("Lottery 1:\n");
	generate_numbers(min, max1, result1, size1);
	print_results(result1, size1);
	
	printf("Lottery 2:\n");
	generate_numbers(min, max2, result2, size2);
	print_results(result2, size2);

	return 0;

}

	
