#include <stdio.h>
#include <stdlib.h>
typedef struct node { //node����ü ����
	int key;
	struct node *left;
	struct node *right;
} Node;// ����ü�� ��Ī�� Node�� ����

/* for stack */
#define MAX_STACK_SIZE		20 
Node* stack[MAX_STACK_SIZE]; //����ü ������ �迭 ����
int top = -1; //top�� ��ġ ����

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1; //front ��ġ ����
int rear = -1; // rear ��ġ ����

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
	char command; //Ŀ�ǵ带 �Է¹��� ���� ����
	int key; //int�� ���� key ���� 
	Node* head = NULL;//����ü ���� head �ʱ�ȭ

	do{
		printf("\n\n");
		printf("[----- [���ؿ�] [2019038010] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//command �Է� �޴´�

		switch(command) {
		case 'z': case 'Z': //z�� �Է¹��� ��� initializeBST �Լ� ����
			initializeBST(&head); 
			break;
		case 'q': case 'Q'://q�� �Է¹��� ��� freeBST �Լ� ����
			freeBST(head);
			break;
		case 'i': case 'I': //i�� �Է¹��� ��� key���� �Է¹ް� insert �Լ� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': //d�� �Է¹��� ��� key�� �Է¹ް� deletNode �Լ� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': //r�� �Է¹��� ��� recursiveInorder �Լ� ����
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //t�� �Է¹��� ��� iterativeInorder �Լ� ����
			break;

		case 'l': case 'L': // l�� �Է¹��� ��� levelOrder �Լ� ����
			levelOrder(head->left);
			break;

		case 'p': case 'P': // p�� �Է¹��� ��� printStack �Լ� ����
			printStack();
			break;

		default: //���� Ŀ�ǵ�� �� ���� ��츦 �Է��ϸ� ���� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q�� �Է¹ޱ� ������ �ݺ��� ����

	return 1;
}

int initializeBST(Node** h) { //��带 �����Ҵ� ���ִ� �Լ� 

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //��尡 �Ҵ�Ǿ��ִ� ��� 
		freeBST(*h); //�޸�����

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //��带 ���� �޸� �Ҵ�
	(*h)->left = NULL;	/* root */ 
	(*h)->right = *h; //������� ���� ��带 ���h�� ����
	(*h)->key = -9999; //����� key�� �Ҵ�

	top = -1; //top�� ��ġ ����

	front = rear = -1; //front rear ��ġ ����

	return 1;
}



void recursiveInorder(Node* ptr) //��ȯ ���� ��ȸ
{
	if(ptr) {  //left�� ���� ���� ��� -> �Ѹ� -> ������ ��� ������ ���
		recursiveInorder(ptr->left); 
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //�ݺ��� ���� ��ȸ
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node); //���ÿ� ����
		node = pop(); //���ÿ� ����

		if(!node) break; //���� ���ؽ� �극��ũ
		printf(" [%d] ", node->key);

		node = node->right; //��带 �������� �̵�
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //�������� ��ȸ
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */ //����Ʈ���� ���

	enQueue(ptr); //ť�� ptr�� �ִ´�

	for(;;) //��Ʈ -> ���� -> ������ ������� ��ȸ
	{
		ptr = deQueue();//ptr�� ť�� �ִ� ���� �־��ش�
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left) //���� ����� ���
				enQueue(ptr->left); //ť�� ���� ��� ����
			if(ptr->right)//������ ����� ���
				enQueue(ptr->right);//ť�� ������ ��� ����
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //��� �����Ҵ�
	newNode->key = key; //�Է¹��� key�� ����    
	newNode->left = NULL;//���� ��� �ʱ�ȭ
	newNode->right = NULL;//������ ��� �ʱ�ȭ

	if (head->left == NULL) { //���� ��尡 NULL�� ���
		head->left = newNode; //���� �Է� ���� ��带 �־��ش�
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //ptr�� ��Ʈ ��带 �־��ش�

	Node* parentNode = NULL;//�θ��� �ʱ�ȭ
	while(ptr != NULL) { //��尡 NULL�� ������ �ݺ�

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //key���� �����ϸ� ����

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //�θ��带 ��Ʈ���� ����

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //�Է¹��� key���� ��Ʈ��� ���� ū ��� ���� ���� �̵�
			ptr = ptr->right;
		else //���� ��� ���� ���� �̵�
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)  //�θ����� key���� �� ū ���
		parentNode->left = newNode; //���ʿ� �Է¹��� ��� ����
	else
		parentNode->right = newNode; //�����ʿ� �Է¹��� ��� ����
	return 1;
}


int deleteNode(Node* head, int key) 
{
	if (head == NULL) { //��尡 ����ִ� ���
		printf("\n Nothing to delete!!\n"); //������ ��尡 ���ٴ� �޼��� ���
		return -1;
	}

	if (head->left == NULL) { //��尡 ����ִ� ���
		printf("\n Nothing to delete!!\n");//������ ��尡 ���ٴ� �޼��� ���
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left; //��忡 ��Ʈ��带 ����



	Node* parent = NULL; //�θ��� ����
	Node* ptr = root; // ��Ʈ��� ����

	while((ptr != NULL)&&(ptr->key != key)) { //ptr��尡 NULL�̰� key���� �ٸ� ������ �ݺ�
		if(ptr->key != key) {//ptr key���� �Է¹��� key���̶� �ٸ� ���

			parent = ptr;	/* save the parent */

			if(ptr->key > key) //�Է¹��� key������ ū ���
				ptr = ptr->left;// �������� �̵�
			else //���� ���
				ptr = ptr->right; //���������� �̵� 
		}
	}

	/* there is no node for the key */
	if(ptr == NULL) //��ġ�ϴ� ���� ���� ���
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL) //��������� ���
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr) //ptr�� �θ����� ���� ����� ���
				parent->left = NULL; //���� ��� ����
			else
				parent->right = NULL; //������ ��� ����
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;//��Ʈ��� ����

		}

		free(ptr); //ptr�޸� ����
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL)) //�ڽĳ�尡 1�� �ִ� ���
	{
		Node* child; //����ü ������ ���� ����
		if (ptr->left != NULL) //���� ��尡 �ִ� ���
			child = ptr->left; //�ڽĳ�带 ���� ���� ����
		else
			child = ptr->right;//�ڽĳ�带 ������ ���� ����

		if(parent != NULL) //�θ��尡 �ִ� ���
		{
			if(parent->left == ptr)//�θ����� ���� ��尡 ptr�� ���
				parent->left = child;//�θ����� ���� ��忡 child ��� ����
			else
				parent->right = child; //�θ����� ������ ��忡 child ��� ����
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; //��Ʈ��忡 child ��� ����
		}

		free(ptr);//�޸� ����
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

	Node* candidate; //����ü ������ ���� ����
	parent = ptr;//�θ��� ����


	candidate = ptr->right;//��Ʈ����� ������ ���� ����
	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL) // candidate�� ���� ��尡 NULL�� ������ �ݺ�->Ʈ������ �� ���� �� ���� �̵� 
	{
		parent = candidate;  //�θ��� ����
		candidate = candidate->left; //Ʈ������ �� ���� �� ���� �̵�
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate) //�θ����� ���� ����� ���
		parent->right = candidate->right; //�θ����� ���� ��忡 candidate->right ��� ����
	else
		parent->left = candidate->right; //�θ����� ���� ��忡 candidate->right ��� ����

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key; //ptr�� key���� candidiate key�� ����

	free(candidate); //��� �޸� ����
	return 1;
}


void freeNode(Node* ptr) //��带 �޸����� �ϴ� �Լ�
{
	if(ptr) { //���� ��ȸ
		freeNode(ptr->left); 
		freeNode(ptr->right);
		free(ptr); //ptr��� �޸� ����
	}
}

int freeBST(Node* head) 
{

	if(head->left == head) //����常 �ִ� ���
	{
		free(head);//����� �޸� ����
		return 1;
	}

	Node* p = head->left; //��� p�� ��Ʈ ���� ����

	freeNode(p);//���� �޸����� �Լ�

	free(head);//����� �޸� ����
	return 1;
}



Node* pop() //���ÿ��� ��带 pop�ϴ� �Լ�
{
	if (top < 0) return NULL; //top�� ��ġ�� 0���� ������ NULL ����
	return stack[top--]; //���ÿ��� ž��ġ�� ��� ���� �� ��ġ ��ĭ �̵�
}

void push(Node* aNode)
{
	stack[++top] = aNode; //���ÿ��� top��ġ�� ��ĭ �̵� �� ��� ����
}


void printStack() //������ ����ϴ� �Լ�
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) //���ÿ� �ִ� ������ ���
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()//ť���� ������ �Լ�
{
	if (front == rear) { //ť�� ����ִ� ���
		printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE; //front�� front��ġ�� ť �����ŭ ���� �� ����
	return queue[front]; //ť���ִ� �� ����

}

void enQueue(Node* aNode)//ť�� �����ϴ� �Լ�
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //rear�� rear��ġ�� ť �����ŭ ���� �� ����
	if (front == rear) { //ť�� ���� ���ִ� ���
		printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode; //ť�� rear�� �� �߰� 
}




