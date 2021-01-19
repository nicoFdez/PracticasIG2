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
	//Guardamos la camara pasa usarla en el metodo viewportDimensionsChanged()
	mainCam = cam;
	//Nos subscribimos al viewport para que nos llame a los metodos viewportDimensionsChanged, preRenderTargetUpdate y postRenderTargetUpdate
	windowViewport->addListener(this);
	//Creamos la camara para el reflejo
	camRef = mSM->createCamera("RefCam");

	//Ajustamos su Frustum igual al de cam
	camRef->setNearClipDistance(cam->getNearClipDistance());
	camRef->setFarClipDistance(cam->getFarClipDistance());
	camRef->setAutoAspectRatio(cam->getAspectRatio());

	//Añadimos la camara a la escena
	mSM->getSceneNode("nCam")->attachObject(camRef);

	//Creamos un MovablePlane sobre el que se reflejaran los objetos
	mMovablePlane = new MovablePlane(Vector3::UNIT_Y, 0);
	mNode->attachObject(mMovablePlane);

	//Ajustes de la camara para el reflejo sobre el plano
	camRef->enableReflection(mMovablePlane);
	camRef->enableCustomNearClipPlane(mMovablePlane);

	//Creamos una textura para usarla de RenderTarget y de textura del espejo
	//Se usa el mismo grupo de Resources que la malla del plano
	TexturePtr rttRef = TextureManager::getSingleton().createManual(
		"rttReflejo", // name ejemplo -> (*)
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)windowViewport->getActualWidth(), // widht ejemplo
		(Real)windowViewport->getActualHeight(), // height ejemplo
		0, PF_R8G8B8, TU_RENDERTARGET);

	//Añadimos un viewPort a la textura con la nueva camara
	RenderTexture* renderTexture = rttRef->getBuffer()->getRenderTarget();
	renderTexture->addListener(this);
	Viewport* vpt = renderTexture->addViewport(camRef); // ocupando toda la textura
	vpt->setClearEveryFrame(true); 
	vpt->setBackgroundColour(ColourValue::White); // black/white

	//añadimos al material una nueva unidad de textura con la textura "rttReflejo"
	TextureUnitState* tu = mEntity->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->createTextureUnitState("rttReflejo");

	tu->setColourOperation(LBO_MODULATE); // black/white background?
				// LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE

	//Para hacer que la imagen se proyecte sobre el plano del reflejo conforme al frustum de la camara
	tu->setProjectiveTexturing(true, camRef);
}

//Cuando el viewport de la camara cambia, ajustamos el frustum
void Rio::viewportDimensionsChanged(Viewport* viewport)
{	
	camRef->setNearClipDistance(mainCam->getNearClipDistance());
	camRef->setFarClipDistance(mainCam->getFarClipDistance());
	camRef->setAspectRatio(mainCam->getAspectRatio());
}

void Rio::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	//Mandar evento a todos (de momento solo a la cabeza), para que inviertan texturas si es necesario o lo que sea
	sendEvent(this, msgType::pre_render_reflejo);
}

void Rio::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	//Mandar evento a todos (de momento solo a la cabeza), para que vuelvan a default
	sendEvent(this, msgType::post_render_reflejo);
}
