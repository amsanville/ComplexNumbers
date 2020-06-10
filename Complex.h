#ifndef COMPLEX_H
#define COMPLEX_H
#include <utility>

/*
Complex

The purpose of this class is to implement a complex number class in order to 
refamiliarize myself with operator overloading best practices. The goal is to
explore exactly how to properly do operator overloading and the complications
associated with doing it one versus another. I also want to see how user
defined classes can take advantage of casting.
*/
class Complex {
private:
	double real;
	double imag;
public:
	// Constructor for 2 or fewer doubles directly assigns to real and imaginary
	Complex(double real = 0., double imag = 0.) : real(real), imag(imag) {}
	// Constructor to convert polar coordinates to a complex number
	Complex(std::pair<double, double> polar);
	// Explicit Copy Constructor
	Complex(const Complex& rhs);

	// Magnitude of the complex number squared
	double magnitudeSqr() const;
	// Complex conjugate
	Complex conjugate() const;
	// Return the polar representation of the complex number, radius and angle.
	// In this case, radius first followed by angle in radians.
	std::pair<double, double> polar() const;
	// Take the complex number raised to some power
	// Note: ** cannot be created as an operator, so this is the type of operator
	// we will have to use
	Complex powComplex(double power);

	// Internal Operators
	// Assignment Operators
	// Assignment - just made explicit
	const Complex& operator=(const Complex& rhs);
	// Addition Assignment - add rhs and reassign to this
	const Complex& operator+=(const Complex& rhs);
	// Subtraction Assignment - subtract rhs and reassign to this
	const Complex& operator-=(const Complex& rhs);
	// Multiplication Assignment - multiply by rhs and reassign to this
	const Complex& operator*=(const Complex& rhs);
	// Division Assignment - divide by rhs and reassign to this
	const Complex& operator/=(const Complex& rhs);

	// Friend Operators
	// Relational & Equality Operators
	// Note: these comparisons will be inline
	// Less than - use polar coordinate radius for comparison
	friend bool operator<(const Complex& lhs, const Complex& rhs);
	// Greater than - consistent with less than
	friend bool operator>(const Complex& lhs, const Complex& rhs);
	// Less than or equal to - Consistent with less than
	friend bool operator<=(const Complex& lhs, const Complex& rhs);
	// Greater than or equal to - Consistent with less than
	friend bool operator>=(const Complex& lhs, const Complex& rhs);
	// Equality - equal if real and imaginary parts are equal
	friend bool operator==(const Complex& lhs, const Complex& rhs);
	// Not equal - consistent with equality
	friend bool operator!=(const Complex& lhs, const Complex& rhs);

	// Debug
	// Print out the contents of the complex number with access to the internals
	void print();
	// Mutators
	inline void setReal(double newReal) { real = newReal; }
	inline void setImag(double newImag) { imag = newImag; }
	// Accessors
	inline double getReal() { return real; }
	inline double getImag() { return imag; }
};


// External Operators
// These make no reference to the internals of the Complex number so they can
// be entirely external.

// Arithmetic Operators
// Note: these return a Complex number as they are making a new complex number
// with this number and another. They make use of the copy constructor and are
// consistent with the assignment operators, though they need not be.

// Addition (add real and imaginary parts)
Complex operator+(const Complex& lhs, const Complex& rhs);
// Subtraction (subtract real and imaginary parts)
Complex operator-(const Complex& lhs, const Complex& rhs);
// Multiplication (foil complex and imaginary parts)
Complex operator*(const Complex& lhs, const Complex& rhs);
// Division (use conjugate to peform division)
Complex operator/(const Complex& lhs, const Complex& rhs);
#endif