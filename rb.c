#include <stdio.h>
#include <stdlib.h>
struct node {
  int dat;
  char color;
  struct node *left;
  struct node *right;
  struct node *parent;
};

struct node *new(int dat) {
  struct node *t;

  t = malloc(sizeof(struct node));
  t->dat = dat;
  t->left = 0;
  t->right = 0;
  t->parent = 0;
  t->color = 'r';
  return t;
}
struct node *r_rotate(struct node *n, struct node *root) {
  struct node *temp1, *temp2;
  
  printf("right\n");
  temp1 = n->left->right;
  if (temp1!=0)
    temp1->parent = n; 
  temp2 = n->left;
  if (n->parent!=0)
    n->parent->left = temp2;
  n->left = 0;
  if (temp2!=0) {
    temp2->parent = n->parent;
    temp2->right = n;
  }
  n->parent = temp2;
  n->left = temp1;
  return ((n==root)?temp2:root);
}

struct node *l_rotate(struct node *n, struct node *root) {
  struct node *temp1, *temp2;

  printf("left\n");
  temp1 = n->right->left;
  if(temp1!=0)
    temp1->parent = n;
  temp2 = n->right;
  if(n->parent!=0)
    n->parent->right = temp2;
  n->right = 0;
  if (temp2!=0) {
    temp2->parent = n->parent;
    temp2->left = n;
  }
  n->parent = temp2;
  n->right = temp1;
  printf("left\n");
  return ((n==root)?temp2:root);
}

struct node *grandparent(struct node *n) {
  if ((n != NULL) && (n->parent != NULL))
    return n->parent->parent;
  else
    return NULL;
}

struct node *uncle(struct node *n) {
        struct node *g = grandparent(n);
  if (g == NULL)
    return NULL; // No grandparent means no uncle
  if (n->parent == g->left)
    return g->right;
  else
    return g->left;
}
 
struct node *insert(struct node *h, struct node *n) {
  struct node *temp = h;
  struct node *current=0;
  char d;
  if(h == 0) {
    n->parent = 0;
    return n;
  } else {
    while (temp!=0){
      current = temp;
      if(n->dat < temp->dat) {
	temp = temp->left;
	d = 'l';
      }
      else { 
	temp = temp->right;
	d = 'r';
      }
    }
    if(d=='l')
      current->left = n;
    else
      current->right = n;
    n->parent = current;
  }
    return h;
}
struct node *color(struct node *n, struct node *root) {
  struct node *p=n->parent;
  if(p == 0){
    n->color = 'b';
    return root;
  }
  if(p->color == 'b'){
    return root;
  }

  struct node *u=uncle(n);
  struct node *g=grandparent(n);

  if((u!=0) &&(u->color == 'r')) {
    printf("uncleeeeeeee\n");
    p->color = 'b';
    u->color = 'b';
    g->color = 'r';
    root = color(g, root);
  } else {
      if(g != 0) {
	if((n == p->right) && (p == g->left)) {
	  root = l_rotate(p, root);
	  n = n->left;
	}else if ((n == p->left) && (p == g->right)) {
	  root = r_rotate(p, root);
	  n = n->right;
	}
	p = n->parent;
	g = grandparent(n);
	p->color = 'b';
	g->color = 'r';
	if (n == p->left) 
	  root = r_rotate(g, root);
	else
	  root = l_rotate(g, root);
      }
  }
  return root;
}
struct node *rb_insert(struct node *h, struct node *n) {
  h = insert(h, n);
  h = color(n, h);
  return h;
}
void inorder(struct node *l)
{
  if(l == 0) return;

  inorder(l->left);
  printf("%d\t%c\t",l->dat, l->color);
  if(l->parent)
    printf("%dparent\n",l->parent->dat);
  inorder(l->right);
}

main()
{
  struct node *h = 0;
  int choice, data;

  while(1){
    printf("1.insert\n2.inorder\n3.delete\n");
    scanf("%d",&choice);

    switch(choice){
      case 1:scanf("%d",&data);
	    h = rb_insert(h, new(data));
	    break;
      case 2:inorder(h);
	    printf("\n");
	    break;
    }
  }

}



