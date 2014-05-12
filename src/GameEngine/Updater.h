#ifndef __UPDATER_H__
#define __UPDATER_H__

#include "../IDimension.h"

class Updater : public IDimension
{
	public:

		Updater();

		~Updater();

		virtual void Update(double dt);
};

#endif
