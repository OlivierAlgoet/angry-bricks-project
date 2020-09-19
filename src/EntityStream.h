#ifndef ENTITYSTREAM_H
#define ENTITYSTREAM_H

#include <set>
#include <map>
#include "Entity.h"

class EntityStream
{
public:
    std::set<Entity*> WithTag(Component::Tag tag);

    std::set<Entity*> WithTags(std::set<Component::Tag>& tags);

    void EntityUpdated(Entity* entity, std::vector<Component::Tag>& tags, bool remove);
private:
    std::map<Component::Tag, std::set<Entity*>> tag_map;
};

#endif