#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h>
#include<conio.h>
#include<pthread.h>
pthread_mutex_t lock;
int shared = 0;
void *thread_function(void *args)
{
	pthread_mutex_lock(&lock);
	shared++; //critical condition
	pthread_mutex_unlock(&lock);
}
int main()
{	
	pthread_t thread[5];
	int i;
	for(i = 0 ; i< 5 ; i++)
	{
		pthread_create(&thread[i], NULL , thread_function , NULL);
	}
	for(i = 0 ; i< 5 ; i++)
	{
		pthread_join(thread[i], NULL);
	}
	return 0;
}
