#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#define SIZE 100000000000
int no_of_threads;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
   
//int blocks = 0;

void *quadraticPrecision(void *args){
    pthread_mutex_lock(&mutex);
    unsigned long long int i;
    unsigned long long int *r;
    r = (long int*) args;
    //printf("%ld\n", r);
    char a = 3;
    for (i = 0; i < r;i++) {
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
    }
    pthread_mutex_unlock(&mutex);
}

void *halfPrecision(void *args){
    pthread_mutex_lock(&mutex);
    unsigned long long int i;
    unsigned long long int *r;
    r = (long int*) args;
    //printf("%ld\n", r);
    short a = 3;;
    for (i = 0; i < r;i++) {
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
    }
    pthread_mutex_unlock(&mutex);
}

void *singlePrecision(void *args){
    pthread_mutex_lock(&mutex);
    unsigned long long int i;
    unsigned long long int *r;
    r = (long int*) args;
    //printf("%ld\n", r);
    int a = 3;
    for (i = 0; i < r;i++) {
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
    }
    pthread_mutex_unlock(&mutex);
}

void *doublePrecision(void *args){
    pthread_mutex_lock(&mutex);
    unsigned long long int i;
    unsigned long long int *r;
    r = (long int*) args;
    //printf("%ld\n", r);
    double a = 3;
    for (i = 0; i < r;i++) {
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
        a+a;
    }
    pthread_mutex_unlock(&mutex);
}

//FILL ME IN
int main(int argc, char *argv[]) {
    char type[10];
    char tempBlockSize[10];
    char tempThreads[10];
    int rc;
    //int tid;
    int i;
    //time_t t;
    pthread_t tid;
    struct timeval begin, end;
    float gigOps;
    float eff;
    float theoreticalVal = 73.6;
   
    FILE *file = fopen(argv[1],"rt");
    if(file == NULL){
     printf("\n The file is Null \n");   
    }
    fgets(type, sizeof(type), file);
    //fgets(temp, sizeof(temp), file);
    //block_size = atoi(temp);
    fgets(tempThreads, sizeof(tempThreads), file);
    no_of_threads = atoi(tempThreads);
    fclose(file);
    //printf("%s\n", type);
    //printf("%d\n", no_of_threads);
    long long int r = SIZE/no_of_threads;
    
    //pthread_t threads[no_of_threads];
    //pthread_mutex_init(&mutex, NULL);
    //shared_var = 0;
   // clock_t begin = clock();
    gettimeofday(&begin, NULL);
    if(strncmp(type, "QP", 2) == 0 ){
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, quadraticPrecision, (void *)r);
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
        //printf("Quadratic Precision\n");
    } 
    else if (strncmp(type, "HP", 2) == 0)  {
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, quadraticPrecision, (void *)r);
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
        //printf("Half Precision\n");
    }
    
    else if (strncmp(type, "SP", 2) == 0)  {
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, singlePrecision, (void *)r);
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
        //printf("Single Precision\n"); 
    }
    else if (strncmp(type, "DP", 2) == 0)  {
        if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, doublePrecision, (void *)r);
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
        //printf("Double Precision\n");
    }
    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - begin.tv_sec) + 
              ((end.tv_usec - begin.tv_usec)/1000000.0);
    gigOps = 1000/elapsed;
    eff = (gigOps * 100)/theoreticalVal;
    //clock_t end = clock();
    //double time_taken = ((double)(end-begin))/CLOCKS_PER_SEC;
    //printf("%f\n", elapsed );
    //printf("%f\n", (107374182400/ time_taken) / 1000000000);
    printf("Workload Concurrencey MyCPUBenchValue TheroticalValue Efficiencey\n");
    printf("%.2s\t %d\t %f\t %f\t %f",type,no_of_threads,gigOps,theoreticalVal,eff);
    return 0;
}




