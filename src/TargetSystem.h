#ifndef TARGETSYSTEM_H
#define TARGETSYSTEM_H

#include <vector>

#include "Point.h"
#include "System.h"
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
#include "Sprite.h"
#include "LevelComponents.h"
#include <set>

class TargetSystem : public System {
    public:
        ~TargetSystem(){};
        TargetSystem(Context& context,Engine& engine):context_(context),engine_(engine){};
        void Update();

    private:
        Component::Tag level_list[LEVEL_NR]={Component::Tag::STONE,Component::Tag::TARGET,Component::Tag::BOX};
        Sprite sprite_list[LEVEL_NR]={SPRT_STONE_HIT,SPRT_TARGET_HIT,SPRT_BOX_HIT};
        bool CheckCollision(std::vector<Point>& coordinates_poly_one, std::vector<Point>& coordinates_poly_two);

        std::vector<Point> GetEdges(std::vector<Point>& coordinates);

        void ProjectOnAxis(std::vector<Point>& coordinates, Point& axis, double& min, double& max);

        double DistanceBetweenPolys(double min_a, double max_a, double min_b, double max_b);
        Context& context_;
        Engine& engine_;
        bool to_delete=false;
        std::vector<Point>* _check_hits(Component::Tag tg,Sprite spr);
        void _delete_entity(Entity* ent);
        void _replace_components(std::vector<Point>& replaced_points);
        void _check_end();
        void chain_collision(Point& p,Point& speed);
};

#endif