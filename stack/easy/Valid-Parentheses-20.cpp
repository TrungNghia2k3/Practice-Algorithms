#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10000 // Giới hạn độ dài chuỗi

// Hàm kiểm tra chuỗi có dấu ngoặc hợp lệ không
bool isValid(char *s)
{
    char stack[MAX_SIZE];
    int top = -1; // Con trỏ stack

    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];

        // Nếu là dấu mở, push vào stack
        if (c == '(' || c == '{' || c == '[')
        {
            stack[++top] = c;
        }
        else
        {
            // Nếu stack rỗng nhưng gặp dấu đóng -> Sai
            if (top == -1)
                return false;

            // Lấy phần tử trên cùng của stack
            char topChar = stack[top--];

            // Kiểm tra xem có đóng mở đúng không
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '['))
            {
                return false;
            }
        }
    }

    // Nếu stack còn phần tử, chuỗi không hợp lệ
    return top == -1;
}

// Hàm kiểm tra
int main()
{
    char s1[] = "()";
    char s2[] = "()[]{}";
    char s3[] = "(]";
    char s4[] = "([)]";
    char s5[] = "{[]}";

    printf("Test 1: %s -> %s\n", s1, isValid(s1) ? "Valid" : "Invalid");
    printf("Test 2: %s -> %s\n", s2, isValid(s2) ? "Valid" : "Invalid");
    printf("Test 3: %s -> %s\n", s3, isValid(s3) ? "Valid" : "Invalid");
    printf("Test 4: %s -> %s\n", s4, isValid(s4) ? "Valid" : "Invalid");
    printf("Test 5: %s -> %s\n", s5, isValid(s5) ? "Valid" : "Invalid");

    return 0;
}
