#include <bits/stdc++.h>
using namespace std;
struct Node
{
	Node *left;
	Node *right;
    Node *parent;
    int color;
    long long int ht;
	long long int data;
	
	Node(){
        parent=NULL;
        left=NULL;
        right=NULL;
        ht=1;
        color=0;        ///////////// o represents black color, 1 represents red color
	}
	Node(long long int k){
        parent=NULL;
        left=NULL;
        right=NULL;
        ht=1;
        data=k;
        color=0;
	}
};
int depth=0;
long long int subTreeMax(struct Node *x)
{   
    while(x->left!=NULL && x->right!=NULL)
        x=x->right;
    return x->data;
}
void printGivenLevel(struct Node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1){
        cout<<"("<<root->data<<","<<root->ht<<","<<root->color;
        if(root->parent){
            cout<<","<<root->parent->data;
        }
        if(root->left)
            cout<<","<<root->left->data;
        if(root->right)
            cout<<","<<root->right->data;
        cout<<")"<<"\t";
    }
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}
void printLevelOrder(struct Node* root)
{
    if(!root)
        return;
    int h = root->ht;
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
        return n->ht;
}
struct Node* rightRotate(struct Node *y)
{
    struct Node *x=y->left;
    struct Node *xr=x->right;
    x->right=y;
    y->left=xr;
    xr->parent=y;
    x->parent=y->parent;
    y->parent=x;
    y->ht=max(height(y->left),height(y->right))+1;
    x->ht=max(height(x->left),height(x->right))+1;
    //cout<<x->data<<"rrrrrrrr"<<x->height<<"\n";
    return x;

}
struct Node* leftRotate(struct Node *x)
{
    struct Node *y=x->right;
    struct Node *yl=y->left;
    y->left=x;
    x->right=yl;
    yl->parent=x;
    y->parent=x->parent;
    x->parent=y;
    x->ht=max(height(x->left),height(x->right))+1;
    y->ht=max(height(y->left),height(y->right))+1;
    return y;

}
struct Node* find(struct Node *n, long long int k)
{
    if(n->left==NULL && n->right==NULL)
        return n;
    else if(k<=n->data){
        depth++;
        return find(n->left, k);
    }
    else{
        depth++;
        return find(n->right, k);
    }
}
bool search(struct Node *n, long long int key)
{ 
    struct Node *node1=new Node();
    depth=0;
    if(n==NULL)
    {
        //cout<<"\nNo data found\n";
        return false;
    }
    else
       node1=find(n,key);
    if(key==node1->data)
        return true;
    else
        return false;  
}
void updateHeight(struct Node *y)
{
    while(y->parent!=NULL)
    {
        y=y->parent;
        y->ht=max(height(y->left),height(y->right))+1;

    }
}
void updateData(struct Node *y, long long k)
{
    struct Node *temp=new Node();
    while(y->parent!=NULL)
    {   
        temp=y;
        y=y->parent;
        if(temp==y->left)
        {
            y->data=k;
            break;
        }

    }
}
struct Node* fixRedParent(struct Node *y, struct Node *n)
{
    if(y->parent==NULL){
        y->color=0;
        return n;
    }
    else
    {
        struct Node *q=y->parent;
        if(q->color==0)
        {
            return n;

        }
        struct Node *m=(q==q->parent->right)?q->parent->left:q->parent->right;
        if(m->color==1)
        {
            q->color=0;
            m->color=0;
            q->parent->color=1;
            y=q->parent;
            n=fixRedParent(y, n);
            return n;
        }
        else
        { 
            struct Node *g=q->parent;                               /////////////g is y's grandparent
            if(y==q->left && q==g->left)            /////////left left case
            {
                if(g->parent!=NULL && g==g->parent->left)
                {
                    struct Node *gg=g->parent;
                    gg->left=rightRotate(g);
                    g=gg->left;
                
                }
                else if(g->parent!=NULL && g==g->parent->right)
                {
                    struct Node *gg=g->parent;
                    gg->right=rightRotate(g);
                    g=gg->right;
                }
                else if(g->parent==NULL){
                    n=rightRotate(g);
                    g=n;
                }
                g->color=0;
                g->right->color=1;
                g->data=subTreeMax(g->left);
                
            }
            else if(y==q->right && q==g->right)     /////right right case
            {
                if(g->parent!=NULL && g==g->parent->left)
                {
                    struct Node *gg=g->parent;
                    gg->left=leftRotate(g);
                    g=gg->left;
                
                }
                else if(g->parent!=NULL && g==g->parent->right)
                {
                    struct Node *gg=g->parent;
                    gg->right=leftRotate(g);
                    g=gg->right;
                }
                else if(g->parent==NULL){
                    n=leftRotate(g);
                    g=n;
                }
                g->color=0;
                g->left->color=1;
                long long int k1=subTreeMax(g->right);
                updateData(g, k1);

            }
            else if(y==q->left && q==g->right)      /////////right left case
            {
                g->right=rightRotate(q);
                if(g->parent!=NULL && g==g->parent->left)
                {
                    struct Node *gg=g->parent;
                    gg->left=leftRotate(g);
                    g=gg->left;
                
                }
                else if(g->parent!=NULL && g==g->parent->right)
                {
                    struct Node *gg=g->parent;
                    gg->right=leftRotate(g);
                    g=gg->right;
                }
                else if(g->parent==NULL){
                    n=leftRotate(g);
                    g=n;
                }
                g->color=0;
                g->right->color=1;
                g->left->color=1;
                g->right->data=subTreeMax(g->right->left);
            }            
            else if(y==q->right && q==g->left)          ///////left right case
            {
            
                g->left=leftRotate(q);
                if(g->parent!=NULL && g==g->parent->left)
                {
                    struct Node *gg=g->parent;
                    gg->left=rightRotate(g);
                    g=gg->left;
                
                }
                else if(g->parent!=NULL && g==g->parent->right)
                {
                    struct Node *gg=g->parent;
                    gg->right=rightRotate(g);
                    g=gg->right;
                }
                else if(g->parent==NULL){
                    n=rightRotate(g);
                    g=n;
                }
                g->color=0;
                g->right->color=1;
                g->left->color=1;
                g->right->data=subTreeMax(g->right->left);
            }
        updateHeight(g);
        return n;  
        }
    }
}
struct Node* FixDeletion(struct Node *u, struct Node *n)
{
    if(u->parent==NULL)
    {
        u->color=0;
        return u;
    }
    struct Node *p=u->parent;                       /////////p is u's pArent and s is u's sibling
    struct Node *s=(u==p->left)?p->right:p->left;
    if(s->color==0)                                 /////////////sibling s is black
    {
        if(s->right->color==1 || s->left->color==1)     ////////////// atleast one of siblings child is red
        {
            if(s==s->parent->left && s->left->color==1)     //////left left case
            {
                
                if(p->parent!=NULL && p==p->parent->left)
                {
                    struct Node *gg=p->parent;
                    gg->left=rightRotate(p);
                    s=gg->left;
                
                }
                else if(p->parent!=NULL && p==p->parent->right) 
                {
                    struct Node *gg=p->parent;
                    gg->right=rightRotate(p);
                    s=gg->right;
                }
                else if(p->parent==NULL){
                    n=rightRotate(p);
                    s=n;
                }
                struct Node *r=s->left;
                s->color=p->color;
                s->right->color=0;
                r->color=0;
                u->color=0;
                updateHeight(u);
                updateData(u, u->data);
                return n;
            }
            else if(s==s->parent->left && s->right->color==1)       /////////left right case
            {
                struct Node *r=s->right;
                p->left=leftRotate(s);
                if(p->parent!=NULL && p==p->parent->left)
                {
                    struct Node *gg=p->parent;
                    gg->left=rightRotate(p);
                    r=gg->left;
                
                }
                else if(p->parent!=NULL && p==p->parent->right)
                {
                    struct Node *gg=p->parent;
                    gg->right=rightRotate(p);
                    r=gg->right;
                }
                else if(p->parent==NULL){
                    n=rightRotate(p);
                    r=n;
                }
                r->color=p->color;
                r->left->color=0;
                r->right->color=0;
                u->color=0;
                updateHeight(u);
                updateData(u, u->data);
                return n;
            }
            else if(s==s->parent->right && s->right->color==1)      //////////right right
            {
                
                if(p->parent!=NULL && p==p->parent->left)
                {
                    struct Node *gg=p->parent;
                    gg->left=leftRotate(p);
                    s=gg->left;
                
                }
                else if(p->parent!=NULL && p==p->parent->right)
                {
                    struct Node *gg=p->parent;
                    gg->right=leftRotate(p);
                    s=gg->right;
                }
                else if(p->parent==NULL){
                    n=leftRotate(p);
                    s=n;
                }
                struct Node *r=s->right;
                s->color=p->color;
                s->left->color=0;
                r->color=0;
                u->color=0;
                updateHeight(u);
                updateData(u, u->data);
                return n;
            }
            else if(s==s->parent->right && s->left->color==1)          /////////right left
            {
                struct Node *r=s->left;
                p->right=rightRotate(s);
                if(p->parent!=NULL && p==p->parent->left)
                {
                    struct Node *gg=p->parent;
                    gg->left=leftRotate(p);
                    r=gg->left;
                
                }
                else if(p->parent!=NULL && p==p->parent->right)
                {
                    struct Node *gg=p->parent;
                    gg->right=leftRotate(p);
                    r=gg->right;
                }
                else if(p->parent==NULL){
                    n=leftRotate(p);
                    r=n;
                }
                r->color=p->color;
                r->left->color=0;
                r->right->color=0;
                u->color=0;
                updateHeight(u);
                updateData(u, u->data);
                return n;
            }
        }
        else                        /////////both children are black
        {
            s->color=1;
            if(s->parent->color==1)
            {
                p->color=0;
                u->color=0;
                updateHeight(u);
                updateData(u, u->data);
                return n;
            }
            else
            {
                p->color=2;
                u->color=0;
                n=FixDeletion(p, n);
                updateHeight(u);
                updateData(u, u->data);
                return n;
            }
        }
    }
    else                                     ///////////////sibling is red
    {
       if(s==s->parent->right)
       {
            if(p->parent!=NULL && p==p->parent->left)
            {
                struct Node *gg=p->parent;
                gg->left=leftRotate(p);
                s=gg->left;
            
            }
            else if(p->parent!=NULL && p==p->parent->right)
            {
                struct Node *gg=p->parent;
                gg->right=leftRotate(p);
                s=gg->right;
            }
            else if(p->parent==NULL){
                n=leftRotate(p);
                s=n;
            }
            s->color=0;
            s->left->color=1;
            n=FixDeletion(u,n);
            updateHeight(u);
            updateData(u, u->data);
            return n;
       }
       else
       {
            if(p->parent!=NULL && p==p->parent->left)
            {
                struct Node *gg=p->parent;
                gg->left=rightRotate(p);
                s=gg->left;
            
            }
            else if(p->parent!=NULL && p==p->parent->right)
            {
                struct Node *gg=p->parent;
                gg->right=rightRotate(p);
                s=gg->right;
            }
            else if(p->parent==NULL){
                n=rightRotate(p);
                s=n;
            }
            s->color=0;
            s->right->color=1;
            n=FixDeletion(u,n);
            updateHeight(u);
            updateData(u, u->data);
            return n;
       } 
    }
}

struct Node* insert(struct Node *n, long long int key)
{
    if(n==NULL)
    {
        struct Node *node1=new Node(key);
        return node1;
    }
    else if(n->data==key)
    {
       // cout<<"\nfound already\n";
        return n;
    }
    else if(n->left==NULL && n->right==NULL)
    {
        struct Node *r=new Node();
        struct Node *leaf=new Node(key);
        n->parent=r;
        leaf->parent=r;
        if(n->data<key)
        {
            r->data=n->data;
            r->left=n;
            r->right=leaf;
        }
        else
        {
            r->data=leaf->data;
            r->left=leaf;
            r->right=n;
        }
        r->ht=max(height(r->left),height(r->right))+1;
        return r;
    }
   else
   {
        struct Node *p=find(n,key);
        if(key==p->data)
        {
           // cout<<"\nData already found\n";
            return n;
        }
        struct Node *y=new Node();          /////////// y is new node's parent
        struct Node *leaf=new Node(key);
        leaf->parent=y;
        y->color=1;
        y->parent=p->parent;
        y->ht=2;
        p->parent=y;
        if(p->data<key)
        {
            y->left=p;
            y->right=leaf;
        }
        else
        {
            y->left=leaf;
            y->right=p;
        }
        y->data=y->left->data;
        struct Node *q=y->parent;           ////////////q is y's parent
        if(p==q->left)
            q->left=y;
        else 
            q->right=y;
        ///////////////if y's parent black no problem
        if(q->color==0)
        {
            updateHeight(y);
            if(y==q->left && leaf==y->right)
                q->data=leaf->data;
            else if(y==q->right && leaf==y->right)
                updateData(y, leaf->data);
            return n;

        }
        struct Node *m=(q==q->parent->right)?q->parent->left:q->parent->right;  ////////////// m is y's uncle
        ////////////if y's parent as well as uncle red
        if(m->color==1)
        {
            n=fixRedParent(y,n);
            updateHeight(y);
            if(y==y->parent->left && leaf==y->right)
                y->parent->data=leaf->data;
            else if(y==y->parent->right && leaf==y->right)
                updateData(y, leaf->data);
            return n;
        }
        //////////if y's parent red but uncle black
        else
        {
            n=fixRedParent(y, n); 
            
            return n;    
        }
   }
}
//****************************DELETION***********************************************
struct Node* deletion(struct Node *n, long long int key)
{
     if(n==NULL)
    {
       // cout<<"\nNo data found\n";
        return n;
    }
    else if(n->left==NULL)
    {
        if(n->data==key)
        {   
            delete n;
            return NULL;
        }
        else
        {
           // cout<<"\ndata not found\n";
            return n;
        }
    }
    else                                
    {
        struct Node *r=find(n, key);
        if(r->data!=key)
        {
            //cout<<"\ndata not found\n";
            return n; 
        }
        struct Node *q=r->parent;
        struct Node *s=(r==q->left)?q->right:q->left;
        if(q->color==1)                                ////////////if r has red parent
        {
            s->parent=q->parent;
            if(q==q->parent->left)
                q->parent->left=s;
            else 
                q->parent->right=s;
            delete(r);
            delete(q);
            updateHeight(s);
            updateData(s,s->data);
            return n;
        }
        else                                        ///////////if r has black parent
        {
            if(q->parent==NULL)
            {
                s->parent=NULL;
                delete(r);
                delete(q);
                return s;
            }
            else                            
            {
                s->parent=q->parent;
                if(s->color==1)
                {
                    if(q==q->parent->left)
                        q->parent->left=s;
                    else 
                        q->parent->right=s;
                    s->color=0;
                    delete(r);
                    delete(q);
                    updateHeight(s);
                    updateData(s,s->data);
                    return n;
                }
                s->color=2;
                if(q==q->parent->left)
                    q->parent->left=s;
                else 
                    q->parent->right=s;
                delete(r);
                delete(q);
                n=FixDeletion(s,n);
            }
        }

        return n;
    }

} 
int main(int argc, char const *argv[])
{
    struct Node *root=NULL;   
    //struct Node *p=search(root, 234567);
    long long int k;
    //struct Node *p=search(root, 123456);

    char x,c;
    
    //freopen("input.txt", "r", stdin);

    while(scanf("%c", &x)!=-1){
        switch(x){
            case 'S':
            case 's':
            {
                scanf("%lld", &k);
               // depth=-1;
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
               // depth=-1;
                if((search(root, k)==false))
                {
                    root=insert(root, k);
                   // depth=-1;
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
               // depth=-1;
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
    /*root=insert(root, 50);
    root=insert(root, 200);
    root=insert(root, 12);
    root=insert(root, 65);
    root=insert(root, 1);
    root=insert(root, 25);
    root=insert(root, -2);
    root=insert(root, 55);
    root=insert(root, 60);
    root=insert(root, -4);
    root=insert(root, -3);
    root=insert(root, 52);
    root=insert(root, 53);
    root=insert(root, -1);
    root=insert(root, 51);
    root=insert(root, 0);
    root=deletion(root, 52);
    root=deletion(root, -4);
    root=deletion(root, 50);
    root=deletion(root, -1);
    root=insert(root, 62);
    root=deletion(root, 60);
     root=insert(root, 70);

    root=deletion(root, 62);
    root=insert(root, 61);
    root=deletion(root, 70);
    root=deletion(root, 61);
    root=deletion(root, 12);
    root=deletion(root, 1);
    root=deletion(root, -3);
    root=deletion(root, -2);
    printLevelOrder(root);*/
    return 0;
}