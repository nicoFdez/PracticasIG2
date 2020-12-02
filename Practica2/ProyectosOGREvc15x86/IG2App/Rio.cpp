#include "Rio.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <SDL_keycode.h>
#include <OgreCamera.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreRenderTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreTextureUnitState.h>
#include <OgreTechnique.h>

Rio::Rio(Ogre::SceneNode* rootNode, int n) : Plano(rootNode, "Practica2/reflejo", n)
{
	mEntity = (Entity*)mNode->getAttachedObject(0);
}

void Rio::setReflejo(Camera* cam, Viewport* windowViewport)
{
	mainCam = cam;
	windowViewport->addListener(this);
	camRef = mSM->createCamera("RefCam");

	camRef->setNearClipDistance(cam->getNearClipDistance());
	camRef->setFarClipDistance(cam->getFarClipDistance());
	camRef->setAutoAspectRatio(cam->getAspectRatio());

	mSM->getSceneNode("nCam")->attachObject(camRef);

	mMovablePlane = new MovablePlane(Vector3::UNIT_Y, 0);
	mNode->attachObject(mMovablePlane);

	camRef->enableReflection(mMovablePlane);
	camRef->enableCustomNearClipPlane(mMovablePlane);

	TexturePtr rttRef = TextureManager::getSingleton().createManual(
		"rttReflejo", // name ejemplo -> (*)
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)windowViewport->getActualWidth(), // widht ejemplo
		(Real)windowViewport->getActualHeight(), // height ejemplo
		0, PF_R8G8B8, TU_RENDERTARGET);

	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	renderTexture->addListener(this);
	Viewport* vpt = renderTexture->addViewport(camRef); // ocupando toda
	vpt->setClearEveryFrame(true); // la textura
	vpt->setBackgroundColour(ColourValue::White); // black/white

	TextureUnitState* tu = mEntity->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->createTextureUnitState("rttReflejo");

	tu->setColourOperation(LBO_MODULATE); // black/white background?
				// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE

	tu->setProjectiveTexturing(true, camRef);
}

void Rio::viewportDimensionsChanged(Viewport* viewport)
{	
	camRef->setNearClipDistance(mainCam->getNearClipDistance());
	camRef->setFarClipDistance(mainCam->getFarClipDistance());
	camRef->setAspectRatio(mainCam->getAspectRatio());
}

void Rio::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	sendEvent(this, msgType::pre_render_reflejo);
}

void Rio::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	sendEvent(this, msgType::post_render_reflejo);
}
