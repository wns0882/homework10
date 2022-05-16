#include <stdio.h>
#include <stdlib.h>
typedef struct node { //node구조체 정의
	int key;
	struct node *left;
	struct node *right;
} Node;// 구조체의 별칭을 Node로 선언

/* for stack */
#define MAX_STACK_SIZE		20 
Node* stack[MAX_STACK_SIZE]; //구조체 포인터 배열 선언
int top = -1; //top의 위치 설정

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1; //front 위치 설정
int rear = -1; // rear 위치 설정

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command; //커맨드를 입력받을 변수 선언
	int key; //int형 변수 key 선언 
	Node* head = NULL;//구조체 변수 head 초기화

	do{
		printf("\n\n");
		printf("[----- [박준용] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command 입력 받는다

		switch(command) {
		case 'z': case 'Z': //z를 입력받을 경우 initializeBST 함수 실행
			initializeBST(&head); 
			break;
		case 'q': case 'Q'://q를 입력받을 경우 freeBST 함수 실행
			freeBST(head);
			break;
		case 'i': case 'I': //i를 입력받을 경우 key값을 입력받고 insert 함수 실행
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': //d를 입력받을 경우 key값 입력받고 deletNode 함수 실행
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': //r을 입력받을 경우 recursiveInorder 함수 실행
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //t를 입력받을 경우 iterativeInorder 함수 실행
			break;

		case 'l': case 'L': // l을 입력받을 경우 levelOrder 함수 실행
			levelOrder(head->left);
			break;

		case 'p': case 'P': // p를 입력받을 경우 printStack 함수 실행
			printStack();
			break;

		default: //위에 커맨드들 중 없는 경우를 입력하면 주의 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q를 입력받기 전까지 반복문 실행

	return 1;
}

int initializeBST(Node** h) { //노드를 동적할당 해주는 함수 

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //노드가 할당되어있는 경우 
		freeBST(*h); //메모리해제

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //노드를 동적 메모리 할당
	(*h)->left = NULL;	/* root */ 
	(*h)->right = *h; //헤드노드의 우측 노드를 노드h로 설정
	(*h)->key = -9999; //노드의 key값 할당

	top = -1; //top의 위치 설정

	front = rear = -1; //front rear 위치 설정

	return 1;
}



void recursiveInorder(Node* ptr) //순환 중위 순회
{
	if(ptr) {  //left로 가서 왼쪽 노드 -> 뿌리 -> 오른쪽 노드 순으로 출력
		recursiveInorder(ptr->left); 
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //반복적 중위 순회
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node); //스택에 삽입
		node = pop(); //스택에 삭제

		if(!node) break; //공백 스텍시 브레이크
		printf(" [%d] ", node->key);

		node = node->right; //노드를 우측으로 이동
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨순서 순회
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */ //공백트리인 경우

	enQueue(ptr); //큐에 ptr을 넣는다

	for(;;) //루트 -> 왼쪽 -> 오른쪽 방식으로 순회
	{
		ptr = deQueue();//ptr에 큐에 있는 값을 넣어준다
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left) //왼쪽 노드인 경우
				enQueue(ptr->left); //큐에 왼쪽 노드 삽입
			if(ptr->right)//오른쪽 노드인 경우
				enQueue(ptr->right);//큐에 오른쪽 노드 삽입
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //노드 동적할당
	newNode->key = key; //입력받은 key값 대입    
	newNode->left = NULL;//왼쪽 노드 초기화
	newNode->right = NULL;//오른쪽 노드 초기화

	if (head->left == NULL) { //왼쪽 노드가 NULL인 경우
		head->left = newNode; //새로 입력 받은 노드를 넣어준다
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr에 루트 노드를 넣어준다

	Node* parentNode = NULL;//부모노드 초기화
	while(ptr != NULL) { //노드가 NULL일 때까지 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //key값이 존재하면 리턴

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //부모노드를 루트노드로 설정

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //입력받은 key값이 루트노드 보다 큰 경우 우측 노드로 이동
			ptr = ptr->right;
		else //작은 경우 왼쪽 노드로 이동
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  //부모노드의 key값이 더 큰 경우
		parentNode->left = newNode; //왼쪽에 입력받은 노드 삽입
	else
		parentNode->right = newNode; //오른쪽에 입력받은 노드 삽입
	return 1;
}


int deleteNode(Node* head, int key) 
{
	if (head == NULL) { //노드가 비어있는 경우
		printf("\n Nothing to delete!!\n"); //삭제할 노드가 없다는 메세지 출력
		return -1;
	}

	if (head->left == NULL) { //노드가 비어있는 경우
		printf("\n Nothing to delete!!\n");//삭제할 노드가 없다는 메세지 출력
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //노드에 루트노드를 삽입



	Node* parent = NULL; //부모노드 생성
	Node* ptr = root; // 루트노드 설정

	while((ptr != NULL)&&(ptr->key != key)) { //ptr노드가 NULL이고 key값이 다를 때까지 반복
		if(ptr->key != key) {//ptr key값이 입력받은 key값이랑 다른 경우

			parent = ptr;	/* save the parent */

			if(ptr->key > key) //입력받은 key값보다 큰 경우
				ptr = ptr->left;// 왼쪽으로 이동
			else //작은 경우
				ptr = ptr->right; //오른쪽으로 이동 
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //일치하는 값이 없는 경우
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //리프노드인 경우
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //ptr이 부모노드의 왼쪽 노드인 경우
				parent->left = NULL; //왼쪽 노드 삭제
			else
				parent->right = NULL; //오른쪽 노드 삭제
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;//루트노드 삭제

		}

		free(ptr); //ptr메모리 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //자식노드가 1개 있는 경우
	{
		Node* child; //구조체 포인터 변수 선언
		if (ptr->left != NULL) //왼쪽 노드가 있는 경우
			child = ptr->left; //자식노드를 왼쪽 노드로 설정
		else
			child = ptr->right;//자식노드를 오른쪽 노드로 설정

		if(parent != NULL) //부모노드가 있는 경우
		{
			if(parent->left == ptr)//부모노드의 왼쪽 노드가 ptr인 경우
				parent->left = child;//부모노드의 왼쪽 노드에 child 노드 삽입
			else
				parent->right = child; //부모노드의 오른쪽 노드에 child 노드 삽입
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //루트노드에 child 노드 삽입
		}

		free(ptr);//메모리 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //구조체 포인터 변수 선언
	parent = ptr;//부모노드 설정


	candidate = ptr->right;//루트노드의 오른쪽 노드로 설정
	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) // candidate의 좌측 노드가 NULL일 때까지 반복->트리에서 맨 왼쪽 끝 노드로 이동 
	{
		parent = candidate;  //부모노드 유지
		candidate = candidate->left; //트리에서 맨 왼쪽 끝 노드로 이동
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //부모노드의 우측 노드인 경우
		parent->right = candidate->right; //부모노드의 우측 노드에 candidate->right 노드 삽입
	else
		parent->left = candidate->right; //부모노드의 좌측 노드에 candidate->right 노드 삽입

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //ptr에 key값에 candidiate key값 대입

	free(candidate); //노드 메모리 해제
	return 1;
}


void freeNode(Node* ptr) //노드를 메모리해제 하는 함수
{
	if(ptr) { //후위 순회
		freeNode(ptr->left); 
		freeNode(ptr->right);
		free(ptr); //ptr노드 메모리 해제
	}
}

int freeBST(Node* head) 
{

	if(head->left == head) //헤드노드만 있는 경우
	{
		free(head);//헤드노드 메모리 해제
		return 1;
	}

	Node* p = head->left; //노드 p를 루트 노드로 설정

	freeNode(p);//노드들 메모리해제 함수

	free(head);//헤드노드 메모리 해제
	return 1;
}



Node* pop() //스택에서 노드를 pop하는 함수
{
	if (top < 0) return NULL; //top의 위치가 0보다 작으면 NULL 리턴
	return stack[top--]; //스택에서 탑위치에 노드 리턴 후 위치 한칸 이동
}

void push(Node* aNode)
{
	stack[++top] = aNode; //스택에서 top위치를 한칸 이동 후 노드 삽입
}


void printStack() //스택을 출력하는 함수
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) //스택에 있는 값들을 출력
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()//큐에서 꺼내는 함수
{
	if (front == rear) { //큐가 비어있는 경우
		printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front에 front위치를 큐 사이즈만큼 나눈 후 대입
	return queue[front]; //큐에있는 값 리턴

}

void enQueue(Node* aNode)//큐에 삽입하는 함수
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear에 rear위치를 큐 사이즈만큼 나눈 후 대입
	if (front == rear) { //큐가 가득 차있는 경우
		printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //큐에 rear에 값 추가 
}




