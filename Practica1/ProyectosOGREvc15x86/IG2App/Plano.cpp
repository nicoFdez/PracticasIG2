#include "Plano.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

Plano::Plano(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Plano"))
{
	MeshManager::getSingleton().createPlane("mPlane1080x800",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
	mNode->attachObject(plane);
}
