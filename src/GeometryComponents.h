#ifndef GEOMETRIC
#define GEOMETRIC
#include "Component.h"
#include "Point.h"
#include "Sprite.h"
#include <vector>

class PolygonComponent: public Component
/*for this class setters and getters are used since the polygon should automatically change when
  the position is changed*/
{
public:
    ~PolygonComponent(){};
    PolygonComponent(Point& pos,std::vector<Point> &rel_poly){
        this->pos=pos;
        std::vector<Point>::iterator it=rel_poly.begin();
        for(;it!=rel_poly.end();it++){
            polygon.push_back(Point(it->x_+pos.x_,it->y_+pos.y_));  // shallow copy constructor of point used in vector
        }
    };
    void set_position(Point& new_pos){
        std::vector<Point>::iterator it=polygon.begin();
        for(;it!=polygon.end();it++){
            *it=*it+new_pos-pos;
        }
        pos=new_pos;//invoke shallow copy constructor of point class
    };
    Point& get_position(){
        return pos;
    };

    std::vector<Point>& get_polygon(){
        return polygon;
    };
    
    
    Tag GetTag(){return tg;};
private:
    Tag tg=POLYGON;
    Point pos;
    std::vector<Point> polygon;
};

class CircleComponent: public Component
/*for this class setters and getters are used since the circle should automatically change when
  the position is changed*/
{
public:
    ~CircleComponent(){};
    CircleComponent(Point& pos,Point &rel_center,double radius){
        this->pos=pos;this->center=rel_center+pos;this->radius=radius;}
    
    double radius;
    void set_pos(Point& new_pos){
        center=center+new_pos-pos;
        pos=new_pos;
    }
    Point& get_pos(){return pos;}
    Point& get_center(){return center;}
    Tag GetTag(){return tg;}
private:
    Tag tg=CIRCLE;
    Point pos;
    Point center;
};

class SpriteComponent: public Component
{
public:
    ~SpriteComponent(){};
    SpriteComponent(Sprite sprt){this->sprt=sprt;}
    Tag GetTag(){return tg;}
    Sprite sprt;
private:
    Tag tg=SPRITE;
};
#endif
