#include "List.h"

void insertAtNth(Node** head, Order newOrder, int n){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->thisOrder = newOrder;
    newNode->next = NULL;

    if(*head == NULL){
        *head = newNode;
        return;
    }

    if(n == 1){
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* temp = *head;

    if(n == -1){
        while(1){
            if (temp->next == NULL) {
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }   
            temp = temp->next;
        }
    }
    
    for(int i = 1; i < n-1; i++){
        if (temp->next == NULL) {
            printf("Error: Invalid position\n");
            return;
        }   
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

int removeFirstNode(Node** head){
    if(*head == NULL){
        printf("The linked list is empty!");
        return 0;
    }

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);

    return 1;
}

void clearList(Node** head){
    int check = removeFirstNode(head);
    while(check){
        check = removeFirstNode(head);
    }
}