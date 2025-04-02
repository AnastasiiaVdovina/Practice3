#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_THREADS 10000

void *thread_func(void *arg){
	sleep(1);
	return NULL;
}

int main(){
	pthread_t threads[MAX_THREADS];
	int i;

	for(i = 0; i < MAX_THREADS; i++){
		if(pthread_create(&threads[1], NULL, thread_func, NULL) != 0) {
			printf("Unavailable to create thread #%d.\n",i);
			break;
		}
	}

	printf("%d threads was created\n", i);

	for(int j = 0; j<i; j++){
		pthread_join(threads[j], NULL);
	}

	return 0;
}
