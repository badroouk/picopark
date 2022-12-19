
#ifndef __BOX_H__
#define __BOX_H__

#include "cocos2d.h"
using namespace cocos2d;
//creating a class representing every image in the layer in other word every square in the layer surface and walls
class OurBox
{

public:

	cocos2d::Vec2 getposition();
	void setposition(float x, float y);
	void setDynamic(bool dynamic);
	void fall();
	void removeFromParent();
	cocos2d::Rect getrect();
	OurBox(cocos2d::Layer* layer);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite* Pico;

	cocos2d::ParticleMeteor* particle;
};
#endif