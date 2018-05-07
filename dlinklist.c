#include<stdio.h>
#include<stdlib.h>

typedef char DLinkType; //定义参数类型

typedef struct DLinkNode { //定义结点
	DLinkType data; 
	struct DLinkNode* next; 
	struct DLinkNode* prev; 
} DLinkNode; 

//创建新结点
DLinkNode*CreateNewNode(DLinkType value){
	DLinkNode* new_node = (DLinkNode *)malloc(sizeof(DLinkNode));
	new_node->data = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}
//对带环双链表进行初始化
void DLinkListInit(DLinkNode** head){
	(*head)->next =(*head);
	(*head)->prev = (*head);
} 

//输入链表
void PrintLinkList(DLinkNode* head,char * str){
	printf("\n*********%s*************\n",str);
	DLinkNode* cur = head->next;
	while(cur != head){
		printf("%c ",cur->data);
		cur = cur->next;
	}
	printf("\n");
}

//对带环双链表进行尾插
void DLinkListPushBack(DLinkNode** head, DLinkType value){
	DLinkNode* new = CreateNewNode(value);
	DLinkNode* tmp = (*head)->prev;
	tmp->next = new;
	new->prev = tmp;
	new->next = (*head);
	(*head)->prev = new;
	return;
}

//对带环双链表进行尾删
void DLinkListPopBack(DLinkNode** head){
	if(head == NULL){
		//非法输入
		return;
	}
	if((*head)->next == (*head)){
		//空链表
		return;
	}
	DLinkNode* delete = (*head)->prev;
	delete->prev->next = delete->next;
	delete->next->prev = delete->prev;
	free(delete);
}
//对带环双链表进行头插
void DLinkListPushFront(DLinkNode** head, DLinkType value){
	DLinkNode* new = CreateNewNode(value);
	DLinkNode* tmp = (*head)->next;
	tmp->prev = new;
	new->next = tmp;
	new->prev = (*head);
	(*head)->next = new;
	return;
} 
//对带环双链表进行头删
void DLinkListPopFront(DLinkNode** head){
	if(head == NULL){
		//非法输入
		return;
	}
	if((*head)->next == (*head)){
		//空链表
		return;
	}
	DLinkNode* delete = (*head)->next;
	delete->next->prev = (*head);
	delete->prev->next = delete->next;
	free(delete);

}
//对双链表进行指定元素的查找
DLinkNode* DLinkListFind(DLinkNode* head, DLinkType to_find); 

//往指定位置之前插入一个元素
void DLinkListInsert(DLinkNode* pos, DLinkType value); 
//往指定元素之后插入一个元素
void DLinkListInsertAfter(DLinkNode* pos, DLinkType value);

//检测函数
void textDLinkListPushBack(){
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	DLinkListInit(&head);
   	DLinkListPushBack(&head, 'a');
	DLinkListPushBack(&head, 'b');
	DLinkListPushBack(&head, 'c');
	DLinkListPushBack(&head, 'd');
	PrintLinkList(head,"DLinkListPushBack");
}
void textDLinkListPopBack(){
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	DLinkListInit(&head);
   	DLinkListPushBack(&head, 'a');
	DLinkListPushBack(&head, 'b');
	DLinkListPushBack(&head, 'c');
	DLinkListPushBack(&head, 'd');
	DLinkListPopBack(&head);
	PrintLinkList(head,"DLinkListPopBack");
}
void textDLinkListPushFront(){
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	DLinkListInit(&head);
   	DLinkListPushFront(&head, 'a');
	DLinkListPushFront(&head, 'b');
	DLinkListPushFront(&head, 'c');
	DLinkListPushFront(&head, 'd');
	PrintLinkList(head,"DLinkListPushBack");
}
void textDLinkListPopFront(){
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	DLinkListInit(&head);
   	DLinkListPushBack(&head, 'a');
	DLinkListPushBack(&head, 'b');
	DLinkListPushBack(&head, 'c');
	DLinkListPushBack(&head, 'd');
	DLinkListPopFront(&head);
	PrintLinkList(head,"DLinkListPushBack");
}
void textDLinkListPopBack(){
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	DLinkListInit(&head);
   	DLinkListPushBack(&head, 'a');
	DLinkListPushBack(&head, 'b');
	DLinkListPushBack(&head, 'c');
	DLinkListPushBack(&head, 'd');
	DLinkListPopBack(&head);
	PrintLinkList(head,"DLinkListPopBack");
}
void textDLinkListPushFront(){
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	DLinkListInit(&head);
   	DLinkListPushFront(&head, 'a');
	DLinkListPushFront(&head, 'b');
	DLinkListPushFront(&head, 'c');
	DLinkListPushFront(&head, 'd');
	PrintLinkList(head,"DLinkListPushBack");
}
void textDLinkListPopFront();
void textDLinkListInsert();
void textDLinkListInsertAfter();

//主函数
int main(){
	textDLinkListPushBack();
	textDLinkListPopBack();
	textDLinkListPushFront();
	textDLinkListPopFront();
}
