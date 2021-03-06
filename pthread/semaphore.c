/*producer and constmer*/
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<semaphore.h>
sem_t pro_sem;
sem_t cus_sem;
int good = 0;
void *customer(void *argv)
{
	while(1)
	{
		sem_wait(&cus_sem);
		good--;
		printf("customer:%d\n",good);
		sem_post(&pro_sem);
	}
	return NULL;
}
void *producer(void *argv)
{
	while(1)
	{
		sem_wait(&pro_sem);
		good++;
		printf("producer:%d\n",good);
		sem_post(&cus_sem);
	}
	return NULL;
}
void main()
{
	pthread_t pt1,pt2;
	sem_init(&pro_sem,0,3);//3 is product read the data at same time
	sem_init(&cus_sem,0,0);
	pthread_create(&pt1,NULL,customer,NULL);
	pthread_create(&pt2,NULL,producer,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	sem_destroy(&pro_sem);
	sem_destroy(&cus_sem);
}
