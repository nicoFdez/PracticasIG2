#pragma once
#include <OgreInput.h>
#include <OGRE\OgreSceneNode.h>

using namespace Ogre;

class EntidadIG : public OgreBites::InputListener
{
public:
	//Constructora y destructora
	EntidadIG(SceneNode* node);
	EntidadIG() {}

	virtual ~EntidadIG();

	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;

	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad) { appListeners.push_back(entidad); };

	Ogre::SceneNode* getmNode() { return mNode; }
protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	void sendEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt);

	virtual void receiveEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt) {};

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) {
		return false;
	};
};

