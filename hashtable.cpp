#include<iostream> // standard header file included using <>
// #include "vector.h" // user defined header file included using ""
#include<unordered_map>
using namespace std;

template<typename T>  // because we have applied template to a 
//class so we have use Node<T> node = new Node<T>() when 
//creating its object but avoid doing Node node = new Node();
class Node{
public:
	string key;
	int value;
	Node<T>* next;

	Node(string k, int v){
		this->key = k; // since this is a pointer to Node class so using -> to fetch its fields
		this->value = v;
		this->next = NULL;
	}

	~Node(){
		if(this->next != NULL){
			delete this->next;
		}
	}

};

template<typename T>
class HashTable{
public:
	Node<T>** table; // dynamic array of Node*
	int curSize;
	int tableSize;

	HashTable(int ts){
		this->tableSize = ts;
		table = new Node<T>*[tableSize];
		curSize = 0;
		for(int i = 0; i < tableSize; i++) {
			table[i] = NULL;
		}
	}

	void print(){
		for(int i = 0; i < tableSize; i++){
			Node<T>* head = table[i];
			cout << "Bucket " << i << " ";
			while(head != NULL){
				cout << "-> " << head->key << "," << head->value;
				head = head->next;
			}
			cout << "\n";
		}
	}

	// a hash function to take input as string key and return an integer index
	int hashFn(string key){
		int p = 1;
		int resIdx = 0;
		for(int i = 0; i < key.length(); i++){
			resIdx = ((resIdx % tableSize) + (key[i] * p) % tableSize ) % tableSize;
			// powers of prime numbers, especially a large prime number is very effective in distributing keys uniformly in the hash table
			p = (p * 29) % tableSize;
		}
		return resIdx;
	}

	void rehash(){
		Node<T>** oldTable = table;
		int oldTableSize = tableSize;
		tableSize = 2 * tableSize; // you can also make a next prime number >= 2 times of current tablesize
		table = new Node<T>*[tableSize];
		for(int i = 0; i < tableSize; i++){
			table[i] = NULL;
		}

		// fill new table from old table with hash function
		for(int i = 0; i < oldTableSize; i++){
			Node<T>* head = oldTable[i];
			while(head != NULL){
				insert(head->key, head->value);
				head = head->next;
			}
			if(oldTable[i] != NULL){
				delete oldTable[i]; // recursively delete all nodes in the linked list chain as per the destructure in Node class
			}
		}
	}

	void insert(string key, T value){
		int idx = hashFn(key);
		Node<T>* node = new Node<T>(key, value);
		// insert at the head of the linked list with id = idx
		node->next = table[idx]; // table[idx] wiil always contains address which stores the head of the linked list
		table[idx] = node; // storing new nodes address in the table[idx] at head.
		curSize++;

		// rehash...
		float loadFactor = curSize/tableSize;
		if(loadFactor > 0.7){
			rehash();
		}
	}

	T* search(string key){
		int idx = hashFn(key);
		Node<T>* head = table[idx];
		while(head != NULL){
			if(head->key == key){
				return &(head->value); // because the return type is pointer (address)
			}
			head = head->next;
		}
		return NULL;// to return NULL we have to change the return type from T to T* (pointer type)
	}

	void erase(string key){
		int idx = hashFn(key);
		Node<T>* head = table[idx];
		if(head->key == key){
			table[idx] = head->next;
			delete head;
		}
		else{
			while(head->next != NULL){
				if(head->next->key == key){
					Node<T>* temp = head->next;
					head->next = head->next->next;
					delete temp;
				}
				head = head->next;
			}
		}
	}

	T& operator[](string key){
		T* val = search(key);
		if(val == NULL){
			T garbage;
			insert(key, garbage);
			val = search(key);

		}
		return *val;
	}

};

// ------UNORDERED_MAP_WITH_CUSTOM_CLASS-------
class Student{
public:
	string firstName;
	string lastName;
	int rollNo;

	Student(string fn, string ln, int rn){
		firstName = fn;
		lastName = ln;
		rollNo = rn;
	}

	bool operator==(const Student &A) const{
		// return (this->rollNo) == A.rollNo;
		return rollNo == A.rollNo;
	}

};

class HashFn{
public:
	// size_t is an unsigned int or long while int is signed
	size_t operator()(const Student& A) const{
		return A.firstName.length() + A.lastName.length();
	}
};

int main(){

	HashTable<int> priceMenu(5);
	priceMenu.insert("Pizza", 120);
	priceMenu.insert("Burger", 345);
	priceMenu.insert("Sandwich", 45);
	priceMenu.insert("Choley", 456);
	priceMenu.insert("Chowmein", 456);

	priceMenu.print();

	priceMenu["Dosa"] = 60;
	priceMenu["Dosa"] += 10;
	cout << priceMenu["Dosa"] << "\n";

	priceMenu.print();

	unordered_map<Student, int, HashFn> studentMap; // key is Student and value is their Marks
	Student s1("Piyush", "Kumar", 45);
	Student s3("Piyush", "Kum", 45);
	Student s4("Piyush", "Kulkarni", 45);
	Student s2("Pranav", "Jha", 34);
	studentMap[s1] = 20;
	studentMap[s2] = 40;
	studentMap[s3] = 20;
	studentMap[s4] = 40;

	for(auto s : studentMap){
		cout << s.first.firstName << " " << s.first.lastName << " Marks : " << s.second << "\n";
	}


	return 0;
}