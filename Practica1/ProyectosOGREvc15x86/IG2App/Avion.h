#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "AspasMolino.h"

class Avion : public OgreBites::InputListener
{
public:
	Avion(Ogre::SceneNode* rootNode);
	~Avion() { 
		delete heliceI; heliceI = nullptr;
		delete heliceD; heliceD = nullptr;
	}
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	Ogre::SceneNode* alaINode = nullptr;
	Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;
	Ogre::SceneNode* pilotoNode = nullptr;
	AspasMolino* heliceI = nullptr;
	AspasMolino* heliceD = nullptr;
};

