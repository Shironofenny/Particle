#ifndef __REGION_H__
#define __REGION_H__

#include "../Utilities/MathHeader.h"
#include "../../GLHeader.h"

class Region
{
public:

	// Constructor
	Region();

	// Destructor
	~Region();

	// Return the left near bottom corner
	Vector & getLeftNearBottom();
	Vector const & getLeftNearBottom() const;

	// Return the right far top corner
	Vector & getRightFarTop();
	Vector const & getRightFarTop() const;

	// Render the wireframe of the region
	void render();

protected:
	
	// The left near bottom corner
	Vector m_LeftNearBottom;

	// The right far top corner
	Vector m_RightFarTop;

};

#endif
