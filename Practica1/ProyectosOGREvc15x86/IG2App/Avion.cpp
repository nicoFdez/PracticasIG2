#include "Avion.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

Avion::Avion(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Avion"))
{
	Ogre::Entity* ent;

	//Crear cuerpo
	ent = mSM->createEntity("sphere.mesh");
	cuerpoNode = mNode->createChildSceneNode("Cuerpo");
	cuerpoNode->attachObject(ent);
	cuerpoNode->setScale(2,2,2);

	//Cerar alas
	//AlaIzda
	ent = mSM->createEntity("cube.mesh");
	alaINode = mNode->createChildSceneNode("AlaI");
	alaINode->attachObject(ent);
	alaINode->setPosition(-425, 0, 0);
	alaINode->scale(5, 0.2, 1);
	//AlaDcha
	ent = mSM->createEntity("cube.mesh");
	alaDNode = mNode->createChildSceneNode("AlaD");
	alaDNode->attachObject(ent);
	alaDNode->setPosition(425, 0, 0);
	alaDNode->scale(5, 0.2, 1);

	//Crear frente
	ent = mSM->createEntity("Barrel.mesh");
	frenteNode = mNode->createChildSceneNode("Frente");
	frenteNode->attachObject(ent);
	frenteNode->pitch(Ogre::Degree(90.0));
	frenteNode->scale(15, 10, 15);
	frenteNode->setPosition(0, 0, 185);

	//Crear Helices
	//HeliceIzda
	heliceI = new AspasMolino(mNode, 5, 2);
	heliceI->getmNode()->setPosition(-400, 0, 55);
	heliceI->getmNode()->setScale(0.35, 0.35, 0.35);
	//HeliceDcha
	heliceD = new AspasMolino(mNode, 5, 3);
	heliceD->getmNode()->setPosition(400, 0, 55);
	heliceD->getmNode()->setScale(0.35, 0.35, 0.35);

	//Crear piloto
	ent = mSM->createEntity("ninja.mesh");
	pilotoNode = mNode->createChildSceneNode("Piloto");
	pilotoNode->attachObject(ent);
	pilotoNode->yaw(Ogre::Degree(-180));
	pilotoNode->setPosition(0, 80, 0);

	//Crear foco
	Ogre::Light* foco = mSM->createLight("FocoAvion");
	foco->setType(Ogre::Light::LT_SPOTLIGHT);
	foco->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	foco->setSpotlightOuterAngle(Ogre::Degree(45.0f));

	focoNode = mNode->createChildSceneNode("FocoAvionNode");
	focoNode->attachObject(foco);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g)
	{
		heliceI->volar();
		heliceD->volar();
	}
	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	heliceI->volar();
	heliceD->volar();

	mNode->translate( radius, 0, 0, Ogre::Node::TS_LOCAL);
	mNode->yaw(Ogre::Degree(1));
	mNode->translate(-radius, 0, 0, Ogre::Node::TS_LOCAL);
}
