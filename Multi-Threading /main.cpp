#include <iostream>
#include <thread>
#include <mutex>
#include "Queue.h"

using namespace std;

Queue q;     // Added queue object
mutex m;    //Mutex object

void producer()
{
    cout << "\n[T1 - Producer] Thread started" << endl;

    for(int i = 1; i <= 5; i++)
    {
        cout << "\n[T1 - Producer] Waiting to acquire lock..." << endl;

        m.lock();   //locked
        cout << "[T1 - Producer] Lock acquired >> Running" << endl;

        q.enqueue(i);
        cout << "[T1 - Producer] Produced : " << i << "  |  Queue size in progress..." << endl;

        m.unlock();
        cout << "[T1 - Producer] Lock released" << endl;
    }

    cout << "\n[T1 - Producer] Thread finished\n" << endl;
}

void consumer()
{
    cout << "\n[T2 - Consumer] Thread started" << endl;

    for(int i = 1; i <= 5; i++)
    {
        cout << "\n[T2 - Consumer] Waiting to acquire lock..." << endl;

        m.lock();   //locked
        cout << "[T2 - Consumer] Lock acquired >> Running" << endl;

        if(!q.isEmpty())
        {
            cout << "[T2 - Consumer] Consumed : " << q.peek() << "  |  Removing from queue..." << endl;
            q.dequeue();
        }
        else
        {
            cout << "[T2 - Consumer] Queue is empty, skipping this iteration" << endl;
        }

        m.unlock();     //unlocked
        cout << "[T2 - Consumer] Lock released" << endl;
    }

    cout << "\n[T2 - Consumer] Thread finished\n" << endl;
}

int main(void)
{
    cout << "======================================" << endl;
    cout << "   Producer-Consumer MultiThreading   " << endl;
    cout << "======================================" << endl;

    cout << "\n[MAIN] Launching T1 (Producer) and T2 (Consumer)...\n" << endl;

    thread t1(producer);
    thread t2(consumer);

    cout << "[MAIN] Both threads are running concurrently..." << endl;

    t1.join();
    t2.join();

    cout << "\n[MAIN] Both threads completed." << endl;
    cout << "[MAIN] Program exiting cleanly. Exit code: 0" << endl;
    cout << "======================================" << endl;

    return 0;
}
