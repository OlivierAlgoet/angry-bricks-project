#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#include "Allkit.h"
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
#include "MissileComponents.h"
#include "Sprite.h"
#include <set>
class RenderSystem: public System{
    public:
        ~RenderSystem(){};
        RenderSystem(Context& context,Engine& engine):context_(context),engine_(engine){
            ak_ = &Allkit::Get();
        };
        void Update();

    private:
        Allkit* ak_ = NULL;
        Context& context_;
        Engine& engine_;


};

#endif