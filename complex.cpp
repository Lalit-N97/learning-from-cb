#include<iostream>
using namespace std;

/*
you should be able to perform following things with complex numbers -
input 
output
add
subtract
multiply
get the real part
get the imaginary part
*/

class Complex{
private:
	int real;
	int imaginary;
public:

	Complex(){
		real = 0;
		imaginary = 0;
	}

	// if any contructor of class is defined then 
	// default contructor will be overridden
	// hence defining our own contructor with 
	// zero non of params above
	Complex(int r, int i){
		this->real = r;
		Complex::imaginary = i;
	}

	// copy contructor exist by default
	void setReal(int const r){
		real = r;
	}

	void setImaginary(int const i){
		imaginary = i;
	}

	int getReal() const{
		return real;
	}

	int getImaginary() const{
		return imaginary;
	}

	void toString() const{
		if(imaginary > 0){
			printf("%d + %di\n", real, imaginary);
		}
		else{
			printf("%d - %di\n", real, -1*imaginary);
		}
	}

	void add(const Complex& x){
		this->real += x.real;
		this->imaginary += x.imaginary;
	}

	// to replace add with + operator using operator overloading
	// binary operation
	void operator+(Complex& x){
		real += x.real;
		imaginary += x.imaginary;
	}

	// Complex& operator+(Complex& x){
	// 	Complex y;
	// 	y.real = real + x.real;
	// 	y.imaginary = imaginary + x.imaginary;
	// 	return &y;
	// }

	// unary operation
	void operator!(){
		imaginary *= -1;
	}

	int operator[](string s){
		if(s == "real") return real;
		else if(s == "img") return imaginary;
		else return -1;
	}

	// cin and cout are special objects of Istream and Ostream classes respectively
	// which are defined under iostream header file
	// below obejct of Istream is "is" it could be "cin" or any other name
	// void operator>>(istream& is, Complex& x){
	// 	int r, i;
	// 	is >> r >> i;
	// 	x.setReal(r);
	// 	x.setImaginary(i);
	// }

	// void operator<<(ostream& os, Complex& x){
	// 	x.toString();
	// }

	// let's operator overload the cascading style
	istream& operator>>(istream& is, Complex& x){
		int r, i;
		is >> r >> i;
		x.setReal(r);
		x.setImaginary(i);
		return is;
	}

	ostream& operator<<(ostream& os, Complex& x){
		x.toString();
		return os;
	}

};

int main(){
	Complex c1(5, 6);
	Complex c2;
	c2.setImaginary(3);
	c2.setReal(2);
	Complex c3(c2); // default copy constructor
	c1.toString();
	c2.toString();
	c3.toString();
	// c1.add(c2);
	c1 + c2;
	// !c1;
	c1.toString();
	// cout << c1["real"] << "\n";
	// cout << c1;
	return 0;
}