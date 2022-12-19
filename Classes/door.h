
#ifndef __DOOR_H__
#define __DOOR_H__

#include "cocos2d.h"
using namespace cocos2d;
//creating a class representing every image in the layer in other word every square in the layer surface and walls
class OurDoor
{

public:
	bool exist;
	cocos2d::Vec2 getposition();
	void setposition(float x, float y);
	void setposition2(float x, float y);
	cocos2d::Rect getrect();
	void OpenDoor();
	OurDoor(cocos2d::Layer* layer);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	//desctructor
	//this is where we initiate the sprite with a file path,
	cocos2d::Sprite* Door;
	cocos2d::Sprite* OpenedDoor;
};
#endif