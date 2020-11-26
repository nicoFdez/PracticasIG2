#pragma once
#include "Plano.h"
#include <OgreViewport.h>
#include <OgreEntity.h>

class Rio : public Plano
{
public:
	Rio(Ogre::SceneNode* rootNode, int n);
	~Rio() {
		delete mMovablePlane;
	}
	void setReflejo(Camera* camara, Ogre::Viewport* windowViewport);
protected:
	MovablePlane* mMovablePlane = nullptr;
	Entity* mEntity = nullptr;
};

