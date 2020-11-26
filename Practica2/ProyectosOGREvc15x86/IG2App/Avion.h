#pragma once
#include "AspasMolino.h"
#include "EntidadIG.h"

class Avion : public EntidadIG
{
public:
	Avion(Ogre::SceneNode* rootNode);
	~Avion() { 
		delete heliceI; heliceI = nullptr;
		delete heliceD; heliceD = nullptr;
	}
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

	int getRotateRadius(){ return radius; }


protected:

	virtual void receiveEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt);

	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	Ogre::SceneNode* colaNode = nullptr;
	Ogre::SceneNode* psNode = nullptr;
	AspasMolino* heliceI = nullptr;
	AspasMolino* heliceD = nullptr;

	int radius = 450;
	bool moving = true;

	ParticleSystem* pSys = nullptr;
	ParticleSystem* smokeTrail = nullptr;
};

