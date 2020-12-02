#pragma once
#include "EntidadIG.h"

class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* rootNode);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
protected:
	virtual void receiveEvent(EntidadIG* entidad, msgType evt);
private:
	Ogre::Entity* ent;

	AnimationState* animationDance;
	AnimationState* animationRunBase;
	AnimationState* animationRunTop;
	AnimationState* animationMove;
	AnimationState* animationIdle;

	Ogre::Entity* sword;
	bool leftHanded;
};

