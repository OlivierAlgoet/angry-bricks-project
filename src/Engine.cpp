#include "Engine.h"

std::vector<Entity*>::iterator Engine::_delEnt(Entity* entity){
    std::vector<Entity*>::iterator it = std::find(_Entities.begin(), _Entities.end(), entity);
    if(it!=_Entities.end()){
        _Entities.erase(it);
    }
    return it;
}
void Engine::AddEntity(Entity* entity) {
    stream.EntityUpdated(entity,entity->GetTags(),false);
    _Entities.push_back(entity);
}

void Engine::UpdateEntity(Entity* entity, std::vector<Component::Tag>& tags, bool remove) {
    stream.EntityUpdated(entity,tags,remove);
    if(remove)
        _delEnt(entity);
}

std::vector<Entity*>::iterator Engine::RemoveEntity(Entity* entity) {
    stream.EntityUpdated(entity,entity->GetTags(),true);
    return _delEnt(entity);
}

void Engine::AddSystem(System* system) {
    _Systems.push_back(system);
}

std::vector<System*>::iterator Engine::RemoveSystem(System* system) {
    std::vector<System*>::iterator it = std::find(_Systems.begin(), _Systems.end(), system);
    if(it!=_Systems.end()){
        _Systems.erase(it);
    }
    return it;
}
std::vector<System*>& Engine::GetSystem(){
    return _Systems;

}

std::vector<Entity*>& Engine::GetEntities() {
    return _Entities;
}

void Engine::Update() {
    std::vector<System*>::iterator it = _Systems.begin();
	for (; it != _Systems.end(); it++) {
		(*it)->Update();
	}
}

EntityStream& Engine::GetEntityStream() {
    return stream;
}

Context& Engine::GetContext() {
    return _Context;
}
