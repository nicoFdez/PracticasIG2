#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include <OgreEntity.h>
#include "AspasMolino.h"
#include "EntidadIG.h"

class Molino: public EntidadIG
{
public:
	Molino(Ogre::SceneNode* rootNode, int numAspas);
	~Molino() { delete aspasMolino; aspasMolino = nullptr; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt); 
	virtual void frameRendered(const Ogre::FrameEvent& evt);
protected:

	virtual void receiveEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt);

	bool moving = true;
	Ogre::SceneNode* techoNode = nullptr;
	Ogre::SceneNode* cuerpoNode = nullptr;
	AspasMolino* aspasMolino = nullptr;

	Ogre::Entity* techo;
};

