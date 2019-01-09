#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define BUFF_SIZE 64
#define ERROR -1
int sockfd, newfd, rc;
#define PORT 8080
#define SIZE 1073741824		//Declare 1 GB file

int userInput = 1;
int no_of_threads;
int block_size;
char *src;
char *dest;
int loop;
unsigned long long int i;
int clientsock;

time_t t;
int valread,new_socket;
double elapsedTotal, elapsedClient, elapsedServer;
struct timeval beginClient, endClient;
struct timeval beginServer, endServer;
int new_socket;
int offset = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;   
char buffer[1024] = {0};
    
	

int setupTCPClient() {			//Setup the client
	//int offset = 0;
    src = (char *) malloc(SIZE * sizeof(char)); 
    srand((unsigned) time(&t));
    for( i = 0 ; i < SIZE ; i++ ) {
      src[i] = rand() % 10;
    }
    printf("Source Reserved\n");
    struct sockaddr_in address;
    clientsock = 0, valread;
    struct sockaddr_in client_addr;
    //char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((clientsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)	//Create Client Socket
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    else {
        printf("Client socket created\n");
    }
  
    memset(&client_addr, '0', sizeof(client_addr));
  
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr)<=0) //Connect to the server set up on the loop back address
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(clientsock, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0)	//Connect to the server socket
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    else {
    	//sendClient();
    	/*printf("Package Sent \n");
		for (loop = 0; loop < 100; loop ++) {
       		for (i =0; i < SIZE/block_size;i++) {
        		send(sock , src[offset] , block_size, 0);
        		offset = offset + block_size;
        		if (offset = SIZE) {
            		offset = 0;
        		}
       		}	 
    	}*/
    	//close(sock);
    }

    //printf("Hello message sent\n");
    //valread = read( sock , buffer, 1024);
    //printf("%s\n",buffer );
    return 0;
    
}

int sendClient(void *args) {			//Function to send data to the server
	pthread_mutex_lock(&mutex);
	
	gettimeofday(&beginClient, NULL);
    	for (loop = 0; loop < 100/no_of_threads; loop ++) {
       		for (i =0; i < SIZE/block_size;i++) {
        		send(clientsock , src[offset] , block_size, 0); //send data of block size from the source array
        		offset = offset + block_size;
        		if (offset = SIZE) {
            		offset = 0;
        		}
       		}	 
    	}
    gettimeofday(&endClient, NULL);
    pthread_mutex_unlock(&mutex);	
    return 0;
}


int sendLatency(void *args) {	//Latency Function
	pthread_mutex_lock(&mutex);
	
	gettimeofday(&beginClient, NULL);
    	for (loop = 0; loop < 1000000/no_of_threads; loop ++) {
       		send(clientsock , 'A' , 1 , 0);
        	read(clientsock , buffer, 1);	 
    	}
    gettimeofday(&endClient, NULL);
    pthread_mutex_unlock(&mutex);	
    return 0;
}


int setupTCPServer() {			//Setup Server
	dest = (char *) malloc(SIZE * sizeof(char));
    printf("Destination Reserved\n");
    int server_sock, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    //char *hello = "Hello from server";
    // Creating socket file descriptor
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) ///Create the socket
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Socket created\n");
    }
     // Bind the socket to port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_sock, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Server is Setup and bound to port 8080\n");
    }

    if (listen(server_sock, 3) < 0)	//Start listening on the socket created
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Listening for new connection\n");
        //setupTCPClient();
    }

    if ((new_socket = accept(server_sock, (struct sockaddr *)&address, 	//Accept any client connections
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Connection accepted\n");
    	
   
	}
    //valread = read( new_socket ,buffer, 1024);
    //printf("%s\n",buffer);
    //close(server_fd);
    
    return 0;
} 

int revServer(void *args) {		//Function for the server to receive the data and store it in dest array
	pthread_mutex_lock(&mutex);
	
	 for (loop = 0; loop < 100/no_of_threads; loop ++) {
       for (i =0; i < SIZE/block_size;i++) {
        read(new_socket , dest[offset], block_size);
        //printf("%s\n", dest[offset]);
        offset = offset + block_size;
        if (offset = SIZE) {
            offset = 0;
        }
       } 
    }
    pthread_mutex_unlock(&mutex);
	
}

int recvLatency(void *args) {
	pthread_mutex_lock(&mutex);
	
	gettimeofday(&beginClient, NULL);
    	for (loop = 0; loop < 1000000/no_of_threads; loop ++) {
       		read(new_socket , buffer, 1);
       		send(new_socket , 'A' , 1 , 0);
        		 
    	}
    gettimeofday(&endClient, NULL);
    pthread_mutex_unlock(&mutex);	
    return 0;
}

int main(int argc, char const *argv[]) {
	pthread_t tid;
	char type[10];
    char temp[10];
    //pthread_t tid;
    char *serviceType = argv[2];
    printf("%s\n", serviceType);
   
    FILE *file = fopen(argv[1],"rt");
    if(file == NULL){
     printf("\n The file is Null \n");   
    }
    fgets(type, sizeof(type), file);
    fgets(temp, sizeof(temp), file);
    block_size = atoi(temp);
    fgets(temp, sizeof(temp), file);
    no_of_threads = atoi(temp);
    fclose(file);
    //printf("The Block Size is:%d\n", block_size);
    printf("%s\n", serviceType);
    if(strncmp(type, "TCP", 3) == 0 && strncmp(serviceType, "Server", 6) == 0) {
     	setupTCPServer();
     	if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        if (block_size == 1) {
        	gettimeofday(&beginServer, NULL);
   			for(i = 0; i < no_of_threads; i++){
            	pthread_create(&tid, NULL, recvLatency, (void *)i);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        	}
        	for(i = 0; i < no_of_threads; i++){
        		pthread_join(tid, NULL);
        	}
        	gettimeofday(&endServer, NULL);
        }

     	gettimeofday(&beginServer, NULL);
     	for(i = 0; i < no_of_threads; i++){
     		pthread_create(&tid, NULL, revServer, (void *)i);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(i = 0; i < no_of_threads; i++){
        	pthread_join(tid, NULL);
        }
        gettimeofday(&endServer, NULL);
    
        elapsedServer = (endServer.tv_sec - beginServer.tv_sec) + 
              ((endServer.tv_usec - beginServer.tv_usec)/1000000.0);
	    printf("%f\n", elapsedServer );
	    pthread_mutex_destroy(&mutex);

   	}
   	else if (strncmp(type, "TCP", 3) == 0 && strncmp(serviceType, "Client", 5) == 0){
   		setupTCPClient();
   		if (pthread_mutex_init(&mutex, NULL) != 0)
        {
            printf("\n mutex init has failed\n");
            return 1;
        }
        if (block_size == 1) {
        	gettimeofday(&beginClient, NULL);
   			for(i = 0; i < no_of_threads; i++){
            	pthread_create(&tid, NULL, sendLatency, (void *)i);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        	}	
        	for(i = 0; i < no_of_threads; i++){
        		pthread_join(tid, NULL);
        	}
        	gettimeofday(&endClient, NULL);
        }
   		gettimeofday(&beginClient, NULL);
   		for(i = 0; i < no_of_threads; i++){
            pthread_create(&tid, NULL, sendClient, (void *)i);
            //if(rc){
            //printf("Counld not create a thread\n");   
            //}
        }
        for(i = 0; i < no_of_threads; i++){
        	pthread_join(tid, NULL);
        }
        gettimeofday(&endClient, NULL);
		elapsedClient = (endClient.tv_sec - beginClient.tv_sec) + 
        	      ((endClient.tv_usec - beginClient.tv_usec)/1000000.0);
    	printf("%f\n", elapsedClient );	

   	}

   	//elapsedTotal = elapsedServer + elapsedClient;
   	//printf("%f\n", elapsedTotal);
   	//printf("Time:");
   	return 0;
}





