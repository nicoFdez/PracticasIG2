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
		if (id == 0) { //Clock solo existe en la escena con id = 1
			mSM->getSceneNode("aspas")->roll(Ogre::Degree(1.0));
			for (int i = 0; i < num; ++i) {
				mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Ogre::Degree(-1.0));
			}
		}
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
  delete aspasMolino;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::createObjects()
{
	switch (id)
	{
	case 0: {
		Ogre::Entity* ent;
		aspas = mSM->getRootSceneNode()->createChildSceneNode("aspas");

		for (int i = 0; i < num; ++i) {
			aspaNode = aspas->createChildSceneNode("aspa_" + std::to_string(i));
			tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(i));
			cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(i));

			aspaNode->roll(Ogre::Degree(-90.0 * i / 3.0));

			ent = mSM->createEntity("cube.mesh");
			tableroNode->attachObject(ent);
			tableroNode->setPosition(200, 0, 0);
			tableroNode->scale(5, 1, 0.1);

			ent = mSM->createEntity("Barrel.mesh");
			cilindroNode->attachObject(ent);
			cilindroNode->scale(5, 12, 5);
			cilindroNode->roll(Ogre::Degree(90.0 * i / 3.0));
			cilindroNode->setPosition(400, 0, 10);
		}
		break;
	}
	case 1: {
		aspasMolino = new AspasMolino(mSM, num);
		addInputListener(aspasMolino);

		Aspa** arrayAspas = aspasMolino->getArrayAspas();
		for (int i = 0; i < num; ++i) {
			addInputListener(arrayAspas[i]);
		}
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

