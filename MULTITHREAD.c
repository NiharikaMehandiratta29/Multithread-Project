#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>
#include<pthread.h>

pthread_mutex_t wrt  , mutex;
int shared = 0, readCount = 0;



void *writer(void *args)
{
	int id;
	id = ((int) args);
	pthread_mutex_lock(&wrt);
	shared++;
	printf("The writer process %d has updated the shared value to %d\n",id+1,shared);
	pthread_mutex_unlock(&wrt);

}

void *reader(void *args)
{
	int id;
	id = ((int) args);
	pthread_mutex_lock(&mutex);
	readCount++;
	if(readCount == 1) // the first reader will not allow the writers to enter the critical condition
	{
		pthread_mutex_lock(&wrt);
	}
	pthread_mutex_unlock(&mutex);
	printf("The reader process %d has entered the critical condition and the shared value is %d\n" , id+1,shared);

	sleep(1);

	pthread_mutex_lock(&mutex);
	readCount--;
	if(readCount==0)
	{
		pthread_mutex_unlock(&wrt);
	}
	pthread_mutex_unlock(&mutex);

}
int main()
{
	pthread_t read_thread[5],  write_thread[5];
    pthread_mutex_init(&wrt,NULL);
	pthread_mutex_init(&mutex,NULL);

	int i;
	for(i = 0 ; i< 5 ; i++)
	{
		pthread_create(&write_thread[i], NULL , writer , (void *) i );
		pthread_create(&read_thread[i], NULL , reader , (void *) i);
	}
	for(i = 0 ; i< 5 ; i++)
	{
		pthread_join(read_thread[i], NULL);
		pthread_join(write_thread[i], NULL);
	}
	pthread_mutex_destroy(&wrt);
	pthread_mutex_destroy(&mutex);
	return 0;
}
