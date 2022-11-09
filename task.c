#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"

pthread_mutex_t lock;
sem_t * empty;
sem_t * full;
int response_time[NUMBER_OF_PROCESSES];
int turn_around_time[NUMBER_OF_PROCESSES];
timeal

struct Buffer * buffer; 

// int process_num = 0;

void* produce(void* arg){
	while (1){
		sem_wait(&full);
        struct * p = generateProcess();
        //mutex_lock
        pthread_mutex_lock(&lock);
		/*--critical section*/
        add(buffer,p);
        // process_num++;
		/*--end of critical section*/
        //mutex unlock
        pthread_mutex_unlock(&lock);
        sem_post(&empty);
	}
}

void* consume(void* arg){
	int * consumer_index = int*(arg);
	struct timeval t_start,t_end;
	int previous_burst_time = 0;
	while (1){
		sem_wait(&empty);
		//mutex_lock
		pthread_mutex_lock(&lock);
		/*--critical section*/
        struct * p = remove(buffer);
        // process_num --;
        previous_burst_time = p->iBurstTime;
        simulateRoundRobinProcess(p,&t_start,&t_end);
        printf("Consumer ID = %d, Process ID = %d, Previous Burst Time =%d, New Burst Time =%d",
        	                  consumer_index,p->iProcessId,previous_burst_time,p->iBurstTime);
        if(p->iState == NEW){
        	response_time[p->iProcessId] = getDifferenceInMilliSeconds(t_start,p->oTimeCreated);
        	printf(", Response Time = %d\n",getDifferenceInMilliSeconds(t_start,p->oTimeCreated));
        }
        if(p->iState == READY){
        	add(buffer,p);
        	// process_num ++;
        	printf("\n");
        }
        if(p->iState == FINISHED){
        	turn_around_time[p->iProcessId] = getDifferenceInMilliSeconds(p->oTimeCreated,t_end);
        	printf(", Turn Around Time = %d\n",getDifferenceInMilliSeconds(p->oTimeCreated,t_end));
        }
		/*--end of critical section*/
        //mutex unlock
        pthread_mutex_unlock(&lock);
        sem_post(&full);
	}
}

int main(void){
    pthread_mutex_init(&lock, NULL);

    for(int j = 0; j < NUMBER_OF_PROCESSES; j++){
    	response_time[j] = 0;
        turn_around_time[j] = 0;
    }

    sem_init(&empty, 1, NUMBER_OF_PROCESSES);
    sem_init(&full, 1, 0);

    pthread_t producer_id;
    pthread_create(&producer_id, NULL, produce, NULL);

    pthread_t comsumer_id[NUMBER_OF_CONSUMERS];
    int consumer_index[NUMBER_OF_CONSUMERS];

    buffer = newBuffer();

    for(int i = 0; i < NUMBER_OF_CONSUMERS; i++){
    	consumer_index[NUMBER_OF_CONSUMERS] = i;
    	pthread_create(&consumer_id[i], NULL, consume, consumer_index+i);
    }

    pthread_join(producer_id, NULL);

    for(int i = 0; i < NUMBER_OF_CONSUMERS; i++){
    	pthread_join(consumer_id, NULL);
    }


    //calculate average response time and turn around time
    //TO DO
    int sum_response_time = 0;
    int sum_turn_around_time = 0;

    for(int k = 0; k < NUMBER_OF_PROCESSES;k++){
    	sum_response_time += response_time[k];
    	sum_turn_around_time += turn_around_time[k];
    }

    printf("Average response time = %lf",double(sum_response_time)/NUMBER_OF_PROCESSES);
    printf("Average turn around time = %lf",double(sum_turn_around_time)/NUMBER_OF_PROCESSES);

    pthread_mutex_destroy(&lock);
    sem_destroyed(&empty);
    sem_destroyed(&full);
}




















