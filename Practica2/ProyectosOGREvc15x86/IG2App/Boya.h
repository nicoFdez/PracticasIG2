#pragma once
#include "EntidadIG.h"
class Boya : public EntidadIG
{
public:
	Boya(Ogre::SceneNode* rootNode);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
private:
	AnimationState* animationState;
};

