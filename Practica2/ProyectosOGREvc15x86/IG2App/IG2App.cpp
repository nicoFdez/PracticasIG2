#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

#include "Plano.h"

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
	case SDLK_h:
		if (id == 3) {
			segundosRotationNode->roll(Ogre::Degree(-2));
		}
		break;
	case SDLK_j:
		if (id == 4) {
			//MoverTierra
			tierraNode->setPosition(0, 0, 0);
			tierraNode->yaw(Ogre::Degree(5));
			tierraNode->translate(earthOrbitRadius, 0, 0, Node::TS_LOCAL);

			//MoverLuna
			lunaNode->setPosition(0, 0, 0);
			lunaNode->yaw(Ogre::Degree(-20));
			lunaNode->translate(moonOrbitRadius, 0, 0, Node::TS_LOCAL);
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
	delete aspasMolino; aspasMolino = nullptr;
	delete molino; molino = nullptr;
	delete avion; avion = nullptr;
	delete simbad; simbad = nullptr;
	delete boya; boya = nullptr;

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

			aspaNode->roll(Ogre::Degree(-360.0 / num * i));

			ent = mSM->createEntity("cube.mesh");
			tableroNode->attachObject(ent);
			tableroNode->setPosition(200, 0, 0);
			tableroNode->scale(5, 1, 0.1);

			ent = mSM->createEntity("Barrel.mesh");
			cilindroNode->attachObject(ent);
			cilindroNode->scale(5, 12, 5);
			cilindroNode->roll(Ogre::Degree(360.0 / num * i));
			cilindroNode->setPosition(400, 0, 10);
		}
		break;
	}
	case 1: {
		aspasMolino = new AspasMolino(mSM->getRootSceneNode(), num);
		break;
	}
	case 2: {
		molino = new Molino(mSM->getRootSceneNode(), num);
		addInputListener(molino);
		break;
	}
	case 3: {
		Ogre::Entity* ent;
		Ogre::SceneNode* mClockNode = mSM->getRootSceneNode()->createChildSceneNode("Clock");
		Ogre::SceneNode* mSpheresNode = mClockNode->createChildSceneNode("Spheres");
		Ogre::SceneNode* mHourNode[12];
		//Las bolitas
		for (int i = 0; i < nHourIndicators; ++i) {
			ent = mSM->createEntity("sphere.mesh");
			Ogre::SceneNode* hijo = mSpheresNode->createChildSceneNode("Hora " + std::to_string(i + 1));
			hijo->attachObject(ent);
			hijo->setPosition(500 * Ogre::Math::Sin((Math::PI * i / 6)), 500 * Ogre::Math::Cos((Math::PI * i / 6)), 0);
			mHourNode[i] = hijo;
		}

		//Bolita pequeña - bolita grande
		for (int i = 1; i <= 12; i += 2) {
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
		segundosRotationNode = mClockNode->createChildSceneNode("SegunderoRotacion");
		agujas = segundosRotationNode->createChildSceneNode("Aguja segundos");
		ent = mSM->createEntity("cube.mesh");
		agujas->attachObject(ent);
		agujas->setScale(0.05, 4, 0.05);
		agujas->setPosition(0, -160, 0);
		segundosRotationNode->roll(Ogre::Degree(-45));
		break;
	}
	case 4: {
		Ogre::Entity* ent;

		ent = mSM->createEntity("sphere.mesh");
		tierraNode = mSM->getRootSceneNode()->createChildSceneNode("Tierra");
		tierraNode->attachObject(ent);
		tierraNode->setPosition(earthOrbitRadius, 0, 0);

		ent = mSM->createEntity("sphere.mesh");
		Ogre::SceneNode* solNode = mSM->getRootSceneNode()->createChildSceneNode("Sol");
		solNode->attachObject(ent);
		solNode->setScale(2, 2, 2);

		ent = mSM->createEntity("sphere.mesh");
		lunaNode = tierraNode->createChildSceneNode("Luna");
		lunaNode->attachObject(ent);
		lunaNode->setScale(0.35, 0.35, 0.35);
		lunaNode->setPosition(moonOrbitRadius, 0, 0);

		break;
	}
	case 5: {

		Ogre::Entity* ent;
		avion = new Avion(mSM->getRootSceneNode());
		addInputListener(avion);

		break;
	}
	case 6: {

		MeshManager::getSingleton().createPlane("mPlane1080x800",
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			Plane(Vector3::UNIT_Y, 0),
			1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

		mPlane = new Plano(mSM->getRootSceneNode(), "Practica1/agua");
		EntidadIG::addListener(mPlane);
		//Plano abajo a la izda
		mPlane1 = new Plano(mSM->getRootSceneNode(),"Practica1/rojo",1);
		mPlane1->getmNode()->setPosition(-351, 1, 260);
		mPlane1->getmNode()->setScale(0.35, 1, 0.35);
		
		//Plano arriba a la dcha
		mPlane2 = new Plano(mSM->getRootSceneNode(),"Practica1/marron",2);
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

		//Avion
		avion = new Avion(mSM->getRootSceneNode());
		avion->getmNode()->setPosition(-avion->getRotateRadius(), 630, 0);
		avion->getmNode()->setScale(0.2, 0.2, 0.2);
		addInputListener(avion);
		EntidadIG::addListener(avion);

		//Cabeza
		Ogre::Entity* ent;
		ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("Practica1/cabezaAmarilla");
		Ogre::SceneNode* cabezaNode = mSM->getRootSceneNode()->createChildSceneNode("cabezaAmarilla");
		cabezaNode->attachObject(ent);
		cabezaNode->setPosition(440, 40, -130);
		cabezaNode->setScale(.4, .4, .4);

		//Boya
		//boya = new Boya(mSM->getRootSceneNode());
		//boya->getmNode()->setScale(20, 15, 20);
		//boya->getmNode()->setPosition(0, 0, 0);
		//boya->getmNode()->setInitialState();
		//addInputListener(boya);
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

	mSM->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.85, 0.85, 0.85);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();
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

