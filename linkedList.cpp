#include <iostream>
using namespace std;

class Node{
public:
	int data;
	Node* next;

	Node(int d){
		this->data = d; // this statement can be rewritten as (*this).data = d;
		this->next = NULL; // every pointer can be deferenced and then using . operator to fetch the field's value on that deferenced object
	}
};

Node* buildLinkedList(int* arr, int n){
	Node* head = NULL;
	Node* prev = NULL;
	for(int i = 0; i < n; i++){
		Node* node = new Node(arr[i]);
		if(i == 0){
			head = node;
			prev = node;
		}
		else{
			prev->next = node;
			prev = node;
		}
	}
	return head;
}

int length(Node* head){
	int len = 0;
	while(head != NULL){
		head = head->next;
		len++;
	}
	return len;
}

void printLinkedList(Node* head){
	while(head != NULL){
		cout << head->data << "->";
		head = head->next;
	}
	cout << "\n";
}

// INSERTION :
void insertAtHead(Node* &head, int d){
	Node* node = new Node(d);
	if(head == NULL){
		head = node;
		return;
	}
	node->next = head;
	head = node;
	return;
}

void insertAtTail(Node* &head, int d){
	Node* node = new Node(d);
	if(head == NULL){
		head = node;
		return;
	}
	Node* tail = head;
	while(tail->next != NULL){
		tail = tail->next;
	}
	tail->next = node;
	return;
}

void insertAtMiddle(Node* &head, int d, int pos){
	if(pos <= 1){
		insertAtHead(head, d);
		return;
	}
	else if(pos > length(head)){
		insertAtTail(head, d);
		return;
	}
	else{
		Node* node = new Node(d);
		pos -= 2;
		Node* cur = head;
		while(pos--){
			cur = cur->next;
		}
		node->next = cur->next;
		cur->next = node;
	}

}

// DELETION :
void deleteHead(Node* &head){
	if(head == NULL) return;
	Node* temp = head->next;
	delete head;
	head = temp;
	return;
}

void deleteTail(Node* head){
	if(head == NULL) return;
	Node* prev = NULL;
	Node* tail = head;
	while(tail->next != NULL){
		prev = tail;
		tail = tail->next;
	}
	prev->next = NULL;
	delete tail;
	return;
}

void deleteMiddle(Node* &head, int pos){
	if(pos <= 1){
		deleteHead(head);
		return;
	}
	if(pos >= length(head)){
		deleteTail(head);
		return;
	}
	if(head == NULL) return;
	pos = pos - 1;
	Node* cur = head;
	Node* prev = NULL;
	while(pos--){
		prev = cur;
		cur = cur->next;
	}
	prev->next = cur->next;
	delete cur;
	return;
}

void reverseLinkedList(Node* &head){
	if(head == NULL || head->next == NULL) return;
	Node* prev = NULL;
	Node* cur = head;
	while(cur != NULL){
		Node* after = cur->next;
		cur->next = prev;
		prev = cur;
		cur = after;
	}
	head = prev;
}



int main(){
	int n = 5;
	int *arr = new int[n]{5, 4, 3, 2, 1};
	Node* head = buildLinkedList(arr, n);
	printLinkedList(head);
	reverseLinkedList(head);
	printLinkedList(head);
	insertAtMiddle(head, 100, 5);
	// deleteHead(head);
	// deleteTail(head);
	// deleteMiddle(head, 10);
	printLinkedList(head);
	return 0;
}