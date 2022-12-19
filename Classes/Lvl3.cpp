#include "Lvl3.h"
#include "GameOver.h"
#include "ui/UITextField.h"
#include "AudioEngine.h"

USING_NS_CC;
bool UpPressed = false;
bool Dpressed = false;
bool Apressed = false;
bool moving = false;
bool SpacePressed = false;
bool ifDoorOpened = false;
bool Ground = true;
bool buttonPressed = false;
bool haveKey = false;

Scene* Lvl3::createScene()
{
    auto scene = Scene::createWithPhysics();
 // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -400));
    //scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
    auto layer = Lvl3::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there

// on "init" you need to initialize your instance
bool Lvl3::init()
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
    wall->setPosition(Point( origin.x+500,  origin.y+20));
    if (Frame4body != nullptr)
    {
        Frame4body->setDynamic(false);
        wall->setPhysicsBody(Frame4body);
    }
    this->addChild(wall);


    player = new OurPlayer(this,!Ground , moving,!moving);
    player->setposition(origin.x + 300, origin.y + 80);
    key = new OurKey(this);
    key->setposition(origin.x + 500, origin.y +220);
    door = new OurDoor(this);
    door->setposition(origin.x + 680, origin.y + 90);
    door->setposition2(origin.x + 680, origin.y + 90);
    auto button1 = Sprite::create("button.png");
    button1->setScale(0.10);
    button1->setPosition(Point(origin.x + 500, origin.y + 50));
    auto  b1 = PhysicsBody::createBox(button1->getContentSize(), PhysicsMaterial(0, 0, 0));
    button1->setPhysicsBody(b1);
    this->addChild(button1);
    b1->setCollisionBitmask(5);
    b1->setContactTestBitmask(true);
    b1->setDynamic(false);
    auto camera = Camera::create();
    camera->setPositionZ(5);
    camera->clearBackground();
    this->addChild(camera);
    time = 10.0;
    this->scheduleUpdate();
    timeTxt = Label::createWithTTF("0","fonts/Marker Felt.ttf", 15);
    timeTxt->setTextColor(Color4B::BLACK);
    timeTxt->setPosition(Vec2(origin.x + 500, origin.y + 125));
    this->addChild(timeTxt);
    inst = Label::createWithTTF("x greater than 0 and smaller than 0.3", "fonts/Marker Felt.ttf", 15);
    inst->setTextColor(Color4B::BLACK);
    inst->setPosition(Vec2(origin.x + 500, origin.y + 300));
    this->addChild(inst);


    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
     
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
            case EventKeyboard::KeyCode::KEY_A:
               
                Apressed = true;
               
                    this->schedule(SEL_SCHEDULE(&Lvl3::moveleft), 0.01);
                
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
               
                Dpressed = true;
               
                    this->schedule(SEL_SCHEDULE(&Lvl3::moveright), 0.01);
                 
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:
                if (SpacePressed == false)
                {
                    this->schedule(SEL_SCHEDULE(&Lvl3::movetop), 0.01);
                    SpacePressed = true;
                    Ground = false;
                    cocos2d::AudioEngine::preload("audio/jump.mp3");
                    cocos2d::AudioEngine::play2d("audio/jump.mp3", false, 0.3f);
                }
                
                   
                    
            
                break;
          
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                UpPressed = true;

                break;
                  
            } 

      



    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
   
            switch (keyCode) {
                //case wich key is pressed
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
              
                Apressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl3::moveleft));

                    cocos2d::AudioEngine::pauseAll();
                 
                break;
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
              
                Dpressed = false;
                    this->unschedule(SEL_SCHEDULE(&Lvl3::moveright));

                    cocos2d::AudioEngine::pauseAll();
                break;
            case EventKeyboard::KeyCode::KEY_SPACE:
            case EventKeyboard::KeyCode::KEY_W:

                    this->unschedule(SEL_SCHEDULE(&Lvl3::movetop));
                   
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
             
                    this->unschedule(SEL_SCHEDULE(&Lvl3::movebot));
                   
                break;
            case EventKeyboard::KeyCode::KEY_UP_ARROW:

                UpPressed = false;

                break;
         
            }
    };

    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    //we create a contact listener to detect the collision of the ball with te walls and the obstacles
    auto contactListener = EventListenerPhysicsContact::create();
    //make a call back to the function everytime a contact happen
    contactListener->onContactBegin = CC_CALLBACK_1(Lvl3::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}
void Lvl3::moveright(float dt) {
    Vec2 playerPos = player->getposition();
    player->setposition(playerPos.x + 80* dt, playerPos.y);
}
void Lvl3::moveleft(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x - 80 * dt, ballpos.y);
}
void Lvl3::movebot(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y -80 * dt);
}
void Lvl3::movetop(float dt) {
    Vec2 ballpos = player->getposition();
    player->setposition(ballpos.x, ballpos.y + 160 * dt);
}

bool Lvl3::onContactBegin(cocos2d::PhysicsContact& contact)
{
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    auto p = contact.getContactData()->points;

    // check if the bodies have collided
    if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        SpacePressed = false;
        Ground = true;
    }
    else if ((1 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask()) || (3 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        ifDoorOpened = false;
        auto scene = Lvl3::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
    }
    else if ((1 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask()) || (5 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
        buttonPressed = true;
        
    }
    else if ((1 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask()) || (4 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
    {
        SpacePressed = false;
      
    }
    return true;
}
 


void Lvl3::update(float dt) {
        
        Rect rect1 = player->getrect();
        Rect rect2 = key->getrect();
        Rect rect3 = door->getrect();
        Rect rect5 = wall->getBoundingBox();
        auto v = Director::getInstance()->getWinSize();
        Layer::setAnchorPoint(Vec2(player->getposition().x / v.width, player->getposition().y /v.height));
        if (time <= 0.0f) {
            time = 0;
            log("%f", time);
            ifDoorOpened = false;
            auto scene = Lvl3::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }
        else if (!buttonPressed)
        {
            time -= dt;
            std::string mytime = std::to_string(time);
            timeTxt->setString(mytime);
           
        }
        else if (buttonPressed) {
            std::string mytime = std::to_string(time);
            timeTxt->setString(mytime);
            if (time <= 0.3 && time >=0)
            {
                key->getkey();
            }
            else
            {
                buttonPressed = false;
                auto scene = Lvl3::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
            }
        }
         
        if (rect1.intersectsRect(rect2))
        {
            key->setposition(player->getposition().x-10, player->getposition().y + 10);
            
            if (!haveKey)
            {
                cocos2d::AudioEngine::preload("audio/key.mp3");
                cocos2d::AudioEngine::play2d("audio/key.mp3", false, 0.3f);
                haveKey = true;
            }

        }
        if (rect2.intersectsRect(rect3) && UpPressed == true && ifDoorOpened == false) {
            key->removeFromParent();
            door->OpenDoor();
            //isDpressed = true;
            ifDoorOpened = true;
            UpPressed = false;
            cocos2d::AudioEngine::preload("audio/door.mp3");
            cocos2d::AudioEngine::play2d("audio/door.mp3", false, 0.3f);
            log("colisin key still here");
        }
        if (rect1.intersectsRect(rect3) && ifDoorOpened == true && UpPressed==true) {
            UpPressed = false;
            auto scene = GameOver::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.2, scene));
        }
        if (Apressed)
        {
            player->turnLeft(180);
        }
        else if (Dpressed)
        {
            player->turnRight();

        }

        //condition to moove to next level 

}