#include "Region.h"

Region::Region()
{

}

Region::~Region()
{

}
Vector & Region::getLeftNearBottom()
{
	return m_LeftNearBottom;
}
	
Vector const & Region::getLeftNearBottom() const
{
	return m_LeftNearBottom;
}

Vector & Region::getRightFarTop()
{
	return m_RightFarTop;
}
	
Vector const & Region::getRightFarTop() const
{
	return m_RightFarTop;
}

void Region::render()
{
	Vector LNT(m_LeftNearBottom[0], m_LeftNearBottom[1], m_RightFarTop[2]);
	Vector LFT(m_LeftNearBottom[0], m_RightFarTop[1], m_RightFarTop[2]);
	Vector LFB(m_LeftNearBottom[0], m_RightFarTop[1], m_LeftNearBottom[2]);
	Vector RFB(m_RightFarTop[0], m_RightFarTop[1], m_LeftNearBottom[2]);
	Vector RNB(m_RightFarTop[0], m_LeftNearBottom[1], m_LeftNearBottom[2]);
	Vector RNT(m_RightFarTop[0], m_LeftNearBottom[1], m_RightFarTop[2]);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	{
		glVertex3v(m_LeftNearBottom);
		glVertex3v(LNT);
		glVertex3v(LNT);
		glVertex3v(LFT);
		glVertex3v(LFT);
		glVertex3v(LFB);
		glVertex3v(LFB);
		glVertex3v(m_LeftNearBottom);
		glVertex3v(m_LeftNearBottom);
		glVertex3v(RNB);
		glVertex3v(LNT);
		glVertex3v(RNT);
		glVertex3v(LFB);
		glVertex3v(RFB);
		glVertex3v(LFT);
		glVertex3v(m_RightFarTop);
		glVertex3v(m_RightFarTop);
		glVertex3v(RNT);
		glVertex3v(RNT);
		glVertex3v(RNB);
		glVertex3v(RNB);
		glVertex3v(RFB);
		glVertex3v(RFB);
		glVertex3v(m_RightFarTop);
	}
	glEnd();
}
