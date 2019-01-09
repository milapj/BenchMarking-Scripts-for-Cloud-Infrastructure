#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#define SIZE 1000000000         // Declaring 1 GB size 
int no_of_threads;              // holds the number of threads specified in the .dat file
int block_size;
char *src;                      //initializing the source array
char *dest;                     //initializing the destination array
struct timeval begin, end;  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;      //Mutex initializer

       
//int blocks = 0;

void *sequentialReadWrite(void *args){
    pthread_mutex_lock(&mutex); //locks this function to a thread
    int o,m;
    int offset = 0;             //The offset that increments according to the block size
    if(block_size > 1) {
        //printf("%d\n", no_of_threads );
        for(o=0;o<100/no_of_threads;o++) {          // The 100x operations divided by number of threads.
            for (m = 0; m<SIZE/block_size * sizeof(char); m++) {
                memcpy(dest + offset, src + offset, block_size* sizeof(char));  //copies the block size data from destination to source 
                offset = offset + block_size * sizeof(char) ;   //ncrements the pointer
                if (offset == SIZE) { //prevent offset overflow
                    offset = 0;
                }
                if (offset > SIZE) { // prevent offset overflow
                    break;
                }
            }
        }
    }
    else if (block_size == 1) {
        //printf("Latency Calculation");
        for(o=0;o<50000000/no_of_threads;o++) { // 50 million iterations
            memcpy(dest + offset, src + offset, block_size * sizeof(char)); //Since memcpy is read + write function thus total of 100 million
            offset = offset + block_size ;
            if (offset == SIZE) { // prevent offset overflow
                offset = 0;
            } 
            if (offset > SIZE) { // prevent offset overflow
                    break;
            }   
        }
    }
    pthread_mutex_unlock(&mutex); //unlock the function
    
}

void *randomReadWrite(void *args) {
    pthread_mutex_lock(&mutex);
    time_t t;
    int o,m;
    srand((unsigned) time(&t));
    if(block_size > 1) {    
        printf("%d\n", no_of_threads);
        for(o=0;o<100/no_of_threads;o++) {
            for (m = 0; m<SIZE/block_size * sizeof(char); m++) {
                int offset = rand() % ((SIZE/no_of_threads) - block_size);  //Random function to choose a random offset
                memcpy(dest + offset, src + offset, block_size * sizeof(char));
                offset = offset + block_size ;
                if (offset == SIZE) {
                    offset = 0;
                }
                if (offset > SIZE) {
                    break;
                }
            }
        }
    }
    else if (block_size == 1){  //Latency Calculation
        //printf("Latency Calculation");
        for(o=0;o<50000000/no_of_threads;o++) {
            int offset = rand() % ((50000000/no_of_threads) - block_size);
            memcpy(dest + offset, src + offset, block_size * sizeof(char));
            offset = offset + block_size ;
            if (offset == SIZE) {
                offset = 0;
            }
            if (offset > SIZE) {
                    break;
            }    
        }
    }
    pthread_mutex_unlock(&mutex);
}


//FILL ME IN
int main(int argc, char *argv[]) {
    char type[10];      //Type of Worload from .dat file
    char tempBlockSize[10];     //Block Size from .dat file
    char tempThreads[10];   //Number of Threads from .dat fle
    int rc;
    //int tid;
    int i;
    time_t t;
    pthread_t tid;
    float ramSpeed = 2.13; //2133MHZ - DDR3
    float dataBus = 8.00; //64bits: 8bytes
    float no_of_CPU = 2.00; // Number of CPUS on the cluster
    float theoreticalVal = ramSpeed * dataBus * no_of_CPU;  //Theoretical Value Calculation
    float theoreticalValLatency = 0.057;
    float ramBenchlatncy;
    float latencyEff;
    
   
    src = (char *) malloc(SIZE * sizeof(char)); 
    dest = (char *) malloc(SIZE * sizeof(char));
    srand((unsigned) time(&t));
    for( i = 0 ; i < SIZE ; i++ ) {         //Fill up the source array with random characters
      src[i] = rand() % 10;
    }
    //printf("Source and Destination have been reserverd\n");
    //printf("%ld\n", malloc_size(src));
    FILE *file = fopen(argv[1],"rt");       // Open the .dat file
    if(file == NULL){
     printf("\n The file is Null \n");   
    }
    fgets(type, sizeof(type), file);
    fgets(tempBlockSize, sizeof(tempBlockSize), file);
    block_size = atoi(tempBlockSize) * sizeof(char);
    fgets(tempThreads, sizeof(tempThreads), file);
    no_of_threads = atoi(tempThreads);
    fclose(file);
    
    //pthread_t threads[no_of_threads];
    //pthread_mutex_init(&mutex, NULL);
    //shared_var = 0;
    gettimeofday(&begin, NULL); //Function to record total time taken
    if(strncmp(type, "RWS", 3) == 0){
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, sequentialReadWrite, (void *)i);     //Create threads
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(i = 0; i < no_of_threads; i++){
        pthread_join(tid, NULL);        //Join Threads
        //if(rc){
         //printf("Cound not join the thread\n");   
        //}
        }
        pthread_mutex_destroy(&mutex);     //Destroy the mutex once the function is executed
    } 
    else {
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, randomReadWrite, (void *)i);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(i = 0; i < no_of_threads; i++){
        pthread_join(tid, NULL);
        //if(rc){
         //printf("Cound not join the thread\n");   
        //}
        }
        pthread_mutex_destroy(&mutex);     
    }
    gettimeofday(&end,NULL);
    float elapsed = (end.tv_sec - begin.tv_sec) * 1000000 +     //Time taken converting to seconds
              ((end.tv_usec - begin.tv_usec));
    float ramBenchGBs = 100/elapsed;  
    float effiency = ramBenchGBs*100/theoreticalVal; // Operating Over 100GB        
    
    //printf("%f\n", elapsed);
    //printf("%f\n", (107374182400/ elapsed) / 1000000000);
    //printf("Memory Benchmarking Ends.\n");
    printf("\n Workload Concurrency BlockSize MyRAMBenchValue TheoreticalValue MyRAMBenchEfficiency\n");
    if (block_size == 1) {
        ramBenchlatncy = elapsed/100000000;  //100 million
        latencyEff = (theoreticalValLatency /ramBenchlatncy) - 1;
        //printf("%f\n", elapsed);
        printf(" %.3s       %d         %d           %.6f         %.6f         %.6f",type ,no_of_threads, block_size, ramBenchlatncy, theoreticalValLatency, latencyEff);
    
    }
    else {
        printf(" %.3s       %d         %d           %.6f         %.6f         %.6f",type ,no_of_threads, block_size, ramBenchGBs, theoreticalVal, effiency);
    }
    return 0;
}


