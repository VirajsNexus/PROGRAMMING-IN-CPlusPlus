#include <iostream>
#include "Queue.h"

using namespace std;

Queue :: Queue()
{
    front = -1;
    rear = -1;
}

bool Queue::isEmpty()
{
    return(front == -1 || front > rear);
}

void Queue::enqueue(int value)
{
    if(rear == 99)\
    {
        cout << "QUEUE IS FULL....!!\n" << endl;
        return;
    }

    if (front == -1)
    {
        front = 0;
    }
    
    rear++;
    arr[rear] = value;
}

void Queue::dequeue()
{
    if (isEmpty())
    {
        cout <<"\nQUEUE IS EMPTY....!!\n" << endl;
        return;
    }

    front++;   
}

int Queue::peek()
{
    if(isEmpty())
    {
        return -1;
    }

    return arr[front];
}