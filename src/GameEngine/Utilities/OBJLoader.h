#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__

#include "../../GLHeader.h"
#include <string>
#include <vector>
#include <fstream>

class OBJLoader
{
	public:
		
		// Singleton.
		static OBJLoader & getInstance()
		{
			static OBJLoader instance;
			return instance;
		}

		// Initialize the obj loader
		void initialize(std::string _runDir);

		// Load the obj file. Return the number in display list.
		int loadOBJ(std::string const & _filename);

	private:

		// Constructor
		OBJLoader();

		// Destructor
		~OBJLoader();

		// Prevent any external implementaion
		OBJLoader(OBJLoader const &);
		void operator = (OBJLoader const &);

		// Restore the current running directory
		std::string m_RunDir;
};

struct coordinate
{
	float x, y, z;
	coordinate(float a, float b, float c) : x(a), y(b), z(c) {};
};

//for faces,  it can contain triangles and quads as well,  the four variable contain which is that
struct face
{
	int facenum;
	bool four;
	int faces[4];
	
	face(int facen, int f1, int f2, int f3) : facenum(facen)
	{
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		four=false;
	}

	face(int facen, int f1, int f2, int f3, int f4) : facenum(facen)
	{
		faces[0]=f1;
		faces[1]=f2;
		faces[2]=f3;
		faces[3]=f4;
		four=true;
	}
};

#endif
