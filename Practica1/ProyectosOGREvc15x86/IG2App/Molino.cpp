#include "Molino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

Molino::Molino(Ogre::SceneNode* rootNode, int numAspas) : EntidadIG(rootNode->createChildSceneNode("molino"))
{
	mNode->setPosition(0, 0, -250);
	Ogre::Entity* ent;

	//Crear aspas
	aspasMolino = new AspasMolino(mNode, numAspas);
	aspasMolino->getmNode()->setPosition(0, 200, 250);

	//Cerar el techo
	techoNode = mNode->createChildSceneNode("techo");
	ent = mSM->createEntity("sphere.mesh");
	techoNode->attachObject(ent);
	techoNode->setPosition(0, 200, 0);
	techoNode->scale(2.2, 2.2, 2.2);
	
	//Crear el cuerpo
	cuerpoNode = mNode->createChildSceneNode("cuerpo");
	ent = mSM->createEntity("Barrel.mesh");
	cuerpoNode->attachObject(ent);
	cuerpoNode->scale(90, 160, 90);
	cuerpoNode->setPosition(0, -280, 0);

}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g)
	{
		aspasMolino->move();
	}
	else if (evt.keysym.sym == SDLK_c)
	{
		aspasMolino->moveAxis();
	}
	else if (evt.keysym.sym == SDLK_h)
	{
		aspasMolino->rotate();
	}
	return true;
}
