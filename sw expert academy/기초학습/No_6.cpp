// 기초 Single Linked List 연습(3. 연결리스트 관련 문제)
#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
  nodeCnt = 0;
  head = getNode(0);
}

void addNode2Head(int data) 
{
  Node* new_node = getNode(data);

  new_node->next = head->next;
  head->next = new_node;
}

void addNode2Tail(int data) 
{
  Node* new_node = getNode(data);
  Node* cur = head;

  while(cur->next != nullptr)
    cur = cur->next;
    
  cur->next = new_node;
}

void addNode2Num(int data, int num) 
{
  Node* new_node = getNode(data);
  Node* cur = head;

  for(int i=1; (i < num) && (cur->next != nullptr); i++)
    cur = cur->next;
  
  new_node->next = cur->next;
  cur->next = new_node;
}

void removeNode(int data) 
{
  Node* cur = head;

  while((cur->next != nullptr) && (cur->next->data != data))
    cur = cur->next;

  if(cur->next != nullptr)
    cur->next = cur->next->next;
}

int getList(int output[MAX_NODE]) 
{
  int count = 0;
  Node* cur = head->next;

  while(cur != nullptr){
    output[count++] = cur->data;
    cur = cur->next;
  }

  return count;
}

/*
진짜 개노.답 문제
addNode2Num()이랑 removeNode() 함수에서 예외처리 안 해줘서 계속 segmentation fault 났음.
즉 addNode2Num의 인자 num으로 리스트의 전체 원소 개수보다 큰 숫자가 들어간다든가, removeNode의 인자 data로 리스트에 존재하지 않는 값이 
들어간다든가 할 때와 같은 경우를 예외처리(49행의 for문의 두번째 조건, 60행 while문의 첫번째 조건, 63행 if문 조건 확인하는 부분)를
해주라는 건데, 아니 그럴 거면 문제에 명시를 하든가 시1발 이런 예외적인 입력에는 이런 동작을 하도록 하라 이렇게 써놔야 그거에 맞춰서 코드를
짜지 그걸 안 해주면 그냥 아~ 아다리 맞는 입력만 주어지는구나 하고 예외처리를 안 하고 그냥 짜게 되지 않을까 문제 제작자야????????????????
*/