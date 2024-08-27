#include<iostream>
#include<vector>
using namespace std;

class Heap{
private:
	vector<int> v;
	bool isMinHeap;

	bool compare(int a, int b){
		if(isMinHeap){
			return a < b;
		}
		else{
			return a > b;
		}
	}

	void heapify(int idx){
		int lastIdx = v.size() - 1;
		int leftChildIdx = idx*2;
		int rightChildIdx = idx*2 + 1;
		int minIdx = idx;
		// point the minIdx to left index if left value is smaller than parent
		if(leftChildIdx <= lastIdx && compare(v[leftChildIdx], v[idx])){
			minIdx = leftChildIdx;
		}
		// point minIdx to right index, if right value is smaller than parent value and left value
		if(rightChildIdx <= lastIdx && compare(v[rightChildIdx], v[minIdx])){
			minIdx = rightChildIdx;
		}
		if(minIdx != idx){ // if minIdx == idx then further swapping and recursion will stop
			swap(v[minIdx], v[idx]);
			heapify(minIdx);
		}
	}

public:
	Heap(int default_size = 100, bool minHeap = true){
		v.reserve(default_size);
		v.push_back(-1); // 0th index should hold something say -1 or INT_MIN anything
		isMinHeap = minHeap;
	}

	void push(int d){ // Time - O(logN)
		v.push_back(d);
		// heapify
		int lastIdx = v.size() - 1;
		int parentIdx = lastIdx/2;
		/**keep pushing to the top till you reach a root node or stop midway because 
		current element is already in the right place **/
		while(lastIdx > 1 && compare(v[lastIdx], v[parentIdx])){
			swap(v[lastIdx], v[parentIdx]);
			lastIdx = parentIdx;
			parentIdx = parentIdx/2;
		}

	}

	int top(){ // Time - O(1)
		return v[1];
	}

	void pop(){ // Time - O(logN)
		int firstIdx = 1;
		int lastIdx = v.size() - 1;
		swap(v[firstIdx], v[lastIdx]);
		v.pop_back();
		heapify(firstIdx);
	}

	bool empty(){
		return v.size() == 1;
	}

	void heapify(vector<int> &arr, int idx){
		int lastIdx = arr.size() - 1;
		int leftIdx = 2*idx;
		int rightIdx = 2*idx + 1;
		int minIdx = idx;
		if(leftIdx <= lastIdx && compare(arr[leftIdx], arr[minIdx])) {
			minIdx = leftIdx;
		}
		if(rightIdx <= lastIdx && compare(arr[rightIdx], arr[minIdx])){
			minIdx = rightIdx;
		}
		if(minIdx != idx){
			swap(arr[minIdx], arr[idx]);
			heapify(arr, minIdx);
		}
	}

	void buildHeapOptimized(vector<int> &arr){ // Time - O(N) explained in notes
		// starts from first non-leaf node
		int idx = (arr.size() - 1)/2;
		// take each element of array and apply heapify on those elements
		for(int i = idx; i > 0; i--) heapify(arr, i);
	}

};

// ----Given a vector, modify its elements such that it represents a min heap-----
// Time - O(N*logN) - for each vector element we are iterating to the top (starting from that element)
// for last level there are total N/2 elements in complete binary tree and height will be logN
// so for the last level total time comes out to be (N/2 * logN);
void buildHeap(vector<int> &v){
	// here v[0] contains -1, and other indexes contains random elements
	for(int i = 2; i < v.size(); i++){
		int idx = i;
		int parent = idx/2;
		while(idx > 1 && v[idx] > v[parent]){
			swap(v[idx], v[parent]);
			idx = parent;
			parent = parent/2;
		}
	}
}

void print(vector<int> v){
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << "\n";
}

int main(){
	int arr[] = {1, 2, 3, 17, 19, 36, 7, 25, 100};
	int n = sizeof(arr)/sizeof(int);
	Heap h;
	// Heap h(10, false); 
	for(int i = 0; i < n; i++){
		h.push(arr[i]);
	}

	while(!h.empty()){
		cout << h.top() << " ";
		h.pop();
	}
	cout << "\n";

	vector<int> v = {-1, 10, 20, 5, 6, 1, 8, 9, 4};
	print(v);
	h.buildHeapOptimized(v);
	print(v);

	return 0;
}