#include "Simbad.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreFrameListener.h>

Simbad::Simbad(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Simbad"))
{
	ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);

	animationDance = ent->getAnimationState("Dance");
	animationDance->setEnabled(true); 
	animationDance->setLoop(true);

	animationRunBase = ent->getAnimationState("RunBase");
	animationRunBase->setLoop(true);

	animationRunTop = ent->getAnimationState("RunTop");
	animationRunTop->setLoop(true);

	sword = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Handle.R", sword);
	leftHanded = false;
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (animationDance->getEnabled()) animationDance->addTime(evt.timeSinceLastFrame);
	else {
		animationRunBase->addTime(evt.timeSinceLastFrame);
		animationRunTop->addTime(evt.timeSinceLastFrame);
	}
}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_c) {
		if (animationDance->getEnabled()) {
			animationDance->setEnabled(false);
			animationRunBase->setEnabled(true);
			animationRunTop->setEnabled(true);		
		}
		else {
			animationRunBase->setEnabled(false);
			animationRunTop->setEnabled(false);
			animationDance->setEnabled(true);
		}
	}
	else if (evt.keysym.sym == SDLK_e) {
		ent->detachObjectFromBone(sword);
		if (leftHanded) {
			ent->attachObjectToBone("Handle.R", sword);
			leftHanded = false;
		}
		else {
			ent->attachObjectToBone("Handle.L", sword);
			leftHanded = true;
		}
	}
	return false;
}
