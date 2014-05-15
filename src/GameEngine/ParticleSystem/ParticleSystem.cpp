#include "ParticleSystem.h"
#include "../Utilities/TextureLoader.h"
#include "../Utilities/RandomGenerator.h"
#include "../Utilities/XMLParser.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::parseXML(string const & _filename)
{
	xml_node<> * config = XMLParser::getInstance().parseXMLFile(_filename)->first_node("Particle");
	
	// Load texture
	int w, h;

	string texture = config->first_attribute("texture")->value();
	m_ParticleTexture = TextureLoader::getInstance().loadTexture(texture, w, h);

	// Warning if texture image is not square
	if (w != h) 
	{	
		cout<<"[feinfo] Warning : Texture image is not square. Scale according to width."<<endl;
	}

	float scale = str2num(config->first_attribute("scale")->value());

	Particle::buildParticle( w * scale );

	// Read other data
	m_LifeMean = str2num(config->first_node("Life")->first_attribute("mean")->value());
	m_LifeVar = str2num(config->first_node("Life")->first_attribute("var")->value());
	
	xml_node<> * source = config->first_node("Source");
	m_SourceMean = Vector(str2num(source->first_node("Position")->first_attribute("x")->value()),\
			str2num(source->first_node("Position")->first_attribute("y")->value()),\
			str2num(source->first_node("Position")->first_attribute("z")->value()));
	m_SourceVar = str2num(source->first_attribute("var")->value());
	
	m_MassMean = str2num(config->first_node("Mass")->first_attribute("mean")->value());
	m_MassVar = str2num(config->first_node("Mass")->first_attribute("var")->value());

	m_GenerationPerSecond =\
			str2num(config->first_node("Generation")->first_attribute("persecond")->value());

	// Initialize the color sequence
	xml_node<> * color = config->first_node("KeyFrames");
	xml_node<> * frame = color->first_node("Frame");
	while(frame != NULL)
	{
		m_ParticleProperty.addFrame(str2num(frame->first_attribute("tr")->value()),\
			 											 str2num(frame->first_attribute("r")->value()),\
			 											 str2num(frame->first_attribute("g")->value()),\
			 											 str2num(frame->first_attribute("b")->value()),\
			 											 str2num(frame->first_attribute("a")->value()),\
			 											 str2num(frame->first_attribute("sx")->value()),\
			 											 str2num(frame->first_attribute("sy")->value()),\
			 											 str2num(frame->first_attribute("sz")->value()),\
			 											 str2num(frame->first_attribute("p")->value()));
		frame = frame->next_sibling();
	}
}
	
void ParticleSystem::update(double dt)
{
	// Remove all dead particles
	for(vector<Particle>::iterator it = m_Particles.begin(); it != m_Particles.end(); it++)
	{
		it->update(dt);
		if (it->isDead())
		{
			m_Particles.erase(it);
			it -= 1;
		}
	}
	
	// Generate new ones
	for(int i = 1; i < (int)(m_GenerationPerSecond * dt); i++)
	{
		Particle par(m_ParticleTexture,\
			 m_LifeMean + RandomGenerator::getInstance().getRandom() * m_LifeVar);
		par.getPosition() = m_SourceMean +\
			 RandomGenerator::getInstance().getRandomUnitVector() * m_SourceVar;
		par.getMass() = m_MassMean + RandomGenerator::getInstance().getRandom() * m_MassVar;
		par.getPressure() = -0.2;
		m_Particles.push_back(par);
	}
}

void ParticleSystem::render(Camera & _camera)
{
	GLfloat color[4];
	Vector scale;
	float pressure;
	for(vector<Particle>::size_type i = 0; i < m_Particles.size(); i++)
	{
		m_ParticleProperty.getProperty(m_Particles[i].getLifeRatio(), color, scale, pressure);
		glColor4fv(color);
		m_Particles[i].getScale() = scale;
		m_Particles[i].getPressure() = pressure;
		m_Particles[i].render(_camera);
	}
}

int ParticleSystem::getParticleNumber()
{
	return m_Particles.size();
}
	
vector<Particle> & ParticleSystem::getParticles()
{
	return m_Particles;
}
	
vector<Particle> const & ParticleSystem::getParticles() const
{
	return m_Particles;
}
	
Vector & ParticleSystem::getSource()
{
	return m_SourceMean;
}
	
Vector const & ParticleSystem::getSource() const
{
	return m_SourceMean;
}
