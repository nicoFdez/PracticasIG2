#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>
#include "Aspa.h"

class AspasMolino// : public OgreBites::InputListener
{
public:
	AspasMolino(Ogre::SceneNode* rootNode, int numAspas, int number = 1);
	~AspasMolino() {
		for (int i = 0; i < numAspas; ++i) {
			delete arrayAspas[i]; arrayAspas[i] = nullptr;
		}
		delete[] arrayAspas; arrayAspas = nullptr;
	}
	// Métodos de InputListener que pueden redefinirse
	//virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void move();
	void volar();
	void moveAxis();
	void rotate();
	//Aspa** getArrayAspas() { return arrayAspas; }

	Ogre::SceneNode* getmNode() { return aspasNode; }
private:
		int modoGiro = 0;
		int rotationY = 0;
		Ogre::SceneNode* nodoFicticio = nullptr;

	Aspa** arrayAspas;
	Ogre::SceneNode* aspasNode = nullptr;
	Ogre::SceneNode* ejeNode = nullptr;
	int numAspas = 0;
};

