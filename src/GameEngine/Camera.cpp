#include "Camera.h"
#include <iostream>

Camera::Camera():
	m_Position(), 
	m_Rotation(1., 0., 0., 0.), 
	m_CameraDirectionX(1., 0., 0.), 
	m_CameraDirectionY(0., 1., 0.), 
	m_CameraDirectionZ(0., 0., -1.) 
	//m_RotationY(0., 0., 1., 0.)
{
	m_RotationX = 0.0;
	m_RotationY = 0.0;
	m_AccumulateX = 0;
	m_AccumulateY = 0;
}

Camera::Camera(Vector const & _initPos):
	m_Position(_initPos), 
	m_Rotation(1., 0., 0., 0.), 
	m_CameraDirectionX(1., 0., 0.), 
	m_CameraDirectionY(0., 1., 0.), 
	m_CameraDirectionZ(0., 0., -1.)
	//m_RotationY(0., 0., 1., 0.)
{
	m_RotationX = 0.0;
	m_RotationY = 0.0;
	m_AccumulateX = 0;
	m_AccumulateY = 0;
}

Camera::Camera(double const & _initRotX, double const & _initRotY):
	m_Position(), 
	m_RotationX(_initRotX),
 	m_RotationY(_initRotY), 
	m_Rotation(1., 0., 0., 0.), 
	m_CameraDirectionX(1., 0., 0.), 
	m_CameraDirectionY(0., 1., 0.), 
	m_CameraDirectionZ(0., 0., -1.)
{
	m_AccumulateX = 0;
	m_AccumulateY = 0;
}

Camera::Camera(Vector const & _initPos, double const & _initRotX, double const & _initRotY):
	m_Position(_initPos), 
	m_RotationX(_initRotX),
 	m_RotationY(_initRotY),
	m_Rotation(1., 0., 0., 0.), 
	m_CameraDirectionX(1., 0., 0.), 
	m_CameraDirectionY(0., 1., 0.), 
	m_CameraDirectionZ(0., 0., -1.)
{
	m_AccumulateX = 0;
	m_AccumulateY = 0;
}

Camera::~Camera()
{

}

void Camera::update(double dt)
{
	pointwiseRotation(dt);
}

void Camera::pointwiseRotation(double dt)
{
	// Rotate the base directions using previous rotation
	m_CameraDirectionX = ((m_Rotation*Quaternion(0., 1., 0., 0.))*m_Rotation.conj()).im();
	m_CameraDirectionY = ((m_Rotation*Quaternion(0., 0., 1., 0.))*m_Rotation.conj()).im();
	m_CameraDirectionZ = ((m_Rotation*Quaternion(0., 0., 0., 1.))*m_Rotation.conj()).im();

	// Make sure that they are normalized
	m_CameraDirectionX.normalize();
	m_CameraDirectionY.normalize();
	m_CameraDirectionZ.normalize();

	// Translate camera
	if(Keyboard::getInstance().isKeyDown('w'))
		m_Position += m_CameraDirectionY * ConstantHandler::getInstance().cameraSpeed;
	if(Keyboard::getInstance().isKeyDown('s'))
		m_Position -= m_CameraDirectionY * ConstantHandler::getInstance().cameraSpeed;
	if(Keyboard::getInstance().isKeyDown('a'))
		m_Position -= m_CameraDirectionX * ConstantHandler::getInstance().cameraSpeed;
	if(Keyboard::getInstance().isKeyDown('d'))
		m_Position += m_CameraDirectionX * ConstantHandler::getInstance().cameraSpeed;

	// Extra Z direction rotation if applicable
	if(Keyboard::getInstance().isKeyDown('e'))
	{
		Quaternion dqz = Quaternion(cos(ConstantHandler::getInstance().cameraRotateZ / 2), \
										m_CameraDirectionZ * sin(ConstantHandler::getInstance().cameraRotateZ / 2));
		m_Rotation = dqz * m_Rotation;
	}
	if(Keyboard::getInstance().isKeyDown('q'))
	{
		Quaternion dqz = Quaternion(cos(-ConstantHandler::getInstance().cameraRotateZ / 2), \
										m_CameraDirectionZ * sin(-ConstantHandler::getInstance().cameraRotateZ / 2));
		m_Rotation = dqz * m_Rotation;
	}

	// Calculate the difference in x and y direction
	double diffx = 0;
	double diffy = 0;
	
	if (Mouse::getInstance().isMouseRightDown())
	{
		diffx = (double) Mouse::getInstance().getDifferenceX() / ConstantHandler::getInstance().windowSizeY;
		diffy = -(double) Mouse::getInstance().getDifferenceY() / ConstantHandler::getInstance().windowSizeY;
	}

	// If there is no move, stops here.
	if (diffx == 0 && diffy == 0) return;
	
	// Calculate the exact mouse move vector
	Vector mouseMove = m_CameraDirectionX * diffx + m_CameraDirectionY * diffy;

	// Calculate the direction that the rotation is about
	Vector rotateCenter = -cross(m_CameraDirectionZ, mouseMove);

	rotateCenter.normalize();

	// Calculate the rotation angle
	double angle = atan(sqrt(diffx * diffx + diffy * diffy) / ConstantHandler::getInstance().virtualRotationRadius);

	// Assembly the quaternion
	Quaternion dq = Quaternion(cos(angle/2), rotateCenter * sin(angle/2));

	// Be Cautious about the order!
	m_Rotation = dq * m_Rotation;

	m_Position = (dq * Quaternion(0, m_Position) * dq.conj()).im();
}

void Camera::setup()
{
	glRotated(-m_Rotation.getAngle() * 180/ M_PI, m_Rotation.getVector()[0],\
		 				m_Rotation.getVector()[1], m_Rotation.getVector()[2]);

	glTranslatev((-m_Position));
}

void Camera::irrotate2D()
{
	glRotated(m_Rotation.getAngle() * 180/ M_PI, m_Rotation.getVector()[0],\
		 				m_Rotation.getVector()[1], m_Rotation.getVector()[2]);
}

void Camera::drawAxes() const
{
	glPushMatrix();

	glTranslatef(0., 0., -4);
		glColor3d(1., 1., 1.);
		glutSolidSphere(0.05, 20, 20);
		glColor3d(1., 0., 0.);
		glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(m_CameraDirectionX[0], m_CameraDirectionX[1], m_CameraDirectionX[2]);
		glEnd();
		glColor3d(0., 1., 0.);
		glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(m_CameraDirectionY[0], m_CameraDirectionY[1], m_CameraDirectionY[2]);
		glEnd();
		glColor3d(0., 0., 1.);
		glBegin(GL_LINES);
			glVertex3f(0., 0., 0.);
			glVertex3f(m_CameraDirectionZ[0], m_CameraDirectionZ[1], m_CameraDirectionZ[2]);
		glEnd();
	glPopMatrix();
}

Vector & Camera::getCameraPosition()
{
	return m_Position;
}

Vector const & Camera::getCameraPosition() const
{
	return m_Position;
}

Vector & Camera::getCameraCoordinateX()
{
	return m_CameraDirectionX;
}

Vector const & Camera::getCameraCoordinateX() const
{
	return m_CameraDirectionX;
}

Vector & Camera::getCameraCoordinateY()
{
	return m_CameraDirectionY;
}

Vector const & Camera::getCameraCoordinateY() const
{
	return m_CameraDirectionY;
}

Vector & Camera::getCameraCoordinateZ()
{
	return m_CameraDirectionZ;
}

Vector const & Camera::getCameraCoordinateZ() const
{
	return m_CameraDirectionZ;
}
