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

Bool removeFirstNode(Node** head){
    if(*head == NULL){
        printf("The linked list is empty!");
        return FALSE;
    }

    Node* temp = *head;
    *head = (*head)->next;
    free(temp);

    return TRUE;
}

void clearList(Node** head){
    Bool check = removeFirstNode(head);
    while((int)check){
        check = removeFirstNode(head);
    }
}