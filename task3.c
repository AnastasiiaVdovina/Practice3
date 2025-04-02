#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

#define FILE_NAME "diceroll_results.txt"
#define MAX_FILE_SIZE 1024 //1 kb

int get_file_size(const char *filename){
	struct stat st;
	if(stat(filename, &st) == 0) {
		return st.st_size;
	}
	return 0;
}		


int roll_dice(){
	return (rand() % 6) + 1;
}

int main(){
	srand((unsigned int)time(NULL));
	int num_rolls;
	printf("Enter the number of rolls: ");
	scanf("%d",&num_rolls);

	FILE *file = fopen(FILE_NAME, "a");
	if (!file){
		perror("Failed to open file!");
		return EXIT_FAILURE;
	}

	for(int i = 1; i <= num_rolls; i++){
		if(get_file_size(FILE_NAME) >= MAX_FILE_SIZE){
			printf("File size limit reached\n");
			break;
		}

		int result = roll_dice();
		fprintf(file, "%d\n", result);
		fflush(file);
		
		printf("Rolled: %d\n", result);
		//sleep(1);
	}

	fclose(file);
	return 0;

}
