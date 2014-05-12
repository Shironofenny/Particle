#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "../../GLHeader.h"

#include <cmath>
#include <Eigen/Core>
#include <assert.h>
#include <iostream>

#define _USE_MATH_DEFINES

class Vector
{
	public:

		// Default constructor
		Vector();

		// Constructor with initial values
		Vector(double, double, double);

		// Destructor
		~Vector();

		// Get the norm of the vector
		double norm() const;

		// Normalize the vector
		void normalize();

		// Transform using OpenGL matrix
		Vector transform(GLfloat _matrix[16]);

		// Project a this vector into a new basis defined by _coord x, y, z, and get a new vector
		Vector projection(Vector const & _coordx, Vector const & _coordy, Vector const & _coordz);

		// Multiply a this vector with _coord x, y, z, and get a new vector
		Vector changeCoordinate(Vector const & _coordx, Vector const & _coordy, Vector const & _coordz);

		// Change this vector into eigen used vector form
		Eigen::Vector3d toEigenVector();

		// Get value using indicies
		double & operator[] (int _index);
		double const & operator[] (int _index) const;

		// Addition
		Vector operator + (Vector const & _v) const;

		// Addition and assign
		Vector & operator += (Vector const & _v);
		
		// Negate
		Vector operator - () const;

		// Substract
		Vector operator - (Vector const & _v) const;

		// Substract and assign
		Vector & operator -= (Vector const & _v);

		// Scalar multiplication
		Vector operator * (double const _c) const;

		// Scalar multiplication and assign
		Vector & operator *= (double const _c);

		// Scalar division
		Vector operator / (double const _c) const;

		// Scalar division and assign
		Vector & operator /= (double const _c);

	private:

		// Value of x, y, z
		double m_Position[3];
};

// Dot product of two vectors
double dot(Vector const & _v1, Vector const & _v2);

// Cross product of two vectors
Vector cross(Vector const & _v1, Vector const & _v2);

// Output vector using standard stream
std::ostream & operator << (std::ostream & output, Vector const & _v);

// Override gltranslate function:
void glTranslatev(Vector const & v);

// Override glVertex function:
void glVertex3v(Vector const & v);

// Override glScale function:
void glScalev(Vector const & v);

#endif
