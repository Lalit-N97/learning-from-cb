template<typename T>
class Vector{
	int curSize;
	int maxSize;
	T* arr;

public:
	Vector(){
		curSize = 0;
		maxSize = 1;
		arr = new T[maxSize];
	}

	int size() const{
		return curSize;
	}

	int capacity() const{
		return maxSize;
	}

	bool empty() const{
		return curSize == 0;
	}

	void pushBack(const T ele){
		if(curSize == maxSize){
			maxSize = 2 * maxSize;
			T *temp = new T[maxSize];
			for(int i = 0; i < curSize; i++){
				temp[i] = arr[i];
			}
			temp[curSize] = ele;
			curSize++;
			delete arr;
			arr = temp;
		}
		else {
			arr[curSize] = ele;
			curSize++;
		}
	}

	void popBack(){
		if(curSize == 0) {
			cout << "No elements to be popped out\n";
			return;
		}
		curSize--;
	}

	T front() const{
		if(curSize == 0) {
			cout << "No elements are present\n";
			return -1;
		}
		return arr[0];
	}

	T back() const{
		if(curSize == 0) {
			cout << "No elements are present\n";
			return -1;
		}
		return arr[curSize - 1];
	}

	T operator[](const int idx){
		if(idx >= curSize) {
			cout << "Index out of bound Error";
			return -1;
		}
		return arr[idx];
	}

};