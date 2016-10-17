#include "apue.h"
#include <pthread.h>

struct foo{
		int a,b,c,d;
}

void printfoo(const char *s,const struct foo *p){
	printf(s);
	printf("struct as 0x%x\n",(unsigned)p);
	printf("foo.a is %d\n",p->a);
	printf("foo.b is %d\n",p->b);
	printf("foo.c is %d\n",p->c);
	printf("foo.d is %d\n",p->d);
}

void * thr_fn1(void *arg){
	struct foo foo={1,2,3,4};
	printfoo("thread 1:\n",&foo);
	pthread_exit((void *)&foo);
}

void * thr_fn2(void *arg){
	printf("thread 2:ID is %d\n",pthread_self());
	pthrad_exit((void *)0);
} 

int main(void){
	int err;
	pthread_t tid1,tid2;
	struct foo *p;

	err = pthread_create(&tid1,NULL,thr_fn1,NULL);
	if(err!=0){
		err_quit("cant't create thread 1:%s\n",strerror(err));
	}
	err = pthread_join(tid1,(void *)&p);
	if(err!=0)
		err_quit("can't join with thraed1:%s\n",strerror(err));
	sleep(1);
	printf("parent  starting second thread");
	err = pthread_create(&tid2,NULL,thr_fn2,NULL);
	if(err!=0)
		err_quit("can't create thread 2:%s\n",strerror(err));
	sleep(1);
	printfoo("parent : \n",p);
	exit(0);
}
