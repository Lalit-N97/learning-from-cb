#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<stack>
using namespace std;

class Node{
public:
	int val;
	Node* next;

	Node(int d){
		val = d;
		next = NULL;
	}

};

class Queue{
private:
	int* arr;
	int front;
	int rear;
	int curSize;
	int maxSize;
public:
	Queue(int n = 5){
		maxSize = n;
		arr = new int[maxSize];
		curSize = 0;
		front = 0;
		rear = maxSize - 1;
	}

	bool full(){
		return curSize == maxSize;
	}

	bool empty(){
		return curSize == 0;
	}

	void push(int d){
		if(!full()){
			rear = (rear + 1) % maxSize;
			arr[rear] = d;
			curSize++;
		}
		else {
			cout << "Queue is FULL\n";
		}
	}

	void pop(){
		if(!empty()){
			front = (front + 1) % maxSize;
			curSize--;
		}
		else {
			cout << "Queue is EMPTY\n";
		}
	}

	int top(){
		if(!empty()) return arr[front];
		else cout << "Queue is EMPTY\n";
	}

	void print(){
		printf("front - %d, rear - %d, curSize - %d, maxSize - %d\n", front, rear, curSize, maxSize);
	}

	~Queue(){
		if(arr != NULL){
			delete arr;
			arr = NULL;
		}
	}

};

// implement Queue using STL list
class QueueListSTL{
private:
	int curSize;
	list<int> l;
public:
	QueueListSTL(){
		curSize = 0;
	}

	bool empty(){
		return curSize == 0;
	}

	void push(int d){
		l.push_back(d);
		curSize++;
	}

	void pop(){
		if(!empty()){
			l.pop_front();
			curSize--;
		}
	}

	int front(){
		return l.front();
	}
};

// implemented Queue using linkedList head and tail pointers.
// push happens at tail
// pop happens at head
class QueueLinkedList{
private:
	Node* head;
	Node* tail;
public:
	QueueLinkedList(){
		head = NULL;
		tail = NULL;
	}

	bool empty(){
		return head == NULL;
	}

	void push(int d){
		Node* node = new Node(d);
		if(empty()) {
			head = node;
			tail = node;
		}
		else{
			tail->next = node;
			tail = node;
		}
	}

	void pop(){
		if(!empty()){
			Node* temp = head->next;
			delete head;
			head = temp;
			if(head == NULL) tail = NULL;
		}
		else{
			cout << "Queue is EMPTY!\n";
		}
	}

	int front(){
		if(!empty()) return head->val;
	}

};

// first non repeating character in a running stream
// Time - O(N) and Space - O(N)
void FNRC(){
	queue<char> q;
	int freq[257] = {0};
	char ch;
	cin >> ch;
	while(ch != '.'){
		q.push(ch);
		freq[ch - 'a']++;
		while(!q.empty()){
			if(freq[q.front() - 'a'] == 1) {
				cout << q.front() << "\n";
				break;
			}
			else q.pop();
		}

		if(q.empty()) cout << -1 << "\n";
		cin >> ch;
	}
}

template<typename T>
class StackUsingQueues{ // Implement stack using 2 queues
private:
	queue<T> q1;
	queue<T> q2;
public:
	void push(T d){
		q1.push(d);
	}

	void pop(){ // Time - O(N)
	    // remove the last added element in q1
	    // move n-1 elements from q1 to q2
	    // pop the front element of q1 and swap q1 and q2
	    if(q1.empty()) return;
	    while(q1.size() > 1){
	    	q2.push(q1.front());
	    	q1.pop();
	    }
	    // remove the last element
	    q1.pop();
	    // swap q1 and q2
	    swap(q1, q2);
	}

	T top(){ // Time - O(N)
		while(q1.size() > 1){
			q2.push(q1.front());
			q1.pop();
		}
		T ele = q1.front();
		q1.pop();
		q2.push(ele);
		swap(q1, q2);
		return ele;
	}

	int size(){
		return q1.size() + q2.size();
	}

	bool empty(){
		return size() == 0;
	}

};

template<typename T>
class QueueUsingStacks{ // implement queue using two stacks
private:
	stack<T> s1;
	stack<T> s2;
public:

	void push(T data){ // Time - O(1)
		s1.push(data);
	}

	void pop(){ // Time - O(N)
		// transfer all elements from s1 to s2
		while(!s1.empty()){
			s2.push(s1.top());
			s1.pop();
		}
		// remove or pop element from s2
		s2.pop();
		// shift all remaining elements from s2 back to s1;
		while(!s2.empty()){
			s1.push(s2.top());
			s2.pop();
		}
	}

	T front(){ // Time - O(N)
		// transfer all elements from s1 to s2
		while(!s1.empty()){
			s2.push(s1.top());
			s1.pop();
		}
		// get the top element now
		T ele = s2.top();
		// shift all elements from s2 back to s1;
		while(!s2.empty()){
			s1.push(s2.top());
			s2.pop();
		}
		return ele;
	}

	int size(){
		return s1.size() + s2.size();
	}

	bool empty(){
		return size() == 0;
	}

};

int main(){

	// Queue q;

	// for(int i = 1; i <= 5; i++){
	// 	q.push(i);
	// }

	// q.print();
	// q.pop();
	// q.print();
	// cout << q.top() << "\n";
	// q.pop();
	// q.print();
	// q.push(6);
	// q.print();

	// while(!q.empty()){
	// 	cout << q.top() << "\n";
	// 	q.pop();
	// }

	// QueueListSTL q;

	// for(int i = 1; i <= 5; i++){
	// 	q.push(i);
	// }

	// q.pop();
	// cout << "front -> " <<  q.front() << "\n";
	// q.pop();
	// q.push(6);

	// while(!q.empty()){
	// 	cout << q.front() << "\n";
	// 	q.pop();
	// }

	QueueLinkedList q;

	for(int i = 1; i <= 5; i++){
		q.push(i);
	}

	q.pop();
	cout << "front -> " <<  q.front() << "\n";
	q.pop();
	q.push(6);

	// for(int i = 0; i < 5; i++) q.pop();

	while(!q.empty()){
		cout << q.front() << "\n";
		q.pop();
	}

	// FNRC();



	return 0;
}