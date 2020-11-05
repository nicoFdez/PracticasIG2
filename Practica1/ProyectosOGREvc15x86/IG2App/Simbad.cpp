#include "Simbad.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

Simbad::Simbad(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Simbad"))
{
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	mNode->attachObject(ent);
}
