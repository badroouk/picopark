
#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "cocos2d.h"
using namespace cocos2d;
//creating a class representing every image in the layer in other word every square in the layer surface and walls
class OurButton
{

public:

	cocos2d::Vec2 getposition();
	void setposition(float x, float y);
	cocos2d::Rect getrect();
	void removeFromParent();
	OurButton(cocos2d::Layer* layer);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	//desctructor
	//this is where we initiate the sprite with a file path,
	cocos2d::Sprite* button1;
	cocos2d::Sprite* button2;
	cocos2d::Sprite* button3;
	cocos2d::Sprite* button4;
	cocos2d::Sprite* button5;
	cocos2d::Sprite* button6;
	cocos2d::Sprite* button7;
	cocos2d::Sprite* button8;
	cocos2d::Sprite* button9;


};
#endif