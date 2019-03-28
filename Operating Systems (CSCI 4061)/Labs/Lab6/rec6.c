#define _BSD_SOURCE
#define NUM_ARGS 3

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

void shallowCopy(char* old, char* new) {

	// TODO: Create links to all files in old in new.
	DIR* oldDir = opendir(old);
	
	DIR* newDir = opendir(new);
	//int link(const char *path1, const char *path2);
	struct dirent* entry;

	while(entry = readdir(oldDir)){
		//printf("entry name %s\n", entry->d_name);
		if(entry->d_type != DT_DIR){
			//Then we must link
			char* filePath = malloc(1000*sizeof(char));
			strcpy(filePath, old);
			strcat(filePath, "/");
			strcat(filePath, entry->d_name);
			
			char* linkName = malloc(1000*sizeof(char));
			strcpy(linkName, new);
			strcat(linkName, "/");
			strcat(linkName, entry->d_name);

			//strcpy(linkName, filePath);
			//printf("old %s new %s\n", 
			link(filePath, linkName);
		} 
	}

}

void deepCopy(char* old, char* new) {

	// TODO: Copy the contents of all files in old to new.
	//Do the same thing as shallowcopy but instead of calling link,
	//actually copy the inside a given file and write it into a new file.
	DIR* oldDir = opendir(old);
	
	DIR* newDir = opendir(new);
	//int link(const char *path1, const char *path2);
	struct dirent* entry;
	while(entry = readdir(oldDir)){
		//printf("entry name %s\n", entry->d_name);
		if(entry->d_type != DT_DIR){
			//Then we must link
			char* filePath = malloc(1000*sizeof(char));
			strcpy(filePath, old);
			strcat(filePath, "/");
			strcat(filePath, entry->d_name);
			
			FILE* oldFile = fopen(filePath, "r");
			fseek(oldFile, 0, SEEK_END);
			long fileSize = ftell(oldFile);
			fseek(oldFile, 0, SEEK_SET);
			char* buffer = malloc(fileSize + 1);
			fread(buffer, 1, fileSize, oldFile);
			printf("buffer value %s\n", buffer);
			fclose(oldFile);
			
			char* linkName = malloc(1000*sizeof(char));
			strcpy(linkName, new);
			strcat(linkName, "/");
			strcat(linkName, entry->d_name);
		
			FILE* newFile = fopen(linkName, "w");
			printf("old file path %s new file path %s\n", filePath, linkName);


			fputs(buffer, newFile);
			
			fclose(newFile);

			//strcpy(linkName, filePath);
			//printf("old %s new %s\n", 
			link(filePath, linkName);
		} 
	}


}

int main(int argc, char** argv) {

	if (argc < NUM_ARGS + 1) {

		printf("Wrong number of args, expected %d, given %d\n", NUM_ARGS, argc - 1);
		exit(1);
	}
	
	time_t initialTime = time(0);
	shallowCopy(argv[1], argv[2]);
	time_t afterShallow = time(0);
	deepCopy(argv[1], argv[3]);
	time_t afterDeep = time(0);

	time_t shallowTime = afterShallow - initialTime;
	time_t deepTime = afterDeep - afterShallow;

	printf("Shallow copy took %ld seconds\n", shallowTime);
	printf("Deep copy took %ld seconds\n", deepTime);

	// TODO: Time how long it takes to execute each copy and print the results.

}
