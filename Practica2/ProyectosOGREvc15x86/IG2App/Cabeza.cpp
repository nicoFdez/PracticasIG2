#include "Cabeza.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>

Cabeza::Cabeza(Ogre::SceneNode* rootNode) : EntidadIG(rootNode->createChildSceneNode("Cabeza"))
{
	ent = mSM->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/cabezaAmarilla");
	mNode = mSM->getRootSceneNode()->createChildSceneNode("cabezaAmarilla");
	mNode->attachObject(ent);
}

void Cabeza::receiveEvent(EntidadIG* entidad, msgType evt)
{
	if (evt == msgType::pre_render_reflejo) {
		ent->setMaterialName("Practica2/cabezaAmarillaInvertida");
	}
	else if (evt == msgType::post_render_reflejo) {
		ent->setMaterialName("Practica1/cabezaAmarilla");
	}
}
