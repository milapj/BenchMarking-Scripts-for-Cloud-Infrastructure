#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
int no_of_threads;
long long int block_size;
struct timeval begin, end;
long long i;
long long int fileSize = 10000000000;
char *buffer;
FILE *fileRead;
FILE *fileWrite;
long long filePointer = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
char type[10];
char tempBlockSize[10];
char tempThreads[10];
    

void *sequentialRead(void *args) {	//Function to read sequentially
	pthread_mutex_lock(&mutex);
	
	//block_size = 1000000;
	//block_size = 1048576;
	long long int counter = 0;
	//printf("%d\n", block_size);
	int m = (int *)args;
	///printf("%d\n",m );
	buffer = (char *) malloc(block_size * sizeof(char));  		
    long fileCurrentPointer = (m * (fileSize/no_of_threads)); // Pointer that points to start of the file for each thread, thread 0: ptr:0; thread 1: ptr:50000000000 
    fseek(fileRead, fileCurrentPointer, SEEK_SET); 				//sets the pointer of the file to start reading
    //printf("%d\n", (fileSize/block_size)/ no_of_threads);
    for (i = 0; i < (fileSize/(block_size*no_of_threads));i++) {
   		if(((fileSize/block_size)/no_of_threads - counter > block_size)) {
   			break;
   		}
   		//fseek(fileRead, fileCurrentPointer + block_size, SEEK_SET);
   		//printf("%d\n", i);
   		fgets(buffer, block_size,fileRead); 		//read function, stores the value into buffer
   		counter = counter + block_size;
    }
	
    free(buffer);
    //fclose(fileRead);
    //m = m + 1;
    pthread_mutex_unlock(&mutex);
    
}

void *sequentialWrite(void *args) {
	pthread_mutex_lock(&mutex);
	//block_size = 1000000;
	//block_size = 1048576;
	long long int counter = 0;
	//printf("%d\n", block_size);
	int m = (int *)args;
	///printf("%d\n",m );
	buffer = (char *) malloc(block_size * sizeof(char));  		
    long fileCurrentPointer = (m * (fileSize/no_of_threads));
    fseek(fileWrite, fileCurrentPointer, SEEK_SET);
    memset(buffer,'ABCDEFGHHIJKLMNOPQRSTUVWXYZ',block_size);
    //printf("%d\n", (fileSize/block_size)/ no_of_threads);
    for (i = 0; i < (fileSize/(block_size*no_of_threads));i++) {
   		if(fileSize - counter < block_size) {
   			break;
   		}
   		fseek(fileWrite, counter, SEEK_SET);
   		//printf("%d\n", i);
   		fputs(buffer,fileWrite);
   		counter = counter + block_size;
    }
	
    free(buffer);
    //fclose(fileRead);
    //m = m + 1;
    pthread_mutex_unlock(&mutex);
}

void *randomRead(void *args) {
	pthread_mutex_lock(&mutex);
	time_t t;
	long long int counter = 0;
	int m = (int *)args;
	if (tempBlockSize == 1000) {
		buffer = (char *) malloc(block_size * sizeof(char));  		
    	long fileCurrentPointer = (m * (fileSize/no_of_threads));
    	fseek(fileRead, fileCurrentPointer, SEEK_SET);
    //printf("%d\n", (fileSize/block_size)/ no_of_threads);
    	srand((unsigned) time(&t));
    	for (i = 0; i < 1000000;i++) {
   			if(fileSize - counter < block_size) {
   				break;
   			}
   		//fseek(fileRead, fileCurrentPointer + block_size, SEEK_SET);
   		//printf("%d\n", i);
   		long int random = rand() % ((fileSize/no_of_threads) - block_size); 
   		//random = random + (fileSize/(block_size*no_of_threads));
   		//printf("%ld\n", random);
   		random = random + fileCurrentPointer;
   		fseek(fileRead,random ,SEEK_SET);
   		fgets(buffer, 1,fileRead);
   		counter = counter + block_size;
   		free(buffer);
    	}
	}
	else {
	//block_size = 1000000;
	//block_size = 1048576;
		
	//printf("%d\n", block_size);
		
	///printf("%d\n",m );
		buffer = (char *) malloc(block_size * sizeof(char));  		
    	long fileCurrentPointer = (m * (fileSize/no_of_threads));
    	fseek(fileRead, fileCurrentPointer, SEEK_SET);
    //printf("%d\n", (fileSize/block_size)/ no_of_threads);
    	srand((unsigned) time(&t));
    	for (i = 0; i < (fileSize/(block_size*no_of_threads));i++) {
   			if(fileSize - counter < block_size) {
   				break;
   			}
   		//fseek(fileRead, fileCurrentPointer + block_size, SEEK_SET);
   		//printf("%d\n", i);
   		long int random = rand() % ((fileSize/no_of_threads) - block_size); 
   		//random = random + (fileSize/(block_size*no_of_threads));
   		//printf("%ld\n", random);
   		random = random + fileCurrentPointer;
   		fseek(fileRead,random ,SEEK_SET);
   		fgets(buffer, block_size,fileRead);
   		counter = counter + block_size;
    	}
	
    free(buffer);
    //fclose(fileRead);
    //m = m + 1;
	}

}

void *randomWrite(void *args) {
	pthread_mutex_lock(&mutex);
	time_t t;
	long long int counter = 0;
	int m = (int *)args;
	if (tempBlockSize == 1000) {
		int m = (int *)args;
	///printf("%d\n",m );
		buffer = (char *) malloc(block_size * sizeof(char));  		
    	long fileCurrentPointer = (m * (fileSize/no_of_threads));
    	fseek(fileRead, fileCurrentPointer, SEEK_SET);
    	memset(buffer,'ABCDEFGHHIJKLMNOPQRSTUVWXYZ',block_size);
    //printf("%d\n", (fileSize/block_size)/ no_of_threads);
    	srand((unsigned) time(&t));
    	for (i = 0; i < 1000000;i++) {
   			if(((fileSize/block_size)/no_of_threads - counter > block_size)) {
   			break;
   			}
   		//fseek(fileRead, fileCurrentPointer + block_size, SEEK_SET);
   		//printf("%d\n", i);
   		long int random = rand() % ((fileSize/no_of_threads) - block_size); 
   		//random = random + (fileSize/(block_size*no_of_threads));
   		//printf("%ld\n", random);
   		random = random + fileCurrentPointer;
   		fseek(fileWrite,random ,SEEK_SET);
   		fputs(buffer,fileWrite);
   		counter = counter + block_size;
    	}
	
    	free(buffer);
	} 
	else {
	//block_size = 1000000;
	//block_size = 1048576;
		//intf("%d\n", block_size);
		//rintf("%d\n",m );
		buffer = (char *) malloc(block_size * sizeof(char));  		
    	long fileCurrentPointer = (m * (fileSize/no_of_threads));
    	fseek(fileRead, fileCurrentPointer, SEEK_SET);
    	memset(buffer,'ABCDEFGHHIJKLMNOPQRSTUVWXYZ',block_size);
    //printf("%d\n", (fileSize/block_size)/ no_of_threads);
    	srand((unsigned) time(&t));
    	for (i = 0; i < (fileSize/(block_size*no_of_threads));i++) {
   			if(((fileSize/block_size)/no_of_threads - counter > block_size)) {
   				break;
   			}
   		//fseek(fileRead, fileCurrentPointer + block_size, SEEK_SET);
   		//printf("%d\n", i);
   		long int random = rand() % ((fileSize/no_of_threads) - block_size); 
   		//random = random + (fileSize/(block_size*no_of_threads));
   		//printf("%ld\n", random);
   		random = random + fileCurrentPointer;
   		fseek(fileWrite,random ,SEEK_SET);
   		fputs(buffer,fileWrite);
   		counter = counter + block_size;
    	}
	
   	 	free(buffer);
    //fclose(fileRead);
    //m = m + 1;
    }
    pthread_mutex_unlock(&mutex);

}



int main(int argc, char *argv[]) {
    int rc;
    int j;
    //int tid;
    time_t t;
    pthread_t tid;
    float diskThroughput;
    float theoreticalVal = 600.00;
    float efficiency;
    float latency;
    float theoreticalLat = 4.16;
    float iops;
    float latEff;
    FILE *file = fopen(argv[1],"rt");
    if(file == NULL){
     printf("\n The file is Null \n");   
    }
    fgets(type, sizeof(type), file);
    fgets(tempBlockSize, sizeof(tempBlockSize), file);
    block_size = atoi(tempBlockSize) * 1000 * sizeof(char);
    //printf("%d\n", block_size);
    fgets(tempThreads, sizeof(tempThreads), file);
    no_of_threads = atoi(tempThreads);
    fclose(file);
    //pthread_t threads[no_of_threads];
    //pthread_mutex_init(&mutex, NULL);
    //shared_var = 0;
    gettimeofday(&begin, NULL);
    if(strncmp(type, "RR", 2) == 0){
    	if (pthread_mutex_init(&mutex, NULL) != 0)
    	{
        	printf("\n mutex init has failed\n");
        	return 1;
    	}
        for(j= 0; j < no_of_threads; j++){
        	fileRead = fopen("disk_bench_read.txt","r");
			if (fileRead == NULL) {
    		printf("Could not open file");
   			}
        	pthread_create(&tid, NULL, randomRead, (void *)j);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(j = 0; j < no_of_threads; j++){
        pthread_join(tid, NULL);
        //if(rc){
         //printf("Cound not join the thread\n");   
        //}
    	}
    	fclose(fileRead);  
        pthread_mutex_destroy(&mutex);   
    }
	else if(strncmp(type, "WR", 2) == 0) {
		for(j = 0; j < no_of_threads; j++){
            pthread_create(&tid, NULL, randomWrite, (void *)j);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(j = 0; j < no_of_threads; j++){
        pthread_join(tid, NULL);
        //if(rc){
         //printf("Cound not join the thread\n");   
        //}
    	}

	} 
    else if(strncmp(type,"RS",2) == 0) {
        if (pthread_mutex_init(&mutex, NULL) != 0)
    	{
        	printf("\n mutex init has failed\n");
        	return 1;
    	}
        for(j = 0; j < no_of_threads; j++){
            fileRead = fopen("disk_bench_read.txt","r");
			if (fileRead == NULL) {
    		printf("Could not open file");
   			}
   			pthread_create(&tid, NULL, sequentialRead, (void *)j);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        //
        for(j = 0; j < no_of_threads; j++){
        pthread_join(tid, NULL);
        //if(rc){
         //printf("Cound not join the thread\n");   
        //}
        } 
        fclose(fileRead);  
        pthread_mutex_destroy(&mutex);
    }

    else if(strncmp(type, "WS",2) == 0) {
    	if (pthread_mutex_init(&mutex, NULL) != 0)
    	{
        	printf("\n mutex init has failed\n");
        	return 1;
    	}
    	for(j = 0; j < no_of_threads; j++){
            fileWrite = fopen("disk_bench_write.txt", "w+");
            if (fileWrite == NULL) {
    			printf("Could not open file");
   			}
			//buffer = (char *)malloc(block_size * sizeof(char)); 
    		//memset(buffer,'a',block_size);
            pthread_create(&tid, NULL, sequentialWrite, (void *)j);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(j = 0; j < no_of_threads; j++){
        pthread_join(tid, NULL);
        //if(rc){
         //printf("Cound not join the thread\n");   
        //}
        }
        pthread_mutex_destroy(&mutex);
        fclose(fileWrite);  
        
    }
    gettimeofday(&end,NULL);
    double elapsed = (end.tv_sec - begin.tv_sec) + 
              ((end.tv_usec - begin.tv_usec)/1000000.0);
    diskThroughput = (10/elapsed) * 1000;
    efficiency = (diskThroughput/theoreticalVal) * 100;
    if (tempBlockSize == 1) {
    	latency = elapsed/1000;
    	iops = (theoreticalVal*1000000)/block_size;
    	latEff = (latency/theoreticalLat)*100;
    	printf("\nWorkLoad 	Concurrency 	BlockSize 	MyLatency 	MyIOPS 		TheoreticalLatency 	Efficiency\n"); 
		printf("%.2s		%d		%d		%.2f		%.2f		%f		  %.2f",type,no_of_threads,block_size,latency,iops,theoreticalLat,latEff);
    }
    else {
    	printf("WorkLoad Concurrency BlockSize MyDiskThroughput TheoreticalThroughput Efficiency\n");    
    	printf("%s 		%d         %d         %lf                   %lf                   %lf\n",type,no_of_threads,block_size,diskThroughput,theoreticalVal,efficiency);
    }
    //printf("Memory Benchmarking Ends.\n"); 
    return 0;
}


