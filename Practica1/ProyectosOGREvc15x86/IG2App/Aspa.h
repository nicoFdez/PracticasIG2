#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "EntidadIG.h"

class Aspa : public EntidadIG
{
public:
	Aspa(Ogre::SceneNode* aspaNode, Ogre::SceneNode* tableroNode, Ogre::SceneNode* cilindroNode);
	~Aspa() {}
	virtual void receiveEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt);
	void move(int degrees);
private:
	Ogre::SceneNode
		* aspaNode = nullptr,
		* tableroNode = nullptr,
		* cilindroNode = nullptr;
};

