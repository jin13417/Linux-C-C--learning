#define N 16

 typedef int  datatype;

 typedef struct node
{
	datatype data;
	struct node *next;
}linknode,*linklist;

typedef struct
{
	linklist front,rear;
}linkqueue;

linkqueue *Createlinkqueue();
int Emptylinkqueue(linkqueue *lq);
void Clearlinkqueue(linkqueue *lq);
void Enlinkqueue(linkqueue *lq,datatype x);
datatype Delinkqueue(linkqueue *lq);

typedef struct stack1{
	datatype data[N];
	int top;
}seqstack;

seqstack *Create();
int Emptyseqstack(seqstack *s);
void pushseqstack(seqstack *s,datatype x);
datatype popstack(seqstack *s);
datatype gettopseqstack(seqstack *s);
void Clearseqstack(seqstack *s);




