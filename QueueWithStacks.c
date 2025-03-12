#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *arr;
    int top;
    int capacity;
} MyStack;

MyStack* myStackCreate(int capacity) {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity * sizeof(int));
    return stack;
}

void myStackPush(MyStack* obj, int x) {
    obj->arr[++obj->top] = x;
}

int myStackPop(MyStack* obj) {
    return obj->arr[obj->top--];
}

int myStackTop(MyStack* obj) {
    return obj->arr[obj->top];
}

bool myStackEmpty(MyStack* obj) {
    return obj->top == -1;
}

void myStackFree(MyStack* obj) {
    free(obj->arr);
    free(obj);
}

// Queue structure using two stacks
typedef struct {
    MyStack *stack_in;
    MyStack *stack_out;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->stack_in = myStackCreate(100);
    queue->stack_out = myStackCreate(100);
    return queue;
}

// Push element to queue
void myQueuePush(MyQueue* obj, int x) {
    myStackPush(obj->stack_in, x);
}

void moveInToOut(MyQueue* obj) {
    if (myStackEmpty(obj->stack_out)) {
        while (!myStackEmpty(obj->stack_in)) {
            myStackPush(obj->stack_out, myStackPop(obj->stack_in));
        }
    }
}


int myQueuePop(MyQueue* obj) {
    moveInToOut(obj);
    return myStackPop(obj->stack_out);
}


int myQueuePeek(MyQueue* obj) {
    moveInToOut(obj);
    return myStackTop(obj->stack_out);
}


bool myQueueEmpty(MyQueue* obj) {
    return myStackEmpty(obj->stack_in) && myStackEmpty(obj->stack_out);
}

void myQueueFree(MyQueue* obj) {
    myStackFree(obj->stack_in);
    myStackFree(obj->stack_out);
    free(obj);
}


int main() {
    MyQueue* queue = myQueueCreate();
    myQueuePush(queue, 1);
    myQueuePush(queue, 2);
    myQueuePush(queue, 3);
    printf("Peek: %d\n", myQueuePeek(queue)); // 1
    printf("Pop: %d\n", myQueuePop(queue)); // 1
    printf("Pop: %d\n", myQueuePop(queue)); // 2
    printf("Pop: %d\n", myQueuePop(queue)); // 3
    printf("Empty: %d\n", myQueueEmpty(queue)); // 1
    myQueueFree(queue);
    return 0;
}
