#include "GameOver.h"
#include "AudioEngine.h"

USING_NS_CC;
Scene* GameOver::createScene()
{
    
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    LayerColor* _bgColor = LayerColor::create(Color4B(206, 248, 252, 255));
    this->addChild(_bgColor, -10);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto youwin = Sprite::create("youwin.png");
    youwin->setPosition(Point((visibleSize.width/2) + origin.x, (visibleSize.height / 2) + origin.y));
    youwin->setScale(1.5);
    this->addChild(youwin);

    /*auto celeb1 = ParticleFireworks::create();
    celeb1->setPosition(Point((visibleSize.width ) + origin.x, (visibleSize.height/2 ) + origin.y));
    celeb1->setDuration(3);
    celeb1->setAngle(120);
    this->addChild(celeb1);

    auto celeb2 = ParticleFireworks::create();
    celeb2->setPosition(Point(visibleSize.width /2.5, (visibleSize.height/2 ) + origin.y));
    celeb2->setDuration(3);
    celeb2->setAngle(55);
    this->addChild(celeb2);*/

   
    };

