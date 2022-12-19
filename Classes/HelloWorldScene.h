
#ifndef __MYWORLD_SCENE_H__
#define __MYWORLD_SCENE_H__
#include "cocos2d.h"
#include "player.h"
#include "key.h"
#include "box.h"
#include "door.h"
#include "light.h"



class MyWorld : public cocos2d::Layer
{
public:
    void update(float dt);
    void moveright(float dt);
    void moveleft(float dt);
    void movetop(float dt);
    void movebot(float dt);
    static cocos2d::Scene* createScene();

    virtual bool init();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    

    
    // implement the "static create()" method manually
    CREATE_FUNC(MyWorld);
    OurPlayer* player;
    OurKey* key;
    OurDoor* door;
    OurLight* lights;
    Sprite* wall;
    Sprite* laser;
    OurBox* box;
    Action* action;
    Action* action2;
    Action* action3;
    Action* action4;
};

#endif // __MYWORLD_SCENE_H__
