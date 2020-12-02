#pragma once
#include "Plano.h"
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreRenderTargetListener.h>

class Rio : public Plano, public RenderTargetListener, public Viewport::Listener
{
public:
	Rio(Ogre::SceneNode* rootNode, int n);
	~Rio() {
		delete mMovablePlane; mMovablePlane = nullptr;
	}
	void setReflejo(Camera* camara, Ogre::Viewport* windowViewport);
protected:

	virtual void viewportDimensionsChanged(Viewport* viewport);
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

	MovablePlane* mMovablePlane = nullptr;
	Entity* mEntity = nullptr;
	Camera* camRef = nullptr;
	Camera* mainCam = nullptr;
};

