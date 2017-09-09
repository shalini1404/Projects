#include <bits/stdc++.h>
using namespace std;
struct Node
{
	Node *left;
	Node *right;
	long long int data;
	long long int height;
	Node(){
        left=NULL;
        right=NULL;
        height=1;
	}
	Node(long long int k){
        left=NULL;
        right=NULL;
		data=k;
		height=1;
	}
};
int depth=0;
void printGivenLevel(struct Node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        cout<<root->data;
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        cout<<"\t";
        printGivenLevel(root->right, level-1);
    }
}
void printLevelOrder(struct Node* root)
{
    int h = root->height;
    int i;
    for (i=1; i<=h; i++){
        printGivenLevel(root, i);
        cout<<"\n";
    }
}

long long int max(long long int a, long long int b)
{
    return (a>b)?a:b;
}
long long int height(struct Node *n)
{
    if(n==NULL)
        return 0;
    else 
        return n->height;
}
struct Node* findPredecessor(struct Node *n)
{
	struct Node* pre=n->left;
	while(pre->right!=NULL)
	{
		pre=pre->right;
	}
	return pre;
}
bool search(struct Node *n, long long int key)
{
	depth++;
	if(n==NULL)
	{
		return false;
	}
	else if(n->data==key && n->left==NULL)
	{
		return true;
	}

	else if(n->data>=key)
	{
		return search(n->left, key);
	}
	else
		return search(n->right, key);
}
struct Node* rightRotate(struct Node *y)
{
	struct Node *x=y->left;
	struct Node *xr=x->right;
	x->right=y;
	y->left=xr;
	long long int a;
	long long int b;
	if(y->left==NULL)
		a=0;
	else
		a=y->left->height;
	if(y->right==NULL)
		b=0;
	else
		b=y->right->height;
	y->height=max(a,b)+1;
	if(x->left==NULL)
		a=0;
	else
		a=x->left->height;
	if(x->right==NULL)
		b=0;
	else
		b=x->right->height;
	x->height=max(a,b)+1;
	//cout<<x->data<<"rrrrrrrr"<<x->height<<"\n";
	return x;

}
struct Node* leftRotate(struct Node *x)
{
	struct Node *y=x->right;
	struct Node *yl=y->left;
	y->left=x;
	x->right=yl;
	long long int a;
	long long int b;
	if(x->left==NULL)
		a=0;
	else
		a=x->left->height;
	if(x->right==NULL)
		b=0;
	else
		b=x->right->height;
	x->height=max(a,b)+1;
	if(y->left==NULL)
		a=0;
	else
		a=y->left->height;
	if(y->right==NULL)
		b=0;
	else
		b=y->right->height;
	y->height=max(a,b)+1;
	
	//cout<<y->data<<"llllllll"<<y->height<<"\n";
	return y;

}
struct Node* insert(struct Node *n, long long int key)
{
	//cout<<key<<"aaa\n";
	if(n==NULL)
	{
        //cout<<key<<"aaaaa\n";
		struct Node *node1=new Node(key);
		return node1;
	}
	else if(n->data==key)
	{
		//cout<<"already present\n";
		//cout<<"fhjk";
		return n;
	}
	else if(n->left==NULL && n->right==NULL)
	{
		struct Node *leaf=new Node(key);
		struct Node *q=new Node();
		if(n->data>key)
		{
			q->left=leaf;
			q->right=n;
			q->data=leaf->data;
			q->height=2;
			return q;
		}
		else
		{
			q->left=n;
			q->right=leaf;
			q->data=n->data;
			q->height=2;
			return q;
		}

	}
	else if (n->data>key)
	{	
		n->left=insert(n->left, key);
		
	}
	else if(n->data<key){
		n->right=insert(n->right, key);
	}
	int balance;
	
	balance=height(n->left)-height(n->right);
	n->height=max(height(n->left),height(n->right))+1;
	//cout<<n->height<<"hhhhhhhh\n";
	if((balance>1)&&(key<n->left->data))
		n=rightRotate(n);
	else if((balance<-1)&&(key>n->right->data))
		n=leftRotate(n);
	else if((balance>1)&&(key>n->left->data))
	{
		n->left=leftRotate(n->left);
		n=rightRotate(n);
	}
	else if((balance<-1)&&(key<n->right->data))
	{
		n->right=rightRotate(n->right);
		n=leftRotate(n);
	}
	return n;
}
struct Node* deletion(struct Node *n, long long int key)
{
	
	if(n==NULL)
	{
        //cout<<"No data found\n";
        return n;
	}
	else if(n->data==key && n->left==NULL && n->right==NULL)
	{
			delete n;
			return NULL;
	}
	else if(n->data>=key)
	{
		n->left=deletion(n->left, key);
		if(n->right==NULL && n->left==NULL)
			return n;
		else if ((n->right!=NULL) && (n->left==NULL))
		{	//cout<<n->data<<"right child\n";
			struct Node *temp=n->right;
			*n=*temp;
			delete temp;
			return n;
		}
		else
		{
			struct Node *p=findPredecessor(n);
			n->data=p->data;
		}	
		//cout<<n->data<<"backlefty\n";
	}
	else if(n->data<key)
	{
		n->right=deletion(n->right,key);
		if(n->right==NULL && n->left==NULL)
			return n;
		if ((n->right==NULL)&&(n->left!=NULL))
		{	//cout<<n->data<<"left child\n";
			struct Node *temp=n->left;
			*n=*temp;
			delete temp;
		}
	}	
	
	int balance;
	long long int a;
	long long int b;
	if(n->left==NULL)

        //cout<<key<<"adavaa\n";
		a=0;
	else
        //cout<<key<<"ada\n";
		a=n->left->height;
	if(n->right==NULL)

        //cout<<key<<"adavaa\n";
		b=0;
	else
		b=n->right->height;
	balance=a-b;
	
	n->height=max(a,b)+1;
	//cout<<n->height<<"hhhhhhhh\n";

	if(balance>1)
	{
//		cout<<n->data<<"rrrrrrrrrrr\n";
		int balLeft;
		long long int c;
		long long int d;
		if(n->left->left==NULL)
			c=0;
		else
    		c=n->left->left->height;
		if(n->left->right==NULL)
			d=0;
		else
			d=n->left->right->height;
		balLeft=c-d;
		if(balLeft>=0)
			n=rightRotate(n);
		else
		{
			n->left=leftRotate(n->left);
			n=rightRotate(n);
		}
//		printLevelOrder(n);

	}

	else if(balance<-1)
	{
		int balRight;
		long long int c;
		long long int d;
		if(n->right->left==NULL)
			c=0;
		else
    		c=n->right->left->height;
		if(n->right->right==NULL)
			d=0;
		else
			d=n->right->right->height;
		balRight=c-d;
		if(balRight<=0)
			n=leftRotate(n);
		else
		{
			n->right=rightRotate(n->right);
			n=leftRotate(n);
		}
	}
	
	return n;

}
int main()
{
	struct Node *root=NULL;
	long long int k;
	//struct Node *p=search(root, 123456);

	char x,c;
	
	while(scanf("%c", &x)!=-1){
		switch(x){
			case 'S':
			case 's':
			{
				scanf("%lld", &k);
				depth=-1;
				if(search(root, k)){
					cout<<"f "<<depth<<endl;
				}
				else
					cout<<"nf\n";
				break;
			}
			case 'I':
			case 'i':
			{
				scanf("%lld", &k);
				depth=-1;
				if((search(root, k)==false))
				{
					root=insert(root, k);
					depth=-1;
					search(root, k);
					cout<<"i "<<depth<<endl;
				}
				else
					cout<<"fa\n";
				break;
			}
			case 'D':
			case 'd':
			{
				scanf("%lld", &k);
				depth=-1;
				if(search(root, k))
				{
					cout<<"d "<<depth<<endl;
					root=deletion(root,k);
				}
				else
					cout<<"nf\n";
				
				break;
			}
			case 'P':
			case 'p':
			{
				printLevelOrder(root);
				break;
			}
			default:exit(0);
		}
		scanf("%c", &c);
	}
	
	/*root=insert(root, 12);

	/*p=search(root, 12);
	//cout<<p->data<<"\n";
	root=insert(root, 12);
	//printLevelOrder(root);
	//cout<<root->data;
	//cout<<"aaaaaaaa";
	root=insert(root, 1);
	//printLevelOrder(root);
	//cout<<root->data;
	root=insert(root, 1467);
	//printLevelOrder(root);
	//cout<<root->data;
	root=insert(root, 612);
	//printLevelOrder(root);
	//cout<<root->data;
	root=insert(root, 6);
	//printLevelOrder(root);
	//cout<<root->data;
	root=insert(root, 4512);
	//printLevelOrder(root);
	root=insert(root, 412);
	//printLevelOrder(root);
	root=insert(root, 42);
	//printLevelOrder(root);
	//p=search(root, 42);
	root=insert(root, 1212);
	//root=insert(root, 42);
	root=insert(root, 4);
	root=insert(root, 53);
	root=insert(root, 9872);
	root=insert(root, 987);
	root=insert(root, 562);
	root=insert(root, 92);

	root=insert(root, 82);
	root=insert(root, 9);
	root=insert(root, 678);
	root=insert(root, 9874);
	root=insert(root, 21);
	root=insert(root, 90);
	root=insert(root, 9999);
	//root=insert(root, 568);
	//root=insert(root, 42);
//	printLevelOrder(root);
//	p=search(root, 4512);
	root=deletion(root, 987);
	root=deletion(root, 9);
	//printLevelOrder(root);
	root=deletion(root, 987);
	//printLevelOrder(root);
	root=deletion(root, 1467);
	//printLevelOrder(root);
	root=deletion(root, 92);
	//printLevelOrder(root);
	//p=search(root, 9874);
	//p=search(root, 6);
	//cout<<p->right->data<<"\n";
	//p=search(root, 562);
	//p=search(root, 6);
	//cout<<p->right->data<<"\n";
	root=deletion(root, 678);
	//printLevelOrder(root);
	root=deletion(root, 562);
	//printLevelOrder(root);
	root=deletion(root, 568);
	//printLevelOrder(root);
	root=deletion(root, 612);
//	printLevelOrder(root);
	root=deletion(root, 9999);
//	printLevelOrder(root);
	root=deletion(root, 9874);
//	printLevelOrder(root);
	root=deletion(root, 4512);
//	printLevelOrder(root);
	root=deletion(root, 1);
//	printLevelOrder(root);
	/*root=deletion(root, 6);
//	printLevelOrder(root);
	root=deletion(root, 4);
//	printLevelOrder(root);
	root=deletion(root, 12);
//	printLevelOrder(root);
	root=deletion(root, 42);
	printLevelOrder(root);*/
	return 0;

}
