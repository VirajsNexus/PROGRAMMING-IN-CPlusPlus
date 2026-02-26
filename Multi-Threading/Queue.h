#ifndef QUEUE_H
#define QUEUE_H

class Queue
{
    private:
        int arr[100];
        int front;
        int rear;

    public:
        Queue();
        void enqueue(int value);
        void dequeue();
        int peek();
        bool isEmpty();
};

#endif