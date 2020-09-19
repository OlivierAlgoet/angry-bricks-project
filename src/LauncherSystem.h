#ifndef LAUNCHERSYSTEM_H
#define LAUNCHERSYSTEM_H
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
class LauncherSystem: public System{
    public:
        ~LauncherSystem(){};
        LauncherSystem(Context& context,Engine& engine):context_(context),engine_(engine){};
        void Update();

    private:
        bool PolyCollision_(Point& mouse,std::vector<Point>& poly);
        Context& context_;
        Engine& engine_;
        Component::Tag missile_list[MISS_NR]={Component::Tag::MISSILE1,Component::Tag::MISSILE2,Component::Tag::MISSILE3};
        bool CircleCollision_(Point& mouse,Point& center,double radius);
        double DistanceBetweenPolys(double min_dotp_poly, double max_dotp_poly, double dotp_mouse);
        void ProjectOnAxis(std::vector<Point>& coordinates, Point& axis, double& min, double& max);
        std::vector<Point> GetEdges(std::vector<Point>& coordinates);

};

#endif