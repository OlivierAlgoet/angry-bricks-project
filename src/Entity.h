#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <algorithm>
#include "Component.h"
#include  <algorithm>
class Entity
{
public:
    void Add(Component* component);

    void Remove(Component* component);

    Component* GetComponent(Component::Tag tag);

    std::vector<Component*>& GetComponents();
                                            
    std::vector<Component::Tag>& GetTags();

private:
    std::vector<Component*> _Components;
    std::vector<Component::Tag> _Tags;
};

#endif