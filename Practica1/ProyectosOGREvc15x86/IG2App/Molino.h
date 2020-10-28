#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "AspasMolino.h"
#include "EntidadIG.h"

class Molino: public EntidadIG
{
public:
	Molino(Ogre::SceneNode* rootNode, int numAspas);
	~Molino() { delete aspasMolino; aspasMolino = nullptr; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:

	Ogre::SceneNode* techoNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	AspasMolino* aspasMolino = nullptr;
};

