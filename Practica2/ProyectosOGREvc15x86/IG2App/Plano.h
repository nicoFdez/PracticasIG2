#pragma once
#include "EntidadIG.h"
#include <OgreEntity.h>

class Plano : public EntidadIG
{
public:
	Plano(Ogre::SceneNode* rootNode, std::string const& matName = "", int num = 0);

protected:
	virtual void receiveEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt);
	Ogre::Entity* plane = nullptr;

};

