#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include <RapidXML/rapidxml.hpp>
#include <RapidXML/rapidxml_utils.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "ConstantHandler.h"

using namespace rapidxml;
using namespace std;

class XMLParser
{
	public:
		
		// Singleton.
		static XMLParser & getInstance()
		{
			static XMLParser instance;
			return instance;
		}

		// Initialize the obj loader
		void initialize(string _runDir);

		// Parse the xml file and return the node of xml file
		xml_node <>  * parseXMLFile(string _filename);

		// Release currently loaded xml file
		void releaseXMLFile();

		// Get the buffer of the file
		vector <char> * & getBuffer();
		vector <char> const * & getBuffer() const;

		// Get the document of the file
		xml_document <> * & getDocument();
		xml_document <> const * & getDocument() const;

	private:

		// Constructor
		XMLParser();

		// Destructor
		~XMLParser();

		// Prevent any external implementaion
		XMLParser(XMLParser const &);
		void operator = (XMLParser const &);

		// Restore the current running directory
		std::string m_RunDir;

		// Restore the current using xml file until destroy
		xml_document <> * m_Document;

		// Restore the current buffer untile destroy
		vector <char> * m_Buffer;

		// Restore the file used to open xml
		std::ifstream m_Infile;
};

// Data conversion function
float str2num(char const * _str);
char const * num2str(float _num); 

#endif
