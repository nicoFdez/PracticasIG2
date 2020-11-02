#include "Plano.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

Plano::Plano(Ogre::SceneNode* rootNode, int num) : EntidadIG(rootNode->createChildSceneNode("Plano" + std::to_string(num)))
{

	Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
	mNode->attachObject(plane);
}
