#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* reverse_list(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node *prev = NULL;      // 현재 노드의 이전 노드 = reverse 시 curr 다음 노드
    Node *curr = head;      // 현재 처리 노드
    Node *next_node = NULL; // 현재 노드의 다음 노드 = reverse 시 curr 이전 노드 보관

    // while 전 상태
    // (curr)head=1 / (prev)null / (nextnode)NULL

    while (curr != NULL) {
        next_node = curr->next;

        curr->next = prev;
        prev = curr;

        curr = next_node;
    }
    // while 과정 중 상태
    // (curr)head=1 ---> (prev)null / (nextnode)2
    // (curr)head=2 ---> (prev)1->null / (nextnode)3
    // (curr)head=3 ---> (prev)2->1->null / (nextnode)NULL

    
    // wile문 종료 시 상태
    // (curr)NULL / (prev)3->2->1->null / (nextnode)NULL
    return prev;
    
}


void print_list(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node* head) {
    Node* curr = head;
    Node* next_node;

    while (curr != NULL) {
        next_node = curr->next;
        free(curr);
        curr = next_node;
    }
}

int main() {
    // 1 -> 2 -> 3 리스트 생성
    Node* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);

    printf("=======Reverse Linked List=======\n");


    printf("input  : ");
    print_list(head);

    head = reverse_list(head);

    printf("output : ");
    print_list(head);
    
    printf("List Reversed.\n");

    free_list(head);
    head = NULL;

    return 0;
}