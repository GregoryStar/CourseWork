#define _BSD_SOURCE

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

void printStats(char* path, int max) {
	DIR* dir = opendir(path);
	struct dirent* entry = readdir(dir);
	entry = readdir(dir);
	off_t totalDirSize = 0;
	for(int i = 0; i < max && (entry = readdir(dir)); i++){
		char newPath[1000] = "";
		strcpy(newPath, path);
		strcat(newPath, "/");
		strcat(newPath, entry->d_name);
		struct stat* buffer = malloc(sizeof(struct stat));
		stat(newPath, buffer);
		totalDirSize += buffer->st_size;
	}
	dir = opendir(path);
	entry = readdir(dir);
	entry = readdir(dir);
	for(int i = 0; i < max && (entry = readdir(dir)); i++){
		if(entry->d_type == DT_DIR){
			//concatenate name to path then call printStats on it
			char newPath[1000] = "";
			strcpy(newPath, path);
			strcat(newPath, "/");
			strcat(newPath, entry->d_name);
			printStats(newPath, max);
		} else {
			char newPath[1000] = "";
			strcpy(newPath, path);
			strcat(newPath, "/");
			strcat(newPath, entry->d_name);
			printf("Stats for %s: \n", newPath);
			struct stat* buffer = malloc(sizeof(struct stat));
			stat(newPath, buffer);

			uid_t userID = buffer->st_uid;
			off_t sizeOfFile = buffer->st_size;
			time_t accessTime = buffer->st_atime;
			time_t currentTime = time(0);

			time_t timeSinceAccess = currentTime - accessTime;

			printf("Owner ID:\t%d\n", userID);
			printf("File size:\t%.2f%%\n", ((double)sizeOfFile/(double)totalDirSize)*100);
			printf("Last access:\t%ld seconds ago\n", timeSinceAccess);

			//printStats();
		}
	}
	// TODO: Put code here.
}

/*
void recOpenDirs(DIR* dir, int max){
	for(int i = 0; i < max; i++){
		struct dirent* entry = readdir(dir);
		if(entry == NULL){
			continue;
		} else if(entry->d_type == DT_DIR){
			recOpenDirs(entry, max);
		} else {
			printf("name %s", entry->d_name);
			//printStats();
		}
	}
}
*/

int main(int argc, char** argv) {

	if (argc < 3) {

		printf("Wrong number of args, expected 2, given %d", argc - 1);
		exit(1);
	}

	printStats(argv[1], atoi(argv[2]));
}
