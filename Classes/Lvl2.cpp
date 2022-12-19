#include "Lvl2.h"
#include "Lvl3.h"
#include "AudioEngine.h"

USING_NS_CC;
bool isUpPressed = false;
bool isDpressed = false;
bool isApressed = false;
bool imoving = false;
bool isSpacePressed = false;
bool isdoorOpened = false;
bool OnGround = true;
bool isKeycollected = false;

Scene* Lvl2::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, -400));
    auto layer = Lvl2::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there

// on "init" you need to initialize your instance
bool Lvl2::init()
{
    if (!Layer::init())
    {
        return false;
    }

    //------------------------------------------------------------create backgroud color-------------------------------------------------

    LayerColor* _bgColor = LayerColor::create(Color4B(206, 248, 252, 255));
    this->addChild(_bgColor, -10);

    //---------------------------------------------create variables for positioning our instance-------------------------------------------------------

    auto visibleSize = Director::getInstance()->getWinSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //-------------------------------------------------create an edge box for our game------------------------------------------------------

    auto edgebody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgebody->setCollisionBitmask(3);
    edgebody->setContactTestBitmask(true);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point((visibleSize.width / 2) , (visibleSize.height / 2)));
    edgeNode->setPhysicsBody(edgebody);
    this->addChild(edgeNode);
    
    this->setScale(1.3);
   // this->setScaleY(1.2);
    //this->setScaleZ(1);
    wall = Sprite::create("ground.png");
    wall->setScale(0.4);
    auto Frame4body = PhysicsBody::createBox(Size(wall->getContentSize().width, wall->getContentSize().height), PhysicsMaterial(0, 0, 0));
    Frame4body->setCollisionBitmask(2);
    Frame4body->setContactTestBitmask(true);
    wall->setPosition(Point( origin.x+220,  origin.y+20));
    if (Frame4body != nullptr)
    {
        Frame4body->setDynamic(false);
        wall->setPhysicsBody(Frame4body);
    }
    this->addChild(wall);

    auto gound2 = Sprite::create("ground.png");
    gound2->setScale(0.4);
    auto gound2body = PhysicsBody::createBox(Size(gound2->getContentSize().width, gound2->getContentSize().height), PhysicsMaterial(0, 0, 0));
    gound2body->setCollisionBitmask(2);
    gound2body->setContactTestBitmask(true);
    gound2->setPosition(Point(origin.x +780, origin.y + 20));
    if (gound2body != nullptr)
    {
        gound2body->setDynamic(false);
        gound2->setPhysicsBody(gound2body);
    }
    this->addChild(gound2);

    player = new OurPlayer(this,!OnGround,imoving,!imoving);
    key = new OurKey(this);
    key->setposition(origin.x + 500, origin.y + 125);
    door = new OurDoor(this);
  //  door->setposition(visibleSize.width - 100, visibleSize.height + 85);
    button = new OurButton(this);
    laser = Sprite::create("redlaser.png");
    laser->setPosition(Point(origin.x + 500, origin.y + 30));
    laser->setScale(0.3);
    this->addChild(laser);
    auto camera = Camera::create();
    camera->setPositionZ(5);
    camera->clearBackground();
    this->addChild(camera);
    this->scheduleUpdate();


    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
     
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
            case EventKeyboard::KeyCode::KEY_A:
                
              
                isApressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl2::moveleft), 0.01);
                  
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
               
                isDpressed = true;
                    this->schedule(SEL_SCHEDULE(&Lvl2::moveright), 0.01);
                 
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                if (isSpacePressed == false)
                {
                    cocos2d::AudioEngine::preload("audio/jump.mp3");
                    cocos2d::AudioEngine::play2d("audio/jump.mp3", false, 0.3f);
                    this->schedule(SEL_SCHEDULE(&Lvl2::movetop), 0.01);
                    isSpacePressed = true;
                    OnGround = false;
                }
                
                   
                    
            
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                isUpPressed = true;

                break;
                  
            } 

      



    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
   
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
               
                isApressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl2::moveleft));
                    cocos2d::AudioEngine::pauseAll();
                 
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                isDpressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl2::moveright));
                    cocos2d::AudioEngine::pauseAll();
                  
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:

                    this->unschedule(SEL_SCHEDULE(&Lvl2::movetop));
                   
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
             
                    this->unschedule(SEL_SCHEDULE(&Lvl2::movebot));
                   
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                isUpPressed = false;

                break;
         
            }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    //we create a contact listener to detect the collision of the ball with te walls and the obstacles
    auto contactListener = EventListenerPhysicsContact::create();
    //make a call back to the function everytime a contact happen
    contactListener->onContactBegin = CC_CALLBACK_1(Lvl2::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}
void Lvl2::moveright(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x + 80* dt, playerPos.y);
}
void Lvl2::moveleft(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x - 80 * dt, playerPos.y);
}
void Lvl2::movebot(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x, playerPos.y -80 * dt);
}
void Lvl2::movetop(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x, playerPos.y + 160 * dt);
}

bool Lvl2::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    auto p = contact.getContactData()->points;

    // check if the bodies have collided
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        isSpacePressed = false;
        OnGround = true;
    }
    else if ((1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask()) || (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        isdoorOpened = false;
        auto scene = Lvl2::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
       
    }
    else if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        isSpacePressed = false;
      
    }
    if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        if (isDpressed)
        {
            player->setposition(player->getposition().x - 40, player->getposition().y);
           
        }
        else if (isApressed)
        {
            player->setposition(player->getposition().x + 40, player->getposition().y);
          
        }
    }
    return true;
}
 


void Lvl2::update(float dt) {
        Rect rect1 = player->getrect();
        Rect rect2 = key->getrect();
        Rect rect3 = door->getrect();
        Rect rect5 = wall->getBoundingBox();
        Rect rect6 = laser->getBoundingBox();
        auto v = Director::getInstance()->getWinSize();
        Layer::setAnchorPoint(Vec2(player->getposition().x / v.width, player->getposition().y /v.height));

        if (rect1.intersectsRect(rect2))
        {
            key->setposition(player->getposition().x-10, player->getposition().y + 10);
            if (!isKeycollected)
            {
                cocos2d::AudioEngine::preload("audio/key.mp3");
                cocos2d::AudioEngine::play2d("audio/key.mp3", false, 0.3f);
                isKeycollected = true;
            }

            
            
        }
        if (rect2.intersectsRect(rect3) && isUpPressed == true && isdoorOpened == false) {
            key->removeFromParent();
            door->OpenDoor();
            //isDpressed = true;
            isdoorOpened = true;
            isUpPressed = false;
            cocos2d::AudioEngine::preload("audio/door.mp3");
            cocos2d::AudioEngine::play2d("audio/door.mp3", false, 0.3f);
            log("colisin key still here");
        }
        if (rect1.intersectsRect(rect3) && isdoorOpened == true && isUpPressed==true) {
            isUpPressed = false;
            auto scene = Lvl3::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }
        if (isApressed)
        {

            player->turnLeft(180);
        }
        else if (isDpressed)
        {
            player->turnRight();

        }
        if (rect1.intersectsRect(rect6))
        {
            isdoorOpened = false;
            auto scene = Lvl2::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }

        //condition to moove to next level 

}