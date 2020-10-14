#include "AspasMolino.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <SDL_keycode.h>

AspasMolino::AspasMolino(Ogre::SceneManager* mSM, int numAspas) : numAspas(numAspas)
{
	Ogre::Entity* ent;
	aspasNode = mSM->getRootSceneNode()->createChildSceneNode("aspas");

	arrayAspas = new Aspa*[numAspas];

	for (int i = 0; i < numAspas; ++i) {
		Ogre::SceneNode* aspaNode = aspasNode->createChildSceneNode("aspa_" + std::to_string(i));
		Ogre::SceneNode* tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(i));
		Ogre::SceneNode* cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(i));

		arrayAspas[i] = new Aspa(aspaNode, tableroNode, cilindroNode);
		
		aspaNode->roll(Ogre::Degree(-90.0 * i / 3.0));
		cilindroNode->roll(Ogre::Degree(90.0 * i / 3.0));
	}
}

bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
	{
		aspasNode->roll(Ogre::Degree(1.0));
	}
	return true;
}
