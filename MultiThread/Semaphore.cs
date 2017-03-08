using System;
using System.Threading;
class Semaphore {
	//Binary Semaphore
	bool s = false;
	public Semaphore(bool s) {
		this.s = s;
	}
	public void Signal() {
		s = true;
	}
	public void Wait() {
		while (!s) ; //wait
		s = false;
	}
	public static implicit operator Semaphore(bool v) {
		//Implicit Converison from bool to Semaphore
		//Power Of C# :D :)
		return new Semaphore(v);
	}
}
class Test {
	public static void Main(string[] args) {
		Semaphore s0 = true , s1 = false , s2 = false;
		Thread t1 = new Thread(() => {
			while (!false) {
				s0.Wait();
				Console.Write("0");
				s1.Signal();
				s2.Signal();
			}
		});
		Thread t2 = new Thread(() => {
			s1.Wait();
			s0.Signal();
		});
		Thread t3 = new Thread(() => {
			s1.Wait();
			s0.Signal();
		});
		t1.Start();
		t2.Start();
		t3.Start();
	}
}
