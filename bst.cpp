#include<iostream>
#include<queue>
#include<climits>
#include<utility>
#include<set> // multiset is also defined here
typedef multiset<int> :: iterator IT
using namespace std;

class personCompare{
	public:
		bool operator()(pair<string, int> p1, pair<string, int> p2){
			return p1.second < p2.second;
		}
};

class TreeNode{
public:
	int val;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int d){
		val = d;
		left = NULL;
		right = NULL;
	}

};

class LinkedList{
public:
	TreeNode* head;
	TreeNode* tail;
};

// this recursive pattern is important to understand other bst operations.
TreeNode* insertInBST(TreeNode* root, int d){
	if(root == NULL){
		return new TreeNode(d);
	}
	if(d <= root->val){
		root->left = insertInBST(root->left, d); // these recursive function calls will help traverse the tree nodes one by one
	}
	else{
		root->right = insertInBST(root->right, d);
	}
	return root;
}

TreeNode* build(int *arr){
	// int d;
	// cin >> d;
	TreeNode* root = NULL;
	int i = 0;
	// while(d != -1){
	while(arr[i] != -1){
		root = insertInBST(root, arr[i]);
		i++;
		// root = insertInBST(root, d);
		// cin >> d;
	}
	return root;
}

void printInorder(TreeNode* root){
	if(root == NULL) return;
	printInorder(root->left);
	cout << root->val << " ";
	printInorder(root->right);
}

void printLevelOrder(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		TreeNode* node = q.front(); q.pop();
		if(node == NULL){
			cout << "\n";
			if(!q.empty() && (q.front() != NULL)) q.push(NULL);
		}
		else{
			cout << node->val << " ";
			if(node->left != NULL) q.push(node->left);
			if(node->right != NULL) q.push(node->right); 
		}
	}
	cout << "\n";
}

TreeNode* search(TreeNode* root, int d){
  if(root == NULL) return NULL;
  if(d == root->val) return root;
  if(d < root->val) return search(root->left, d);
  return search(root->right, d);
}

TreeNode* deleteInBST(TreeNode* root, int d){
	// In case we are not able to find the d node and came at the very end of the tree then we should return NULL
	if(root == NULL) return NULL;
	// find the node d;
	if(root->val == d){
		// a node with its 2 children
		if(root->left != NULL && root->right != NULL){
			// find immediate successor of the current node to be deleted, which can be found in the right.
			// then keep moving left until NULL comes because the minimum val of the right subtree of the cur node will 
			// be the inorderSuccessor of current node.
			TreeNode* inorderSuccessor = root->right;
			while(inorderSuccessor->left != NULL){
				inorderSuccessor = inorderSuccessor->left;
			}
			// make the value of the current node same as that of inorderSuccessor
			root->val = inorderSuccessor->val;
			//delete the inorderSuccessor node using recursion because it could have its futher children on the right
			root->right = deleteInBST(root->right, root->val);
			return root;
		}
		// a node with only 1 right child
		else if(root->left == NULL && root->right != NULL) {
			TreeNode* temp = root->right; // let's save and send the address of the node of its immediate child
			delete root;
			return temp;
		} 
		else if(root->left != NULL && root->right == NULL){
			TreeNode* temp = root->left;
			delete root;
			return temp;
		}
		// a node with 0 child
		else{
			delete root;
			return NULL;
		}
	}
	else if(d <= root->val){
		root->left = deleteInBST(root->left, d);
		return root;
	}
	else {
		root->right = deleteInBST(root->right, d);
		return root;
	}
}



/** incomplete approach
// a tree is a BST if every node of the tree >= left subtree node and <= right subtree node
// plus the every node should be greater than its inorder predecessor and less than inorder successor.
bool isBST(TreeNode* root){
  if(root->left == NULL && root->right == NULL) return true;
  if(root->left != NULL && root->right == NULL) return 
  if(root->val <= root->right->val && root->val >= root->left->val){
  	int leftAns = isBST(root->left);
  	int rightAns = isBST(root->right);
  	// find inorder predecessor (max val in the left subtree) of the cur node
  	TreeNode* inorderPredecessor = root->left;
  	while(inorderPredecessor->right != NULL) {
  		inorderPredecessor = inorderPredecessor->right;
  	}
  	// find current node's inorder successor (min val in the right subtree) 
  	TreeNode* inorderSuccessor = root->right;
  	while(inorderSuccessor->left != NULL){
  		inorderSuccessor = inorderSuccessor->left;
  	}
  	if(root->val < inorderPredecessor->val || root->val > inorderSuccessor->val) return false;
  	return leftAns && rightAns;
  }
  else return false;
}
**/


bool isBST(TreeNode* root, int minV = INT_MIN, int maxV = INT_MAX){
	if(root == NULL) return true;
	if(root->val >= minV && root->val <= maxV && isBST(root->left, minV, root->val) && isBST(root->right, root->val, maxV)){
		return true;
	}
	return false;
}

LinkedList flatten(TreeNode* root){
	LinkedList ll;
	if(root == NULL){
		ll.head = NULL;
		ll.tail = NULL;
		return ll;
	}
	// leaf node
	if(root->left == NULL && root->right == NULL){
		ll.head = root;
		ll.tail = root;
		return ll;
	}
	// right subtree does not exist
	if(root->left != NULL && root->right == NULL){
		LinkedList leftLL = flatten(root->left);
		leftLL.tail->right = root;
		ll.head = leftLL.head;
		ll.tail = root;
		return ll;
	}
	// left subtree does not exist
	if(root->left == NULL && root->right != NULL){
		LinkedList rightLL = flatten(root->right);
		root->right = rightLL.head;
		ll.head = root;
		ll.tail = rightLL.tail;
		return ll;
	}
	// both the left and right subtrees exist
	LinkedList leftLL = flatten(root->left);
	LinkedList rightLL = flatten(root->right);
	leftLL.tail->right = root;
	root->right = rightLL.head;
	ll.head = leftLL.head;
	ll.tail = rightLL.tail;
	return ll;
}

void multisetInfo(){
	/** 
	multiset - that can store multiple elements that have same elements
	stored in a specific -> sorted according to internal comparison object
	values once inserted can't be modified, alternatively values can be removed and new value can be inserted
	assiciative container => elements are refered by their value and not by the index
	underlying data structure -> BST
	**/
	int arr[] = {10, 30, 20, 30, 20, 10, 10, 30};
	int n = sizeof(arr)/sizeof(int);
	multiset<int> m(arr, arr + 6);

	// iterate
	for (int x : m) cout << x << ", ";

	// erase 20 will erase all its occurences
	m.erase(20);

	// insert 80
	m.insert(80);

	// count
	cout << m.count(10); // 3

	// find -> get an iterator to the element
	// multiset<int> :: iterator it = m.find(30);
	auto it = m.find(30);
	cout << (*it) << endl;

	// get all elements which are equal to 30
	multiset<IT, IT> range = m.equal_range(30);

	for(auto it = range.first; it != range.second; it++) cout << *it << " - ";

	cout << endl;
	 
	// lower (>=) and upper bound (>)
	for(auto it = m.lower_bound(10); it != m.upper_bound(80); it++){
		cout << *it << ",  ";
	}


	pair<string, int> p1 = make_pair("A", 100);
	pair<string, int> p2 = make_pair("B", 20);

    // custom data type
    // pair - name(string), money(int)
    multiset<pair<string, int>, personCompare> mm;
    mm.insert(p1);
    mm.insert(p2);

}

int main(){

	int arr[] = {5, 3, 7, 1, 6, 8, -1};
	TreeNode* root = build(arr);
	// printInorder(root);
	printLevelOrder(root);
	// TreeNode* node = search(root, 1);
	// if(node != NULL) cout << node->val << "\n";
	// else cout << "NOT FOUND \n";

	// root = deleteInBST(root, 5);
	// printLevelOrder(root);

	cout << "\n" << isBST(root) << "\n";

	LinkedList l = flatten(root);
	TreeNode* temp = l.head;
	while(temp != NULL){
		cout << temp->val << "-->";
		temp = temp->right;
	}
	return 0;
}
