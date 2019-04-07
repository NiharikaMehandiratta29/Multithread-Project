#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>
#include<pthread.h>
#include<semaphore.h
sem_t wrt , mutex;
int shared = 0, readCount = 0;



void *writer(void *args)
{
	int id;
	id = ((int) args);
	sem_wait(&wrt);
	shared++;
	printf("The writer process %d has updated the shared value to %d\n",id+1,shared);
	sem_post(&wrt);

}

void *reader(void *args)
{
	int id;
	id = ((int) args);
	sem_wait(&mutex);
	readCount++;
	if(readCount == 1) // the first reader will not allow the writers to enter the critical condition
	{
		sem_wait(&wrt);
	}
	sem_post(&mutex);
	printf("The reader process %d has entered the critical condition and the shared value is %d\n" , id+1,shared);

	sleep(1);

	sem_wait(&mutex);
	readCount--;
	if(readCount==0)
	{
		sem_post(&wrt);
	}
	sem_post(&mutex);

}
int main()
{
	pthread_t   write_thread[5];
	sem_init(&wrt , 0 , 1);

	int i;
	for(i = 0 ; i< 5 ; i++)
	{
		pthread_create(&write_thread[i], NULL , writer , (void *) i );
		pthread_create(&read_thread[i], NULL , reader , (void *) i);
	}
	for(i = 0 ; i< 5 ; i++)
	{
		pthread_join(write_thread[i], NULL);
		pthread_join(write_thread[i], NULL);
	}
	return 0;
}
