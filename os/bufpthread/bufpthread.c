#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TNUM 3
#define MAX 10

static volatile char count = 0;
static volatile char end = 0;
static volatile char point = 0;
static volatile char *buffer;

pthread_cond_t empty;
pthread_cond_t fill;
pthread_mutex_t mutex;

void put(char data){
	buffer[end++] = data;
	end %= MAX;
	count++;
}

char get(){
	char data= buffer[point++];
	point %= MAX;
	count--;
	return data;
}

void *producer(void *arg){

	char *data = (char *)arg;
	char i;
	for (i =data[0]; i <= data[1]; i++) {
	        pthread_mutex_lock(&mutex);
        while(count == MAX)
		pthread_cond_wait(&empty, &mutex);
        if(i > 'Z' && i < 'a') {
		i = 'a';
	}
        put(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg){
	char tn;
	char *data = (char *)arg;
	char i;
	for (i = data[0]; i <= data[1]; i++) {
		pthread_mutex_lock(&mutex);
	        while(count == 0)
			pthread_cond_wait(&fill,&mutex);
			tn = get();
			printf(tn > 50?"%c":"%d",tn);
			printf(i % 10?"\t":"\n");
			pthread_cond_signal(&empty);
			pthread_mutex_unlock(&mutex);
    	}
}

int main(int argc, char *argv[]) {
	pthread_t pt[TNUM];
	char i,j;
	char tn[TNUM][2] = { 
		{'A','z'},
		{1,50},
		{1,102}
	};
	buffer = calloc(0,sizeof(char)* MAX);
	pthread_create(&pt[0],NULL,producer,(void *)tn[0]);
	pthread_create(&pt[1],NULL,producer,(void *)tn[1]);
	pthread_create(&pt[2],NULL,consumer,(void *)tn[2]);

	for (i = 0;i < TNUM; i++)pthread_join(pt[i], NULL);
	printf("\n");
    	return 0;
}
