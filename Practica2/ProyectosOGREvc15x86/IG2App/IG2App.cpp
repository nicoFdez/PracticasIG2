#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <OgreCompositorManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_ESCAPE:
		getRoot()->queueEndRendering();
		break;
	case SDLK_l:
		luminance = !luminance;
		CompositorManager::getSingleton().setCompositorEnabled(getRenderWindow()->getViewport(0),
			"Practica2/Luminance", luminance);
		break;
	case SDLK_k:
		edgeEmboss = !edgeEmboss;
		CompositorManager::getSingleton().setCompositorEnabled(getRenderWindow()->getViewport(0),
			"Practica2/EdgeEmboss", edgeEmboss);
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
	delete molino; molino = nullptr;
	delete avion; avion = nullptr;
	delete simbad; simbad = nullptr;
	delete boya; boya = nullptr;
	delete mRio; mRio = nullptr;
	delete mPlane2; mPlane2 = nullptr;
	delete cabeza; cabeza = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::createObjects()
{
	switch (id)
	{
	case 0: {

		//Se crea la malla de la cual se hacen las entities de Plane (y por ello de tambi�n de Rio)
		MeshManager::getSingleton().createPlane("mPlane1080x800",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0),
			1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

		mRio = new Rio(mSM->getRootSceneNode(), 0);
		mRio->setReflejo((Camera*)mCamNode->getAttachedObject(0), getRenderWindow()->getViewport(0));
		EntidadIG::addListener(mRio);
		
		//Plano arriba a la dcha
		mPlane2 = new Plano(mSM->getRootSceneNode(),"Practica1/marron", 1);
		mPlane2->getmNode()->setPosition(378, 1, -238);
		mPlane2->getmNode()->setScale(0.3, 1, 0.405);
		
		//Molino
		molino = new Molino(mSM->getRootSceneNode(), 10);
		molino->getmNode()->setPosition(378, 230, -238);
		molino->getmNode()->setScale(0.3, 0.3, 0.3);
		addInputListener(molino);
		EntidadIG::addListener(molino);

		//Sinbad
		simbad = new Simbad(mSM->getRootSceneNode());
		simbad->getmNode()->setScale(12, 12, 12);
		simbad->getmNode()->setPosition(-351, 60, 260);
		simbad->getmNode()->setInitialState();
		addInputListener(simbad);
		EntidadIG::addListener(simbad);

		//Avion
		avion = new Avion(mSM->getRootSceneNode());
		avion->getmNode()->setPosition(-avion->getRotateRadius(), 630, 0);
		avion->getmNode()->setScale(0.2, 0.2, 0.2);
		addInputListener(avion);
		EntidadIG::addListener(avion);

		//Boya
		boya = new Boya(mSM->getRootSceneNode());
		boya->getmNode()->setPosition(0, 0, 0);
		boya->getmNode()->setInitialState();
		addInputListener(boya);
		EntidadIG::addListener(boya);

		//Cabeza
		cabeza = new Cabeza(mSM->getRootSceneNode());
		cabeza->getmNode()->setPosition(440, 40, -130);
		cabeza->getmNode()->setScale(.4, .4, .4);
		EntidadIG::addListener(cabeza);

		//Skyplane
		mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20),
			"Practica2/spaceGSLS", 1, 1, true, 1.0, 10, 10);

		/* Descomentar para cambiar distancias y hacer el bow (curvatura) 0.0
			mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200),
				"Practica2/space", 1, 1, true, 0.0, 10, 10);
		*/

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
	vp->setBackgroundColour(Ogre::ColourValue(.0, .0, .0));

	//Compositors
		//Luminance
		CompositorManager::getSingleton().addCompositor(vp,
			"Practica2/Luminance");
		CompositorManager::getSingleton().setCompositorEnabled(vp,
			"Practica2/Luminance", luminance);

		//EdgeEmboss
		CompositorManager::getSingleton().addCompositor(vp,
			"Practica2/EdgeEmboss");
		CompositorManager::getSingleton().setCompositorEnabled(vp,
			"Practica2/EdgeEmboss", edgeEmboss);

	//------------------------------------------------------------------------

	//mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.8, 0.8, 0.8);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//Luz ambiente
	mSM->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

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

