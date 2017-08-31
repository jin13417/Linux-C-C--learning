
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
