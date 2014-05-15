#include "ParticleProperty.h"

ParticleProperty::ParticleProperty()
{

}

ParticleProperty::~ParticleProperty()
{

}
	
void ParticleProperty::getProperty(float _timeRatio, GLfloat color[4], Vector & scale, float & p)
{
	// Sanity check
	if(_timeRatio > 1.0 || _timeRatio < 0.0)
	{
		cout<<"[feinfo] Error : Input time ratio must between [0.0, 1.0]."<<endl;
		return;
	}

	// As data size is relatively small, use linear search
	int keyFrame1 = 0, keyFrame2 = 0;
	
	if(_timeRatio >= m_TimeRatio[m_TimeRatio.size() - 1])
	{
		keyFrame1 = m_TimeRatio.size() - 1;
		keyFrame2 = -1;
	}
	else if(_timeRatio <= m_TimeRatio[0])
	{
		keyFrame1 = -1;
		keyFrame2 = 0;
	}
	else
	{
		for(vector<float>::size_type i = 1; i < m_TimeRatio.size(); i++)
		{
			if(_timeRatio < m_TimeRatio[i])
			{
				keyFrame1 = i-1;
				keyFrame2 = i;
				break;
			}
		}
	}

	// Get RGBA color
	if(keyFrame2 == -1)
	{
		color[0] = m_RGB.back()[0];
		color[1] = m_RGB.back()[1];
		color[2] = m_RGB.back()[2];
		color[3] = m_Alpha.back();

		scale = m_Scale.back();
		p = m_Pressure.back();
	}
	else if(keyFrame1 == -1)
	{
		color[0] = m_RGB.front()[0];
		color[1] = m_RGB.front()[1];
		color[2] = m_RGB.front()[2];
		color[3] = m_Alpha.front();

		scale = m_Scale.front();
		p = m_Pressure.front();
	}
	else
	{
		// Linear interpolation
		float w1, w2;
		w1 = m_TimeRatio[keyFrame2] - _timeRatio;
		w2 = _timeRatio - m_TimeRatio[keyFrame1];

		// Normalize w1, w2
		float total = w1 + w2;
		w1 = w1 / total;
		w2 = w2 / total;
		
		color[0] = m_RGB[keyFrame1][0] * w1 + m_RGB[keyFrame2][0] * w2;
		color[1] = m_RGB[keyFrame1][1] * w1 + m_RGB[keyFrame2][1] * w2;
		color[2] = m_RGB[keyFrame1][2] * w1 + m_RGB[keyFrame2][2] * w2;
		color[3] = m_Alpha[keyFrame1] * w1 + m_Alpha[keyFrame2] * w2;

		scale = m_Scale[keyFrame1] * w1 + m_Scale[keyFrame2] * w2;
		p = m_Pressure[keyFrame1] * w1 + m_Pressure[keyFrame2] * w2;
	}
}

void ParticleProperty::addFrame(float _tr, float _r, float _g, float _b, float _a,\
		float _sx, float _sy, float _sz, float _p)
{
	m_TimeRatio.push_back(_tr);
	m_RGB.push_back(Vector(_r, _g, _b));
	m_Alpha.push_back(_a);
	m_Scale.push_back(Vector(_sx, _sy, _sz));
	m_Pressure.push_back(_p);
}

void ParticleProperty::initialize()
{
	// Validity check
	
	// Check the order of all the time ratios
	float tPrevious, tNow;

	for(vector<float>::size_type i = 1; i < m_TimeRatio.size(); i++)
	{
		tPrevious = m_TimeRatio[i-1];
		tNow = m_TimeRatio[i];
		if (tPrevious > tNow)
		{
			cout<<"[feinfo] Error : Time ratio must be a increasing sequence."<<endl;
			cout<<"[feinfo] Please check your configuration of particle system"<<endl;
			exit(0);
		}
		if (tNow < 0.0 || tNow > 1.0)
		{
			cout<<"[feinfo] Error : Time ratio must be in [0.0, 1.0]."<<endl;
			cout<<"[feinfo] Please check your configuration of particle system"<<endl;
			exit(0);
		}
	}

	// Check starting point
	if(m_TimeRatio[0] <= 0.0)
	{
		cout<<"[feinfo] Error : Time ratio must be in [0.0, 1.0]."<<endl;
		cout<<"[feinfo] Please check your configuration of particle system"<<endl;
		exit(0);
	}
}
