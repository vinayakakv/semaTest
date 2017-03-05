# semaTest
A simple synchronization problem is as follows

The following Program consists of 3 concurrently running Threds and 3 Binary Semaphores.
The Semaphores are initialized as follows, S0 = true, S1 = false and S2 = true

The executable section of the codes are as follows

T0:
	
	while(!false) {
		wait(S0);
		print("0");
		signal(S1);
		signal(S2);
	}
	
T1:

	wait(S1);
	signal(S0);

T2:

	wait(S2);
	signal(S0);


How many times will the process print "0" ?

a) At least Twice
b) Exactly Twice
c) Exactly Thrice
d) Exactly Once


An attempt to solve this program using C#,Java,C++,C and x64 Assembly is Presented here.

x64 assembly uses the code from [Pure assembly, library-free Linux threading demo] (https://github.com/skeeto/pure-linux-threads-demo/blob/master/threads-x86_64.s)
