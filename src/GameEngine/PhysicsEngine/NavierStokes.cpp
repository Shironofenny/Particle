#include "NavierStokes.h"

NavierStokes::NavierStokes()
{
}

NavierStokes::~NavierStokes()
{
}

void NavierStokes::initialize(Vector _scale, Vector _deviation, float _spacing)
{
	m_FrameScale = _scale;

	m_Pressure.resize(getSize());
	m_VelocityX.resize(getSize());
	m_VelocityY.resize(getSize());
	m_VelocityZ.resize(getSize());

	m_VelocityX0.resize(getSize());
	m_VelocityY0.resize(getSize());
	m_VelocityZ0.resize(getSize());
	m_VDiv.resize(getSize());

	m_VelocityX.setZero();
	m_VelocityY.setZero();
	m_VelocityZ.setZero();
	m_Pressure.setZero();
	m_VDiv.setZero();

	m_IsVelocityInitialized = false;
	m_Bouyancy = 1.5;
	m_Diffusivity = 5.0;
	m_Viscousity = 10.0;

	m_Spacing = _spacing;
	m_OneOverSpacing = 1. / m_Spacing;

	m_Deviation = _deviation;

	m_IterationTime = 10;

	m_Region.getLeftNearBottom() = Vector(- (int)m_FrameScale[0] / 2,\
		 	- (int)m_FrameScale[1] / 2, - (int)m_FrameScale[2] / 2) * m_Spacing + m_Deviation;
	m_Region.getRightFarTop() = Vector((int)m_FrameScale[0] / 2 + (int)m_FrameScale[0] % 2,\
		 	(int)m_FrameScale[1] / 2 + (int)m_FrameScale[1] % 2,\
			(int)m_FrameScale[2] / 2 + (int)m_FrameScale[2] % 2) * m_Spacing + m_Deviation;
}
	
void NavierStokes::process(vector<Particle> & _particles, Vector & _source, double dt)
{
	// First compute all the physics quantities in grid
	setVelocity(_source);
	
	diffuse(m_VelocityX0, m_VelocityX, m_Viscousity, 1, dt);
	diffuse(m_VelocityY0, m_VelocityY, m_Viscousity, 2, dt);
	diffuse(m_VelocityZ0, m_VelocityZ, m_Viscousity, 3, dt);

	removeCurl(m_VelocityX0, m_VelocityY0, m_VelocityZ0);

	advect(m_VelocityX, m_VelocityX0, m_VelocityX0, m_VelocityY0, m_VelocityZ0, 1, dt);
	advect(m_VelocityY, m_VelocityY0, m_VelocityX0, m_VelocityY0, m_VelocityZ0, 2, dt);
	advect(m_VelocityZ, m_VelocityZ0, m_VelocityX0, m_VelocityY0, m_VelocityZ0, 3, dt);

	removeCurl(m_VelocityX, m_VelocityY, m_VelocityZ);

	setPressure(_particles);
	addPressure(dt);

	assignVelocity(_particles);
}

void NavierStokes::setPressure(vector<Particle> & _particles)
{
	int x, y, z;
	bool isOut;
	m_Pressure.setZero();
	for(vector<Particle>::size_type i = 0; i < _particles.size(); i++)
	{
		getIndiceFromPosition(_particles[i].getPosition(), x, y, z, isOut);
		if (!isOut) m_Pressure[getIndice(x, y, z)] += _particles[i].getPressure();
	}
}

void NavierStokes::setVelocity(Vector & _source)
{
	int x, y, z;
	bool isOut;
	getIndiceFromPosition(_source, x, y, z, isOut);
	if(! m_IsVelocityInitialized)
	{
		// Initialize with bouyancy
		m_VelocityY.setConstant(m_Bouyancy);

		// Set the source velocity
		m_VelocityX[getIndice(x-1, y, z)] += -1.;
		m_VelocityX[getIndice(x+1, y, z)] += 1.;

		m_VelocityY[getIndice(x, y-1, z)] += -1.;
		m_VelocityY[getIndice(x, y+1, z)] += 1.;

		m_VelocityZ[getIndice(x, y, z-1)] += -1.;
		m_VelocityZ[getIndice(x, y, z+1)] += 1.;

		// Set flag
		m_IsVelocityInitialized = true;
	}
	else
	{
		m_VelocityX[getIndice(x, y, z)] = 0.;
		m_VelocityY[getIndice(x, y, z)] = m_Bouyancy;
		m_VelocityZ[getIndice(x, y, z)] = 0.;
		
		m_VelocityX[getIndice(x-1, y, z)] = -1.;
		m_VelocityX[getIndice(x+1, y, z)] = 1.;

		m_VelocityY[getIndice(x, y-1, z)] = -1. + m_Bouyancy;
		m_VelocityY[getIndice(x, y+1, z)] = 1. + m_Bouyancy;
		
		m_VelocityZ[getIndice(x, y, z-1)] = -1.;
		m_VelocityZ[getIndice(x, y, z+1)] = 1.;
	}
}

void NavierStokes::assignVelocity(vector<Particle> & _particles)
{
	int x, y, z;
	bool isOut;
	for(vector<Particle>::size_type i = 0; i < _particles.size(); i++)
	{
		getIndiceFromPosition(_particles[i].getPosition(), x, y, z, isOut);
		if (!isOut)
		{
			Vector & velocity = _particles[i].getVelocity();
			double & mass = _particles[i].getMass();
			velocity[0] = m_VelocityX[getIndice(x, y, z)] / mass;
			velocity[1] = m_VelocityY[getIndice(x, y, z)] / mass;
			velocity[2] = m_VelocityZ[getIndice(x, y, z)] / mass;
		}
	}
}
	
void NavierStokes::diffuse(Eigen::VectorXf & _newValue, Eigen::VectorXf & _oldValue,\
		float _coeff, int _type, double dt)
{
	float c = dt * _coeff * m_OneOverSpacing * m_OneOverSpacing * m_OneOverSpacing;
	for (int l = 0; l < m_IterationTime; l++)
	{
		for (int i = 1; i < m_FrameScale[0] - 1; i++)
		{
			for (int j = 1; j < m_FrameScale[1] - 1; j++)
			{
				for (int k = 1; k < m_FrameScale[2] - 1; k++)
				{
					_newValue[getIndice(i, j, k)] = (_oldValue[getIndice(i, j, k)]\
						 + c * (_oldValue[getIndice(i-1, j, k)] + _oldValue[getIndice(i+1, j, k)]\
							 		+ _oldValue[getIndice(i, j-1, k)] + _oldValue[getIndice(i, j+1, k)]\
									+ _oldValue[getIndice(i, j, k-1)] + _oldValue[getIndice(i, j, k+1)]))/(1+6*c);
				}
			}
		}
		setBoundary(_newValue, _type);
	}
}

void NavierStokes::advect(Eigen::VectorXf & _newValue, Eigen::VectorXf & _oldValue,\
	 	Eigen::VectorXf & _vx, Eigen::VectorXf & _vy, Eigen::VectorXf & _vz,\
		int _type, double dt)
{
	// Inverse advection
	float c = dt * m_OneOverSpacing;
	for (int i = 1; i < m_FrameScale[0] - 1; i++)
	{
		for (int j = 1; j < m_FrameScale[1] - 1; j++)
		{
			for (int k = 1; k < m_FrameScale[2] - 1; k++)
			{
				// Compute the backwards grid
				float x0 = i - c * _vx[getIndice(i, j, k)];
				if(x0 < 0.5) x0 = 0.5;
				if(x0 > m_FrameScale[0] - 1.5) x0 = m_FrameScale[0] - 1.5;
				int i0 = (int) x0;
				int i1 = i0 + 1;
				float wx1 = x0 - i0;
				float wx0 = 1 - wx1;

				float y0 = j - c * _vy[getIndice(i, j, k)];
				if(y0 < 0.5) y0 = 0.5;
				if(y0 > m_FrameScale[1] - 1.5) y0 = m_FrameScale[1] - 1.5;
				int j0 = (int) y0;
				int j1 = j0 + 1;
				float wy1 = y0 - j0;
				float wy0 = 1 - wy1;

				float z0 = k - c * _vz[getIndice(i, j, k)];
				if(z0 < 0.5) z0 = 0.5;
				if(z0 > m_FrameScale[2] - 1.5) z0 = m_FrameScale[2] - 1.5;
				int k0 = (int) z0;
				int k1 = k0 + 1;
				float wz1 = z0 - k0;
				float wz0 = 1 - wz1;

				_newValue[getIndice(i, j, k)] =\
						 wx0 * (wy0 * (wz0 * _oldValue[getIndice(i0, j0, k0)]\
									+ wz1 * _oldValue[getIndice(i0, j0, k1)])\
								 	+ wy1 * (wz0 * _oldValue[getIndice(i0, j1, k0)]\
									+ wz1 * _oldValue[getIndice(i0, j1, k1)]))\
					 + wx1 * (wy0 * (wz0 * _oldValue[getIndice(i1, j0, k0)]\
									+ wz1 * _oldValue[getIndice(i1, j0, k1)])\
								 	+ wy1 * (wz0 * _oldValue[getIndice(i1, j1, k0)]\
									+ wz1 * _oldValue[getIndice(i1, j1, k1)]));
						
			}
		}
		setBoundary(_newValue, _type);
	}
}

void NavierStokes::addPressure(double dt)
{
	for (int i = 1; i < m_FrameScale[0] - 1; i++)
	{
		for (int j = 1; j < m_FrameScale[1] - 1; j++)
		{
			for (int k = 1; k < m_FrameScale[2] - 1; k++)
			{
				m_VelocityX[getIndice(i, j, k)] += 0.5 * m_OneOverSpacing * dt\
													 * (m_Pressure[getIndice(i+1, j, k)] - m_Pressure[getIndice(i-1, j, k)]);
				m_VelocityY[getIndice(i, j, k)] += 0.5 * m_OneOverSpacing * dt\
													 * (m_Pressure[getIndice(i, j+1, k)] - m_Pressure[getIndice(i, j-1, k)]);
				m_VelocityZ[getIndice(i, j, k)] += 0.5 * m_OneOverSpacing * dt\
													 * (m_Pressure[getIndice(i, j, k+1)] - m_Pressure[getIndice(i, j, k-1)]);
			}
		}
	}
}

void NavierStokes::removeCurl(Eigen::VectorXf & _vx, Eigen::VectorXf & _vy, Eigen::VectorXf & _vz)
{
	m_Pressure.setZero();
	for (int i = 1; i < m_FrameScale[0] - 1; i++)
	{
		for (int j = 1; j < m_FrameScale[1] - 1; j++)
		{
			for (int k = 1; k < m_FrameScale[2] - 1; k++)
			{
				m_VDiv[getIndice(i, j, k)] = - 0.5 * m_Spacing *\
										 (_vx[getIndice(i+1, j, k)] - _vx[getIndice(i-1, j, k)]\
										+ _vy[getIndice(i, j+1, k)] - _vy[getIndice(i, j-1, k)]\
										+ _vz[getIndice(i, j, k+1)] - _vz[getIndice(i, j, k-1)]);
			}
		}
	}

	setBoundary(m_VDiv, 0);
	setBoundary(m_Pressure, 0);

	for (int l = 0; l < m_IterationTime; l++)
	{
		for (int i = 1; i < m_FrameScale[0] - 1; i++)
		{
			for (int j = 1; j < m_FrameScale[1] - 1; j++)
			{
				for (int k = 1; k < m_FrameScale[2] - 1; k++)
				{
					m_Pressure[getIndice(i, j, k)] = 1. / 6 * (m_VDiv[getIndice(i, j, k)]\
							+ m_Pressure[getIndice(i-1, j, k)] + m_Pressure[getIndice(i+1, j, k)]\
							+ m_Pressure[getIndice(i, j-1, k)] + m_Pressure[getIndice(i, j+1, k)]\
							+ m_Pressure[getIndice(i, j, k-1)] + m_Pressure[getIndice(i, j, k+1)]);
				}
			}
		}
		setBoundary(m_Pressure, 0);
	}

	for (int i = 1; i < m_FrameScale[0] - 1; i++)
	{
		for (int j = 1; j < m_FrameScale[1] - 1; j++)
		{
			for (int k = 1; k < m_FrameScale[2] - 1; k++)
			{
				_vx[getIndice(i, j, k)] -= 0.5 * m_OneOverSpacing\
													 * (m_Pressure[getIndice(i+1, j, k)] - m_Pressure[getIndice(i-1, j, k)]);
				_vy[getIndice(i, j, k)] -= 0.5 * m_OneOverSpacing\
													 * (m_Pressure[getIndice(i, j+1, k)] - m_Pressure[getIndice(i, j-1, k)]);
				_vz[getIndice(i, j, k)] -= 0.5 * m_OneOverSpacing\
													 * (m_Pressure[getIndice(i, j, k+1)] - m_Pressure[getIndice(i, j, k-1)]);
			}
		}
	}

	setBoundary(_vx, 1);
	setBoundary(_vy, 2);
	setBoundary(_vz, 3);
}
void NavierStokes::setBoundary(Eigen::VectorXf & _value, int type)
{
	// Set face boundary condition to no penetration
	for (int j = 1; j < m_FrameScale[1] - 1; j++)
	{
		for (int k = 1; k < m_FrameScale[2] - 1; k++)
		{
			_value[getIndice(0, j, k)] = type == 1 ? \
							-_value[getIndice(1, j, k)] : _value[getIndice(1, j, k)];
			_value[getIndice(m_FrameScale[0] - 1, j, k)] = type == 3 ? \
			 				-_value[getIndice(m_FrameScale[2] - 1, j, k)] : \
			 				_value[getIndice(m_FrameScale[2] - 1, j, k)];
		}
	}

	for (int i = 1; i < m_FrameScale[0] - 1; i++)
	{
		for (int k = 1; k < m_FrameScale[2] - 1; k++)
		{
			_value[getIndice(i, 0, k)] = type == 2 ? \
							-_value[getIndice(i, 1, k)] : _value[getIndice(i, 1, k)];
			_value[getIndice(i, m_FrameScale[1] - 1, k)] = type == 3 ? \
			 				-_value[getIndice(i, m_FrameScale[1] - 1, k)] : \
			 				_value[getIndice(i, m_FrameScale[1] - 1, k)];
		}
	}

	for (int i = 1; i < m_FrameScale[0] - 1; i++)
	{
		for (int j = 1; j < m_FrameScale[1] - 1; j++)
		{
			_value[getIndice(i, j, 0)] = type == 3 ? \
							-_value[getIndice(i, j, 1)] : _value[getIndice(i, j, 1)];
			_value[getIndice(i, j, m_FrameScale[2] - 1)] = type == 3 ? \
			 				-_value[getIndice(i, j, m_FrameScale[2] - 1)] : \
			 				_value[getIndice(i, j, m_FrameScale[2] - 1)];
		}
	}

	// Set corner boundary conditions
	_value[getIndice(0, 0, 0)] = 1. / 3 * (_value[getIndice(0, 0, 1)]\
		 	+ _value[getIndice(0, 1, 0)] + _value[getIndice(1, 0, 0)]);

	_value[getIndice(m_FrameScale[0] - 1, 0, 0)] = 1. / 3 * (_value[getIndice(m_FrameScale[0] - 1, 0, 1)]\
		 	+ _value[getIndice(m_FrameScale[0] - 1, 1, 0)] + _value[getIndice(m_FrameScale[0] - 2, 0, 0)]);
	
	_value[getIndice(0, m_FrameScale[1] - 1, 0)] = 1. / 3 * (_value[getIndice(0, m_FrameScale[1] - 1, 1)]\
		 	+ _value[getIndice(1, m_FrameScale[1] - 1, 0)] + _value[getIndice(0, m_FrameScale[1] - 2, 0)]);
	
	_value[getIndice(0, 0, m_FrameScale[2] - 1)] = 1. / 3 * (_value[getIndice(0, 1, m_FrameScale[2] - 1)]\
		 	+ _value[getIndice(1, 0, m_FrameScale[2] - 1)] + _value[getIndice(0, 0, m_FrameScale[2] - 2)]);
	
	_value[getIndice(m_FrameScale[0] - 1, m_FrameScale[1] - 1, 0)] = 1. / 3 * \
			(_value[getIndice(m_FrameScale[0] - 1, m_FrameScale[1] - 1, 1)]\
		 	+ _value[getIndice(m_FrameScale[0] - 1, m_FrameScale[1] - 2, 0)]\
		 	+ _value[getIndice(m_FrameScale[0] - 2, m_FrameScale[1] - 1, 0)]);
	
	_value[getIndice(m_FrameScale[0] - 1, 0, m_FrameScale[2] - 1)] = 1. / 3 * \
			(_value[getIndice(m_FrameScale[0] - 1, 1, m_FrameScale[2] - 1)]\
		 	+ _value[getIndice(m_FrameScale[0] - 1, 0, m_FrameScale[2] - 2)]\
		 	+ _value[getIndice(m_FrameScale[0] - 2, 0, m_FrameScale[2] - 1)]);
	
	_value[getIndice(0, m_FrameScale[1] - 1, m_FrameScale[2] - 1)] = 1. / 3 * \
			(_value[getIndice(1, m_FrameScale[1] - 1, m_FrameScale[2] - 1)]\
		 	+ _value[getIndice(0, m_FrameScale[1] - 1, m_FrameScale[2] - 2)]\
		 	+ _value[getIndice(0, m_FrameScale[1] - 2, m_FrameScale[2] - 1)]);
	
	_value[getIndice(m_FrameScale[0] - 1, m_FrameScale[1] - 1, m_FrameScale[2] - 1)] = 1. / 3 * \
			(_value[getIndice(m_FrameScale[0] - 1, m_FrameScale[1] - 1, m_FrameScale[2] - 2)]\
		 	+ _value[getIndice(m_FrameScale[0] - 1, m_FrameScale[1] - 2, m_FrameScale[2] - 1)]\
		 	+ _value[getIndice(m_FrameScale[0] - 2, m_FrameScale[1] - 1, m_FrameScale[2] - 1)]);
}

int NavierStokes::getIndice(int x, int y, int z)
{
	int value = (m_FrameScale[0] * m_FrameScale[1] * z + m_FrameScale[0] * y + x);
	if (value >= getSize())
	{
		cout<<"Problem occurs for"<<x<<'\t'<<y<<'\t'<<z<<endl;
		exit(0);
	}
	return value;
}

int NavierStokes::getSize()
{
	return m_FrameScale[0] * m_FrameScale[1] * m_FrameScale[2];
}
	
void NavierStokes::getIndiceFromPosition(Vector & _position, int & x, int & y, int & z, \
		bool & isOut)
{
	x = (_position[0] - m_Deviation[0]) * m_OneOverSpacing + m_FrameScale[0] / 2;
	y = (_position[1] - m_Deviation[1]) * m_OneOverSpacing + m_FrameScale[1] / 2;
	z = (_position[2] - m_Deviation[2]) * m_OneOverSpacing + m_FrameScale[2] / 2;

	if (x >= m_FrameScale[0] || x <= 0 || y >= m_FrameScale[1] || y <= 0 || z >= m_FrameScale[2] || z <= 0)
	{
		isOut = true;
	}
	else isOut = false;
}

void NavierStokes::renderRegion()
{
	m_Region.render();
}
