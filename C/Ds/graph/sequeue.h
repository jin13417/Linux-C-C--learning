#define N 5

typedef int datatyde;
typedef struct {
	datatyde data[N];
	int front,rear;
 }sequeue;

sequeue *Createsequeue();
int Emptysequeue(sequeue *sq);
int Fullsequeue(sequeue *sq);
void Clearsequeue(sequeue *sq);
void Ensequeue(sequeue *sq,datatyde x);
datatyde Desequeue(sequeue *sq);

