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
#include "Boya.h"
#include "Rio.h"
#include "Cabeza.h"

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

	int id = 0;

	Molino* molino = nullptr;
	Avion* avion = nullptr;
	Rio* mRio = nullptr;
	Plano *mPlane2 = nullptr;
	Ogre::SceneNode* cabezaNode = nullptr;
	Simbad* simbad = nullptr;
	Boya* boya = nullptr;
	Cabeza* cabeza = nullptr;

	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

	bool luminance = false;
	bool edgeEmboss = false;
};

#endif
