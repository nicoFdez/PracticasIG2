#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>

class Aspa //: public OgreBites::InputListener
{
public:
	Aspa(Ogre::SceneNode* aspaNode, Ogre::SceneNode* tableroNode, Ogre::SceneNode* cilindroNode);
	~Aspa() {}
	// Métodos de InputListener que pueden redefinirse
	//virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void move(int degrees);
private:
	Ogre::SceneNode
		* aspaNode = nullptr,
		* tableroNode = nullptr,
		* cilindroNode = nullptr;
};

