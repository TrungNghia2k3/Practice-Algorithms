// C++ code to add two linked list using recursion

#include <iostream>
using namespace std;

class Node {
  public:
    int data;
    Node *next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

// Function to reverse a linked list
Node *reverse(Node *head) {
    Node *prev = nullptr;
    Node *curr = head;
    Node *next = nullptr;

    // Loop to reverse the linked list
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Recursive function to add two numbers represented
// by linked lists
Node *addListRec(Node *num1, Node *num2, int &carry) {

    // Base case: If both lists are empty and no carry is left
    if (num1 == nullptr && num2 == nullptr && carry == 0) {
        return nullptr;
    }

    int sum = carry;

    // Add the value from the first list if it exists
    if (num1 != nullptr) {
        sum += num1->data;
        num1 = num1->next;
    }

    // Add the value from the second list if it exists
    if (num2 != nullptr) {
        sum += num2->data;
        num2 = num2->next;
    }

    carry = sum / 10;
    Node *result = new Node(sum % 10);

    // Recursively add remaining digits
    result->next = addListRec(num1, num2, carry);

    return result;
}

// function to trim leading zeros in linked list
Node* trimLeadingZeros(Node* head) {
	while (head != nullptr && head->data == 0) {
        head = head->next;
    }
    return head;
}

// function for adding two linked lists
Node *addTwoLists(Node *num1, Node *num2) {
	num1 = trimLeadingZeros(num1);
	num2 = trimLeadingZeros(num2);

    // Reverse both lists to start addition from 
    // the least significant digit
    num1 = reverse(num1);
    num2 = reverse(num2);

    int carry = 0;
    Node *result = addListRec(num1, num2, carry);

    // If there's any carry left after the addition,
    // create a new node for it
    if (carry != 0) {
        Node *newNode = new Node(carry);
        newNode->next = result;
        result = newNode;
    }

    // Reverse the result list to restore
    // the original order
    return reverse(result);
}

void printList(Node *head) {
    Node *curr = head;
	while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << "\n";
}

int main() {
  
    // Creating first linked list: 1 -> 2 -> 3 
      // (represents 123)
    Node *num1 = new Node(2);
    num1->next = new Node(4);
    num1->next->next = new Node(3);

    // Creating second linked list: 9 -> 9 -> 9 
	// (represents 999)
    Node *num2 = new Node(5);
    num2->next = new Node(6);
    num2->next->next = new Node(4);

    Node *sum = addTwoLists(num1, num2);
    printList(sum);

    return 0;
}