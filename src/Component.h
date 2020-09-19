#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    enum Tag {MISSILE1,MISSILE2,MISSILE3,
    CURRENTMISSILE,BOX,STONE,
    TARGET,POLYGON,CIRCLE,SPRITE,};    
    virtual Tag GetTag() = 0;
    virtual ~Component(){}; // virtual deconstructor important for easily deleting the heap components

};

#endif