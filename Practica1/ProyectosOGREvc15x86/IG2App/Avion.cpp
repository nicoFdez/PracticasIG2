#include "Avion.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

Avion::Avion(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Avion"))
{
	Ogre::Entity* ent;

	//Crear cuerpo
	ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/rojo");
	cuerpoNode = mNode->createChildSceneNode("Cuerpo");
	cuerpoNode->attachObject(ent);
	cuerpoNode->setScale(2,2,2);

	//Cerar alas
	//AlaIzda
	ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/checker");
	alaINode = mNode->createChildSceneNode("AlaI");
	alaINode->attachObject(ent);
	alaINode->setPosition(-425, 0, 0);
	alaINode->scale(5, 0.2, 1);
	//AlaDcha
	ent = mSM->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/checker");
	alaDNode = mNode->createChildSceneNode("AlaD");
	alaDNode->attachObject(ent);
	alaDNode->setPosition(425, 0, 0);
	alaDNode->scale(5, 0.2, 1);

	//Crear frente
	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/marron");
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
	ent->setMaterialName("Practica1/amarillo");
	pilotoNode = mNode->createChildSceneNode("Piloto");
	pilotoNode->attachObject(ent);
	pilotoNode->yaw(Ogre::Degree(-180));
	pilotoNode->setPosition(0, 80, 0);

	//Crear foco
	Ogre::Light* foco = mSM->createLight("FocoAvion");
	foco->setType(Ogre::Light::LT_SPOTLIGHT);
	foco->setDiffuseColour(0.75, 0.75, 0.75);
	foco->setDirection(Ogre::Vector3(0, -1, 0.25));  //vec3.normalise();
	foco->setSpotlightInnerAngle(Ogre::Degree(5.0f));
	foco->setSpotlightOuterAngle(Ogre::Degree(45.0f));

	focoNode = mNode->createChildSceneNode("FocoAvionNode");
	focoNode->attachObject(foco);
}

bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g){
		heliceI->volar();
		heliceD->volar();
	}
	else if (evt.keysym.sym == SDLK_r){
		sendEvent(this, evt);
	}
	return true;
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	heliceI->volar();
	heliceD->volar();
	if (moving) {
		mNode->translate( radius, 0, 0, Ogre::Node::TS_LOCAL);
		mNode->yaw(Ogre::Degree(1));
		mNode->translate(-radius, 0, 0, Ogre::Node::TS_LOCAL);
	}
}

void Avion::receiveEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_r) {
		heliceI->hideOrnaments();
		heliceI->hideOrnaments();
		focoNode->getAttachedObject("FocoAvion")->setVisible(false);
		moving = false;
	}
}

