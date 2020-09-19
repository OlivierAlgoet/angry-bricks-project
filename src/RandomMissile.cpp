#include "RandomMissile.h"
Entity* RandomMissile(double x, double y,Entity * ent){
    Component* cmp;
    Component* sprt;
    Component* pg;
    Point p;
    MissileOneComponent *m1;
    CircleComponent* c;
    int miss=std::rand()%MISS_NR;
    switch(miss){
        case 0:
            sprt= new SpriteComponent(SPRT_MISSILE_1);
            p=Point(x,y);
            m1=new MissileOneComponent;
            pg=new PolygonComponent(p,m1->rel_poly); // dynamic cast this
            c=new CircleComponent(p,m1->rel_center,m1->radius);
            ent->Add(c);
            cmp=m1;
            break;
        case 1:
            cmp=new MissileTwoComponent;
            sprt= new SpriteComponent(SPRT_MISSILE_2);
            p=Point(x,y);
            pg=new PolygonComponent(p,dynamic_cast<MissileTwoComponent*>(cmp)->rel_poly); // dynamic cast this
            break;
        case 2:
            cmp=new MissileThreeComponent;
            sprt= new SpriteComponent(SPRT_MISSILE_3);
            p=Point(x,y);
            pg=new PolygonComponent(p,dynamic_cast<MissileThreeComponent*>(cmp)->rel_poly); // dynamic cast this
            break;

    }
    ent->Add(cmp);
    ent->Add(sprt);
    ent->Add(pg);
    return ent;
}
