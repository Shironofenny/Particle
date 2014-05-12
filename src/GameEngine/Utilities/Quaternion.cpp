#include "Quaternion.h"

Quaternion::Quaternion()
:m_Scalar( 1. ),
 m_Vector( 0., 0., 0. )
{

}
   
Quaternion::Quaternion( const Quaternion& q )
:m_Scalar( q.m_Scalar ),
 m_Vector( q.m_Vector )
{

}

Quaternion::Quaternion( double _s, double _vi, double _vj, double _vk )
:m_Scalar( _s ),
 m_Vector( _vi, _vj, _vk )
{

}

Quaternion::Quaternion( double _s, const Vector & _v )
:m_Scalar( _s),
 m_Vector( _v )
{

}

double& Quaternion::re( void )
{
	return m_Scalar;
}
 
const double& Quaternion::re( void ) const
{
	return m_Scalar;
}

Vector& Quaternion::im( void )
{
	return m_Vector;
}
 
const Vector& Quaternion::im( void ) const
{
	return m_Vector;
}

Quaternion Quaternion::conj( void ) const
{
	return Quaternion(m_Scalar, -m_Vector);
}

void Quaternion::toMatrix( GLdouble Q[4][4] ) const
{
	Q[0][0] =    m_Scalar; Q[0][1] = -m_Vector[0]; Q[0][2] = -m_Vector[1]; Q[0][3] = -m_Vector[2];
	Q[1][0] = m_Vector[0]; Q[1][1] =     m_Scalar; Q[1][2] = -m_Vector[2]; Q[1][3] =  m_Vector[1];
	Q[2][0] = m_Vector[1]; Q[2][1] =  m_Vector[2]; Q[2][2] =     m_Scalar; Q[2][3] = -m_Vector[0];
	Q[3][0] = m_Vector[2]; Q[3][1] = -m_Vector[1]; Q[3][2] =  m_Vector[0]; Q[3][3] =     m_Scalar;
}

Vector Quaternion::rotateVector(Vector & _v)
{
	return ((*this) * Quaternion(0, _v) * this->conj()).im();
}

double Quaternion::getAngle() const
{
	return acos(m_Scalar) * 2;
}

Vector Quaternion::getVector() const
{
	return m_Vector / sin(getAngle() / 2);
}

double & Quaternion::operator [] ( int index )
{
	return ( &m_Scalar )[ index ];
}

Quaternion Quaternion::operator + ( Quaternion const & q ) const
{
	return Quaternion( m_Scalar+q.m_Scalar, m_Vector+q.m_Vector );
}

Quaternion & Quaternion::operator+=( const Quaternion& q )
{
	m_Scalar += q.m_Scalar;
	m_Vector += q.m_Vector;
	return (*this);
}

Quaternion Quaternion::operator - () const
{
	return Quaternion( -m_Scalar, -m_Vector );
}

Quaternion Quaternion::operator - ( const Quaternion& q ) const
{
	return Quaternion( m_Scalar-q.m_Scalar, m_Vector-q.m_Vector );
}

Quaternion & Quaternion::operator -= ( const Quaternion& q )
{
	m_Scalar -= q.m_Scalar;
	m_Vector -= q.m_Vector;
	return (*this);
}

Quaternion Quaternion::operator*( double c ) const
{
	return Quaternion( m_Scalar*c, m_Vector*c );
}

Quaternion & Quaternion::operator*=( double c )
{
	m_Scalar *= c;
	m_Vector *= c;
	return (*this);
}

Quaternion Quaternion::operator/( double c ) const
{
	return Quaternion( m_Scalar/c, m_Vector/c );
}

Quaternion & Quaternion::operator/=( double c )
{
	m_Scalar /= c;
	m_Vector /= c;
	return (*this);
}

Quaternion Quaternion::operator*( const Quaternion& q ) const
{
	const double & m_Scalar1( m_Scalar );
	const double & m_Scalar2( q.m_Scalar );
	const Vector & m_Vector1( m_Vector );
	const Vector & m_Vector2( q.m_Vector );

	return Quaternion( m_Scalar1*m_Scalar2 - dot(m_Vector1,m_Vector2), m_Vector2*m_Scalar1 + m_Vector1*m_Scalar2 + cross(m_Vector1,m_Vector2) );
}

Quaternion & Quaternion::operator*=( const Quaternion& q )
{
	*this = ( *this * q );
	return (*this);
}

void glRotated(Quaternion & _q)
{
	glRotated(_q.getAngle() * 180/ M_PI, _q.getVector()[0], _q.getVector()[1], _q.getVector()[2]);
}
