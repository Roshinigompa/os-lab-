#include<stdio.h>
#include <pthread.h> 
#include <semaphore.h> 
#include<stdlib.h>
#include<unistd.h>
#define n 5 //number of philosophers
#define THINKING  1
#define HUNGRY 2 
#define EATING 0 
#define LEFT (phili + 4) % n 
#define RIGHT (phili + 1) % n 

int state[n],i=0; 
int phil[n]; 
int c=0;
sem_t mutex; 
sem_t S[n]; 
void test(int phili) 
{ 
	if (state[phili] == HUNGRY 
		&& state[LEFT] != EATING 
		&& state[RIGHT] != EATING) { 
		// state that eating 
		state[phili] = EATING; 

		sleep(2); 

		printf("Philosopher %d -> takes chops (%d,%d)\n", 
					phili + 1, LEFT + 1, phili + 1); 
printf("==>Philosopher %d is Eating\n", phili + 1); 
		sem_post(&S[phili]);
	} 
} 

// take up chopsticks 
void take_fork(int phili) 
{ 
	sem_wait(&mutex); 

	// state that hungry 
	state[phili] = HUNGRY; 
	printf("\tPhilosopher %d is Hungry\n", phili + 1); 
	// eat if neighbours are not eating 
	test(phili); 
	sem_post(&mutex); 
// if unable to eat wait to be signalled 
	sem_wait(&S[phili]); 

	sleep(1); 
} 

// put down chopsticks 
void put_fork(int phili) 
{ 
	sem_wait(&mutex); 
// state that thinking 
	state[phili] = THINKING; 

	printf("Philosopher %d -> puts down chops (%d,%d)\n", 
		phili + 1, LEFT + 1, phili + 1); 
	c= c+1;
	if (c==6)
	{
		exit(0);
	}
	printf("Philosopher %d is thinking\n", phili + 1); 

	test(LEFT); 
	test(RIGHT); 

	sem_post(&mutex); 
	
} 

void* philospher(void* num) 
{ 
	while (1) { 
		int* i = num; 
		sleep(1); 
		take_fork(*i); 

		sleep(0); 

		put_fork(*i);
		} 
} 
int main() 
{
while(i<n){
	phil[i]=i;
i++;

	} 
	int i; 
	pthread_t thread_id[n];  
         // initialize the semaphores 
	sem_init(&mutex, 0, 1); 
	for (i = 0; i < n; i++) 
		{ sem_init(&S[i], 0, 0); }
for (i = 0; i < n; i++) { 
	// create philosopher processes 
		pthread_create(&thread_id[i], NULL,philospher, &phil[i]); 
printf("Philosopher %d is thinking\n", i+1); 
	} 
	for (i = 0; i < n; i++) 
pthread_join(thread_id[i], NULL); 
}
