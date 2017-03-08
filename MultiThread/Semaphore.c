#include <stdio.h>
#include <stdlib.h>
#define new(X) malloc(sizeof(X))
#include <pthread.h>
//Compile : gcc -pthread -std=c99
typedef struct {
	int s;
} Semaphore;

Semaphore* newSemaphore(int);
void Wait(Semaphore*);
void Signal(Semaphore*);


Semaphore* newSemaphore(int s) {
	Semaphore* semaphore = new(Semaphore);
	if(semaphore != NULL)
		semaphore->s = s;
	return semaphore;
}

void Wait(Semaphore* sem) {
	while(sem->s != 1); //Wait
	sem->s = 0;
}

void Signal(Semaphore* sem) {
	sem->s = 1;
}

Semaphore *s0,*s1,*s2;

void init() {
	s0 = newSemaphore(1);
	s1 = newSemaphore(0);
	s2 = newSemaphore(0);
	return;
}

void* t0(void* args) {
	while(1) {
		Wait(s0);
		printf("%d",0);
		Signal(s1);
		Signal(s2);
	}
	pthread_exit(NULL);
}

void* t1(void* args) {
	Wait(s1);
	Signal(s0);
	pthread_exit(NULL);
}

void* t2(void* args) {
	Wait(s2);
	Signal(s0);
	pthread_exit(NULL);
}

int main() {
	init();
	void* (*tArray [3])(void*) = {t0,t1,t2};
	//Array of Function Pointers 
	//Power of C! :P
	pthread_t threads[3];
	for(int i = 0 ; i<3 ; i++)
		pthread_create(&threads[i],NULL,tArray[i],NULL);
	pthread_detach(threads[0]);
	for(int i=1 ; i<3 ; i++) {
		pthread_join(threads[i],NULL);
	}
	return 0;
}
