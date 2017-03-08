#include <iostream>
#include <thread>  
//Compile : g++ -pthread 
using namespace std;
class Semaphore {
	private:
		bool s;
	public:
		Semaphore(bool s) {
			this->s = s;
		}
		void Wait() {
			while(!s);
			s = false;
		}
		void Signal() {
			s = true;
		}
};
Semaphore s0(true) ,s1(false), s2(false);
void f0() {
	while(!false) {
		s0.Wait();
		cout<<"0";
		s1.Signal();
		s2.Signal();
	}
}
void f1() {
	s1.Wait();	
	s0.Signal();
}
void f2() {
	s2.Wait();	
	s0.Signal();
}
int main() {
	thread t1(f1),t2(f2),t0(f0);
	t1.join();
	t2.join();
	t0.detach();
	return 0;
}
