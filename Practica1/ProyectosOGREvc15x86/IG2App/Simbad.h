#pragma once
#include "EntidadIG.h"


class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* rootNode);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
	Ogre::Entity* ent;

	AnimationState* animationDance;
	AnimationState* animationRunBase;
	AnimationState* animationRunTop;

	Ogre::Entity* sword;
	bool leftHanded;
};

