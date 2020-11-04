#pragma once
#include "EntidadIG.h"

class Plano : public EntidadIG
{
public:
	Plano(Ogre::SceneNode* rootNode, std::string const& matName = "", int num = 0);
};

