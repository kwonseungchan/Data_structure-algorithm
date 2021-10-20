#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

enum menu_code //열거형 (앞에서부터 차례대로 0부터 1씩 증가하는 상수값을 갖는다.)
{	// 관련있는 데이터의 상수값을 여러 개 할당 시 사용
	// 중간에 값을 넣으면 그 값부터 다시 시작한다
	INSERT = 1, DISPLAY, FIRST_DEL, VAL_DEL, REVERSE, TERMINATE = 0
};

typedef struct doublyNode
{
	int value;					//값	
	struct doublyNode* pNext;			//다음 노드의 주소를 저장
	struct doublyNode* pPrev;			//이전 노드의 주소를 저장
}DNode;

DNode* head = NULL; //시작 노드의 주소를 저장하는 포인터(전역변수)

void deleteFirstNode();
void insertFrontNode();
void displayNode();
void terminate();
void insertNodeKthBegin();
int getNodeCount();
void deleteValudeNode();
int main()
{
	int select;

	while (1)
	{
		system("cls");
		printf("*** 메뉴선택 ***\n");
		printf("1. 노드 삽입\n");
		printf("2. 노드 출력\n");
		printf("3. 노드 삭제\n");
		printf("4. 검색한 수의 노드 삭제\n");
		printf("0. 종료\n");
		printf("메뉴선택 : [  ]\b\b\b");
		scanf("%d", &select);

		switch (select)
		{
		case INSERT:
			//insertFrontNode(); //노드 맨앞 삽입
			//노드 맨 뒤 삽입
			//노드 정렬 삽입
			//노드 n번째 삽입
			insertNodeKthBegin();
			break;
		case DISPLAY:
			displayNode();
			break;
		case FIRST_DEL:
			deleteFirstNode(); //첫번째 노드 삭제
			break;
		case VAL_DEL:
			deleteValudeNode(); //검색한 값과 같은 노드 삭제
			break;
		case REVERSE:
			break;
		case TERMINATE:
			terminate();
			exit(0);

		}

		printf("\n\n\t\t");
		system("pause"); //일시대기
	}

	return 0;
}
void deleteFirstNode() {
	DNode* deleteNode;

	if (head == NULL)return;

	if (head->pNext == NULL) {
		free(head);
		head = NULL;
		return;
	}

	deleteNode = head;
	head = deleteNode->pNext;
	head->pPrev = NULL;
	free(deleteNode);
	printf("첫 번째 노드 삭제\n");
}
void deleteValudeNode() {
	DNode* curNode;
	DNode* delNode;
	int num;
	int cnt = 0;
	printf("\n\n\t\t삭제할 숫자를 입력해주세요 : ");
	scanf("%d", &num);
	if (head == NULL) {
		return;
	}
	if (head->pNext == NULL) {
		free(head);
		head = NULL;
		return;
	}
	if (head->value == num) {
		
		if (head->pNext == NULL) {
			free(head);
			head = NULL;
		}
		else {
			delNode = head;
			head = head->pNext;
			head->pPrev = NULL;
			free(delNode);
		}
		return;
	}

	curNode = head;
	while (curNode->pNext != NULL) {
		if (curNode->value == num) {
			(curNode->pPrev)->pNext = (curNode->pNext);
			(curNode->pNext)->pPrev = (curNode->pPrev);
			delNode = curNode;
			cnt++;
		}
		curNode = delNode->pNext;
		free(delNode);
	}
	if (cnt > 0) {
		printf("%d가 든 노드를 성공적으로 해제했습니다!!\n");
	}
	else {
		printf("%d가 든 노드가 없습니다!!\n");
	}
}
void insertFrontNode() {
	DNode* newNode;

	newNode = (DNode*)malloc(sizeof(DNode));
	printf("\n정수 입력 : ");
	
	scanf("%d", &newNode->value);
	newNode->pNext = NULL;
	newNode->pPrev = NULL;

	if (!head)//(head == NULL) 
	{
		head = newNode;
		printf("\n\n\t\t리스트의 첫 노드 연결\n");
		return;
	}
	newNode->pNext = head;
	head->pPrev = newNode;
	head = newNode;
}
void displayNode() {

	DNode* curNode = head;
	if (!head)
		return;

	while (curNode->pNext != NULL) {
		printf("%d => ", curNode->value);
		curNode = curNode->pNext; //다음 노드로 이동
	}
	printf("%d\n", curNode->value); //맨 마지막 노드 출력
}
void terminate() {
	DNode* delNode;

	if (!head) {
		return;
	}
	while (head) {
		delNode = head;
		head = head->pNext;
		free(delNode);
		printf("동적 메모리 해제\n");
	}
	printf("\n\n\t\t프로그램 종료 !!");
}
void insertNodeKthBegin() {
	DNode* newNode;
	DNode* curNode;
	int count,k;
	int i;
	newNode = (DNode*)malloc(sizeof(DNode));
	printf("\n정수 입력 : ");
	scanf("%d", &newNode->value);
	newNode->pNext = newNode->pPrev = NULL;

	count = getNodeCount(); //노드의 갯수를 구해 리턴

	do {
		printf("\n1~%d번째에 노드를 추가하실 수 있습니다.\n", count + 1);
		printf("몇 번째에 노드를 추가 하시겠습니까???");
		scanf("%d", &k);
	} while (k < 1 || k > count + 1);


	//1. node가 비워 있는 경우
	if (head == NULL) {
		head = newNode;
		printf("%d번쨰 노드 추가(case 1)\n", k);
		return;
	}
	//2. 1번째 노드로 추가하는 경우????(맨 앞 추가)
	if (k == 1) {
		head->pPrev = newNode;
		newNode->pNext = head;
		head = newNode;
		printf("%d번째 노드 추가(case 2)\n", k);
		return;
	}
	//3. 맨 뒤 노드로 추가하는 경우??
	curNode = head;
	for (i = 1; i <= k - 2; i++) {
		curNode = curNode->pNext;
	}
	if (k == count + 1) {
		newNode->pPrev = curNode;
		curNode->pNext = newNode;
		printf("%d번째 노드 추가(case 3)\n", k);
		return;
	}
	// 4. 중간에 추가하는 경우???
	newNode->pPrev = curNode;
	newNode->pNext = curNode->pNext;
	curNode->pNext = newNode;
	curNode->pNext->pPrev = newNode;
}
int getNodeCount() {
	DNode* cntNode;
	int count =1;

	cntNode = head;

	if (head == NULL)return 0;

	while (cntNode->pNext != NULL) {
		cntNode = cntNode->pNext;
		count++;
	}

	return count;
}
