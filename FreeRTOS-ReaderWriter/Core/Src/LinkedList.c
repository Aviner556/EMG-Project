#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LinkedList* LinkedList_init()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->counter = 0;
    return list;
}

void LinkedList_addBegin(LinkedList* list, TYPE type, char * newMessage)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    strcpy(newNode->message,newMessage);
    newNode->next = list->head;
    list->head = newNode;
    list->counter++;
}

void LinkedList_add(LinkedList* list, TYPE type, char * newMessage) //sorted
{
	if (list->head == NULL || list->head->message > newMessage) {
        LinkedList_addBegin(list, type, newMessage);
    }
    else {
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        ListNode* pNode = list->head;
        while (pNode->next != NULL) {
            if (newMessage <= pNode->next->message) {
                break;
            }
            pNode = pNode->next;
        }
        strcpy(newNode->message,newMessage);
        newNode->next = pNode->next;
        pNode->next = newNode;
        list->counter++;
    }
}

int LinkedList_count(LinkedList* list)
{
    return list->counter;
}

int LinkedList_delete(LinkedList* list, TYPE type, char * message)
{
    if (list->head == NULL) {
        return 0;
    }
    ListNode* pNode = list->head;
    if (strcpy(pNode->message,message) == 0) {
        list->head = list->head->next;
        free(pNode);
        list->counter--;
        return 1;
    }
    while (pNode != NULL) {
        if (pNode->next != NULL && pNode->next->message == message) {
            ListNode* pNodeDel = pNode->next;
            pNode->next = pNode->next->next;
            free(pNodeDel);
            list->counter--;
            return 1;
        }
        pNode = pNode->next;
    }
    return 0;
}

void LinkedList_printAndDelete(LinkedList* list)
{
    if (list->head == NULL) {
        printf("empty list!\n\n");
        return;
    }
    ListNode* pNode;
    pNode = list->head;
    printf("nodes on the list: %d\n", LinkedList_count(list));
    printf("List: ");
    while (pNode != NULL) {
        printf("[%s]->", pNode->message);
        pNode = pNode->next;
    }
    printf("\n\n");
}
