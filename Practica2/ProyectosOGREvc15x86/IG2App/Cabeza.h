#pragma once
#include "EntidadIG.h"
class Cabeza : public EntidadIG
{
public:
	Cabeza(Ogre::SceneNode* rootNode);
private:
	Entity* ent = nullptr;
	virtual void receiveEvent(EntidadIG* entidad, msgType evt);
};

