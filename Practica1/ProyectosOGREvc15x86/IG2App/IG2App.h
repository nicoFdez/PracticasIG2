#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

#include "AspasMolino.h"
#include "Molino.h"
#include "Avion.h"
#include "Plano.h"
#include "Simbad.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener
{
public:
	explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
	virtual ~IG2App() { };   // delete -> shutdown()  

protected:
	void createObjects();

	virtual void setup();
	virtual void shutdown();
	virtual void setupScene();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

	int id = 6;
	//Usados cuando id = 0
	Ogre::SceneNode* aspas = nullptr,
		* aspaNode = nullptr,
		* tableroNode = nullptr,
		* cilindroNode = nullptr;
	int num = 12;

	//Usados cuando id = 1
	AspasMolino* aspasMolino = nullptr;

	//Usados cuando id = 2 o 6
	Molino* molino = nullptr;

	//Usados cuando id = 3
	Ogre::SceneNode* segundosRotationNode = nullptr;
	unsigned int nHourIndicators = 12;

	//Usados cuando id = 4
	Ogre::SceneNode* tierraNode = nullptr;
	Ogre::SceneNode* lunaNode = nullptr;
	int earthOrbitRadius = 500;
	int moonOrbitRadius = 163;

	//Usados cuando id = 5 o 6
	Avion* avion = nullptr;

	//Usados cuando id = 6
	Plano* mPlane = nullptr, *mPlane1 = nullptr, * mPlane2 = nullptr;
	Ogre::SceneNode* sinbadNode = nullptr;

	Simbad* simbad = nullptr;

	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

};

#endif
