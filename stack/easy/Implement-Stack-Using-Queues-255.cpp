#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *queue1; // Hàng đợi chính
    int *queue2; // Hàng đợi phụ để hỗ trợ Pop/Top
    int front1, rear1;
    int front2, rear2;
    int capacity;
} MyStack;

// Hàm khởi tạo stack
MyStack *myStackCreate()
{
    MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
    stack->capacity = 100;
    stack->queue1 = (int *)malloc(stack->capacity * sizeof(int));
    stack->queue2 = (int *)malloc(stack->capacity * sizeof(int));
    stack->front1 = stack->rear1 = -1;
    stack->front2 = stack->rear2 = -1;
    return stack;
}

// Kiểm tra hàng đợi có rỗng không
bool isQueueEmpty(int front, int rear)
{
    return front == -1 || front > rear;
}

// Thêm phần tử vào stack
void myStackPush(MyStack *obj, int x)
{
    if (obj->front1 == -1)
        obj->front1 = 0;
    obj->queue1[++(obj->rear1)] = x;
}

// Xóa phần tử trên cùng của stack
int myStackPop(MyStack *obj)
{
    if (isQueueEmpty(obj->front1, obj->rear1))
        return -1; // Stack rỗng

    // Chuyển tất cả phần tử trừ phần tử cuối sang queue2
    while (obj->front1 < obj->rear1)
    {
        if (obj->front2 == -1)
            obj->front2 = 0;
        obj->queue2[++(obj->rear2)] = obj->queue1[obj->front1++];
    }

    int topElement = obj->queue1[obj->front1++]; // Lấy phần tử cuối
    obj->front1 = obj->rear1 = -1;               // Reset queue1

    // Hoán đổi queue1 và queue2
    int *tempQueue = obj->queue1;
    obj->queue1 = obj->queue2;
    obj->queue2 = tempQueue;

    obj->front1 = obj->front2;
    obj->rear1 = obj->rear2;
    obj->front2 = obj->rear2 = -1;

    return topElement;
}

// Lấy phần tử trên cùng của stack mà không xóa
int myStackTop(MyStack *obj)
{
    if (isQueueEmpty(obj->front1, obj->rear1))
        return -1;

    return obj->queue1[obj->rear1]; // Phần tử cuối cùng là top của stack
}

// Kiểm tra stack rỗng
bool myStackEmpty(MyStack *obj)
{
    return isQueueEmpty(obj->front1, obj->rear1);
}

// Giải phóng bộ nhớ
void myStackFree(MyStack *obj)
{
    free(obj->queue1);
    free(obj->queue2);
    free(obj);
}

// Hàm kiểm tra
int main()
{
    MyStack *obj = myStackCreate();

    myStackPush(obj, 1);
    myStackPush(obj, 2);
    myStackPush(obj, 3);

    printf("Top: %d\n", myStackTop(obj));     // Output: 3
    printf("Pop: %d\n", myStackPop(obj));     // Output: 3
    printf("Pop: %d\n", myStackPop(obj));     // Output: 2
    printf("Empty: %d\n", myStackEmpty(obj)); // Output: 0 (false)
    printf("Pop: %d\n", myStackPop(obj));     // Output: 1
    printf("Empty: %d\n", myStackEmpty(obj)); // Output: 1 (true)

    myStackFree(obj);
    return 0;
}
