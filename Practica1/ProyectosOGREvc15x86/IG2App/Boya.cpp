#include "Boya.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>

Boya::Boya(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Boya"))
{
	Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/checker");
	mNode->attachObject(ent);
}
