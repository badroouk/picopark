
#ifndef __Lvl2_H__
#define __Lvl2_H__
#include "cocos2d.h"
#include "player.h"
#include "key.h"
#include "box.h"
#include "door.h"
#include "button.h"



class Lvl2 : public cocos2d::Layer
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
    CREATE_FUNC(Lvl2);
    OurPlayer* player;
    OurKey* key;
    OurDoor* door;
    Sprite* wall;
    Sprite* laser;
    OurButton* button;
    Action* action;
    Action* action2;
};

#endif // __Lvl2_H__
