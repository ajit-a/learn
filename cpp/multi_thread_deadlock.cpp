#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

class Thread
{
	private:
		static int a;
		pthread_t id;
		void *ret;
		pthread_mutex_t my_mutex=PTHREAD_MUTEX_INITIALIZER;
		pthread_mutex_t my_mutex1=PTHREAD_MUTEX_INITIALIZER;
	public:
		Thread(){a=0;};
		~Thread(){};
		void *createThread();
		void *joinThread();
		void getLock();
		void releaseLock();
		static void* my_thread(void *);
};
int Thread::a=0;
void* Thread::my_thread(void *arg)
{
	cout<<"Thread id: "<<getpid()<<"  a:"<<a<<endl;
	cout<<"pthread_self: "<<pthread_self()<<endl;
}

void* Thread::createThread()
{
	pthread_create(&id,NULL,Thread::my_thread,NULL);
}
void* Thread::joinThread()
{
	pthread_join(id,&ret);
}
void Thread::getLock()
{
	pthread_mutex_lock(&my_mutex);
	pthread_mutex_lock(&my_mutex1);
	a++;
	pthread_mutex_unlock(&my_mutex);
}
void releaseLock()
{
}
int main()
{
	Thread t;
	//t.createThread();
	t.getLock();
	//t.createThread();
	t.getLock();
	t.joinThread();
	return 0;	
}

