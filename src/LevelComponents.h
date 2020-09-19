#ifndef LEVELCOMPONENTS
#define LEVELCOMPONENTS
#include "Component.h"
#include "Point.h"
#include <vector>
#include "Constants.h"
// All components related to the level
class BoxComponent: public Component
{
public:
    ~BoxComponent(){};
    std::vector <Point> rel_poly{Point(0,0),Point(0,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,0)};
    Tag GetTag(){return tg;}
private:
    Tag tg =BOX;
};

class TargetComponent: public Component
{
public:
    ~TargetComponent(){};
    std::vector <Point> rel_poly{Point(0,0),Point(0,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,0)};
    Tag GetTag(){return tg;}
private:
    Tag tg =TARGET;
};

class StoneComponent: public Component
{
public:
    bool destroyed=false; // A stone can be destroyed by a special missile action
    ~StoneComponent(){};
    std::vector <Point> rel_poly{Point(MISSILE_DST_WIDTH/2,0),Point(0,MISSILE_DST_HEIGHT/2),Point(MISSILE_DST_WIDTH/2,MISSILE_DST_HEIGHT),Point(MISSILE_DST_WIDTH,MISSILE_DST_HEIGHT/2)};
    Tag GetTag(){return tg;}
private:
    Tag tg =STONE;
};

#endif
