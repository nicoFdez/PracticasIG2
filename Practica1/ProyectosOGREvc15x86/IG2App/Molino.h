#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "AspasMolino.h"

class Molino: public OgreBites::InputListener
{
public:
	Molino(Ogre::SceneNode* rootNode, int numAspas);
	~Molino() { delete aspasMolino; aspasMolino = nullptr; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
	Ogre::SceneNode* mNode = nullptr;

	Ogre::SceneNode* techoNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	AspasMolino* aspasMolino = nullptr;
};

