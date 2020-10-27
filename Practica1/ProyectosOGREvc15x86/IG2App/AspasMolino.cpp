#include "AspasMolino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

AspasMolino::AspasMolino(Ogre::SceneNode* rootNode, int numAspas, int number) : numAspas(numAspas)
{
	Ogre::Entity* ent;
	if(modoGiro == 0)
		aspasNode = rootNode->createChildSceneNode("aspas" + std::to_string(number));
	else {
		nodoFicticio = rootNode->createChildSceneNode("molino_aspas_ficticio" + std::to_string(number));
		nodoFicticio->setPosition(0, 0, 0);
		aspasNode = nodoFicticio->createChildSceneNode("aspas" + std::to_string(number));
	}

	arrayAspas = new Aspa*[numAspas];

	for (int i = 0; i < numAspas; ++i) {
		Ogre::SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_" + std::to_string(number) + std::to_string(i));
		Ogre::SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(number) + std::to_string(i));
		Ogre::SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(number) + std::to_string(i));

		arrayAspas[i] = new Aspa(aspaNode, tableroNode, cilindroNode);
		
		aspaNode->roll(Ogre::Degree(-360.0/numAspas * i));
		cilindroNode->roll(Ogre::Degree(360.0 / numAspas * i));
	}

	ejeNode = aspasNode->createChildSceneNode("ejeAspasMolino" + std::to_string(number));

	Ogre::SceneManager* mSM = aspasNode->getCreator();

	ent = mSM->createEntity("Barrel.mesh");
	ejeNode->attachObject(ent);
	ejeNode->pitch(Ogre::Degree(90.0));
	ejeNode->scale(20, 10, 20);
	ejeNode->setPosition(0, 0, 0);
}

void AspasMolino::move()
{
	aspasNode->roll(Ogre::Degree(1.0));
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
		aspasNode->setPosition(0, aspasNode->getPosition().y, 0);
		aspasNode->yaw(Ogre::Degree(2), Ogre::Node::TS_PARENT);
		rotationY += 2;
		aspasNode->translate(0, 0, 250, Ogre::Node::TS_LOCAL);
	}
	else { //Nodo ficticio
		nodoFicticio->yaw(Ogre::Degree(2));
	}
}

void AspasMolino::volar()
{
	aspasNode->roll(Ogre::Degree(-25));
	for (int i = 0; i < numAspas; ++i) {
		arrayAspas[i]->move(25);
	}
}



//bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
//{
//	if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
//	{
//		aspasNode->roll(Ogre::Degree(1.0));
//		for (int i = 0; i < numAspas; ++i) {
//			arrayAspas[i]->move();
//		}
//	}
//	return true;
//}
