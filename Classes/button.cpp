#include "button.h"

USING_NS_CC;

OurButton::OurButton(cocos2d::Layer* layer) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	button1 = Sprite::create("button.png");
	button1->setScale(0.10);
	button1->setPosition(Point(origin.x + 250, origin.y + 50));
	auto  b1 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b1->setCollisionBitmask(5);
	b1->setContactTestBitmask(true);
	b1->setDynamic(false);
	auto timeTxt0 = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt0->setTextColor(Color4B::BLACK);
	timeTxt0->setPosition(Vec2(origin.x + 250, origin.y + 60));
	auto  b2 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b2->setCollisionBitmask(5);
	b2->setContactTestBitmask(true);
	b2->setDynamic(false);
	auto  b3 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b3->setCollisionBitmask(5);
	b3->setContactTestBitmask(true);
	b3->setDynamic(false);
	auto  b6 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b6->setCollisionBitmask(5);
	b6->setContactTestBitmask(true);
	b6->setDynamic(false);
	auto  b7 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b7->setCollisionBitmask(5);
	b7->setContactTestBitmask(true);
	b7->setDynamic(false);
	auto  b8 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b8->setCollisionBitmask(5);
	b8->setContactTestBitmask(true);
	b8->setDynamic(false);
	auto  b9 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
	b9->setCollisionBitmask(5);
	b9->setContactTestBitmask(true);
	b9->setDynamic(false);

	button1->setPhysicsBody(b1);
	button2 = Sprite::create("button.png");
	button2->setScale(0.10);
	button2->setPosition(Point(origin.x + 320, origin.y + 50));
	button2->setPhysicsBody(b2);
	auto timeTxt = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt->setTextColor(Color4B::BLACK);
	timeTxt->setPosition(Vec2(origin.x + 320, origin.y + 60));
	button3 = Sprite::create("button.png");
	button3->setScale(0.10);
	button3->setPosition(Point(origin.x + 390, origin.y + 50));
	button3->setPhysicsBody(b3);
	auto timeTxt2 = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt2->setTextColor(Color4B::BLACK);
	timeTxt2->setPosition(Vec2(origin.x + 390, origin.y + 60));
	button6 = Sprite::create("button.png");
	button6->setScale(0.10);
	button6->setPosition(Point(origin.x + 580, origin.y + 50));
	button6->setPhysicsBody(b6);
	auto timeTxt3 = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt3->setTextColor(Color4B::BLACK);
	timeTxt3->setPosition(Vec2(origin.x + 580, origin.y + 60));
	button7 = Sprite::create("button.png");
	button7->setScale(0.10);
	button7->setPosition(Point(origin.x + 650, origin.y + 50));
	button7->setPhysicsBody(b7);
	auto timeTxt4 = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt4->setTextColor(Color4B::BLACK);
	timeTxt4->setPosition(Vec2(origin.x + 650, origin.y + 60));
	button8 = Sprite::create("button.png");
	button8->setScale(0.10);
	button8->setPosition(Point(origin.x + 710, origin.y + 50));
	button8->setPhysicsBody(b8);
	auto timeTxt5 = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt5->setTextColor(Color4B::BLACK);
	timeTxt5->setPosition(Vec2(origin.x + 710, origin.y + 60));
	button9 = Sprite::create("button.png");
	button9->setScale(0.10);
	button9->setPosition(Point(origin.x + 770, origin.y + 50));
	button9->setPhysicsBody(b9);
	auto timeTxt6 = Label::createWithTTF("dont touch", "fonts/Marker Felt.ttf", 15);
	timeTxt6->setTextColor(Color4B::BLACK);
	timeTxt6->setPosition(Vec2(origin.x + 770, origin.y + 60));
	layer->addChild(button1, 1);
	layer->addChild(button2, 1);
	layer->addChild(button3, 1);
	layer->addChild(button6, 1);
	layer->addChild(button7, 1);
	layer->addChild(button8, 1);
	layer->addChild(button9, 1);
	layer->addChild(timeTxt0,1);
};

cocos2d::Vec2 OurButton::getposition() {
	return button1->getPosition();
}

void  OurButton::setposition(float x, float y) {
	button1->setPosition(Point(x, y));
}
void OurButton::removeFromParent() {
	button1 ->setVisible(false);
}

cocos2d::Rect OurButton::getrect() {
	return button1->getBoundingBox();
}