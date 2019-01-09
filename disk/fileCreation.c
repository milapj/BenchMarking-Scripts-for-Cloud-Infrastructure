#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
long long int i;
long long int fileSize = 10000000000;
char *fileInput = "123456";
int main() {
	FILE *file = fopen("disk_bench_read.txt", "w");
    //fseek(file, fileSize , SEEK_SET);
    for (i = 0; i<fileSize;i++) {
    	fputc('X', file);
    }
    fclose(file);
    return 0;
}