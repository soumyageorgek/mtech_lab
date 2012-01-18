#include<malloc.h>

struct node* insert(struct node *, int);
void display(struct node *);

struct node {
	int info;
	struct node* left;
	struct node* right;
};

main() {
	int ch, el;
	struct node* head=0;

	while(1) {
		printf("Enter your choice\n1.insert\n2.display\n3.remove\n");
		scanf("%d", &ch);
		switch(ch) {
			case 1: 
				scanf("%d", &el);				
				head = insert(head, el);
				break;
			case 2:
				display(head);
		}
	}
}

struct node* insert(struct node* head, int el) {
	int front=0, end=0;
	struct node* new_node;
	struct node* temp;
	struct node* dump[20];

	new_node = (struct node *)malloc(sizeof(struct node));
	new_node->info = el;
	new_node->left = 0;
	new_node->right = 0;
	temp = head;
	printf("%u", temp);
	if(temp == 0)
		return new_node;
	while(1) {
		if(temp->left == 0){
			temp->left = new_node;
			return head;
		}
		dump[end++] = temp->left;
		if(temp->right == 0){
			temp->right = new_node;
			return head;
		}
		dump[end++] = temp->right;
		temp = dump[front++];
	}
}

void display(struct node *head) {
	int front=0, end=0;
	struct node* dump[20];

	printf("%d ", head->info);
	while(head != 0){
		if(head->left == 0){
			return;
		}
		printf("%d ", head->left->info);
		dump[end++] = head->left;
		if(head->right == 0){
			return;
		}
		printf("%d ", head->right->info);
		dump[end++] = head->right;
		head = dump[front++];
	}
}
