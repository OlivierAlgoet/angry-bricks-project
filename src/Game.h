#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include "Engine.h"
#include "Allkit.h"
#include "Context.h"
#include "GeometryComponents.h"
#include "MissileComponents.h"
#include "LevelComponents.h"
#include "Component.h"
#include "Entity.h"
#include "Sprite.h"
#include "Point.h"
#include "RenderSystem.h"
#include "System.h"
#include "RandomMissile.h"
#include "MissileSystem.h"
#include "LauncherSystem.h"
#include "TargetSystem.h"

class Game
{
public:
    Game(Context& context) : context_(context),
                             engine_(context) {
        ak_ = &Allkit::Get();
        srand(time(NULL));
    };

    ~Game();
    bool Run();
    void init_Entities(char ** level);
    void init_Systems();

private:
    Point CoordinateTransform_(Point& p);
    Allkit* ak_ = NULL;
    Context& context_;
    Engine engine_;
    void Inputcapture_();
    
};

#endif