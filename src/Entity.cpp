#include "Entity.h"


void Entity::Add(Component* component) {
    _Components.push_back(component);
    _Tags.push_back(component->GetTag());
}

void Entity::Remove(Component* component) {
    std::vector<Component*>::iterator it = std::find(_Components.begin(), _Components.end(), component);
    if(it!=_Components.end()){
        _Tags.erase(_Tags.begin()+(it-_Components.begin()));
        _Components.erase(it);
    }
}

Component* Entity::GetComponent(Component::Tag tag) {
    std::vector<Component::Tag>::iterator it = std::find(_Tags.begin(), _Tags.end(), tag);
    if(it!=_Tags.end()){
        return _Components[it-_Tags.begin()]; // Tag and Component vectors have the same reference
    }
    return NULL;
}
// approach gives easy return for Tags & components reference, without heap memory    
std::vector<Component::Tag>& Entity::GetTags() {
    return _Tags;
    
}

std::vector<Component*>& Entity::GetComponents() {
    return _Components;
}

