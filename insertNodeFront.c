#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma warning(disable : 4996)

typedef struct Node {
	int value;				//값
	struct Node* pNext;		//다음 노드의 주소를 저장
}Node;

Node* head = NULL; //시작 노드의 주소를 저장하는 포인터(전역변수)
void insertNodeFront();
void printListNode();
void unInitList();

int main() {
	
	int choice;

	while (1) {
		system("cls");
		printf("*** 메뉴선택 ***\n");
		printf("1. 입력\n");
		printf("2. 출력\n");
		printf("0. 종료\n");

		scanf("%d", &choice);
		switch (choice) {
		case 1:
			insertNodeFront();
			break;
		case 2:
			printListNode();
			break;
		case 0:
			unInitList();
			exit(0);
		}
		system("pause"); //일시대기

	}


	return 0;
}
void unInitList() {
	
	Node* delNode;

	if (head == NULL) {
		printf("\n\n\t\t연결 리스트가 비어 있습니다.\n");
		return;
	}
	while (head->pNext != NULL) {
		delNode = head;
		head = head->pNext;
		free(delNode);
	}
	free(head);
}
void insertNodeFront() {
	Node* newNode;

	newNode = (Node*)malloc(sizeof(Node));

	printf("\n정수 입력 :");
	scanf("%d", &newNode->value);
	newNode->pNext = NULL;

	newNode->pNext = head;
	head = newNode;

}

void printListNode() {
	Node* curNode;

	if (head == NULL) {
		printf("\n\n\t\t연결 리스트가 비어 있습니다.\n");
		return;
	}
	curNode = head;
	while (curNode->pNext != NULL) {
		printf("%d <-", curNode->value);
		curNode = curNode->pNext;
	}
	printf("%d\n", curNode->value);
}
