#ifndef __INFODISPLAYER_H__
#define __INFODISPLAYER_H__

#include <string>
#include "../../GLHeader.h"

using namespace std;

class InfoDisplayer
{
public:

	// Singleton.
	static InfoDisplayer & getInstance()
	{
		static InfoDisplayer instance;
		return instance;
	}

	// Display a string at position
	void renderInfo(int _position, string const & _str);

private:

	// Constructor
	InfoDisplayer();
	
	// Prevent any external implementaion
	InfoDisplayer(InfoDisplayer const &);
	void operator = (InfoDisplayer const &);

};

#endif
