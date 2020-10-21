#include "AspasMolino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

AspasMolino::AspasMolino(Ogre::SceneNode* rootNode, int numAspas) : numAspas(numAspas)
{
	Ogre::Entity* ent;
	aspasNode = rootNode->createChildSceneNode("aspas");

	arrayAspas = new Aspa*[numAspas];

	for (int i = 0; i < numAspas; ++i) {
		Ogre::SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_" + std::to_string(i));
		Ogre::SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(i));
		Ogre::SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(i));

		arrayAspas[i] = new Aspa(aspaNode, tableroNode, cilindroNode);
		
		aspaNode->roll(Ogre::Degree(-360.0/numAspas * i));
		cilindroNode->roll(Ogre::Degree(360.0 / numAspas * i));
	}
}

void AspasMolino::move()
{
	aspasNode->roll(Ogre::Degree(1.0));
	for (int i = 0; i < numAspas; ++i) {
		arrayAspas[i]->move();
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
