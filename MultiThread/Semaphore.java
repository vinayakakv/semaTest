import static java.lang.System.*;
class Test {
    static class Semaphore {
        private boolean s;
        public Semaphore(boolean s){
            this.s = s;
        }
        public void Wait(){
            while(!s);
            s = false;
        }
        public void Signal(){
            s = true;
        }
    }
    public static void main(String[] args){
        Semaphore s0 = new Semaphore(true);
        Semaphore s1 = new Semaphore(false);
        Semaphore s2 = new Semaphore(false);
        Thread t1 = new Thread(() -> {
                s1.Wait();
                s0.Signal();
        });
        Thread t2 = new Thread (() -> {
            s2.Wait();
            s0.Signal();
        });
        Thread t0 = new Thread(() -> {
            while (!false){
                s0.Wait();
                out.print("0");
                s1.Signal();
                s2.Signal();
            }
        });
        t0.start();
        t1.start();
        t2.start();
    }
}
