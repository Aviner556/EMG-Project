#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode
{
    int value;
    struct ListNode* next;
};

typedef struct LinkedList
{
    struct ListNode* head;
    int counter;
};

struct LinkedList* LinkedList_init();
void LinkedList_addBegin(struct LinkedList* list, int newValue);
void LinkedList_add(struct LinkedList* list, int newValue);
int LinkedList_count(struct LinkedList* list);
void LinkedList_print(struct LinkedList* list);
int LinkedList_delete(struct LinkedList* list, int value);
void LinkedList_bubbleSort(struct LinkedList* list);


int main()
{
    struct LinkedList* myList = LinkedList_init();
    LinkedList_addBegin(myList, 1);
    LinkedList_addBegin(myList, 4);
    LinkedList_addBegin(myList, 3);
    LinkedList_addBegin(myList, 9);
    LinkedList_addBegin(myList, 12);
    LinkedList_addBegin(myList, 5);
    LinkedList_addBegin(myList, 2);
    LinkedList_bubbleSort(myList);
    LinkedList_print(myList);
    LinkedList_delete(myList, 5);
}



struct LinkedList* LinkedList_init()
{
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->counter = 0;
    return list;
}

void LinkedList_addBegin(struct LinkedList* list, int newValue)
{
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->value = newValue;
    newNode->next = list->head;
    list->head = newNode;
    list->counter++;
}

void LinkedList_add(struct LinkedList* list, int newValue) //sorted
{
    if (list->head == NULL || list->head->value > newValue) {
        LinkedList_addBegin(list, newValue);
    }
    else {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
        struct ListNode* pNode = list->head;
        while (pNode->next != NULL) {
            if (newValue <= pNode->next->value) {
                break;
            }
            pNode = pNode->next;
        }
        newNode->value = newValue;
        newNode->next = pNode->next;
        pNode->next = newNode;
        list->counter++;
    }
}

int LinkedList_count(struct LinkedList* list)
{
    return list->counter;
}

int LinkedList_delete(struct LinkedList* list, int value)
{
    if (list->head == NULL) {
        return 0;
    }
    struct ListNode* pNode = list->head;
    if (pNode->value == value) {
        list->head = list->head->next;
        free(pNode);
        list->counter--;
        return 1;
    }
    while (pNode != NULL) {
        if (pNode->next != NULL && pNode->next->value == value) {
            struct ListNode* pNodeDel = pNode->next;
            pNode->next = pNode->next->next;
            free(pNodeDel);
            list->counter--;
            return 1;
        }
        pNode = pNode->next;
    }
    return 0;
}

void LinkedList_bubbleSort(struct LinkedList* list)
{
    if (list->head == NULL || list->head->next == NULL) {
        return;
    }

    for (int i = 0; i < list->counter - 1; i++) {
        struct ListNode* pNode1 = list->head;
        struct ListNode* pNode2 = list->head->next;
        struct ListNode* pNode3 = pNode2->next;
        if (pNode1->value > pNode2->value) {
            pNode1->next = pNode2->next;
            pNode2->next = pNode1;
            list->head = pNode2;

            pNode1 = list->head;
            pNode2 = list->head->next;
        }
        else {
            for (int j = 1; j < list->counter - i - 1; j++) {
                if (pNode2->value > pNode3->value) {
                    pNode1->next = pNode3;
                    pNode2->next = pNode3->next;
                    pNode3->next = pNode2;

                    struct ListNode* temp1 = pNode1->next;
                    struct ListNode* temp2 = pNode3->next;
                    pNode2 = temp1;
                    pNode3 = temp2;
                }
                pNode1 = pNode1->next;
                pNode2 = pNode2->next;
                pNode3 = pNode3->next;
            }
        }
    }
}

void LinkedList_print(struct LinkedList* list)
{
    if (list->head == NULL) {
        printf("empty list!\n\n");
        return;
    }
    struct ListNode* pNode;
    pNode = list->head;
    printf("nodes on the list: %d\n", LinkedList_count(list));
    printf("List: ");
    while (pNode != NULL) {
        printf("[%d]->", pNode->value);
        pNode = pNode->next;
    }
    printf("\n\n");
}