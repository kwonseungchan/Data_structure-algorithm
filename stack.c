#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

enum stack_menu {
	PUSH = 1, POP, PRINT, CLEAR, TERMINATE = 0
};

typedef struct int_stack {
	int top;			//push할 배열의 인덱스를 입력
	int* data;			//배열은 동적할당(동적할당 된 메모리의 주소 저장)
	int capacity;		//스택의 최대 용량
	int minCapacity;	//스택의 최소 보장 용량
}int_stack;
void terminate(const int_stack*);
void initialize(int_stack*, int);
void push(int_stack*, int);
void print(const int_stack*);
void pop(int_stack*);
int isEmpty(const int_stack* const);
int main() {
	int_stack stack;
	int select;
	int size;
	int value;

	printf("스택 크기 입력 : ");
	scanf("%d", &size);

	initialize(&stack,size);
	
	while (1) {
		system("cls");
		printf("1. push\t2. pop\t3. print\t4. clear\t0. terminate\n");
		printf("select : [ ]\b\b");
		scanf("%d", &select);

		switch (select) {
		case PUSH:
			printf("\ndata push : ");
			scanf("%d", &value);
			push(&stack, value); //push
			break;
		case POP:
			pop(&stack);
			break;
		case PRINT:
			print(&stack);
			break;
		case CLEAR:
			break;
		case TERMINATE:
			terminate(&stack);
			exit(0);

		}
		printf("\n\n\t\t");
		system("pause");
	}
	return;
}
void pop(int_stack* stk) {
	if (isEmpty(stk)) {
		printf("stack underflow\n");
		return;
	}
	stk->top--;
	printf("%d 삭제\n", stk->data[stk->top]);
	
}
void terminate(const int_stack* const stk)
{
	free(stk->data);
	printf("\n\n\t\t동적 배열 해제\n");
}
void push(int_stack* stk,int val) {
	
	if (stk->top < stk->capacity) {
		stk->data[stk->top] = val;
		stk->top++;
	}
	else {
		stk->capacity = stk->capacity * 2;
		stk->data = (int*)realloc(stk->data, stk->capacity * sizeof(int));
		printf("스택의 크기가 두 배가 되었습니다.\n");
		push(stk, val);
		//printf("\n\n\t\tstack overflow\n");
	}
}
void initialize(int_stack* stk, int size) {
	stk->data = (int)malloc(sizeof(int) * size);
	//stk->data = (int*)calloc(size, sizeof(int));
	stk->top = 0;
	stk->capacity = stk->minCapacity = size;
}
int isEmpty(const int_stack* const stk) {
	if (stk->top <= 0)//스택이 비어 있다면?
	{
		return 1;
	}
	else return 0;
}
void print(const int_stack* const stk) {  //포인터로 데이터 접근 가능-> 데이터의 수정 불가능, 주소값 수정 불가능 
	int i;

	if (isEmpty(stk)) {
		printf("stack underflow\n");
		return;
	}

	for (i = stk->top - 1; i >= 0; i--) {
		printf("%d ", stk->data[i]);
	}
	puts("");
}
