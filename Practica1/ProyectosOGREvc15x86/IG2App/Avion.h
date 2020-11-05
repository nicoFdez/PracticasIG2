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
	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	AspasMolino* heliceI = nullptr;
	AspasMolino* heliceD = nullptr;

	int radius = 450;

	Ogre::SceneNode* focoNode;
};

