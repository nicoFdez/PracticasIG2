#include "Simbad.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreFrameListener.h>
#include <OgreAnimationTrack.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

Simbad::Simbad(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Simbad"))
{
	ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);

	animationDance = ent->getAnimationState("Dance");
	animationDance->setLoop(true);

	animationRunBase = ent->getAnimationState("RunBase");
	animationRunBase->setEnabled(true);
	animationRunBase->setLoop(true);

	animationRunTop = ent->getAnimationState("RunTop");
	animationRunTop->setEnabled(true);
	animationRunTop->setLoop(true);

	animationIdle = ent->getAnimationState("IdleTop");
	animationIdle->setEnabled(false);
	animationIdle->setLoop(true);

	sword = mSM->createEntity("Sword.mesh");
	ent->attachObjectToBone("Handle.R", sword);
	leftHanded = false;

	//Hacer la animacion
		int duration = 16;
		Animation* animation = mSM->createAnimation("animWalk", duration);
		NodeAnimationTrack* track = animation->createNodeTrack(0);

		track->setAssociatedNode(mNode);
		Vector3 keyframePos(0., 0., 0.);
		Vector3 rot(0, 0, 1);
		Real durPaso = duration / 4.0; // uniformes
		TransformKeyFrame* kf; // 5 keyFrames: origen(0), fin, giro, origen, giro(4)

		kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
		kf->setTranslate(keyframePos); // Origen: Vector3
		Vector3 newRot{ 351, 0, -260 }; newRot.normalise();
		kf->setRotation(rot.getRotationTo(newRot));

		kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: centro
		keyframePos = { 351, 0, -260 };
		kf->setTranslate(keyframePos);
		kf->setRotation(rot.getRotationTo(newRot));

		kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: giro
		newRot = { -351, 0, 260 }; newRot.normalise();
		kf->setTranslate(keyframePos);
		kf->setRotation(rot.getRotationTo(newRot));

		kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: vuelta
		kf->setRotation(rot.getRotationTo(newRot));

		kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen
		newRot = { 351, 0, -260 }; newRot.normalise();
		kf->setRotation(rot.getRotationTo(newRot));

	animationMove = mSM->createAnimationState("animWalk");
	animationMove->setLoop(true);
	animationMove->setEnabled(true);
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if (animationDance->getEnabled()) animationDance->addTime(evt.timeSinceLastFrame);
	else if(!animationIdle->getEnabled()) {
		animationRunBase->addTime(evt.timeSinceLastFrame);
		animationRunTop->addTime(evt.timeSinceLastFrame);
		animationMove->addTime(evt.timeSinceLastFrame);
	}
	else animationIdle->addTime(evt.timeSinceLastFrame);
}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_c && !animationIdle->getEnabled()) {
		if (animationDance->getEnabled()) {
			animationDance->setEnabled(false);
			animationDance->setTimePosition(0);
			
			animationRunBase->setEnabled(true);
			animationRunTop->setEnabled(true);		
			animationMove->setEnabled(true);
		}
		else {
			animationRunBase->setEnabled(false);
			animationRunBase->setTimePosition(0);

			animationRunTop->setEnabled(false);
			animationRunTop->setTimePosition(0);

			animationMove->setEnabled(false);
			//animationMove->setTimePosition(0);

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

void Simbad::receiveEvent(EntidadIG* entidad, msgType evt)
{
	if (evt == msgType::r_pressed) {
		if (!animationIdle->getEnabled()) {
			mNode->translate(0, -50, 0);
			mNode->pitch(Ogre::Degree(-90));

			animationDance->setEnabled(false);
			animationDance->setTimePosition(0);

			animationRunBase->setEnabled(false);
			animationDance->setTimePosition(0);
			animationRunTop->setEnabled(false);
			animationDance->setTimePosition(0);

			animationMove->setEnabled(false);

			animationIdle->setEnabled(true);
		}
	}
}
