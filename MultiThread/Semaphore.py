from threading import Thread
class Semaphore:
        def __init__(self,s):
                self.s = s
        def wait(self):
                while(self.s==False):
                        '''Waits'''
                self.s = False
        def signal(self):
                self.s = True
if __name__ == '__main__':
        s0 = Semaphore(True)
        s1 = Semaphore(False)
        s2 = Semaphore(False)
        def th1():
                s1.wait()
                s0.signal()
        def th2():
                s2.wait()
                s0.signal()
        def th0():
                while(True):
                        s0.wait()
                        print 0
                        s1.signal()
                        s2.signal()
        t0 = Thread(target=th0)
        t1 = Thread(target=th1)
        t2 = Thread(target=th2)
        t0.start()
        t1.start()
        t2.start()
