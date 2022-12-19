#include "key.h"

USING_NS_CC;

OurKey::OurKey(cocos2d::Layer* layer) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Pico = Sprite::create("key.png");
	Pico->setScale(0.25);
	Pico->setPosition(Point(origin.x +550, origin.y+150));
	layer->addChild(Pico, 1);
};

cocos2d::Vec2 OurKey::getposition() {
	return Pico->getPosition();
}

void  OurKey::setposition(float x, float y) {
	Pico->setPosition(Point(x, y));
}
void OurKey::removeFromParent() {
	Pico ->setVisible(false);
}
void OurKey::getkey(){
	auto action = MoveBy::create(20, Vec2(0,-1));
	Pico->runAction(action);
}
cocos2d::Rect OurKey::getrect() {
	return Pico->getBoundingBox();
}