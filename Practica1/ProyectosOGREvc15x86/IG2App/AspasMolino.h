#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "Aspa.h"

class AspasMolino : public OgreBites::InputListener
{
public:
	AspasMolino(Ogre::SceneManager* mSM, int numAspas);
	~AspasMolino() {
		for (int i = 0; i < numAspas; ++i) {
			delete arrayAspas[i]; arrayAspas[i] = nullptr;
		}
		delete[] arrayAspas; arrayAspas = nullptr;
	}
	// Métodos de InputListener que pueden redefinirse
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	Aspa** getArrayAspas() { return arrayAspas; }
private:
	Aspa** arrayAspas;
	Ogre::SceneNode* aspasNode = nullptr;
	int numAspas = 0;
};

