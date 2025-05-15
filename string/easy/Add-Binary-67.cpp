#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Cần thêm để sử dụng malloc và realloc

char *addBinary(char *a, char *b)
{
    int len1 = strlen(a);
    int len2 = strlen(b);
    int carry = 0, i = len1 - 1, j = len2 - 1;
    int maxLen = len1 > len2 ? len1 : len2;
    char *result = (char *)malloc((maxLen + 1) * sizeof(char)); // Cấp phát bộ nhớ cho chuỗi kết quả
    result[maxLen] = '\0';

    // Cộng từng chữ số nhị phân từ phải sang trái
    while (i >= 0 || j >= 0)
    {
        int sum = carry;
        if (i >= 0)
            sum += a[i--] - '0'; // Lấy bit từ chuỗi `a` nếu còn
        if (j >= 0)
            sum += b[j--] - '0'; // Lấy bit từ chuỗi `b` nếu còn

        carry = sum >> 1;                   // Nếu tổng >= 2 thì bit nhớ (carry) = 1, ngược lại là 0
        result[--maxLen] = (sum & 1) + '0'; // Gán bit phải nhất của tổng vào kết quả
    }

    if (carry)
    {                                                                          // Nếu còn bit nhớ cuối cùng, thêm vào đầu kết quả
        result = (char *)realloc(result, (strlen(result) + 2) * sizeof(char)); // Cấp phát lại bộ nhớ để chứa thêm 1 ký tự
        memmove(result + 1, result, strlen(result) + 1);                       // Dịch chuỗi kết quả sang phải 1 vị trí
        result[0] = '1';                                                       // Đặt bit đầu tiên là '1'
    }

    return result;
}

int main()
{
    char a[] = "101";
    char b[] = "1101";
    char *result = addBinary(a, b);
    printf("Tổng của %s và %s là %s\n", a, b, result);
    free(result); // Giải phóng bộ nhớ đã cấp phát cho chuỗi kết quả
    return 0;
}