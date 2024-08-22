#include<iostream>
#include<vector>
using namespace std;

// template<typename T, typename U>
template<typename T>
class Stack{
private:
	vector<T> v;
	// vector<U> v2;
public:

	void push(T data){
		v.push_back(data);
	}

	bool empty(){
		return v.size() == 0;
	}

	void pop(){
		if(!empty()) v.pop_back();
	}

	T top(){
		return v[v.size() - 1];
	}
};

int main(){
	// Stack<int> s;
	Stack<char> s;
	for(int i = 65; i <= 65 + 5; i++) s.push(i);

	while(!s.empty()){
		// printf("%d\n", s.top());
		cout << s.top() << "\n";
		s.pop();
	}

	return 0;
}