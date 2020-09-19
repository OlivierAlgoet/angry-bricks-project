#include "EntityStream.h"


std::set<Entity*> EntityStream::WithTag(Component::Tag tag) {
    return tag_map[tag];
}

std::set<Entity*> EntityStream::WithTags(std::set<Component::Tag>& tags) {
    std::set<Entity*> interm;
	if (tags.empty()) return interm;
	
	interm = tag_map.find(*tags.begin())->second;
	std::set<Component::Tag>::iterator it = tags.begin();
	if (++it == tags.end()) return interm;
	for (; it != tags.end();it++){
		std::set<Entity*> s = tag_map[*it];
		set_intersection(interm.begin(), interm.end(), s.begin(), s.end(), inserter(interm, interm.begin()));
	}
	return interm;
}

void EntityStream::EntityUpdated(Entity* entity, std::vector<Component::Tag>& tags, bool remove) {
    // Chosen to always first erase the entities
    std::map<Component::Tag, std::set<Entity*>>::iterator it = tag_map.begin(); 
    for(;it!=tag_map.end();it++){
        it->second.erase(entity);
    }
    // Afterwards they are added again with the new tags
    if (!remove){ 
        std::vector<Component::Tag>::iterator it=tags.begin();
        for(;it!=tags.end();it++){
            tag_map[*it].insert(entity);
            
        }
    }   
}

