#ifndef MISSILECOMPONENTS
#define MISSILECOMPONENTS
#include "Component.h"
#include "Point.h"
#include <vector>
#include "Constants.h"
// Polygon, circle hier al invoegen?
enum Action {UP,FAST,DOWN};
class MissileOneComponent: public Component
{
public:
    ~MissileOneComponent(){};
    bool activated=false;
    double radius=MISSILE_DST_HEIGHT/2;
    Point rel_center=Point(MISSILE_DST_WIDTH/2,MISSILE_DST_HEIGHT/2);
    std::vector <Point> rel_poly{Point(0,0),Point(0,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,0)};
    Tag GetTag(){return tg;}
private:
    Tag tg =MISSILE1;
};

class MissileTwoComponent: public Component
{
public:
    ~MissileTwoComponent(){};
    std::vector <Point> rel_poly{Point(0,0),Point(0,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,0)};
    Action act=DOWN;
    bool activated=false;
    Tag GetTag(){return tg;}
private:
    Tag tg =MISSILE2;
};

class MissileThreeComponent: public Component
{
public:
    ~MissileThreeComponent(){};
    std::vector <Point> rel_poly{Point(0,0),Point(MISSILE_DST_WIDTH/2,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,0)};
    Action act=FAST;
    bool activated=false;
    Tag GetTag(){return tg;}
private:
    Tag tg =MISSILE3;
};

class CurrentMissileComponent: public Component
{
public:
    ~CurrentMissileComponent(){};
    bool fired=false;
    bool selected=false;
    bool destroy_rocks=false;
    Point ClickCorrect=Point(0,0);
    Point speed=Point(0,0); // Will use easy linear dependence between stretch shooting mechanism
    Point accel=Point(0,-9.81*5); // assume constant gravity + extra assumption if y position goes negative speed sign changes (perfect elasticity)
    Tag GetTag(){return tg;}
private:
    Tag tg =CURRENTMISSILE;
};

#endif
