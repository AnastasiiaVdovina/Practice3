#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]){
	FILE *source_file, *dest_file;
	char buffer[BUFFER_SIZE];
	size_t bytes_read, bytes_written;
	
	//check amount of args
	if(argc != 3){
		fprintf(stderr, "Program needs two arguments: source file and destination file.\n");
		exit(EXIT_FAILURE);
	}

	const char *source_filename = argv[1];
	const char *dest_filename = argv[2];
	
	//Opening source file for reading
	source_file = fopen(source_filename, "rb");
	if(source_file == NULL){
		fprintf(stderr, "Cannot open file %s for reading.\n", source_filename);
		exit(EXIT_FAILURE);
	}

	//Opening destination file for writing
	dest_file = fopen(dest_filename, "wb");
	if(dest_file == NULL){
		fprintf(stderr, "Cannot open file %s for writing.\n", dest_filename);
		fclose(source_file);
		exit(EXIT_FAILURE);
	}

	while((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0 ){
		bytes_written = fwrite(buffer, 1, bytes_read, dest_file);

		if(bytes_written < bytes_read){
			fprintf(stderr, "Error writing to file.\n");
			fclose(source_file);
			fclose(dest_file);
			exit(EXIT_FAILURE);
		}
	}

	if(ferror(source_file)){
		fprintf(stderr, "Error reading from file.\n");
		fclose(source_file);
		fclose(dest_file);
		exit(EXIT_FAILURE);
	}

	printf("File %s successfully copied to %s.\n", source_filename, dest_filename);
	
	fclose(source_file);
	fclose(dest_file);
	return 0;
}

