//
//二叉树的操作实现
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SeqStackType char
#define SeqMax 1000


typedef char TreeNodeType;
//二叉树结点结构体
typedef struct TreeNode{
	TreeNodeType data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

typedef struct{
	TreeNode* data[SeqMax];
	size_t size;
}SeqStack;
//队列结构体
typedef struct queue{
	int cur;
	TreeNode arr[100];
	int size;
}Queue;

//二叉树结点的创建
TreeNode* CreatTreeNode(TreeNodeType value){
	TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));
	new->data = value;
	new->lchild = NULL;
	new->rchild = NULL;
	return new;
}

//二叉树的遍历
//方式一：先序遍历
//原理：基于二叉树的递归构造，其遍历也可以采取递归的方式，先序遍历<先访问本身结点，再访问左子树，
//最后访问右子树>
void PreOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	printf("%c ",root->data);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}

//先序遍历的检测函数
void textPreOrder(){
	//创建二叉树
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	PreOrder(A);
	printf("\n");
	return;
}

//方式二；中序遍历
//原理：同先序遍历，只是访问顺序有所差异，中序遍历<先访问左子树，再访问本身结点，最后访问右子树>
void InOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	InOrder(root->lchild);
	printf("%c ",root->data);
	InOrder(root->rchild);
}

//中序遍历的检测函数
void textInOrder(){
	//创建二叉树
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	InOrder(A);
	printf("\n");
	return;
}

//方式三：后序遍历
//原理：同先序遍历，只是访问顺序有所差异，后序遍历<先访问左子树，再访问右子树，最后访问本身结点>
void PostOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	printf("%c ",root->data);
}

//后序遍历的检测函数
void textPostOrder(){
	//创建二叉树
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	PostOrder(A);
	printf("\n");
	return;
}

//方式四：层序遍历
//原理：层序遍历与以上几种遍历方式右所不同，先序遍历是将访问结点的左子树与右子树入队，再将本身结点
//出队并访问自身结点，以此循环，直到队列为空，访问结束。
//此遍历中将会用到队列函数，故在此处将先实现队列的出队与入队操作函数的实现

//队列的入队操作
void PushQueue(Queue* head,TreeNode* value){
	if(head == NULL){
		//非法输入
		return;
	}
	if(head->size>=100){
		//队满
		return;
	}
	if(value == NULL){
		return;
	}
	head->arr[(head->size+head->cur)%100] = (*value);
	++head->size;
	return;
}
//队列的出队操作
void PopQueue(Queue* head){
	if(head == NULL){
		//非法输入
		return;
	}
	if(head->size == 0){
		//空队
		return;
	}
	++head->cur;
	--head->size;
	return;
}
//获得队列的队首元素
void QueueTop(Queue*head,TreeNode* value){
	if(head == NULL){
		//非法输入
		return;
	}
	if(head->size == 0){
		//空队
		return;
	}
	(*value) = head->arr[head->cur%100];
   return;	
}
//层序遍历的实现
void _levelOrder(Queue* que){
	TreeNode value;
	if(que == NULL){
		//非法输入
		return;
	}
	while(1){
		if(que->size == 0){
			//空队
			return;
		}
		QueueTop(que,&value);
		printf("%c ",value.data);
		PushQueue(que,value.lchild);
		PushQueue(que,value.rchild);
		PopQueue(que);
	}
}

void levelOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	Queue que = {
		0,
		{0},
		0
	};
	PushQueue(&que,root);
	_levelOrder(&que);
	
}

//层序遍历的检测函数
void textlevelOrder(){
	//创建二叉树
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	levelOrder(A);
	printf("\n");
	return;
}

////根据先序遍历结果构造一棵树--“abd###c##”
TreeNode* CreatTree(TreeNodeType cur[],size_t *index,size_t size,TreeNodeType null_value){
	if(*index == size){
		exit(0);
	}
	if(cur[*index] == null_value){
		return NULL;
	}
	TreeNode* new = CreatTreeNode(cur[*index]);
	++(*index);
	new->lchild = CreatTree(cur,index,size,'#');
	++(*index);
	new->rchild = CreatTree(cur,index,size,'#');
	return new;
}
//根据先序遍历结果构造一棵树的检测函数
void textCreatTree(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNodeType cur[] = "abd###c##";
	printf("cur = %s\n",cur);
	size_t size =sizeof(cur)/sizeof(cur[0])-1;
	size_t index = 0;
	TreeNode* ret = CreatTree(cur,&index,size,'#');
	printf("\n************PreOrder********************\n");
	PreOrder(ret);
	printf("\n************INOrder********************\n");
	InOrder(ret);
	printf("\n************PostOrder********************\n");
	PostOrder(ret);
	printf("\n************LevelOrder********************\n");
	levelOrder(ret);
	printf("\n");
	return;
}
void Destroy(TreeNode* root){
	free(root);
	root =NULL;
	return;
}
//销毁树
//通过后续遍历，将访问操作改为删除结点的操作
void TreeDestroy(TreeNode** root){
	if(root == NULL){
		return;
	}
	TreeDestroy(&((*root)->lchild));
	TreeDestroy(&((*root)->rchild));
	if((*root)->lchild==NULL&&(*root)->rchild==NULL){
		Destroy(*root);
	}
}

void textTreeDestroy(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	TreeDestroy(&A);
	if(A==NULL){
		printf("销毁成功！\n");
	}else{
		printf("销毁失败！\n");
	}
	printf("\n");
	return;
}
//树的拷贝
//通过遍历将树进行拷贝
TreeNode* TreeClone(TreeNode* root){
	if(root == NULL){
		return NULL;
	}
	TreeNode* new = CreatTreeNode(root->data);
	new->lchild = TreeClone(root->lchild);
	new->rchild = TreeClone(root->rchild);
	return new;
}
void textTreeClone(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	TreeNode* ret = TreeClone(A);
	printf("except:a b c d\n");
	printf("actual:");
	PreOrder(ret);
	printf("\n");
}

//求一棵树的叶子结点个数
//先序遍历输出二叉树中叶子结点
size_t TreeLeafSize(TreeNode* root){
	int leafcount;
	if(root==NULL){
		return 0;
	}else if((root->lchild==NULL)&&(root->rchild==NULL)){
		leafcount = 1;
	}else{
		leafcount=TreeLeafSize(root->lchild)+TreeLeafSize(root->rchild);
	}
	return leafcount;
}

void textTreeLeafSize(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	size_t ret = TreeLeafSize(A);
	printf("except:2   ,actual:%d\n",ret);
	printf("\n");
}
//求一棵树的结点个数
size_t TreeSize(TreeNode* root){
	int count;
	if(root == NULL){
		return 0;
	}
	return 1+TreeSize(root->lchild)+TreeSize(root->rchild);
}
void textTreeSize(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	size_t ret = TreeSize(A);
	printf("except:4   ,actual:%d\n",ret);
	return;
}
//求一棵树第K层结点的个数
size_t TreeLevelSize(TreeNode* root,int k){
	if(k<1){
		printf("非法输入！\n");
		exit(1);
	}
	if(root == NULL){
		return;
	}
	if(k==1){
		return 1;
	}
	return TreeLevelSize(root->lchild,k-1)+TreeLevelSize(root->rchild,k-1);
}
void textTreeLevelSize(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	size_t ret = TreeLevelSize(A,3);
	printf("except:1   ,actual:%d\n",ret);
}
//在树中查找元素，这个元素有可能不在这棵树内
TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find){
	if(root == NULL){
		return NULL;
	}
	TreeNode* ret= NULL;
	if(root->data == to_find){
		ret = root;
	}
	ret = TreeFind(root->lchild,to_find);
	if(ret){
		return ret;
	}
	ret = TreeFind(root->rchild,to_find);
	if(ret){
		return ret;
	}
	return ret;
}
void textTreeFind(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	TreeNode* ret = TreeFind(A,'f');
	if(ret==NULL){
		printf("未找到！\n");
		return;
	}
	printf("except:d,   actual:%c\n",ret->data);

}
//求树的高度
size_t TreeHeigh(TreeNode* root){
	int hl,hr,max;
	if(root!=NULL){
		hl = TreeHeigh(root->lchild);
		hr = TreeHeigh(root->rchild);
		max = hl>hr?hl:hr;
		return (max+1);
	}else{
		return 0;
	}
}
void textTreeHeigh(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	size_t ret= TreeHeigh(A);
	printf("except:3   actual:%d\n",ret);

}
//求结点的左子树，首先判断该结点是否为空，如果位空，
//返回NULL，反之返回该结点的左子树
TreeNode* LChild(TreeNode* node){
	if(node == NULL){
		return NULL;
	}
	return node->lchild;
}
//求结点的右子树
//首先判断该结点是否为空结点，如果是空结点，
//返回NULL，反之返回该结点的右子树
TreeNode* RChild(TreeNode* node){
	if(node ==NULL){
		return NULL;
	}
	return node->rchild;
}
void textR_Lchild(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	TreeNode* ret1 = LChild(B);
	if(ret1){
		printf("左子树：except :d    ,actual:%c\n",ret1->data);
	}else{
		printf("未找到！\n");
	}
	TreeNode* ret2 = RChild(A);
	if(ret2){
		printf("右子树：except:c     ,actual:%c\n",ret2->data);
	}else{
		printf("未找到！\n");
	}
	return;
}
//求结点的父结点
TreeNode* parent(TreeNode* root,TreeNode* node){
	if(root==NULL){
		return NULL;
	}
	if(root->lchild==node){
		return root;
	}
	if(root->lchild == node){
		return root;
	}
	parent(root->lchild,node);
	parent(root->rchild,node);
	return NULL;
}
void textParent(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	TreeNode* ret = parent(A,B);
	if(ret){
		printf("except: a   ,actual:%c\n",ret->data);
	}else{
		printf("未找到！\n");
	}
}
//创建栈，提供非递归的遍历使用

//初始化
void SeqStackInit(SeqStack* seq){
	seq->size = 0;
}
//销毁
void SeqStackDestroy(SeqStack* seq){
	seq->size = 0;
}
//入栈
void SeqStackPush(SeqStack* seq,TreeNode* value){
	if(seq == NULL){
		//非法输入
		return;
	}
	seq->data[seq->size] = value;
	++seq->size;
}
//出栈
void SeqStackPop(SeqStack* seq){
	if(seq == NULL){
		//非法输入
		return;
	}
	if(seq->size == 0){
		//空栈
		return;
	}
	--seq->size;
}
//取栈顶元素
int GetStackTop(SeqStack* seq,TreeNode* value){
	if(seq == NULL){
		//非法输入
		return 0;
	}
	if(seq->size == 0){
		//空栈
		return 0;
	}
	*value = *seq->data[seq->size-1];
	return 1;
}
//非递归的先序遍历二叉树
void PreOrderByLoop(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//入栈
	SeqStack q;
	SeqStackInit(&q);
	SeqStackPush(&q,root);
	TreeNode value;
	while(GetStackTop(&q,&value)){
		printf("%c ",value.data);
		SeqStackPop(&q);
		if(value.rchild != NULL){
			//入栈
			SeqStackPush(&q,value.rchild);
		}
		if(value.lchild != NULL){
			//入栈
			SeqStackPush(&q,value.lchild);
		}
	}
	printf("\n");
	return;
}
void textPreOrderByLoop(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	PreOrderByLoop(A);
}
//非递归的中许遍历二叉树
void InOrderByLoop(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//入栈
	SeqStack q;
	SeqStackInit(&q);
	SeqStackPush(&q,root);
	TreeNode* cur = root->lchild;
	while(1){
		while(cur != NULL){
			SeqStackPush(&q,cur);
			cur = cur->lchild;
		}
		TreeNode value;
		if(GetStackTop(&q,&value)){
			printf("%c ",value.data);
			cur =value.rchild;
			SeqStackPop(&q);
		}else{
			printf("\n");
			return;
		}
	}
	return;
}
void textInOrderByLoop(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	InOrderByLoop(A);
}
//非递归的后序遍历二叉树
void PostOrderByLoop(TreeNode* root){
	if(root==NULL){
		//空树
		return;
	}
	//入栈
	SeqStack q;
	SeqStackInit(&q);
	SeqStackPush(&q,root);
	TreeNode* cur = root->lchild;
	while(1){
		while(cur != NULL){
			SeqStackPush(&q,cur);
			cur = cur->lchild;
		}
		TreeNode value;
		TreeNode pre;
		if(GetStackTop(&q,&value)){
			while(value.rchild ==NULL||(value.rchild)->data == pre.data){
				printf("%c ",value.data);
				pre = value;
				SeqStackPop(&q);
				if(GetStackTop(&q,&value)==0){
					printf("\n");
					return;
				}
			}
			cur = value.rchild;
		}else{
			printf("\n");
			return;
		}
	}
}
void textPostOrderByLoop(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	PostOrderByLoop(A);
}
//二叉树的镜像
void swap(TreeNode** lchild,TreeNode** rchild){
	TreeNode* tmp = *lchild;
			*lchild = *rchild;
			*rchild = tmp;
}
void TreeMirror(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	swap(&(root->lchild),&(root->rchild));
	TreeMirror(root->lchild);
	TreeMirror(root->rchild);
}
void textTreeMirror(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	B->lchild = D;
	TreeMirror(A);
	PostOrderByLoop(A);
}
//判断二叉树是否为完全二叉树
//对树进行遍历，每遍历一个结点，判断该结点是否为空，为空，
//将‘#’入队，反正将结点的值入队，然后对队列取队首元素，并
//进行判断，若该队首元素值为'#'并执行出队操作,继续取队首
//元素，直到队列内没有元素，如果出现非‘#’值，说名该树非完全
//二叉树，如果未出现‘#’以外的值，则表示该树为完全二叉树
int _IsCompleteTree(Queue* que){
	TreeNode value;
	static int state = 0;
	if(que->size == 0){
		//空队
		return 1;
	}
	QueueTop(que,&value);
	if(value.data!='#'){
		if(state == 1){
			return 0;
		}
		PopQueue(que);
		if(value.lchild == NULL){
			TreeNode* new = CreatTreeNode('#');
			PushQueue(que,new);
		}else{
			PushQueue(que,value.lchild);
		}
		if(value.rchild == NULL){
			TreeNode* new = CreatTreeNode('#');
			PushQueue(que,new);
		}else{
			PushQueue(que,value.rchild);
		}
		_IsCompleteTree(que);
	}else{
		state = 1;
		PopQueue(que);
		_IsCompleteTree(que);
	}
}

int IsCompleteTree(TreeNode* root){
	if(root == NULL){
		//空树
		return 1;
	}
	Queue que = {
		0,
		{0},
		0
	};
	PushQueue(&que,root);
	return _IsCompleteTree(&que);
}

void textIsCompleteTree(){
	printf("\n*************%s********************\n",__FUNCTION__);
	TreeNode* A = CreatTreeNode('a');
	TreeNode* B = CreatTreeNode('b');
	TreeNode* C = CreatTreeNode('c');
	TreeNode* D = CreatTreeNode('d');
	A->lchild = B;
	A->rchild = C;
	A->lchild = D;
	int ret = IsCompleteTree(A);
	printf("except: 1,    actual:%d\n",ret);
	return;
}

//主函数
int main(){

//	textPreOrder();
//	textInOrder();
//	textPostOrder();
//	textlevelOrder();
//	textCreatTree();
//	textTreeFind();
//	textR_Lchild();
//*	textTreeDestroy();
//	textTreeLeafSize();
//	textTreeHeigh();
//	textParent();
//	textTreeSize();
//	textTreeLevelSize();
//	textTreeClone();
//	textIsCompleteTree();
//	textPreOrderByLoop();
//	textInOrderByLoop();
	textPostOrderByLoop();
//	textTreeMirror();
	return 0;
}
