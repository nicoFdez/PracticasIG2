#include "Avion.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>

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

	//BillBoardSet :)
	BillboardSet* bbSet = mSM->createBillboardSet("avion_cartel", 1);
	bbSet->setDefaultDimensions(200, 120);
	bbSet->setMaterialName("Practica2/Panel");
	Billboard* bb = bbSet->createBillboard(Vector3(0, 0, -100));

	colaNode = mNode->createChildSceneNode("Cola");
	colaNode->setPosition(0, 0, -250);
	colaNode->attachObject(bbSet);

	//Explosion
	pSys = mSM->createParticleSystem("psPumPum", "Practica2/Explosion");
	pSys->setEmitting(false);
	psNode = mNode->createChildSceneNode("psAvion");
	psNode->attachObject(pSys);

	//estela
	smokeTrail = mSM->createParticleSystem("psTrail", "Practica2/SmokeTrail");
	smokeTrail->setEmitting(true);
	psNode->attachObject(smokeTrail);
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

		cuerpoNode->setVisible(false);
		alaINode->setVisible(false);
		heliceI->getmNode()->setVisible(false);
		alaDNode->setVisible(false);
		heliceD->getmNode()->setVisible(false);
		frenteNode->setVisible(false);
		pilotoNode->setVisible(false);
		colaNode->setVisible(false);
		moving = false;

		pSys->setEmitting(true);
		smokeTrail->setEmitting(false);
	}
}

