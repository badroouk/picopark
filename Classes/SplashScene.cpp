#include "SplashScene.h"
#include "menu.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    //Creating a scene
    auto scene = Scene::create();
    //Creating a layer
    auto Layer = SplashScene::create();
    //adding layer to scene
    scene->addChild(Layer);
    //returning the scene created
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    //creating auto of size of screen 
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //creating Vec2 of anchor point of screen 
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //executing method for switching this scene
    auto sprite1 = Sprite::create("HelloWorld.png");
    auto sprite2 = Sprite::create("logo.png");
    sprite1->setPosition(visibleSize.width-300, visibleSize.height/2);
    sprite1->setScale(1.1);
    sprite2->setPosition(visibleSize.width-700 , visibleSize.height / 2);
    sprite2->setScale(0.7);
    this->addChild(sprite1);
    this->addChild(sprite2);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::GoToMenuScene),1);
   return true;
}

//method for switching scenes
void SplashScene::GoToMenuScene(float dt) {
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create( 0.8, scene ));
}