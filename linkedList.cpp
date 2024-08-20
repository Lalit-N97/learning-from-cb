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

class ListNode{
public:
	int val;
	ListNode* next;

	ListNode(int d){
		this->val = d; 
		this->next = NULL; 
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

// -------INSERTION --------:
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

// ---------DELETION------------ :
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

//  -----------SEARCH----------------
int search(Node* head, int key){
	while(head != NULL){
		if(head->data == key){
			return true;
		}
		head = head->next;
	}
	return false;
}

int searchRec(Node* head, int key){
	if(head == NULL) return false;
	if(head->data == key) return true;
	return searchRec(head->next, key);
}

// -------------REVERSE------------
// reverse can be done by using swapping values in the linkedlist
// but his swapping of data is expensive if the data is in MB of size
// So reversing of nodes links should work because link is of 4 byte.
// To swap linkedList data we can use stack to store nodes 
// from mid to end of linked list.
// and then iterate over the list from head to mid and swap nodes
// by taking it from the top of stack.
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

Node* reverseLinkedListRec(Node* head){
	if(head->next == NULL) return head;
	Node* temp = reverseLinkedListRec(head->next);

	/**
	This approach is getting the last node in the reversed linkedList rHead.
	This will take O(N^2) time. We optized(replaced) it with below IMP line
	Node* rHead = temp;
	while(rHead->next != NULL){
		rHead = rHead->next;
	}
	rHead->next = head;
	head->next = NULL;
	**/

	head->next->next = head; // IMP
	head->next = NULL;
	return temp;
}

// ----------MIDPOINT-----------
Node* midpoint(Node* head){
	if(head == NULL || head->next == NULL) return head;
	Node* slow = head;
	Node* fast = head->next;
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

// ------------KthNodeFromEnd-------------
/**
Maintain a slow ponter at head and a fast pointer kth distance way from head
move both poniters one step ahead until fast reaches the end of the linked list.
**/
Node* kthNodeFromEnd(Node* head, int k){
	Node* slow = head;
	Node* fast = head;
	while(k--){
		fast = fast->next;
	}
	while(fast != NULL){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

//--------MERGE_SORTED_LINKED_LIST-----
// 1. using new nodes for keeping elements in ascending order
ListNode* mergeSortedLinkedList(ListNode* list1, ListNode* list2){
		ListNode* prev = NULL;
        ListNode* node = NULL;
        ListNode* head = NULL;
        while(list1 != NULL && list2 != NULL){
            if(list1->val < list2->val){
                node = new ListNode(list1->val);
                list1 = list1->next;
            }
            else{
                node = new ListNode(list2->val);
                list2 = list2->next;
            }
            if(prev == NULL){
                head = node;
                prev = head;
            }
            else{
                prev->next = node;
                prev = node;
            }
        }
        
       if(list1 != NULL){
           // in case list2 is empty, so head should be list1
           if(prev == NULL){
               head = list1;
           }
           // otherwise next of prev pointer should point to list1's head;
           else{
               prev->next = list1;
           }
       }
        
       if(list2 != NULL){
           // in case list1 is empty, so head should be list2
           if(prev == NULL){
               head = list2;
           }
           // otherwise next of prev pointer should point to list2's head;
           else{
               prev->next = list2;
           }
       }
        
        return head;
}

// 2. using dummy node and switching links
Node* mergeSortedLinkedList2(Node* head1, Node* head2){
	Node* dummy = new Node(0);
	Node* prev = dummy;
	while(head1 != NULL && head2 != NULL){
		if(head1->data < head2->data){
			prev->next = head1;
			prev = prev->next;
			head1 = head1->next;
		}
		else{
			prev->next = head2;
			prev = prev->next;
			head2 = head2->next;
		}
	}

	if(head1 == NULL) prev->next = head2;
	if(head2 == NULL) prev->next = head1;

	return dummy->next;
}

// 3. using recursion
Node* mergeSortedLinkedListRec(Node* head1, Node* head2){
	if(head1 == NULL) return head2;
	if(head2 == NULL) return head1;
	Node* cur = NULL;
	if(head1->data < head2->data){
		cur = head1;
		cur->next = mergeSortedLinkedListRec(head1->next, head2);
	}
	else{
		cur = head2;
		cur->next = mergeSortedLinkedListRec(head1, head2->next);
	}
	return cur;
}

// ----------MERGE_SORT------------ Time comlexity - O(N * LogN)
Node* mergeSort(Node* head){
	if(head == NULL || head->next == NULL) return head;
	// find mid of linked list
	Node* mid = midpoint(head);
	Node* head1 = head;
	Node* head2 = mid->next;
	mid->next = NULL;
	Node* sortedFirstPart = mergeSort(head1);
	Node* sortedSecondPart = mergeSort(head2);
	return mergeSortedLinkedListRec(sortedFirstPart, sortedSecondPart);
}

// ------CYCLE_DETECTION---------
// floyd cycle detection algorithm using fast and slow pointer
bool containsCycle(Node* head){
	Node* slow = head;
	Node* fast = head;
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast){
			return true;
		}
	}
	return false;
}

// find the node where cycle starts, so that we can break the cycle from the prev node
Node* getCycleStart(Node* head){
	if(head == NULL) return head;
	// get to the point where slow and fast meets
	Node* slow = head;
	Node* fast = head;
	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;
		if(fast == slow){
			slow = head; // make slow points to head and end the loop
			break;
		}
	}
	// progress fast and slow at same speed until the next pointers collide, they will collide at the cycle starting point.
	while(fast->next != slow->next){
		fast = fast->next;
		slow = slow->next;
	}
	return fast->next;
	// to break the cycle just make fast->next = NULL;
}

int main(){
	int n = 5;
	int *arr = new int[n]{5, 4, 3, 2, 1};
	Node* head = buildLinkedList(arr, n);
	printLinkedList(head);
	reverseLinkedList(head);
	printLinkedList(head);
	insertAtMiddle(head, 100, 5);
	printLinkedList(head);
	// deleteHead(head);
	// deleteTail(head);
	// deleteMiddle(head, 10);
	head = reverseLinkedListRec(head);
	printLinkedList(head);
	Node* node = kthNodeFromEnd(head, 4);
	cout << node->data << "\n";
	printf("%d\n", search(head, 100));
	printf("%d\n", searchRec(head, 110));

	Node* newHead = mergeSort(head);
	printLinkedList(newHead);
	return 0;
}