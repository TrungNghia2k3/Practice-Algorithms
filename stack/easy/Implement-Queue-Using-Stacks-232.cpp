#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *stack1; // Stack chính để đẩy dữ liệu
    int *stack2; // Stack phụ để lấy dữ liệu theo FIFO
    int top1;
    int top2;
    int capacity;
} MyQueue;

// Hàm khởi tạo hàng đợi
MyQueue *myQueueCreate()
{
    MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
    queue->capacity = 100; // Giới hạn hàng đợi
    queue->stack1 = (int *)malloc(queue->capacity * sizeof(int));
    queue->stack2 = (int *)malloc(queue->capacity * sizeof(int));
    queue->top1 = -1;
    queue->top2 = -1;
    return queue;
}

// Hàm đẩy phần tử vào queue
void myQueuePush(MyQueue *obj, int x)
{
    obj->stack1[++(obj->top1)] = x;
}

// Hàm lấy phần tử ra khỏi queue
int myQueuePop(MyQueue *obj)
{
    if (obj->top2 == -1)
    {
        while (obj->top1 != -1)
        {
            obj->stack2[++(obj->top2)] = obj->stack1[obj->top1--];
        }
    }
    return obj->stack2[obj->top2--];
}

// Hàm lấy phần tử đầu tiên mà không xóa
int myQueuePeek(MyQueue *obj)
{
    if (obj->top2 == -1)
    {
        while (obj->top1 != -1)
        {
            obj->stack2[++(obj->top2)] = obj->stack1[obj->top1--];
        }
    }
    return obj->stack2[obj->top2];
}

// Hàm kiểm tra queue rỗng
bool myQueueEmpty(MyQueue *obj)
{
    return obj->top1 == -1 && obj->top2 == -1;
}

// Giải phóng bộ nhớ
void myQueueFree(MyQueue *obj)
{
    free(obj->stack1);
    free(obj->stack2);
    free(obj);
}

// Hàm kiểm tra
int main()
{
    MyQueue *obj = myQueueCreate();

    myQueuePush(obj, 1);
    myQueuePush(obj, 2);
    printf("Peek: %d\n", myQueuePeek(obj));   // Output: 1
    printf("Pop: %d\n", myQueuePop(obj));     // Output: 1
    printf("Empty: %d\n", myQueueEmpty(obj)); // Output: 0 (false)
    printf("Pop: %d\n", myQueuePop(obj));     // Output: 2
    printf("Empty: %d\n", myQueueEmpty(obj)); // Output: 1 (true)

    myQueueFree(obj);
    return 0;
}
