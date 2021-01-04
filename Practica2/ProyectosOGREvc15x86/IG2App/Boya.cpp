#include "Boya.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreFrameListener.h>
#include <OgreAnimationTrack.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>

Boya::Boya(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Boya"))
{
	ent = mSM->createEntity("uv_sphere.mesh");
	ent->setMaterialName("Practica2/EsferaAgujerosGLSL");
	mNode->attachObject(ent);

	//Hacer la animacion
		int duration = 8, longDesplazamiento = 20;
		Animation* animation = mSM->createAnimation("animVV", duration);
		NodeAnimationTrack* track = animation->createNodeTrack(0);

		track->setAssociatedNode(mNode);
		Vector3 keyframePos(0., 0., 0.); 
		Vector3 rot(0, 0, 1);
		Real durPaso = duration / 4.0; // uniformes
		TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)

		kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
		kf->setTranslate(keyframePos); // Origen: Vector3

		kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
		keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento;
		kf->setTranslate(keyframePos); // Arriba
		kf->setRotation(rot.getRotationTo({ 1, 0, 1 }));

		// Keyframe 2: origen ….
		kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: origen
		keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
		kf->setTranslate(keyframePos); // Origen
		kf->setRotation(rot.getRotationTo({ 0, 0, 1 }));

		kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: abajo
		keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
		kf->setTranslate(keyframePos); // Abajo
		kf->setRotation(rot.getRotationTo({ -1, 0, 1 }));

		kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen
		keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento;
		kf->setTranslate(keyframePos); // Origen
		kf->setRotation(rot.getRotationTo({ 0, 0, 1 }));

	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}

void Boya::receiveEvent(EntidadIG* entidad, msgType evt)
{
	if (evt == msgType::r_pressed) {
		ent->setMaterialName("Practica2/Explota2GLSL");
	}
}