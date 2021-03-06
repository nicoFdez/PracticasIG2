#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE: 
		getRoot()->queueEndRendering();
		break;
	case SDLK_g:
		if (id == 1) //Clock solo existe en la escena con id = 1
			mSM->getSceneNode("Clock")->roll(Ogre::Degree(-1.0));
		break;
	case SDLK_h:
		if(id == 1)
			mSM->getSceneNode("Spheres")->roll(Ogre::Degree(-1.0));
		break;
	default:
		break;
	}
  
  return true;
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::createObjects()
{
	switch (id)
	{
	case 0: {
		Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
		mSinbadNode->attachObject(ent);

		mSinbadNode->setPosition(0, 20, 0);
		mSinbadNode->setScale(20, 20, 20);
		//mSinbadNode->yaw(Ogre::Degree(-45));
		//mSinbadNode->showBoundingBox(true);
		//mSinbadNode->setVisible(false);

		ent = mSM->createEntity("RomanBathLower.mesh");

		mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nRomanoBath");
		mSinbadNode->attachObject(ent);

		//mSinbadNode->setPosition(400, 100, -300);
		//mSinbadNode->setScale(20, 20, 20);
		//mSinbadNode->yaw(Ogre::Degree(-45));
		//mSinbadNode->showBoundingBox(true);
		//mSinbadNode->setVisible(false);

		ent = mSM->createEntity("RomanBathUpper.mesh");

		//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nRomanoUpper");
		mSinbadNode->attachObject(ent);

		//mSinbadNode->setPosition(400, 100, -300);
		//mSinbadNode->setScale(20, 20, 20);
		//mSinbadNode->yaw(Ogre::Degree(-45));
		//mSinbadNode->showBoundingBox(true);
		//mSinbadNode->setVisible(false);

		ent = mSM->createEntity("Columns.mesh");

		//mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nRomanoColumns");
		mSinbadNode->attachObject(ent);

		//mSinbadNode->setPosition(400, 100, -300);
		//mSinbadNode->setScale(20, 20, 20);
		//mSinbadNode->yaw(Ogre::Degree(-45));
		//mSinbadNode->showBoundingBox(true);
		//mSinbadNode->setVisible(false);

		break;
	}
	case 1: {
		Ogre::Entity* ent;
		mClockNode = mSM->getRootSceneNode()->createChildSceneNode("Clock");
		mSpheresNode = mClockNode->createChildSceneNode("Spheres");
		//Las bolitas
		for (int i = 0; i < 12; ++i) {
			ent = mSM->createEntity("sphere.mesh");
			Ogre::SceneNode* hijo = mSpheresNode->createChildSceneNode("Hora " + std::to_string(i + 1));
			hijo->attachObject(ent);
			hijo->setPosition(500 * Ogre::Math::Sin((Math::PI * i / 6)), 500 * Ogre::Math::Cos((Math::PI * i / 6)), 0);
			mHourNode[i] = hijo;
		}

		//Bolita peque�a - bolita grande
		for (int i = 1; i <= 12; i+=2) {
			mSM->getSceneNode("Hora " + std::to_string(i))->setScale(0.5, 0.5, 0.5);
		}

		//Las agujitas
		//Horas
		Ogre::SceneNode* agujas = mClockNode->createChildSceneNode("Aguja horas");
		ent = mSM->createEntity("cube.mesh");
		agujas->attachObject(ent);
		agujas->setPosition(100, 0, 0);
		agujas->setScale(0.25, 3, 0.25);
		agujas->roll(Ogre::Degree(-90.0));

		//Minutos
		agujas = mClockNode->createChildSceneNode("Aguja minutos");
		ent = mSM->createEntity("cube.mesh");
		agujas->attachObject(ent);
		agujas->setPosition(0, 150, 0);
		agujas->setScale(0.15, 4, 0.15);

		//Segundos
		agujas = mClockNode->createChildSceneNode("Aguja segundos");
		ent = mSM->createEntity("cube.mesh");
		agujas->attachObject(ent);
		agujas->setPosition(150 * Ogre::Math::Sin(8 * Math::PI / 6), 150 * Ogre::Math::Cos(8 * Math::PI / 6), 0);
		agujas->setScale(0.05, 4, 0.05);
		agujas->roll(Ogre::Degree(120.0));

		break;
	}
	default:
		break;
	}
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  createObjects();

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

