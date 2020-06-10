#define _USE_MATH_DEFINES
#include"Complex.h"
#include<iostream>
#include<math.h>
using namespace std;

int main() {
	// Thoroughly test implemented methods
	cout << "Testing the constructors:" << endl;
	// Constructors
	Complex test1 = Complex();
	cout << "\nExpecting: 0 + 0i" << endl;
	test1.print();

	test1 = Complex(1.);
	// ^^^ Consequently, also operator=
	cout << "\nExpecting: 1. + 0i" << endl;
	test1.print();

	test1 = Complex(1., 1.);
	cout << "\nExpecting: 1. + 1.i" << endl;
	test1.print();

	// Constructors - Polar coordinates
	pair<double, double> polar1;
	polar1.first = 1.;
	polar1.second = M_PI;
	test1 = Complex(polar1);
	cout << "\nExpecting: -1. + 0i" << endl;
	test1.print();
	cout << "Note: numbers on the order of 10^-16 are one or 2 bits off zero." << endl;
	cout << "This is expected for double arithmetic. It also means that the " << endl;
	cout << "constructor is actually doing the math." << endl;

	// Copy Constructor
	Complex test2 = Complex(test1);
	// Note: = Complex(test1) is a different call than = test1;
	cout << "\nExpecting: -1 + 0i (with same difference from 0 as above)." << endl;
	test2.print();

	// Modify test data
	test1.setReal(5.);
	test1.setImag(7.);
	test2.setReal(5.);
	test2.setImag(-7.);

	// Test other internal operators
	// Magnitude Squared
	cout << "\nTesting magnitudeSqr() function:" << endl;
	cout << "Expecting: 60" << endl;
	cout << test1.magnitudeSqr() << endl;
	cout << "Expecting: 60" << endl;
	cout << test2.magnitudeSqr() << endl;
	test2.setReal(0.);
	test2.setImag(0.);
	cout << "Expecting: 0" << endl;
	cout << test2.magnitudeSqr() << endl;
	test2.setReal(-1.);
	cout << "Expecting: 1" << endl;
	cout << test2.magnitudeSqr() << endl;
	test2.setImag(100.);
	cout << "Expecting: 10001" << endl;
	cout << test2.magnitudeSqr() << endl;

	// Conjugate
	cout << "\nTesting the conjugate:" << endl;
	test2 = test1.conjugate();
	cout << "Expecting: 5 - 7i" << endl;
	test2.print();
	test2.setImag(0.);
	test2 = test2.conjugate();
	cout << "Expecting: 5 + 0i" << endl;
	test2.print();

	// Getting the polar representation
	cout << "\n"
	polar1 = test2.polar();

	// Complex power
}