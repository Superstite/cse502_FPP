#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h> //defines miscellaneous symbolic constants and types.


/* Section-1: Declaration of global variables */
char* message;
volatile int shutdown = 0;
pthread_mutex_t lock;
pthread_cond_t cond;
pthread_t thread;

/* Section-2: Worker thread routine */
void* worker_routine(void* args) {
// Consumer code here to consume the “message” created by the producer.
// Terminate if producer has flagged “shutdown”.
	if(shutdown==1){
		return NULL;
	}

	pthread_mutex_lock(&lock);
	if(*message!='C')
		pthread_cond_wait(&cond, &lock);

	else{
		pthread_cond_signal(&cond);
		printf("Message consumed");
		*message='X';
	}
	
	pthread_mutex_unlock(&lock);
	printf("Releasing lock");
	return NULL;
}


/* Section-3: Creation of consumer thread */
void initialize() {
	
	int status;

	if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
     	return;
    }

    if (pthread_cond_init(&cond, NULL) != 0) {
    	printf("\n cond init has failed\n");
        return;
    }

	status = pthread_create(&thread, NULL, worker_routine, NULL);
	if(status!=0) {
		printf("Thread not created");
	}
	return;
}

/* Section-4: Sending message to the consumer by the producer */
void sendMessage(int numMessages) {
	for(int i=0; i<numMessages; i++) {
		// Create message and inform consumer
		//.....
		pthread_mutex_lock(&lock);
		*message = 'C';
		pthread_mutex_unlock(&lock);
		sleep(1); // wait for the message to be consumed
	}

}


/* Section-5: Terminate the consumer thread */
void finalize() {
	pthread_mutex_lock(&lock);
	shutdown = 1;
	pthread_mutex_unlock(&lock);
	int status = pthread_join(thread, NULL);
}


int main(int argc, char ** argv) {
	int numMessages = argc>1?atoi(argv[1]) : 4;
	message = (char*)malloc(sizeof(char));
	initialize();
	sendMessage(numMessages);
	finalize();
	return 0;
}
