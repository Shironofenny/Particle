#include "XMLParser.h"

XMLParser :: XMLParser ()
{
	m_Document = NULL;
	m_Buffer = NULL;
}

XMLParser :: ~XMLParser ()
{
	releaseXMLFile();
}

void XMLParser::initialize(std::string _runDir)
{
	unsigned addtionPath = _runDir.find_last_of('/');
	m_RunDir = _runDir.substr(0, addtionPath+1);
}

xml_node <> * XMLParser::parseXMLFile(string _filename)
{
	m_Document = new xml_document <> ();

	m_Infile.open((m_RunDir+_filename).c_str());
	if(!m_Infile.is_open())
	{
		cout<<strerror(errno)<<endl;
	}
	
	m_Buffer = new vector <char> ((istreambuf_iterator<char>(m_Infile)), istreambuf_iterator<char>());
	m_Buffer->push_back('\0');

	m_Document->parse<0>(&(*m_Buffer)[0]);
	
	m_Infile.close();
	
	return m_Document->first_node("AniConfig");
}

void XMLParser::releaseXMLFile()
{
	delete m_Document;
	delete m_Buffer;
	m_Document = NULL;
	m_Buffer = NULL;
	m_Infile.clear();
}
		
vector <char> * & XMLParser::getBuffer()
{
	return m_Buffer;
}

xml_document <> * & XMLParser::getDocument()
{
	return m_Document;
}

float str2num(char const * _str)
{
	stringstream ss;
	ss<<_str;
	float num;
	ss>>num;
	return num;
}

char const * num2str(float _num)
{
	stringstream ss;
	ss<<_num;
	string str;
	ss>>str;
	return str.c_str();
}
