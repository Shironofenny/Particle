#include "ConstantHandler.h"

ConstantHandler::ConstantHandler()
{
}

void ConstantHandler::restoreWindowSize(int x, int y)
{
	windowSizeX = x;
	windowSizeY = y;
	mousePositionX = windowSizeX / 2;
	mousePositionY = windowSizeY / 2;
}

void ConstantHandler::initialize()
{
	xml_node <> * data = XMLParser::getInstance().parseXMLFile("./data/config.xml");

	isMovieMade = strcmp(data->first_node("MakeMovie")->first_attribute("switch")->value(), "on") == 0;

	xml_node <> * window = data->first_node("Window");
	{
		windowSizeX = str2num(window->first_node("initWindowSize")->first_node("x")->value());
		windowSizeY = str2num(window->first_node("initWindowSize")->first_node("y")->value());
		mousePositionX = str2num(window->first_node("mousePosition")->first_node("x")->value());
		mousePositionY = str2num(window->first_node("mousePosition")->first_node("y")->value());
	}

	xml_node <> * camera = data->first_node("Camera");
	{
		cameraSpeed = str2num(camera->first_node("speed")->value());
		cameraRotateZ = str2num(camera->first_node("rotz")->value());
		virtualRotationRadius = str2num(camera->first_node("virtualRotationRadius")->value());
	}

	xml_node <> * particlesystem = data->first_node("ParticleSystem");
	while(particlesystem != NULL)
	{
		particleSystemSource.push_back(particlesystem->first_attribute("source")->value());
	}
	xml_node <> * navierStokes = data->first_node("NavierStokes");
	while(navierStokes != NULL)
	{
		particleSystemSource.push_back(navierStokes->first_attribute("source")->value());
	}
}
