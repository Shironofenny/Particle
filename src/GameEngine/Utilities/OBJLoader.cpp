#include "OBJLoader.h"

#include <iostream>
#include <algorithm>

OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader()
{

}

void OBJLoader::initialize(std::string _runDir)
{
	unsigned addtionPath = _runDir.find_last_of('/');
	m_RunDir = _runDir.substr(0, addtionPath);
}

int OBJLoader::loadOBJ(std::string const & _filename)
{
	std::vector<std::string*> coord;        //read every single line of the obj file as a string
	std::vector<coordinate*> vertex;
	std::vector<face*> faces;
	std::vector<coordinate*> normals;       //normal vectors for every face
	std::ifstream in( (m_RunDir + _filename).c_str());     				//open the .obj file

	if(!in.is_open())       //if not opened,  exit with -1
	{
		std::cout << "Error: can't find obj file "<<m_RunDir<<_filename<< std::endl;
		return -1;
	}

	char buf[256];

	//read in every line to coord
	while(!in.eof())
	{
		in.getline(buf, 256);
		coord.push_back(new std::string(buf));
	}

	//go through all of the elements of coord,  and decide what kind of element is that
	for(int i=0;i<coord.size();i++)
	{
		if(coord[i]->c_str()[0]=='#')   //if it is a comment (the first character is #)
			continue;      								//we don't care about that
		else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ') //if vector
		{
			float tmpx, tmpy, tmpz;
			sscanf(coord[i]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz); 
			vertex.push_back(new coordinate(tmpx, tmpy, tmpz)); 
		}
		else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n')        //if normal vector
		{
			float tmpx, tmpy, tmpz;   //do the same thing
			sscanf(coord[i]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
			normals.push_back(new coordinate(tmpx, tmpy, tmpz));     
		}
		else if(coord[i]->c_str()[0]=='f')     //if face
		{
			int a, b, c, d, e;
			if(count(coord[i]->begin(), coord[i]->end(), ' ')==3) 
			{
				sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
				faces.push_back(new face(b, a, c, d)); 
			}else{
			sscanf(coord[i]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
			faces.push_back(new face(b, a, c, d, e));   
			}
		}
	}

	//raw
	int num;        //the id for the list
	num=glGenLists(1);      //generate a uniqe
	glNewList(num, GL_COMPILE);      //and create it

	for(int i=0;i<faces.size();i++)
	{
		if(faces[i]->four)      //if it's a quad draw a quad
		{
			glBegin(GL_QUADS);
				glNormal3f(normals[faces[i]->facenum-1]->x, normals[faces[i]->facenum-1]->y, normals[faces[i]->facenum-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x, vertex[faces[i]->faces[0]-1]->y, vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x, vertex[faces[i]->faces[1]-1]->y, vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x, vertex[faces[i]->faces[2]-1]->y, vertex[faces[i]->faces[2]-1]->z);
				glVertex3f(vertex[faces[i]->faces[3]-1]->x, vertex[faces[i]->faces[3]-1]->y, vertex[faces[i]->faces[3]-1]->z);
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLES);
				glNormal3f(normals[faces[i]->facenum-1]->x, normals[faces[i]->facenum-1]->y, normals[faces[i]->facenum-1]->z);
				glVertex3f(vertex[faces[i]->faces[0]-1]->x, vertex[faces[i]->faces[0]-1]->y, vertex[faces[i]->faces[0]-1]->z);
				glVertex3f(vertex[faces[i]->faces[1]-1]->x, vertex[faces[i]->faces[1]-1]->y, vertex[faces[i]->faces[1]-1]->z);
				glVertex3f(vertex[faces[i]->faces[2]-1]->x, vertex[faces[i]->faces[2]-1]->y, vertex[faces[i]->faces[2]-1]->z);
			glEnd();
		}
	}
	glEndList();
	
	//delete everything to avoid memory leaks
	for(int i=0;i<coord.size();i++)
		delete coord[i];
	for(int i=0;i<faces.size();i++)
		delete faces[i];
	for(int i=0;i<normals.size();i++)
		delete normals[i];
	for(int i=0;i<vertex.size();i++)
		delete vertex[i];
	return num;     //return with the id
}
