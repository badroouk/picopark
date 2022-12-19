#include "HelloWorldScene.h"
#include "Lvl2.h"
#include "AudioEngine.h"

USING_NS_CC;
bool ifUpPressed = false;
bool ifDpressed = false;
bool ifApressed = false;
bool ismoving = false;
bool ifSpacePressed = false;
bool doorOpened = false;
bool isOnGround = true;
bool ispushing = false;
bool isLight = true;
bool keycollected = false;
Scene* MyWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -400));
    auto layer = MyWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there

// on "init" you need to initialize your instance
bool MyWorld::init()
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

    wall = Sprite::create("ground.png");
    wall->setScale(0.5);
    auto Frame4body = PhysicsBody::createBox(Size(wall->getContentSize().width, wall->getContentSize().height), PhysicsMaterial(0, 0, 0));
    Frame4body->setCollisionBitmask(2);
    Frame4body->setContactTestBitmask(true);
    wall->setPosition(Point( origin.x+200,  origin.y+15));
    if (Frame4body != nullptr)
    {
        Frame4body->setDynamic(false);
        wall->setPhysicsBody(Frame4body);
    }
    this->addChild(wall);

    auto gound2 = Sprite::create("ground.png");
    gound2->setScale(0.5);
    auto gound2body = PhysicsBody::createBox(Size(gound2->getContentSize().width, gound2->getContentSize().height ), PhysicsMaterial(0, 0, 0));
    gound2body->setCollisionBitmask(2);
    gound2body->setContactTestBitmask(true);
    gound2->setPosition(Point(origin.x +920, origin.y + 15));
    if (gound2body != nullptr)
    {
        gound2body->setDynamic(false);
        gound2->setPhysicsBody(gound2body);
    }
    this->addChild(gound2);
    laser = Sprite::create("redlaser.png");
    laser->setPosition(Point(origin.x + 560, origin.y + 30));
    laser->setScale(0.5);
    this->addChild(laser);


    player = new OurPlayer(this, !isOnGround,ismoving,!ismoving);
    key = new OurKey(this);
    door = new OurDoor(this);
    box = new OurBox(this);
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
               
               
                ifApressed = true;
                    this->schedule(SEL_SCHEDULE(&MyWorld::moveleft), 0.01);
                    
                    
                    
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
      
                ifDpressed = true;
                    this->schedule(SEL_SCHEDULE(&MyWorld::moveright), 0.01);
                 
                   
                 
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                if (ifSpacePressed == false)
                {
                   
              
                    this->schedule(SEL_SCHEDULE(&MyWorld::movetop), 0.01);
                    ifSpacePressed = true;
                    isOnGround = false;
                    cocos2d::AudioEngine::preload("audio/jump.mp3");
                    cocos2d::AudioEngine::play2d("audio/jump.mp3", false, 0.3f);
                }
                
                   
                    
            
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                ifUpPressed = true;

                break;
                  
            } 

      



    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
   
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                ifApressed = false;
                    this->unschedule(SEL_SCHEDULE(&MyWorld::moveleft));
                   
                    cocos2d::AudioEngine::pauseAll();
                   
                 
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
        
                ifDpressed = false;
                    cocos2d::AudioEngine::pauseAll();
                    this->unschedule(SEL_SCHEDULE(&MyWorld::moveright));
                  
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:

               
                    this->unschedule(SEL_SCHEDULE(&MyWorld::movetop));
                   
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                ifUpPressed = false;

                break;
         
            }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    //we create a contact listener to detect the collision of the ball with te walls and the obstacles
    auto contactListener = EventListenerPhysicsContact::create();
    //make a call back to the function everytime a contact happen
    contactListener->onContactBegin = CC_CALLBACK_1(MyWorld::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}
void MyWorld::moveright(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x + 80* dt, playerPos.y);
}
void MyWorld::moveleft(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x - 80 * dt, ballpos.y);
}
void MyWorld::movebot(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y -80 * dt);
}
void MyWorld::movetop(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y + 160 * dt);
}

bool MyWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    auto p = contact.getContactData()->points;

    // check if the bodies have collided
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        ifSpacePressed = false;
        isOnGround = true;
    }
    if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        if (ifDpressed)
        {
            this->unschedule(SEL_SCHEDULE(&MyWorld::moveright));
            player->setposition(player->getposition().x - 10, player->getposition().y);
        }
        else if (ifApressed)
        {
            this->unschedule(SEL_SCHEDULE(&MyWorld::moveleft));
            player->setposition(player->getposition().x + 10, player->getposition().y);
        }
    }
    if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        ispushing = true;
        ifSpacePressed = false;
        if (ifDpressed) {
            box->setposition(box->getposition().x + 4, box->getposition().y);
           
        }
        else if (ifApressed)
        {
            box->setposition(box->getposition().x - 4, box->getposition().y);
        }
      
    }

    if ((3 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()))
    {
        box->fall();
        box->removeFromParent();
        log("oh noooo");

    }
    return true;
}
 


void MyWorld::update(float dt) {

        Rect rect1 = player->getrect();
        Rect rect2 = key->getrect();
        Rect rect3 = door->getrect();
        Rect rect4 = box->getrect();
        Rect rect5 = wall->getBoundingBox();
        Rect rect6 = laser->getBoundingBox();
        auto v = Director::getInstance()->getWinSize();
        Layer::setAnchorPoint(Vec2(player->getposition().x / v.width, player->getposition().y /v.height));

        if (rect1.intersectsRect(rect2))
        {
            key->setposition(player->getposition().x-10, player->getposition().y + 10);
            if (!keycollected)
            {
                cocos2d::AudioEngine::preload("audio/key.mp3");
                cocos2d::AudioEngine::play2d("audio/key.mp3", false, 0.3f);
                keycollected = true;
            }
          
            
            
        }
        if (rect2.intersectsRect(rect3) && ifUpPressed == true && doorOpened == false) {
            key->removeFromParent();
            door->OpenDoor();
          //  ifDpressed = true;
            doorOpened = true;
            ifUpPressed = false;
            cocos2d::AudioEngine::preload("audio/door.mp3");
            cocos2d::AudioEngine::play2d("audio/door.mp3", false, 0.3f);
        }
        if (rect1.intersectsRect(rect3) && doorOpened == true && ifUpPressed==true) {
            ifUpPressed = false;
            auto scene = Lvl2::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }
        if (!rect5.intersectsRect(rect4))
      
        {
            box->setDynamic(true);
        }
        if (ifApressed)
        {
            player->turnLeft(180);
        }
        else if (ifDpressed)
        {
            player->turnRight();

        }
        if (rect1.intersectsRect(rect6))
        {
            doorOpened = false;
            auto scene = MyWorld::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }

        //condition to moove to next level 

}