#include "EntidadIG.h"

std::vector<EntidadIG*> EntidadIG::appListeners = std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(SceneNode* nodo) {
	mNode = nodo;
	mSM = mNode->getCreator();
}

EntidadIG::~EntidadIG() {

}

void EntidadIG::sendEvent(EntidadIG* entidad, const OgreBites::KeyboardEvent& evt) {
	for (EntidadIG* e : appListeners)
		e->receiveEvent(this, evt);
}