#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include "../../GLHeader.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <png.h>

class TextureLoader
{
	public:
		
		// Singleton.
		static TextureLoader & getInstance()
		{
			static TextureLoader instance;
			return instance;
		}

		void initialize(std::string _runDir);

		// Load the texture file. Return the number in texture list.
		GLuint loadTexture(std::string const & _filename, int & width, int & height);

	private:

		// Constructor
		TextureLoader();

		// Destructor
		~TextureLoader();

		// Prevent any external implementaion
		TextureLoader(TextureLoader const &);
		void operator = (TextureLoader const &);

		// Restore the current running directory
		std::string m_RunDir;
};

#endif
