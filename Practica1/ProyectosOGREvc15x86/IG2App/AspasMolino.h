#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "Aspa.h"
#include "EntidadIG.h"

class AspasMolino : public EntidadIG
{
public:
	AspasMolino(Ogre::SceneNode* rootNode, int numAspas, int number = 1);
	~AspasMolino() {
		for (int i = 0; i < numAspas; ++i) {
			delete arrayAspas[i]; arrayAspas[i] = nullptr;
		}
		delete[] arrayAspas; arrayAspas = nullptr;
	}

	void move();
	void volar();
	void moveAxis();
	void rotate();	

private:
		int modoGiro = 0;
		int rotationY = 0;
		Ogre::SceneNode* nodoFicticio = nullptr;

	Aspa** arrayAspas;
	Ogre::SceneNode* ejeNode = nullptr;
	int numAspas = 0;
};

