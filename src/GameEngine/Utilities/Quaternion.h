#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Vector.h"

class Quaternion
{
	public:
		
		// Default constructor
		Quaternion();

		// Construct from existing quaternion
		Quaternion( const Quaternion & q );

		// Construct with specified real (s) and imaginary (v) components
		Quaternion( double s, double vi, double vj, double vk );

		// Construct with specified real (s) and imaginary (v) components
		Quaternion( double s, const Vector& v );

		// returns reference to double part
		double& re( void );
		
		// returns const reference to double part
		const double& re() const;
         
		// returns reference to imaginary part
		Vector& im();
         
		// returns const reference to imaginary part
		const Vector& im() const;

		// Return the conjugate quaternion
		Quaternion conj() const;

		// Rotate the vector using this quaternion
		Vector rotateVector(Vector & _v);

		// Get the rotation matrix
		void toMatrix( GLdouble Q[4][4] ) const;

		// Get the rotation angle in radian
		double getAngle() const;

		// Get the vector that the rotation is about
		Vector getVector() const;
         
		// Get reference to the specified component (0-based indexing: r, i, j, k)
		double & operator[]( int index );

		// Addition
		Quaternion operator+( const Quaternion& q ) const;

		// addition and assignment
		Quaternion & operator+=( const Quaternion& q );

		// Negation
		Quaternion operator-() const;

		// Subtraction
		Quaternion operator-( const Quaternion& q ) const;

		// subtraction and assignment
		Quaternion & operator-=( const Quaternion& q );
         
		// Right scalar multiplication
		Quaternion operator*( double c ) const;

		// scalar multiplication / assignment
		Quaternion & operator*=( double c );

		// Scalar division
		Quaternion operator/( double c ) const;

		// scalar division / assignment
		Quaternion & operator/=( double c );

		// Hamilton product
		Quaternion operator*( const Quaternion& q ) const;

		// Hamilton product and assignment
		Quaternion & operator*=( const Quaternion& q );
         
	protected:
		// scalar (double) part
		double m_Scalar;

		// vector (imaginary) part
		Vector m_Vector;
};

void glRotated(Quaternion & _q);

#endif
