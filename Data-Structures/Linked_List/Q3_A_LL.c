//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 연결 리스트 한 칸(노드)입니다.
typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

// 리스트의 시작 위치와 크기를 저장합니다.
typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/*
	해야 할 일:
	- 홀수 값을 가진 노드를 모두 리스트 뒤쪽으로 보냅니다.
	- 짝수들의 상대적 순서와 홀수들의 상대적 순서는 보통 유지하는 방식이 깔끔합니다.

	생각 방법:
	1) 현재 노드가 홀수인지 확인
	2) 홀수면 그 노드를 떼어서 맨 뒤에 붙임
	3) 짝수면 그냥 다음 노드로 이동

	연결 리스트에서는 "값을 복사"하기보다
	"노드 연결(next)을 바꾸는 것"이 핵심입니다.
*/
void moveOddItemsToBack(LinkedList *ll)
{
	//링크드 리스트가 비어있으면 리턴
	// if (ll->head == NULL){
	// 	return;
	// }
	
	// ListNode *cur1 = ll->head;
	// ListNode *prev = NULL;

	// //값에 의한 복사여서 이중포인터를 사용해야 함
	// LinkedList temp;
	// temp.head = NULL;
	// ListNode **cur2 = &temp.head;
	// ListNode *cur3 = temp.head;
	// int count = 0;
	
	// //리스트의 맨 끝으로 감
	// while (cur1 != NULL) {
	// 	//홀수확인
	// 	if (cur1->item % 2 == 1){
	// 		//처음에 홀수가 나오면
	// 		if (cur1 == ll->head){
	// 			//ll1에서 cur1 떼기
	// 			ll->head = cur1->next;
	// 			cur1->next = NULL;
	// 		} 
	// 		//처음이 아닌 홀수
	// 		else {
	// 			//ll1에서 cur1 떼기
	// 			prev->next = cur1->next;
	// 			cur1->next = NULL;
	// 		}
	
	// 		//ll2에 붙이기
	// 		//비어있는 리스트 라면
	// 		if (temp.head == NULL) {
	// 				*cur2 = cur1;
	// 				cur3 = cur3->next;
	// 		} else { //비어있지 않다면
	// 			cur3->next = cur1;
	// 			cur3 = cur3->next;
	// 		}
	// 	}
		
	// 	prev = cur1;
	// 	cur1 = cur1->next;
	// }

	// //링크드 리스트 2개 붙이기
	// while( cur1->next != NULL ) {
	// 	cur1 = cur1->next;
	// }
	// 	if (*cur2 != NULL){
	// 		cur1->next = *cur2;
	// 	}

	if (ll->head == NULL) return;

    ListNode *tail = ll->head;
    
    // 1. tail 찾기
    while (tail->next != NULL) {
        tail = tail->next;
    }

    ListNode *cur = ll->head;
    ListNode *prev = NULL;
    ListNode *end = tail;  // 처음 tail 기준

    while (cur != NULL && cur != end->next) {
        
        // 다음 노드 미리 저장 (🔥 중요)
        ListNode *next = cur->next;

        if (cur->item % 2 == 1) {
            
            // 앞에서 제거
            if (cur == ll->head) {
                ll->head = next;
            } else {
                prev->next = next;
            }

            // 뒤에 붙이기
            tail->next = cur;
            cur->next = NULL;
            tail = cur;

        } else {
            prev = cur;
        }

        cur = next;
    }
}

///////////////////////////////////////////////////////////////////////////////////

// 리스트를 순서대로 출력합니다.
void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}
	//


// 모든 노드를 해제합니다.
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


// index번째 노드를 찾아 반환합니다.
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

// index 위치에 새 노드를 끼워 넣습니다.
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 리스트 맨 앞 삽입은 head 변경이 필요합니다.
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// 새 노드를 만들고 앞뒤 연결을 다시 이어 줍니다.
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


// index번째 노드를 삭제합니다.
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
