#include "Aspa.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

Aspa::Aspa(Ogre::SceneNode* aspaNode, Ogre::SceneNode* tableroNode, Ogre::SceneNode* cilindroNode) : 
	aspaNode(aspaNode), 
	tableroNode(tableroNode), 
	cilindroNode(cilindroNode)
{
	Ogre::Entity* ent;

	Ogre::SceneManager* mSM = aspaNode->getCreator();

	ent = mSM->createEntity("cube.mesh");
	tableroNode->attachObject(ent);
	tableroNode->setPosition(200, 0, 0);
	tableroNode->scale(5, 1, 0.1);

	ent->setMaterialName("Practica1/marronOscuro");

	ent = mSM->createEntity("Barrel.mesh");
	cilindroNode->attachObject(ent);
	cilindroNode->scale(5, 12, 5);
	cilindroNode->setPosition(400, 0, 10);

	ent->setMaterialName("Practica1/azulMar");
}

void Aspa::move(int degrees)
{
	cilindroNode->roll(Ogre::Degree(degrees));
}

void Aspa::hideOrnament()
{
	cilindroNode->setVisible(false);
}

