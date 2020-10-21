#include "Molino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

Molino::Molino(Ogre::SceneNode* rootNode, int numAspas)
{
	mNode = rootNode->createChildSceneNode("molino");

	Ogre::Entity* ent;
	Ogre::SceneManager* mSM = rootNode->getCreator();

	//Crear aspas
	aspasMolino = new AspasMolino(mNode, numAspas);
	aspasMolino->getmNode()->setPosition(0, 200, 0);

	//Cerar el techo
	techoNode = mNode->createChildSceneNode("techo");
	ent = mSM->createEntity("sphere.mesh");
	techoNode->attachObject(ent);
	techoNode->setPosition(0, 200, -250);
	techoNode->scale(2.2, 2.2, 2.2);
	
	//Crear el cuerpo
	cuerpoNode = mNode->createChildSceneNode("cuerpo");
	ent = mSM->createEntity("Barrel.mesh");
	cuerpoNode->attachObject(ent);
	cuerpoNode->scale(90, 160, 90);
	cuerpoNode->setPosition(0, -280, -250);

}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
	{
		aspasMolino->move();
	}
	return true;
}
