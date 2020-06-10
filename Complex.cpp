#define _USE_MATH_DEFINES
#include"Complex.h"
#include<math.h>
#include<iostream>

// Constructor 2
Complex::Complex(std::pair<double, double> polar) {
	real = polar.first * cos(polar.second);
	imag = polar.first * sin(polar.second);
}

// Copy Constructor
Complex::Complex(const Complex& rhs) : real(rhs.real), imag(rhs.imag) {}

// Magnitude
double Complex::magnitudeSqr() const {
	return pow(real, 2.) + pow(imag, 2.);
}

// Conjugate
Complex Complex::conjugate() const{
	return Complex(real, -imag);
}

// Radial Representation
std::pair<double, double> Complex::polar() const {
	std::pair<double, double> components;
	components.first = sqrt(this->magnitudeSqr());
	// Note: atan2 takes care of anything except for non-sense input
	components.second = atan2(imag, real);
	components.second = components.second < 0 ? components.second + 2. * M_PI : components.second;
	return components;
}

// Exponential
Complex Complex::powComplex(double power) {
	// Extract polar coordinates
	std::pair<double, double> polar = this->polar();
	// Radial part
	polar.first = pow(polar.first, power);
	// Angle part
	polar.second = polar.second * power;
	// Reconstruct the usual representation
	return Complex(polar);
}

// Assignment Operators
// As an additional worry, we need to worry about self-assignment. What I mean
// is that all the assignment operators can break if rhs is actually this.
// Think along the lines of performing a swap. Performing a = b, b = a in code
// will just result in both pieces of memory just becoming b. Similar errors
// can occur with these operators.

// Basic assignment
// Assignment
const Complex& Complex::operator=(const Complex& rhs) {
	// No aliasing issues here, because nothing is deleted. This is what the
	// compiler would likely give us by default. Note though, if we did 
	// delete of what was stored in the pointer first, we could potentially
	// get rid of rhs.real or rhs.imag, so there would be no copy. As it stands,
	// we should not have issues with self-assignment.
	real = rhs.real;
	imag = rhs.imag;
	return *this;
}

// Addition Assignment
const Complex& Complex::operator+=(const Complex& rhs) {
	// No aliasing here as real and imag are decoupled.
	real += rhs.real;
	imag += rhs.imag;
	return *this;
}

// Subtraction Assignment
const Complex& Complex::operator-=(const Complex& rhs) {
	// No aliasing here as real and imag are decoupled.
	real -= rhs.real;
	imag -= rhs.imag;
	return *this;
}

// Multiplication Assignment
const Complex& Complex::operator*=(const Complex& rhs) {
	// The code below has aliasing because when we update real, we could also
	// potentially update rhs.real. Also the math in the second line will use
	// the result from the first line.
	// real = real * rhs.real - imag * rhs.imag;
	// imag = real * rhs.imag + imag * rhs.real;
	// Solution: use temporary variables
	double newReal = real * rhs.real - imag * rhs.imag;
	double newImag = real * rhs.imag + imag * rhs.real;
	real = newReal;
	imag = newImag;
	return *this;
}

// Division Assignment
const Complex& Complex::operator/=(const Complex& rhs) {
	// Same as above
	// real = (real * rhs.real + imag * rhs.imag) / this->magnitudeSqr();
	// imag = (real * rhs.imag - imag * rhs.real) / this->magnitudeSqr();
	double newReal = (real * rhs.real + imag * rhs.imag) / this->magnitudeSqr();
	double newImag = (real * rhs.imag - imag * rhs.real) / this->magnitudeSqr();
	real = newReal;
	imag = newImag;
	return *this;
}

// Comparison Operators
// We are going to define < based on radii of the complex number
inline bool operator<(const Complex& lhs, const Complex& rhs) {
	return lhs.magnitudeSqr() < rhs.magnitudeSqr();
}

// Note: equality tests if they are the same complex number
inline bool operator==(const Complex& lhs, const Complex& rhs) {
	return (lhs.real == rhs.real && lhs.imag == rhs.imag);
}

inline bool operator>(const Complex& lhs, const Complex& rhs) {
	return rhs < lhs;
}

// Note: the equality part is associated with the radius rather than the values
// of the real and imaginary field as in the == operator
inline bool operator<=(const Complex& lhs, const Complex& rhs) {
	return lhs.magnitudeSqr() <= rhs.magnitudeSqr();
}

inline bool operator>=(const Complex& lhs, const Complex& rhs) {
	return rhs <= lhs;
}

// Print (for debugging)
void Complex::print() {
	std::cout << "Real part: " << real << std::endl;
	std::cout << "Imaginary part: " << imag << std::endl;
}

// Arithematic
// Addition
Complex operator+(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);
	result += rhs;
	return result;
}

// Subtraction
Complex operator-(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);
	result -= rhs;
	return result;
}

// Multiplication
Complex operator*(const Complex& lhs, const Complex& rhs) {
	/*
	double newReal = real * rhs.real - imag * rhs.imag;
	double newImag = real * rhs.imag + imag * rhs.real;
	return Complex(newReal, newImag);
	*/
	Complex result(lhs);
	result *= rhs;
	return result;
}

// Division
Complex operator/(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);
	result /= rhs;
	return result;
}
