#include "Plano.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>
#include <OgreCamera.h>

Plano::Plano(Ogre::SceneNode* rootNode, std::string const& matName, int num) : EntidadIG(rootNode->createChildSceneNode("Plano" + std::to_string(num)))
{
	plane = mSM->createEntity("mPlane1080x800");
	plane->setMaterialName(matName);
	mNode->attachObject(plane);
}

void Plano::receiveEvent(EntidadIG* entidad, msgType evt)
{
	if (evt == msgType::r_pressed) {
		plane->setMaterialName("Practica1/rioSeco");
	}
}
