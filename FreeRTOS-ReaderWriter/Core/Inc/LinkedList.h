#ifndef INC_LINKEDLIST_H_
#define INC_LINKEDLIST_H_

typedef enum _TYPE
{
	TYPE_DEBUG,
	TYPE_INFO,
	TYPE_WARNING,
	TYPE_ERROR,
}TYPE;

typedef struct _ListNode
{
	TYPE type;
    char message[80];
    struct _ListNode* next;
}ListNode;


typedef struct _LinkedList
{
    ListNode* head;
    int counter;
}LinkedList;



LinkedList* LinkedList_init();
void LinkedList_addBegin(LinkedList* list, TYPE type, char * newMessage);
void LinkedList_add(LinkedList* list, TYPE type, char * newMessage);
int LinkedList_count(LinkedList* list);
void LinkedList_printAndDelete(LinkedList* list);
int LinkedList_delete(LinkedList* list, TYPE type, char * message);




#endif /* INC_LINKEDLIST_H_ */
