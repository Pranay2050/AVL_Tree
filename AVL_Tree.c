#include<stdio.h>
#include<stdlib.h>

struct AVLtreenode
{
	int value;
	int height;
	struct AVLtreenode * left;
	struct AVLtreenode * right;
};
int max(int a,int b)
{
	return (a>b)?a:b ;
}

struct AVLtreenode* findmin(struct AVLtreenode * ptr)
{
	while(ptr->left != NULL)
		ptr=ptr->left;
	return ptr;
}

int getHeight(struct AVLtreenode *r)
{
	int height,htr,htl;
	if(r==NULL)
	return -1;
	if(r->left==NULL && r->right==NULL)
	return 0;
	htl=getHeight(r->left);
	htr=getHeight(r->right);
	height=1+max(htl,htr);
	return height;
}

int getBalance(struct AVLtreenode *r)
{
    if (r == NULL)
        return 0;
    return getHeight(r->left)-getHeight(r->right);
}

struct AVLtreenode * singlerotateright(struct AVLtreenode * P)
{
	struct AVLtreenode *LC;
	LC=P->left;
	P->left=LC->right;
	LC->right=P;
	P->height=1+max(getHeight(P->left),getHeight(P->right));
	LC->height=1+max(getHeight(LC->left),getHeight(LC->right));
	return LC;
}
struct AVLtreenode * singlerotateleft(struct AVLtreenode * P)
{
	struct AVLtreenode *RC;
	RC=P->right;
	P->right=RC->left;
	RC->left=P;
	P->height=1+max(getHeight(P->left),getHeight(P->right));
	RC->height=1+max(getHeight(RC->left),getHeight(RC->right));
	return RC;
}
struct AVLtreenode * doublerotateleftright(struct AVLtreenode * P)
{
	struct AVLtreenode * ptr;
	P->left=singlerotateleft(P->left);
	ptr=singlerotateright(P);
	return ptr;
}
struct AVLtreenode * doublerotaterightleft(struct AVLtreenode * P)
{
	struct AVLtreenode * ptr;
	P->right=singlerotateright(P->right);
	ptr=singlerotateleft(P);
	return ptr;
}

void traverse (struct AVLtreenode *r)
{
    if(r==NULL)
	return ;

	traverse(r->left);
	printf("%d %d\n",r->value,r->height);
	traverse(r->right);
}
struct AVLtreenode * insert(struct AVLtreenode *r,int val)
{

	if(r==NULL)
	{
		struct AVLtreenode * newnode;
		newnode=(struct AVLtreenode *)malloc(sizeof(struct AVLtreenode));
		if(newnode==NULL)
		{
			printf("Malloc failed\n");
			exit(-1);
		}
		newnode->value=val;
		newnode->height=0;
		newnode->left=NULL;
		newnode->right=NULL;
		return newnode;
	}
	if(val<r->value)
		{
			r->left=insert(r->left,val);
			if(getBalance(r)==2)
			{
				if(val<(r->left)->value)
				r=singlerotateright(r);
				else
				r=doublerotateleftright(r);
			}
		}
	else if(val>=(r->value))
		{
			r->right=insert(r->right,val);
			if(getBalance(r)==-2)
			{
				if(val>=(r->right)->value)
				r=singlerotateleft(r);
				else
				r=doublerotaterightleft(r);
			}
		}
	r->height=max(getHeight(r->left),getHeight(r->right))+1;
	return r;

}

struct AVLtreenode* delete(struct AVLtreenode* root, int val)
{
	struct AVLtreenode* ptr, *temp;
	if(root == NULL)
		return root;

	else if(val<(root->value))
		root->left=delete(root->left,val);

	else if(val>(root->value))
		root->right = delete(root->right,val);
	else
	{
		if((root->left)==NULL && (root->right)==NULL)
		{
			free(root);
			return NULL;
		}

		else if(root->left==NULL)
		{
			temp=root->right;
			free(root);
			return temp;
		}

		else if(root->right==NULL)
		{
			temp=root->left;
			free(root);
			return temp;
		}

		else
		{
			ptr= findmin(root->right);
			root->value=ptr->value;
			root->right=delete(root->right,ptr->value);
		}
	}
	root->height=max(getHeight(root->left),getHeight(root->right))+1;

	int balance=getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)
        return singlerotateright(root);
    if (balance > 1 && getBalance(root->left) < 0)
        return doublerotateleftright(root);
    if (balance < -1 && getBalance(root->right) <= 0)
        return singlerotateleft(root);
    if (balance < -1 && getBalance(root->right) > 0)
        return doublerotaterightleft(root);

return root;
}

int main()
{
	struct AVLtreenode * root;
	root=NULL;
	int value;
	printf("Enter node to insert,-1 to end\n");
	while(1)
	{
		scanf("%d",&value);
		if(value==-1)
			break;
		root=insert(root,value);
	}
	printf("\nDisplaying tree\n");
	traverse(root);

    printf("\nEnter node to delete,-1 to end\n");
    while(1)
	{
		scanf("%d",&value);
		if(value==-1)
			break;
		root=delete(root,value);
	}
	printf("\nDisplaying tree\n");
	traverse(root);
}

/*OUTPUT
Enter node to insert,-1 to end
1
3
2
6
4
9
-1

Displaying tree
1 0
2 1
3 0
4 2
6 1
9 0

Enter node to delete,-1 to end
2
9
-1

Displaying tree
1 0
3 1
4 2
6 0
*/


