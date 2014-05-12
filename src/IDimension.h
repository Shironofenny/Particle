#ifndef __I2D_H__
#define __I2D_H__

// Interface for 2D application
class IDimension
{
	public:

		IDimension() {}

		virtual ~IDimension() {}

		virtual int getDimension() const { return -1; }
};

#endif
