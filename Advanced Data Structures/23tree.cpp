#include <bits/stdc++.h>
using namespace std;
struct Node
{
	Node *left;
    Node *middle;
	Node *right;
    Node *parent;
	long long int Ldata;
	long long int Mdata;
	Node(){
        parent=NULL;
        left=NULL;
        right=NULL;
        middle=NULL;
	}
	Node(long long int k){
        parent=NULL;
        left=NULL;
        right=NULL;
        middle=NULL;
        Ldata=k;
        Mdata=0;
	}
};
int depth=0;
void PreOrder(struct Node *root)
{
    if (root == NULL)
        return;
    if(root->left!=NULL)
        cout<<"internal"<<root->Ldata<<" "<<root->Mdata<<"\n";
    else
    {
        cout<<"leaf"<<root->Ldata<<"\n";
        return;
    }
    PreOrder(root->left);
    PreOrder(root->middle);
    if(root->right!=NULL)
        PreOrder(root->right);
}
struct Node* search(struct Node *n, long long int key)
{
    depth++;
    if(n==NULL)
    {   
        //cout<<"fgh";
        //cout<<"\nNo data found\n";
        return n;
    }
    else if(n->left==NULL)
    {
        //if(key==n->Ldata)
          //  cout<<"\nData found nnn\n";
        //else
          //  cout<<"\nNo data found\n";
        return n;
    }
    //else if(key==n->Ldata||key==n->Mdata)
      //  return n;
    else if (n->Ldata>=key)
        return search(n->left, key);
    else if((n->Ldata<key && n->Mdata>=key)||(n->right==NULL))
        return search(n->middle, key);
    else
        return search(n->right, key);
}
struct Node* searchForInsert(struct Node *n, long long int key)
{

    if(n->left->left==NULL)
    {
       // cout<<"sdfghj";
        return n;
    }
    else if (n->Ldata>=key)
        return searchForInsert(n->left, key);
    else if((n->Ldata<key && n->Mdata>=key)||(n->right==NULL))
        return searchForInsert(n->middle, key);
    else
        return searchForInsert(n->right, key);
}
void updateLM(struct Node *f, long long int key)
{
    struct Node *temp=new Node();
    while(f->parent!=NULL)
    {   
        temp=f;
        f=f->parent;
        if(temp==f->left)
        {
            f->Ldata=key;
            break;
        }
        else if(temp==f->middle)
        {
            f->Mdata=key;
            if(f->right!=NULL)
            {
                break;
            }

        }

    }
}
long long int leftSubMax(struct Node *n)
{   //cout<<"7\n";
    n=n->left;
    if(n->left==NULL)
    {   //cout<<"8\n";
        return n->Ldata;
    }
    while(n->left->left!=NULL)
    {   
        if(n->right==NULL)
            n=n->middle;
        else
            n=n->right;
    }
    if(n->right==NULL)
        return n->middle->Ldata;
    else
        return n->right->Ldata;
}
long long int MidSubMax(struct Node *n)
{   //cout<<"9\n";
    n=n->middle;
    if(n->left==NULL)
    {
        return n->Ldata;
    }
    while(n->left->left!=NULL)
    {
        if(n->right==NULL)
            n=n->middle;
        else
            n=n->right;
    }
    if(n->right==NULL)
        return n->middle->Ldata;
    else
        return n->right->Ldata;
}
long long int rightSubMax(struct Node *n)
{
    n=n->right;
    if(n->left==NULL)
    {
        return n->Ldata;
    }
    while(n->left->left!=NULL)
    {
        if(n->right==NULL)
            n=n->middle;
        else
            n=n->right;
    }
    if(n->right==NULL)
        return n->middle->Ldata;
    else
        return n->right->Ldata;
}
struct Node* addson(struct Node *v, struct Node *fchild)
{   //cout<<"5\n";
    struct Node *p=new Node();
    p->left=v->right;
    p->middle=fchild;
    v->right->parent=p;
    fchild->parent=p;
    v->right=NULL;
    if(p->left->left==NULL)
    {
        p->Ldata=p->left->Ldata;
        p->Mdata=p->middle->Ldata;
    }
    else
    {
        v->Ldata=leftSubMax(v);
        v->Mdata=MidSubMax(v);
        p->Ldata=leftSubMax(p);
        p->Mdata=MidSubMax(p);
    }
    if(v->parent==NULL)             //////////////////////if v was root node
    {   //cout<<"6\n";
        struct Node *r=new Node();
        r->left=v;
        r->middle=p;
        v->parent=r;
        p->parent=r;
        r->Ldata=leftSubMax(r);
        r->Mdata=MidSubMax(r);
        return r;
    }
    else
    {
        if(v->parent->right==NULL)
        {
            if(v==v->parent->left)
            {
                v->parent->right=v->parent->middle;
                v->parent->middle=p;
                p->parent=v->parent;
                v->parent->Ldata=leftSubMax(v->parent);
                v->parent->Mdata=MidSubMax(v->parent);
            }
            else if(v==v->parent->middle)
            {
                v->parent->right=p;
                p->parent=v->parent;
                v->parent->Mdata=MidSubMax(v->parent);
                    /* code */
            }
            long long int k=rightSubMax(v->parent);
            updateLM(v->parent,k);
            return v->parent;
        }
        else
        {
           struct Node *fc=new Node();
           if(v==v->parent->left)
            {
                fc=v->parent->right;
                v->parent->right=v->parent->middle;
                v->parent->middle=p;
                p->parent=v->parent;
                v->parent->Mdata=MidSubMax(v->parent);
            } 
            else if(v==v->parent->middle)
            {
                fc=v->parent->right;
                v->parent->right=p;
                p->parent=v->parent;
            }
            else
            {
                fc=p;
               // p->parent=v->parent;
            }
            return addson(v->parent, fc);
        }
    }
}
struct Node* insert(struct Node *n, long long int key)
{   //cout<<"1\n";
    if(n==NULL)
    {   //cout<<"sdfghj";
        struct Node *node1=new Node(key);
        return node1;
    }

    else if(n->left==NULL)      ///////////////////////////////////if n is the only node in tree
    {   //cout<<"sdf";
        if(n->Ldata==key)
        {
            //cout<<"\nfounddd\n";
            return n;
        }
        else
        {
            struct Node *root2=new Node();
            struct Node *leaf=new Node(key);
            if(key<n->Ldata)
            {
                root2->left=leaf;
                root2->middle=n;
                root2->Ldata=key;
                root2->Mdata=n->Ldata;
                leaf->parent=root2;
                n->parent=root2;
                return root2;
            }
            else
            {
                root2->left=n;
                root2->middle=leaf;
                root2->Mdata=key;
                root2->Ldata=n->Ldata;
                leaf->parent=root2;
                n->parent=root2;
                return root2;
            }
        }
    }
    else
    {
        //cout<<"2";
        struct Node *f=searchForInsert(n,key);                   /////////////////f is the parent where node has to be inserted
        if((f->left->Ldata==key)||(f->middle->Ldata==key))             
        {
            //cout<<"\nfound already\n";
            return n;
        }
        else if(f->right!=NULL && f->right->Ldata==key)
        {
            //cout<<"\nfound already\n";
            return n;  
        }
        else
        {   //cout<<"3";
            struct Node *leaf=new Node(key);
            if(f->right==NULL)                          ///////////////////if f has only two children
            {
                if(f->Ldata>key)
                {
                    f->right=f->middle;
                    f->middle=f->left;
                    f->left=leaf;
                    leaf->parent=f;
                    f->Ldata=f->left->Ldata;
                    f->Mdata=f->middle->Ldata;
                }
                else if(f->Ldata<key && f->Mdata>key)
                {
                    f->right=f->middle;
                    f->middle=leaf;
                    leaf->parent=f;
                    f->Mdata=f->middle->Ldata;
                    /* code */
                }
                else
                {   
                    f->right=leaf;
                    leaf->parent=f;
                    updateLM(f,key);
                }
                return n;
            }
            else                                        ///////////////// if f has three children
            {   //cout<<"4";
                struct Node *fourthChild=new Node();
                if(key<f->Ldata)
                {
                    //cout<<"\n5";
                    fourthChild=f->right;
                    f->right=f->middle;
                    f->middle=f->left;
                    f->left=leaf;
                    leaf->parent=f;
                    f->Ldata=f->left->Ldata;
                    f->Mdata=f->middle->Ldata;
                }
                else if(f->Ldata<key && key<f->Mdata)
                {
                    fourthChild=f->right;
                    f->right=f->middle;
                    f->middle=leaf;
                    leaf->parent=f;
                    f->Mdata=f->middle->Ldata;
                }
                else if(f->Mdata<key && key<f->right->Ldata)
                {
                    fourthChild=f->right;
                    f->right=leaf;
                    leaf->parent=f;
                }
                else
                {
                    fourthChild=leaf;
                    leaf->parent=f;
                }
                n=addson(f,fourthChild);
                for( ; n->parent; n = n->parent);
                return n;
            }
        }
    }
    return n;    
}
struct Node* deletion(struct Node *n, long long int key)
{
    if(n==NULL)
    {
        cout<<"\nNo data found\n";
        return n;
    }
    else if(n->left==NULL)
    {
        if(n->Ldata==key)
        {   
            delete n;
            return NULL;
        }
        else
        {
            cout<<"\nNo data found\n";
            return n;
        }
    }
    else                                
    {
        struct Node *p=search(n,key);
        if(p->Ldata!=key)
        {
            cout<<"\ndata not found\n";
            return n;
        }
        if(p->parent->right!=NULL)
        {
            if(p==p->parent->left)
            {
                p->parent->left=p->parent->middle;
                p->parent->middle=p->parent->right;
                p->parent->right=NULL;
                p->parent->Ldata= leftSubMax(p->parent);
                p->parent->Mdata= MidSubMax(p->parent);
                delete(p);
                return n;
            }
            else if(p==p->parent->middle)
            {
                p->parent->middle=p->parent->right;
                p->parent->right=NULL;
                p->parent->Mdata= MidSubMax(p->parent);;
                delete(p);
                return n;
            }
            else
            {
                p->parent->right=NULL;
                updateLM(p->parent, p->parent->Mdata);
                delete(p);
                return n;
            }
        }
        else                            ///////////////////f has two children including p
        {
            if(p->parent->parent==NULL)
            {
                if(p==p->parent->left)
                {   
                    n=p->parent->middle;
                    n->parent=NULL;
                    delete(p->parent);
                    delete(p);
                    return n;
                }
                else
                {   
                    n=p->parent->left;
                    n->parent=NULL;
                    delete(p->parent);
                    delete(p);
                    return n;
                }
            }
            else
            {
                struct Node *f=p->parent;
                if(f==f->parent->left)
                {
                    struct Node *g=f->parent->middle; ////////////////////////g is brother of f
                    
                    if(g->right==NULL)                 /////////////////////////g has two children
                    {
                       //if(p==f->left)
                        struct Node *s=(p==f->left)?f->middle:f->left;
                        //else
                          //  struct Node *s=f->left;
                        g->right=g->middle;
                        g->middle=g->left;
                        g->left=s;
                        s->parent=g;
                        g->Ldata= leftSubMax(g);
                        g->Mdata= MidSubMax(g);
                        f->left=NULL;
                        f->middle=NULL;
                        
                        
                        
                        delete(p);
                        n=deletion(n, f->Ldata);
                        long long int k1=rightSubMax(g);
                        updateLM(g,k1);
                        if(g->parent!=NULL)
                        {
                            if(g->parent->middle->right!=NULL)
                                k1=rightSubMax(g->parent->middle);
                            else
                                k1=MidSubMax(g->parent->middle);
                            updateLM(g->parent->middle, k1);
                        }
                        return n;
                    }
                    else
                    {
                       //if(p==f->left)
                        struct Node *s=(p==f->left)?f->middle:f->left;
                       // else
                         //   struct Node *s=f->left;
                        f->left=s;
                        f->middle=g->left;
                        g->left->parent=f;
                        g->left=g->middle;
                        g->middle=g->right;
                        f->right=NULL;
                        g->right=NULL;
                        f->Ldata=leftSubMax(f);
                        f->Mdata=MidSubMax(f);
                        g->Ldata=leftSubMax(g);
                        g->Mdata=MidSubMax(g);
                        updateLM(f, f->Mdata);
                        updateLM(g, g->Mdata);
                        return n;
                    }
                }
                else
                {
                    //if(f==f->parent->middle)
                        struct Node *g=(f==f->parent->middle)?f->parent->left:f->parent->middle;
                    //else
                      //  struct Node *g=f->parent->middle;
                    if(g->right==NULL)                 /////////////////////////g has two children
                    {
                       //if(p=f->left)
                            struct Node *s=(p==f->left)?f->middle:f->left;
                        //else
                          //  struct Node *s=f->left;
                        g->right=s;
                        s->parent=g;
                        
                        
                        f->left=NULL;
                        f->middle=NULL;
                        delete(p);
                        n=deletion(n, f->Ldata);
                        long long int k1=rightSubMax(g);
                        updateLM(g,k1);
                        if(g->parent!=NULL)
                        {   
                            struct Node *gb=(g==g->parent->middle)?g->parent->left:g->parent->middle;
                            if(gb->right!=NULL)
                                k1=rightSubMax(gb);
                            else
                                k1=MidSubMax(gb);
                            updateLM(gb, k1);
                        }
                        return n;
                    }
                    else
                    {
                       //if(p=f->left)
                        struct Node *s=(p==f->left)?f->middle:f->left;
                       // else
                         //   struct Node *s=f->left;
                        f->left=g->right;
                        f->middle=s;
                        g->right->parent=f;
                        f->right=NULL;
                        g->right=NULL;
                        f->Ldata=leftSubMax(f);
                        f->Mdata=MidSubMax(f);
                        g->Ldata=leftSubMax(g);
                        g->Mdata=MidSubMax(g);
                        updateLM(f, f->Mdata);
                        updateLM(g, g->Mdata);
                        return n;
                    }
                }
            }
        }
    }
}
int main()
{
    struct Node *root=NULL;
    long long int k;
    struct Node *p=new Node();

    char x,c;
    
    while(scanf("%c", &x)!=-1){
        switch(x){
            case 'S':
            case 's':
            {
                scanf("%lld", &k);
                depth=-1;
                p=search(root, k);
                if(p==NULL || p->Ldata!=k){
                    cout<<"nf\n";   
                }
                else
                    cout<<"f "<<depth<<endl;
                break;
            }
            case 'I':
            case 'i':
            {
                scanf("%lld", &k);
                depth=-1;
                p=search(root, k);
                if(p==NULL || p->Ldata!=k)
                {
                    root=insert(root, k);
                    depth=-1;
                    p=search(root, k);
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
                p=search(root, k);
                if(p==NULL || p->Ldata!=k)
                {
                    cout<<"nf\n";
                    
                }
                else{
                    cout<<"d "<<depth<<endl;
                    root=deletion(root,k);
                }
                break;
            }
            case 'P':
            case 'p':
            {
                PreOrder(root);
                break;
            }
            default:exit(0);
        }
        scanf("%c", &c);
    }
    /*struct Node *p=search(root, 123456);
    root=insert(root, 25);
 //   PreOrder(root);
    //root=insert(root, 2);
    //root=insert(root, 1234);
    //p=search(root, 25);
    //p=search(root, 2);
    //root=insert(root, 234567);
    //root=insert(root, 1112);
    //p=search(root, 25);
    //root=insert(root, 25);
    root=insert(root, 72);
  //  PreOrder(root);
  //  p=search(root, 72);
    //root=insert(root, 72);
    root=insert(root, 51);
    //PreOrder(root);
//    p=search(root, 51);
//    p=search(root, 72);
//    p=search(root, 25);
    root=insert(root, 12);
    
    root=insert(root, 20);


   root=insert(root, 60);
   
    root=insert(root, 30);
   
    root=insert(root, 10000);
    
    root=insert(root, 35);
    
    root=insert(root, 40);
  
    root=insert(root, 15);
  
    root=insert(root, 13);
    root=insert(root, 33);
    root=insert(root, 18);
    root=insert(root, 38);
    root=insert(root, 28);
    root=insert(root, 1133);
    root=insert(root, 45);
    //root=insert(root, 33);
     
    root=deletion(root, 25);
    root=deletion(root, 20);
    root=deletion(root, 13);
    root=deletion(root, 33);
    root=deletion(root, 10000);
    root=deletion(root, 51);
    root=deletion(root, 60);
    root=deletion(root, 72);
    root=deletion(root, 45);

    //root=deletion(root, 72);
    //root=insert(root, 22);
    //root=deletion(root, 15);
    //root=deletion(root, 22);
    //p=search(root, 20);
    //cout<<p->parent->Ldata;
//    p=search(root, 51);
    PreOrder(root);*/
    return 0;
}
