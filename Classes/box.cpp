#include "box.h"

USING_NS_CC;

OurBox::OurBox(cocos2d::Layer* layer) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	Pico = Sprite::create("box.png");
	Pico->setScale(0.3);
	Pico->setPosition(Point(origin.x+300, origin.y+68));
	auto  Playerbody = PhysicsBody::createBox(Pico->getContentSize(), PhysicsMaterial(0, 0, 0));
	Playerbody->setCollisionBitmask(4);
	Playerbody->setContactTestBitmask(true);
	Playerbody->setDynamic(false);
	Pico->setPhysicsBody(Playerbody);
	particle = ParticleMeteor::create();
	particle->setDuration(ParticleSystem::DURATION_INFINITY);
	particle->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	particle->setPositionX(181.759995);
	particle->setPositionY(78.048782);
	particle->setGravity(Vec2(0, 0));
	particle->setScale(0.6);
	particle->setStartSize(50);
	particle->setEndSize(50);
	particle->setLife(0.09);
	particle->setTotalParticles(100);
	Color4F color = { 255, 165, 1,1 };
	particle->setStartColor(color);


	layer->addChild(particle, 1);
	layer->addChild(Pico, 1);
};

cocos2d::Vec2 OurBox::getposition() {
	return Pico->getPosition();
}

void  OurBox::setDynamic(bool dynamic) {
	Pico->getPhysicsBody()->setDynamic(dynamic);
}
void  OurBox::setposition(float x, float y) {
	Pico->setPosition(Point(x, y));
}
void OurBox::fall() {
	Pico->getPhysicsBody()->removeFromWorld();
}
void OurBox::removeFromParent() {
	Pico->setVisible(false);
}
cocos2d::Rect OurBox::getrect() {
	return Pico->getBoundingBox();
}
