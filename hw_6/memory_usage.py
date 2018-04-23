import os
import resource
import objgraph
import matplotlib.pyplot as plt
import gc

def getCurrentMemoryUsage():
    ''' Memory usage in kB '''
    memusage = resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
    return memusage

class A(object):
    def __init__(self):
        self.infoA = [i * 2 for i in range(10000)]

    def refB(self, b_instance):
        self.b = b_instance

class B(object):
    def __init__(self):
        self.infoB = [i * 3 for i in range(10000)]
    def refA(self, a_instance):
        self.a = a_instance
    def __del__(self):
        print('B dies')

def test():
    a = A()
    b = B()
    a.refB(b)
    b.refA(a)
    #gc.collect()
    #objgraph.show_backrefs([b, b.a], refcounts=True, filename='sample-graph.png')

def test_memory(n):
    memory_free_1 = getCurrentMemoryUsage()
    for i in range(n):
        test()
    memory_used_1 = getCurrentMemoryUsage() - memory_free_1
    return memory_used_1

#print(str(test_memory(1)) + ' kb')
#print(str(test_memory(50)) + 'kb')

def plot_graph():
    memory = []
    for n in range(10, 100, 10):
        memory.append(test_memory(n))
    plt.figure()
    plt.plot(range(10, 100, 10), memory)
    plt.title('Evolution of memory usage with the number of call of test()')
    plt.xlabel('number of calls')
    plt.ylabel('memory usage (kb)')
    plt.savefig('result_memory.png')


plot_graph()
