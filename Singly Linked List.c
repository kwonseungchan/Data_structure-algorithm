#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct Node
{
	int value;					//값	
	struct Node* pNext;			//다음 노드의 주소를 저장
}Node;

Node* head = NULL; //시작 노드의 주소를 저장하는 포인터(전역변수)

void insertNodeFront();
void printListNode();
void unInitList();
void insertNodeRear();
void deleteNode();
void reverseNode();
void insertNodeOrder();

int main()
{
	int choice;

	while (1)
	{
		system("cls");
		printf("*** 메뉴선택 ***\n");
		printf("1. 노드 삽입\n");
		printf("2. 노드 출력\n");
		printf("3. 노드 삭제\n");
		printf("4. 역순 연결\n");
		printf("0. 종료\n");
		printf("메뉴선택 : [  ]\b\b\b");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			//insertNodeFront(); //앞쪽에 노드 삽입
			//insertNodeRear(); //뒤쪽에 노드 삽입
			insertNodeOrder();
			//정렬하면서 삽입
			break;
		case 2:
			printListNode();
			break;
		case 3:
			deleteNode();
			break;
		case 4:
			reverseNode();
			break;
		case 0:
			unInitList();
			exit(0);
		}

		system("pause"); //일시대기
	}

	return 0;
}
void insertNodeOrder() {
	
	Node* newNode = NULL;
	Node* curNode = NULL;
	Node* prevNode = NULL;

	newNode = (Node*)malloc(sizeof(Node));

	printf("\n정수 입력 : ");
	scanf("%d", &newNode->value);
	newNode->pNext = NULL;
	//1.빈노드냐?? 
	if (head == NULL) {
		head = newNode;
		return;
	}
	

	//2. 첫 노드에 저장된 값이 새 노드의 값보다 크다면???
	if (head->value > newNode->value) {
		newNode->pNext = head;
		head = newNode;
		printf("가장 작은 값 입력으로 맨 앞 삽입\n");
		return;
	}
	//3. 순회하며 값 비교
	curNode = prevNode = head;
	while (curNode->pNext != NULL)//다음 노드가 있다면 반복(마지막 노드는 제외)
	{
		curNode = curNode->pNext;
		if (curNode->value > newNode->value) {
			newNode->pNext = curNode;	//새 노드와 다음노드 연결
			prevNode->pNext = newNode;	//이전노드와 새노드 연결
			printf("정렬된 순서로 노드 삽입(오름차순)\n");
			return;
		}
		prevNode = curNode;	
	}
	//4. 마지막에 추가되는 경우
	if (curNode->value > newNode->value) {
		prevNode->pNext = newNode;
		newNode->pNext = curNode;
	}
	else {
		curNode->pNext = newNode;
	}
	


	

}
void reverseNode()
{
	Node* prevNode = NULL, * curNode = NULL, * nextNode = NULL;

	//1. 빈노드냐?? // 또는 노드가 1개인 경우
	if (head == NULL || head->pNext == NULL)
	{
		printf("\n\n\t\t연결리스트가 비어 있습니다.\n");
		return;
	}
	prevNode = head; //첫번째 노드
	curNode = prevNode->pNext; //두번째 노드
	prevNode->pNext = NULL; //첫번째 노드를 마지막 노드로 사용하기 위해 NULL로 초기화

	while (curNode->pNext != NULL)
	{
		nextNode = curNode->pNext;
		curNode->pNext = prevNode;
		prevNode = curNode;
		curNode = nextNode;
	}
	curNode->pNext = prevNode;
	head = curNode;
	printf("\n\n\t\t리스트 역순 연결했습니다..\n");
}

void deleteNode()
{
	int num;
	Node* delNode = NULL, * curNode = NULL;

	//1. 빈노드냐???
	if (head == NULL)
	{
		printf("\n\n\t\t연결리스트가 비어 있습니다.\n");
		return;
	}

	printf("\n삭제하고자 하는 수 입력 : ");
	scanf("%d", &num);
	//2. 삭제할 노드가 첫 번째 노드야???
	if (head->value == num)
	{
		delNode = head; //삭제할 노드 저장
		head = head->pNext; //head는 다음 노드로 변경
		free(delNode);
		printf("\n\n\t\t첫 번재 노드 %d삭제\n", num);
		return;
	}

	curNode = head;
	while (curNode->pNext != NULL) //노드의 끝까지 이동
	{
		delNode = curNode->pNext; //삭제할 노드 = 다음노드의 주소
		if (delNode->value == num)
		{
			curNode->pNext = delNode->pNext; //이전 노드의 주소에 삭제할 다음노드를 저장
			free(delNode);
			printf("\n\n\t\t중간 노드 삭제된 값 : %d\n", num);
		}
		else
			curNode = curNode->pNext;
	}
}

void insertNodeRear()
{
	Node* newNode, * curNode;

	newNode = (Node*)malloc(sizeof(Node));

	printf("정수 입력 : ");
	scanf("%d", &newNode->value);
	newNode->pNext = NULL;

	//1. 빈노드야???
	if (head == NULL)
	{
		//head에 새로 생성된 노드를 연결
		head = newNode;
		printf("\n\n\t\t연결 리스트가 처음 연결됐습니다.\n");
		return;
	}

	//2. 빈노드가 아니라면??? 노드의 개수만큼 순회
	curNode = head; //head를 현재노드로 설정
	while (curNode->pNext != NULL) //순회
	{
		curNode = curNode->pNext; //다음노드를 현재 노드로 설정
	}

	curNode->pNext = newNode; //마지막 노드에 새노드를 연결
	printf("\n\n\t\t리스트 끝에 노드 삽입\n");

}

void unInitList() //시간복잡도 : O(n)
{
	Node* delNode;

	if (head == NULL)
	{
		printf("\n\n\t\t연결 리스트가 비어 있습니다.\n");
		return;
	}

	while (head->pNext != NULL)
	{
		delNode = head;
		head = head->pNext;
		free(delNode);
		printf("동적 메모리 노드 해제\n");
	}
	free(head);
	printf("마지막 동적 메모리 노드 해제\n");
}

void printListNode() //시간복잡도 : O(n)
{
	Node* curNode;

	if (head == NULL)
	{
		printf("\n\n\t\t연결 리스트가 비어 있습니다.\n");
		return;
	}

	curNode = head;

	while (curNode->pNext != NULL) //순회
	{
		printf("%d -> ", curNode->value);
		curNode = curNode->pNext;
	}
	printf("%d\n", curNode->value);
}

void insertNodeFront() //시간복잡도 : O(1)
{
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));

	printf("\n정수 입력 : ");
	scanf("%d", &newNode->value);
	newNode->pNext = NULL;

	newNode->pNext = head;
	head = newNode;//노드를 head로 설정
}
