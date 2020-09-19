#ifndef MISSILESYSTEM_H
#define MISSILESYSTEM_H
#include "Engine.h"
#include "Context.h"
#include "Constants.h"
#include "Color.h"
#include "Point.h"
#include "System.h"
#include "Entity.h"
#include <vector>
#include "EntityStream.h"
#include "GeometryComponents.h"
#include "Sprite.h"
#include "MissileComponents.h"
#include "RandomMissile.h"
#include <set>
class MissileSystem: public System{
    public:
        ~MissileSystem(){};
        MissileSystem(Context& context,Engine& engine):context_(context),engine_(engine){};
        void Update();

    private:
        Context& context_;
        Engine& engine_;
        Component::Tag missile_list[MISS_NR]={Component::Tag::MISSILE1,Component::Tag::MISSILE2,Component::Tag::MISSILE3}; //Used for easy looping instead of long coded lists

};
#endif