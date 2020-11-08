#include "AspasMolino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>
#include "Avion.h"

AspasMolino::AspasMolino(Ogre::SceneNode* rootNode, int numAspas, int number) : EntidadIG(), numAspas(numAspas)
{
	Ogre::Entity* ent;
	if(modoGiro == 0)
		mNode = rootNode->createChildSceneNode("aspas" + std::to_string(number));
	else {
		nodoFicticio = rootNode->createChildSceneNode("molino_aspas_ficticio" + std::to_string(number));
		nodoFicticio->setPosition(0, 0, 0);
		mNode = nodoFicticio->createChildSceneNode("aspas" + std::to_string(number));
	}
	mSM = mNode->getCreator();

	arrayAspas = new Aspa*[numAspas];

	for (int i = 0; i < numAspas; ++i) {
		Ogre::SceneNode* aspaNode = mNode->createChildSceneNode("aspa_" + std::to_string(number) + std::to_string(i));
		Ogre::SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(number) + std::to_string(i));
		Ogre::SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(number) + std::to_string(i));

		arrayAspas[i] = new Aspa(aspaNode, tableroNode, cilindroNode);
		
		aspaNode->roll(Ogre::Degree(-360.0/numAspas * i));
		cilindroNode->roll(Ogre::Degree(360.0 / numAspas * i));
	}

	ejeNode = mNode->createChildSceneNode("ejeAspasMolino" + std::to_string(number));

	ent = mSM->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/hierro");
	ejeNode->attachObject(ent);
	ejeNode->pitch(Ogre::Degree(90.0));
	ejeNode->scale(20, 10, 20);
	ejeNode->setPosition(0, 0, 0);
}

void AspasMolino::move()
{
	mNode->roll(Ogre::Degree(1.0));
	for (int i = 0; i < numAspas; ++i) {
		arrayAspas[i]->move(-1.0);
	}
}

void AspasMolino::moveAxis()
{
	ejeNode->setPosition({ 0, 0, -25 });
}

void AspasMolino::rotate()
{
	if (modoGiro == 0) { //truco
		mNode->setPosition(0, mNode->getPosition().y, 0);
		mNode->yaw(Ogre::Degree(2), Ogre::Node::TS_PARENT);
		rotationY += 2;
		mNode->translate(0, 0, 250, Ogre::Node::TS_LOCAL);
	}
	else { //Nodo ficticio
		nodoFicticio->yaw(Ogre::Degree(2));
	}
}

void AspasMolino::hideOrnaments()
{
	for (int i = 0; i < numAspas; ++i) {
		arrayAspas[i]->hideOrnament();
	}
}

void AspasMolino::volar()
{
	mNode->roll(Ogre::Degree(-25));
	for (int i = 0; i < numAspas; ++i) {
		arrayAspas[i]->move(25);
	}
}
