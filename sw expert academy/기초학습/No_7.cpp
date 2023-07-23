// 기초 Double Linked List 연습(3. 연결리스트 관련 문제)
#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
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
  Node *new_node = getNode(data);

  if(head->next == nullptr){
    new_node->prev = head;
    head->next = new_node;
  }
  else{
    new_node->next = head->next;
    new_node->prev = head;
    head->next->prev = new_node;
    head->next = new_node;
  }
}

void addNode2Tail(int data) 
{
  Node *new_node = getNode(data);
  Node *cur = head;

  while(cur->next != nullptr)
    cur = cur->next;
  
  cur->next = new_node;
  new_node->prev = cur;
}

void addNode2Num(int data, int num) 
{
  Node *new_node = getNode(data);
  Node *cur = head;

  for(int i=1; (i < num) && (cur->next != nullptr); i++)
    cur = cur->next;
    
  if(cur->next == nullptr){
    cur->next = new_node;
    new_node->prev = cur;
  }
  else{
    new_node->next = cur->next;
    new_node->prev = cur;
    cur->next->prev = new_node;
    cur->next = new_node;
  }
}

int findNode(int data) 
{
  Node *cur = head;
  int count = 0;

  while(true){
    if(cur->next == nullptr) return 0;

    cur = cur->next;
    count++;

    if(cur->data == data) return count;
  }
}

void removeNode(int data) 
{
  Node *cur = head->next;

  while((cur != nullptr) && (cur->data != data))
    cur = cur->next;
  
  if(cur != nullptr){
    cur->prev->next = cur->next;

    if(cur->next != nullptr)
      cur->next->prev = cur->prev;
  }
}

int getList(int output[MAX_NODE]) 
{
  Node *cur = head;
  int count = 0;

  while(cur->next != nullptr){
    cur = cur->next;
    output[count++] = cur->data;
  }

  return count;
}

int getReversedList(int output[MAX_NODE]) 
{
  Node *cur = head;
  int count = 0;

  while(cur->next != nullptr)
    cur = cur->next;
  
  while(cur->prev != nullptr){
    output[count++] = cur->data;
    cur = cur->prev;
  }

  return count;
}