#include "AspasMolino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

AspasMolino::AspasMolino(Ogre::SceneNode* rootNode, int numAspas) : numAspas(numAspas)
{
	Ogre::Entity* ent;
	if(modoGiro == 0)
		aspasNode = rootNode->createChildSceneNode("aspas");
	else {
		nodoFicticio = rootNode->createChildSceneNode("molino_aspas_ficticio");
		nodoFicticio->setPosition(0, 0, 0);
		aspasNode = nodoFicticio->createChildSceneNode("aspas");
	}

	arrayAspas = new Aspa*[numAspas];

	for (int i = 0; i < numAspas; ++i) {
		Ogre::SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_" + std::to_string(i));
		Ogre::SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(i));
		Ogre::SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(i));

		arrayAspas[i] = new Aspa(aspaNode, tableroNode, cilindroNode);
		
		aspaNode->roll(Ogre::Degree(-360.0/numAspas * i));
		cilindroNode->roll(Ogre::Degree(360.0 / numAspas * i));
	}

	ejeNode = aspasNode->createChildSceneNode("ejeAspasMolino");

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
		arrayAspas[i]->move();
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
		aspasNode->setPosition(250 * sin(rotationY * 2 * Ogre::Math::PI / 360), 
							   aspasNode->getPosition().y, 
							   250 * cos(rotationY * 2 * Ogre::Math::PI / 360 ));
	}
	else { //Nodo ficticio
		nodoFicticio->yaw(Ogre::Degree(2));
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
