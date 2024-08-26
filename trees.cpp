#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<utility>
using namespace std;

class HBPair{
public:
	int height;
	bool balance;
};

class MaxSumPair{
public:
	int branchSum;
	int maxSum;
    
    MaxSumPair(){
    	branchSum = 0;
    	maxSum = 0;
    }

};

class TreeNode{
public:
	int data;
	TreeNode* left;
	TreeNode* right;

	TreeNode(int d){
		this->data = d;
		this->left = NULL;
		this->right = NULL;
	}

};

class BinaryTree{
public:

	void rightView(TreeNode* root, int d){ 
		if(root == NULL) return;

	}

	void leftView(){}

	void topView(){}

	void lcaUsingPath(){}

	void lcaUsingRecursion(){}


};

// --------BUILD----------

TreeNode* build(int *arr, int &i){
	// ++i; // to do this we have to initiate i with -1
	if(arr[i] == -1) return NULL;
	TreeNode* node = new TreeNode(arr[i]);
	node->left = build(arr, ++i);
	node->right = build(arr, ++i);
	return node;
}

TreeNode* buildByInput(){
	int d;
	cin >> d;
	if(d == -1) return NULL;
	TreeNode* node = new TreeNode(d);
	node->left = buildByInput();
	node->right= buildByInput();
	return node;
}

// --------TREE TRAVERSAL---------

void printPreorder(TreeNode* root){
	if(root == NULL) return;
	cout << root->data << " ";
	printPreorder(root->left);
	printPreorder(root->right);
}


void printPostorder(TreeNode* root){
	if(root == NULL) return;
	printPostorder(root->left);
	printPostorder(root->right);
	cout << root->data << " ";
}

void printInorder(TreeNode* root){
	if(root == NULL) return;
	printInorder(root->left);
	cout << root->data << " ";
	printInorder(root->right);
}

// -------PRINT_ALL_LEVELS-------

// Optimized, Time - O(N), Space - O(N)
void printLevelOrder(TreeNode* root, int level, map<int, set<TreeNode*>> &levelNodes){
	if(root == NULL) return;
	levelNodes[level].insert(root);
	printLevelOrder(root->left, level + 1, levelNodes);
	printLevelOrder(root->right, level + 1, levelNodes);
}

int getHeight(TreeNode* root){
	if(root == NULL) return 0;
	int leftSubTreeHeight = getHeight(root->left);
	int rightSubTreeHeight = getHeight(root->right);
	return 1 + max(leftSubTreeHeight, rightSubTreeHeight);
}

void printElementsAtKLevel(TreeNode* root, int k){
	if(root == NULL) return;
	if(k == 1) {
		cout << root->data << " ";
		return;
	}
	printElementsAtKLevel(root->left, k - 1);
	printElementsAtKLevel(root->right, k - 1);
}

// Time - O(N^2), Space - O(N)
void printAllLevels(TreeNode* root){
	int h = getHeight(root);
	for(int k = 1; k <= h; k++){
		printElementsAtKLevel(root, k);
		cout << "\n";
	}
}

void printBFS(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty()){
		TreeNode* node = q.front();
		q.pop();
		cout << node->data << " ";
		if(node->left != NULL) {
			q.push(node->left);
		}
		if(node->right != NULL){
			q.push(node->right);
		}
	}
	cout << "\n";
}

void printBFSNextLine(TreeNode* root){
	/** using a buffer vector
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty()){
		vector<TreeNode*> buffer;
		while(!q.empty()){
			buffer.push_back(q.front());
			q.pop();
		}
		for(int i = 0; i < buffer.size(); i++){
			TreeNode* node = buffer[i];
			cout << node->data << " ";
			if(node->left != NULL) {
				q.push(node->left);
			}
			if(node->right != NULL){
				q.push(node->right);
			}
		}
		cout << "\n";
	}
	cout << "\n";
	**/

	/**
	pair of node and its associated level, whenever there is a change in level we need to print a nextLine

	queue<pair<TreeNode*, int>> q; 
	q.push(make_pair(root, 1));
	int curLevel = 1;
	while(!q.empty()){
		pair<TreeNode*, int> p = q.front();
		q.pop();
		TreeNode* node = p.first;
		int level = p.second;
		if(curLevel != level){
			cout << "\n";
			curLevel = level;
		}
		cout << node->data << " ";
		if(node->left != NULL){
			q.push(make_pair(node->left, curLevel + 1));
		}
		if(node->right != NULL){
			q.push(make_pair(node->right, curLevel + 1));
		}
	}
	cout << "\n";
	**/

	/**
	Keeping two elements intitally in the queue i.e. root and NULL
	whenever encounter NULL while traversing queue we have to print newline and push NULL again in the end
	because with every NULL encounter we can get a surity that the nodes before NULL in the queue has
	already pushed all their children (at that level) into the queue.

	**/
	queue<TreeNode*> q;
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		TreeNode* node = q.front(); 
		q.pop();
		if(node == NULL){
			cout << "\n";
			if(q.empty()) break; // come out of loop if there are no children available to be printed
			else q.push(NULL);
		}
		else{
			cout << node->data << " ";
			if(node->left != NULL){
				q.push(node->left);
			}
			if(node->right != NULL){
				q.push(node->right);
			}
		}
	}
	cout << "\n";
}

// ---------- DIAMETER --------------

int diameter(TreeNode* root){ // Time - O(N^2) and Space - O(N)
	if(root == NULL) return 0;
	int leftHeight = getHeight(root->left);
	int rightHeight = getHeight(root->right);
	int dia = max(diameter(root->left), diameter(root->right));
	return max(dia, leftHeight + rightHeight);
}

// we can return both height and diameter in a pair object
pair<int, int> diameterOptimized(TreeNode* root){ // instead of calulating height of each node separately let's track the height while recursively finding the diameter
	if(root == NULL) return make_pair(0, 0);
	pair<int, int> left = diameterOptimized(root->left);
	pair<int, int> right = diameterOptimized(root->right);
	pair<int, int> res;
	res.first = max(left.first, right.first) + 1;
	res.second = max(left.first + right.first, max(left.second, right.second));
	return res;
}

// ---------REPLACE THE SUM OF SUBTREE WITH THE CURRENT NODE BUT DON'T UPDATE THE LEAF NODE----------
int sumReplacement(TreeNode* root){
	if(root == NULL) return 0;
	if(root->left == NULL && root->right == NULL) return root->data;
	int temp = root->data;
	int leftSum = sumReplacement(root->left);
	int rightSum = sumReplacement(root->right);
	root->data = leftSum + rightSum;
	return root->data + temp;
}

// ---------- HEIGHT_BALANCED_BINARY_TREE---------
// check if all the nodes of a binary tree left subtree and right subtree height difference of <= 1
HBPair isHeightBalanced(TreeNode* root){
	HBPair p;
	if(root == NULL) {
		p.height = 0;
		p.balance = true;
		return p;
	} 
	HBPair left = isHeightBalanced(root->left);
	HBPair right = isHeightBalanced(root->right);
	p.height = max(left.height, right.height) + 1;
	if((left.balance == true) && (right.balance == true) && (abs(left.height - right.height) <= 1)){
		p.balance = true;
	}
	else p.balance = false;
	return p;
} 

//----------BUILDING_HIEGHT_BALANCED_BINARY_TREE-------------

TreeNode* buildHBTreeFromInorder(int* inorder, int start, int end){ 
	if(start > end) return NULL;
	int mid = start + (end - start)/2;
	TreeNode* root = new TreeNode(inorder[mid]);
	root->left = buildHBTreeFromInorder(inorder, start, mid - 1);
	root->right = buildHBTreeFromInorder(inorder, mid + 1, end);
	return root;
}

TreeNode* buildHBTreeFromPreAndIn(int* inorder, int* preorder, int start, int end){
	static int p = 0;
	if(start > end) return NULL;
	int idx = -1;
	for(int i = start; i <= end; i++){
		if(inorder[i] == preorder[p]){
			idx = i;
			break;
		}
	}
	p++;
	TreeNode* root = new TreeNode(inorder[idx]);
	root->left = buildHBTreeFromPreAndIn(inorder, preorder, start, idx - 1);
	root->right = buildHBTreeFromPreAndIn(inorder, preorder, idx + 1, end);
	return root;
}

// -----------RIGHT_VIEW_OF_A_TREE-----------
void printRightViewUsingLevelOrder(TreeNode* root){
	queue<TreeNode*> q;
	if(root != NULL) cout << root->data << " ";
	q.push(root);
	q.push(NULL);
	while(!q.empty()){
		TreeNode* node = q.front(); q.pop();
		if(node == NULL){
			if(q.empty()) break;
			else {
				cout << q.front()->data << " ";
				q.push(NULL);
			}
		}
		else{
			if(node->right != NULL) q.push(node->right);
			if(node->left != NULL) q.push(node->left);
		}
	}
	cout << "\n";
}

// process the elements in order (Root)(right)(left)
void printRightViewDFS(TreeNode* root, int curLevel, int &maxLevel){
	if(root == NULL) return;
	if(curLevel > maxLevel){ // first time reaching a new level i.e. for the first time at new level curLevel will be greater than maxLevel
		cout << root->data << " ";
		maxLevel = curLevel;
	}
	printRightViewDFS(root->right, curLevel + 1, maxLevel);
	printRightViewDFS(root->left, curLevel + 1, maxLevel);
}

// ------K_DISTANCE_AWAY_NODES----------
void printNodesKDistanceDownwards(TreeNode* node, int k){
	if(node == NULL) return;
	if(k == 0){
		cout << node->data << " ";
		return;
	}
	printNodesKDistanceDownwards(node->left, k - 1);
	printNodesKDistanceDownwards(node->right, k - 1);
	return;
}

// this function does two things
// 1. returning distance of target node from every node you traverse
// 2. It prints the kth distance away nodes (relevant nodes that we want here)
int printAtKDistance(TreeNode* root, TreeNode* target, int k){
	// base case
	if(root == NULL) return -1;
	// when reach the target node
	if(root == target){
		printNodesKDistanceDownwards(target, k);
		return 0;
	}
	// now you could be at one of the ancestor of the target node if leftDist <> 1
	int leftDist = printAtKDistance(root->left, target, k);
	if(leftDist != -1){
		// now check for two cases whether the k distance away node is ancestor itself or need to go to the right subtree
		if(leftDist + 1 == k){
			cout << root->data << " ";
		}
		else {
			printNodesKDistanceDownwards(root->right, k - 2 - leftDist);
		}
		return leftDist + 1;
	}
	int rightDist = printAtKDistance(root->right, target, k);
	if(rightDist != -1){
		// now check for two cases whether the k distance away node is ancestor itself or need to go to the right subtree
		if(rightDist + 1 == k){
			cout << root->data << " ";
		}
		else {
			printNodesKDistanceDownwards(root->right, k - 2 - rightDist);
		}
		return rightDist + 1;
	}
	// when target node is not present in the left or right subtree
	return -1;
}

// -------------LCA------------
// both a and b are present in the tree and all keys are unique
TreeNode* lca(TreeNode* root, int a, int b){
	if(root == NULL) return NULL; // means none of the nodes a and b are found
	if(root->data == a || root->data == b){
		return root;
	}
	TreeNode* leftAns = lca(root->left, a, b);
	TreeNode* rightAns = lca(root->right, a, b);
	if(leftAns != NULL && rightAns != NULL) return root;
	if(leftAns == NULL) return rightAns;
	return leftAns;
}

// variation of lca

// find the level of a node from given node
int search(TreeNode* node, int key, int level){
	if(node == NULL) return -1;
	if(node->data == key) return level;
	int leftLevel = search(node->left, key, level + 1);
	if(leftLevel != -1) return leftLevel;
	return search(node->right, key, level + 1);
}

// function to find distance between two nodes
int findDistance(TreeNode* root, int a, int b){
	TreeNode* lcaNode = lca(root, a, b);
	int l1 = search(lcaNode, a, 0); // starting level = 0
	int l2 = search(lcaNode, b, 0);
	return l1 + l2;
}

int shortestDistanceBetweenNodes(TreeNode* root, int a, int b){
	if(root == NULL) return 0;
	if(root->data == a || root->data == b) return 1;
	int leftDist = shortestDistanceBetweenNodes(root->left, a, b);
	int rightDist = shortestDistanceBetweenNodes(root->right, a, b);
	return leftDist + rightDist;
}

// -------------ANY_NODE_TO_ANY_NODE_MAX_SUM_PATH_BINARY_TREE--------------
MaxSumPair maxSum(TreeNode* root){
	MaxSumPair p;
	if(root == NULL) return p;

	MaxSumPair left = maxSum(root->left);
	MaxSumPair right = maxSum(root->right);

	// contruct values
	int op1 = root->data;
	int op2 = root->data + left.branchSum;
	int op3 = root->data + right.branchSum;
	int op4 = root->data + left.branchSum + right.branchSum;

	int curAnsThroughRoot = max(op1, max(op2, max(op3, op4)));

	// calculation of branch sum of the current root
	p.branchSum = max(left.branchSum, max(right.branchSum, 0)) + root->data;
	p.maxSum = max(left.maxSum, max(right.maxSum, curAnsThroughRoot));
	return p;
}

int main(){

	int arr[] = {1, 2, -1, 4, -1, -1, 3, 5, -1, 6, -1, -1, -1};
	int i = 0;
	TreeNode* root = build(arr, i);
	printPreorder(root);
	cout << "\n";
	printInorder(root);
	cout << "\n";
	printPostorder(root);
	cout << "\n";

	map<int, set<TreeNode*>> levelNodes;
	printLevelOrder(root, 0, levelNodes);

	set<TreeNode*> :: iterator it;
	int level = 0;
	while(!levelNodes[level].empty()){
		set<TreeNode*> nodes = levelNodes[level];
		for(it = nodes.begin(); it != nodes.end(); it++) cout << (*it)->data << " ";
		cout << "\n";
		level++;
	}

	// cout << getHeight(root) << "\n";

	// printAllLevels(root);

	// printBFS(root);

	// printBFSNextLine(root);

	// cout << diameter(root);
	// pair<int, int> p = diameterOptimized(root);
	// cout << p.first << " " << p.second << "\n";

	cout << "----------\n";
	// printBFSNextLine(root);

	// sumReplacement(root);

	// printBFSNextLine(root);
	int inorder[] = {3, 2, 8, 4, 1, 6, 7, 5};
	int preorder[] = {1, 2, 3, 4, 8, 5, 6, 7};
	int n = sizeof(inorder)/sizeof(int);
	// TreeNode* newRoot = buildHBTreeFromInorder(inorder, 0, n - 1);
	TreeNode* newRoot = buildHBTreeFromPreAndIn(inorder, preorder, 0, n - 1);
	printBFSNextLine(newRoot);

	// printRightViewUsingLevelOrder(newRoot);
	// int maxLevel = -1;
	// printRightViewDFS(newRoot, 0, maxLevel);

	// printNodesKDistanceDownwards(newRoot, 2);
	printAtKDistance(newRoot, newRoot->left->left, 2);

	MaxSumPair p = maxSum(newRoot);
	cout << "branchSum - " << p.branchSum << "maxSum - " << p.maxSum << "\n";

	return 0;
}