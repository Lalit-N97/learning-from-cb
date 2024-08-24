#include<iostream>
#include<queue>
#include<map>
#include<set>
#include<utility>
using namespace std;

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

TreeNode* build(int *arr, int &i){
	// ++i; // to do this we have to initiate i with -1
	if(arr[i] == -1) return NULL;
	TreeNode* node = new TreeNode(arr[i]);
	node->left = build(arr, ++i);
	node->right = build(arr, ++i);
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
	printBFSNextLine(root);

	sumReplacement(root);

	printBFSNextLine(root);

	return 0;
}