#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <algorithm>
#include "EntityStream.h"
#include "Context.h"
#include "System.h"

class Engine
{
public:
    Engine(Context& context):_Context(context){}; // Reference to context created in Game (will keep existing till game ends and context and engine is no longer needed)

    void AddEntity(Entity* entity);

    void UpdateEntity(Entity* entity, std::vector<Component::Tag>& tags, bool remove);

    std::vector<Entity*>::iterator RemoveEntity(Entity* entity);

    void AddSystem(System* system);
    
    std::vector<System*>& GetSystem(); // helps obtain the systems for easy deletion when game is over

    std::vector<System*>::iterator RemoveSystem(System* system);
    
    std::vector<Entity*>& GetEntities();

    EntityStream& GetEntityStream();

    Context& GetContext();

    void Update();

private:
    std::vector<Entity*>::iterator _delEnt(Entity* entity); //delete entity from the internal list
    std::vector<System*> _Systems;
	std::vector<Entity*> _Entities; // internal entity list
	Context& _Context;
	EntityStream stream;
};

#endif