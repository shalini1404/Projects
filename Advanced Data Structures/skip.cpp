#include <bits/stdc++.h>
using namespace std;
int depth=0;
struct Node
{
	Node *left;
	Node *right;
	Node *top;
	Node *bottom;
	long long int data;
	Node(){
        left=NULL;
        right=NULL;
        top=NULL;
        bottom=NULL;
	}
	Node(long long int k){
        left=NULL;
        right=NULL;
        top=NULL;
        bottom=NULL;
		data=k;
	}
	/* data */
};

struct List{
	Node *header = NULL;

};
void print(struct List *s){
	struct Node *temp=s->header;
	struct Node *temp2=s->header;
	while(temp!=NULL){
		temp2=temp;
		while(temp2!=NULL){
			cout<<temp2->data<<"\t";
			temp2=temp2->right;
		}
		temp=temp->bottom;
		cout<<"\n";
	}
}

struct Node* search(struct List *s, long long int key){
	struct Node *p=s->header;
	depth=0;
	while(p->bottom!=NULL)
	{
		if(p->data!=key)
			depth++;
		p=p->bottom;
		while(((p->right)->data)<=key){
			depth++;
			p=p->right;
		}
		
	}
	//cout<<p->data;
	return p;

}
struct Node* InsertAtPosition(struct Node *p, struct Node *q, long long int key)
{
	//cout<<x->data<<"\n";
	//cout<<p->data<<"\n";
	//cout<<p->right->data<<"\n";
	struct Node *x=new Node(key);
	//cout<<x->data<<"\n";
	x->right=p->right;
	p->right->left = x;
	p->right=x;
	x->left=p;
	if(q!=NULL){
		//cout<<q->data<<"\n";
		q->top=x;
		x->bottom=q;
		q=q->top;
	}
	else q=x;
	return q;
}
struct List* insert(struct List *s, long long int key)
{
	struct Node *p=search(s, key);
	//cout<<p->data<<"\n";
	if(p->data==key){
		//cout<<"\nfa";
		return s;
	}
	//struct Node *x=new Node(key);
	struct Node *q=new Node();
	q=InsertAtPosition(p,NULL,key);
	if(p==s->header){
        struct Node *left_s=new Node(LLONG_MIN);
        struct Node *right_s=new Node(LLONG_MAX);
        left_s->right=right_s;
        left_s->bottom=p;
        right_s->left=left_s;
       	right_s->bottom=p->right->right;
        p->top=left_s;
        p->right->right->top=right_s;
        s->header=left_s;
        return s;
	}
	//print(s);
	int ra = (rand())%2;
	//cout<<ra<<"\n";
	while(ra==1){
		//struct Node *x1=new Node(key);
		//cout<<ra<<"\n";
		//cout<<"aaaaaaa";
		//cout<<"\naaaaa";
		while(p->top==NULL)
		{
			//cout<<"aaaaaaa";
            p =p->left;
        }
        //cout<<"\naaaaaaa";
		p=p->top;
		//print(s);
		q=InsertAtPosition(p,q,key);
		//print(s);
		if(p==s->header)
        {
            struct Node *left_st=new Node(LLONG_MIN);
            struct Node *right_st=new Node(LLONG_MAX);
            left_st->right=right_st;
            left_st->bottom=p;
            right_st->left=left_st;
            right_st->bottom=p->right->right;
            p->top=left_st;
            p->right->right->top=right_st;
            s->header=left_st;
            break;
        }
        else
            ra = rand()%2;
	}
	return s;

}
/*struct List* delete(struct List *s, long long int key)
{
	struct Node *p=search(s, key);
	struct Node *temp;
	if((p->data)!=key){
		cout<<"No such data in the list";
		return s;
	}
	else{
		while(p!=NULL){
			(p->left)->right=p->right;
			(p->right)->left=p->left;
			temp=p;
			p=p->top;
			free(temp);
		}
		return s;
	}
}*/
struct  List* deletion(struct List *s, long long int key)
{
	struct Node *p=search(s, key);
	struct Node *temp=new Node();
	if((p->data)!=key){
		//cout<<"No such data in the list";
		return s;
	}
	else{
		while(p!=NULL){
			(p->left)->right=p->right;
			(p->right)->left=p->left;
			temp=p;
			p=p->top;
			delete(temp);
	/* data*/
		}
		struct Node *temp2=s->header->bottom;
		while(temp2!=NULL)
		{
			if(temp2->right->right==NULL)
			{
				s->header->bottom=temp2->bottom;
				s->header->right->bottom=temp2->right->bottom;
				if(temp2->bottom!=NULL)
				{
					temp2->bottom->top=s->header;
					temp2->right->bottom->top=s->header->right;
				}

			}
			else
				break;
			temp2=s->header->bottom;
		}

		return s;
	}
}

int main()
{
	struct List *s=new List;
	struct Node *left_sent=new Node(LLONG_MIN);
	struct Node *right_sent=new Node(LLONG_MAX);

	struct Node *m = new Node();
	left_sent->right=right_sent;

	right_sent->left=left_sent;
	s->header=left_sent;
	long long int k;
    //struct Node *p=search(root, 123456);

    char x,c;
    
    while(scanf("%c", &x)!=-1){
        switch(x){
            case 'S':
            case 's':
            {
                scanf("%lld", &k);
                //depth=-1;
                m=search(s, k);
                if(m->data==k){
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
                //depth=-1;
                m=search(s, k);
                if(m->data!=k)
                {
                    s=insert(s, k);
                    //depth=-1;
                    m=search(s, k);
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
                m=search(s, k);
                if(m->data==k)
                {
                    cout<<"d "<<depth<<endl;
                    s=deletion(s,k);
                }
                else
                    cout<<"nf\n";
                
                break;
            }
            case 'P':
            case 'p':
            {
               print(s);;
                break;
            }
            default:exit(0);
        }
        scanf("%c", &c);
    }
	/*long long int key=123456;
	s=insert(s,key);
	s=insert(s,1345);
	s=insert(s,13567);

	s=insert(s,156786745);
	s=insert(s,1346785);
	s=insert(s,185);
	print(s);
	m=search(s,1346785);

	//cout<<m->data;
   // s=insert(s,key);
    s=deletion(s,1346785);
    print(s);
    s=deletion(s,156786745);
    print(s);
    m=search(s,key);
	//cout<<m->data;
	/*insert(s, );*/
	return 0;
	/* code */

}
