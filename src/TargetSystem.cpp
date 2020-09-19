#include "TargetSystem.h"

void TargetSystem::Update() {
    std::set<Entity*> missile=engine_.GetEntityStream().WithTag(Component::Tag::CURRENTMISSILE);
    std::set<Entity*>::iterator it_m;
    CurrentMissileComponent * Cm;
    PolygonComponent*pg;
    if (!missile.empty()){
        it_m=missile.begin();
        pg=(PolygonComponent*)(*it_m)->GetComponent(Component::Tag::POLYGON);
        Cm=(CurrentMissileComponent*)(*it_m)->GetComponent(Component::Tag::CURRENTMISSILE);
    }
    bool fired=(!missile.empty() && Cm->fired);
    std::vector<Point> pointlist;
    if (to_delete){
        context_.changing=true;
        std::vector<Point>* interm;
        to_delete=false;
        for(int i=0;i<LEVEL_NR;i++){
            interm=_check_hits(level_list[i],sprite_list[i]);
            pointlist.insert(pointlist.end(), interm->begin(), interm->end());
            delete interm; // clear memory
        }
        _replace_components(pointlist);
        _check_end();
    }
    if (fired){
        // Quick distance check, if below threshold we check for a collision
        std::set<Entity*> items;
        std::set<Entity*>::iterator it;
        PolygonComponent* level_pg;
        StoneComponent* stone_comp;
        Point p_l;
        Point p_m=pg->get_position();
        for(int i=0;i<LEVEL_NR;i++){
            items=engine_.GetEntityStream().WithTag(level_list[i]);
            it=items.begin();
            for(;it!=items.end();it++){
                level_pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
                p_l=level_pg->get_position();
                if(p_l*p_m<COLLISION_THRESHOLD){
                    if(CheckCollision(level_pg->get_polygon(),pg->get_polygon())){
                        SpriteComponent* sprt=(SpriteComponent*)(*it)->GetComponent(Component::Tag::SPRITE);
                        sprt->sprt=sprite_list[i];
                        chain_collision(level_pg->get_position(),Cm->speed);
                        to_delete=true;
                        // I assume that only one stone can be broken at a time!
                        if(Component::Tag::STONE==level_list[i] && Cm->destroy_rocks){
                            stone_comp=(StoneComponent *)(*it)->GetComponent(Component::Tag::STONE);
                            stone_comp->destroyed=true;
                            
                        }
                    }

                }
            }
        }
        if(to_delete){
            _delete_entity(*it_m);
        }
    }

}
void TargetSystem::chain_collision(Point& p, Point &speed){
    // Used to delete more than one item
    // SPEED1 & SPEED2 are the thresholds here
    std::set<Entity*> items;
    std::set<Entity*>::iterator it;
    PolygonComponent* level_pg;
    Point targ;
    if (speed.x_>SPEED1){
        for(int i=0;i<LEVEL_NR;i++){
            items=engine_.GetEntityStream().WithTag(level_list[i]);
            it=items.begin();
            for(;it!=items.end();it++){
                level_pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
                targ=level_pg->get_position();
                // Only horizontal chain collision supported!
                if (targ.y_==p.y_ && (targ.x_==p.x_+MISSILE_DST_WIDTH||(targ.x_==p.x_+2*MISSILE_DST_WIDTH && speed.x_>SPEED2))){
                    SpriteComponent* sprt=(SpriteComponent*)(*it)->GetComponent(Component::Tag::SPRITE);
                    sprt->sprt=sprite_list[i];
                }
                
            }
        }
    }
}

void TargetSystem::_replace_components(std::vector<Point>& replaced_points){
    // Given a pointlist drop all the entities 
    // Now this is done instantaneous by using - MISSILE_DST
    // This could also be done gradually over a few steps for a more lifelike game
    std::set<Entity*> items;
    std::set<Entity*>::iterator it;
    PolygonComponent* level_pg;
    std::vector<Point>::iterator it_p;
    Point p;
    Point n;
    for(int i=0;i<LEVEL_NR;i++){
        items=engine_.GetEntityStream().WithTag(level_list[i]);
        it=items.begin();
        for(;it!=items.end();it++){
            it_p=replaced_points.begin();
            level_pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
            p=level_pg->get_position();
            for(;it_p!=replaced_points.end();it_p++){
                if((*it_p).x_==p.x_ && p.y_>(*it_p).y_){
                    n=level_pg->get_position();
                    n.y_-=MISSILE_DST_HEIGHT;
                    level_pg->set_position(n);
                }
            }
        } 
    }  
}
std::vector<Point>* TargetSystem::_check_hits(Component::Tag tg,Sprite spr){
    // delete all hit entities and return a pointlist of their coordinates
    std::set<Entity*> items;
    std::set<Entity*>::iterator it;
    PolygonComponent* level_pg;
    StoneComponent* stone_comp;
    SpriteComponent * sprt;
    std::vector<Point>* pointlist=new std::vector<Point>;
    items=engine_.GetEntityStream().WithTag(tg);
    it=items.begin();
    for(;it!=items.end();it++){
        sprt=(SpriteComponent*)(*it)->GetComponent(Component::Tag::SPRITE);
        if (sprt->sprt==spr){
            if(tg==Component::Tag::TARGET ||tg==Component::Tag::BOX){
                level_pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
                pointlist->push_back(level_pg->get_position()); // uses a copy constructor
                _delete_entity((*it));
                if(tg==Component::Tag::TARGET)
                    context_.score+=1;
            }
            else{
                // tg can only be Stone but used an if for certainty
                if(tg==Component::Tag::STONE){
                    stone_comp=(StoneComponent*)(*it)->GetComponent(Component::Tag::STONE);
                    if(stone_comp->destroyed){
                        level_pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
                        pointlist->push_back(level_pg->get_position()); // uses a copy constructor
                        _delete_entity((*it));
                    } 
                    else
                    {
                        sprt->sprt=SPRT_STONE;
                    }
                    
                }
            }
        }
    }
    return pointlist;

}
void TargetSystem::_check_end(){
    // check if all targets are deleted
    std::set<Entity*> items;
    items=engine_.GetEntityStream().WithTag(Component::Tag::TARGET);
    if (items.empty()){
        context_.end_game=true;
    }
}
void TargetSystem::_delete_entity(Entity* ent){
    engine_.UpdateEntity(ent,ent->GetTags(), true);
    std::vector<Component*> components=ent->GetComponents();
    std::vector<Component*>::iterator it_c=components.begin();
    for(;it_c!=components.end();it_c++){
        ent->Remove(*it_c);
        delete (*it_c);
    }
    delete ent;

}
bool TargetSystem::CheckCollision(std::vector<Point>& coordinates_poly_one, std::vector<Point>& coordinates_poly_two) {
    bool collision = true;

    std::vector<Point> edges_poly_one = GetEdges(coordinates_poly_one);
    std::vector<Point> edges_poly_two = GetEdges(coordinates_poly_two);

    Point edge;

    // Loop through all the edges of both polygons
    for (std::size_t edge_id = 0; edge_id < edges_poly_one.size() + edges_poly_two.size(); edge_id++) {
        if (edge_id < edges_poly_one.size()) {
            edge = edges_poly_one[edge_id];
        }
        else {
            edge = edges_poly_two[edge_id - edges_poly_one.size()];
        }

        // Find perpendicular axis to current edge
        Point axis(-edge.y_, edge.x_);
        axis.Normalize();

        // Find projection of polygon on current axis
        double min_dotp_poly_one = 0;
        double max_dotp_poly_one = 0;
        double min_dotp_poly_two = 0;
        double max_dotp_poly_two = 0;
        
        ProjectOnAxis(coordinates_poly_one, axis, min_dotp_poly_one, max_dotp_poly_one);
        ProjectOnAxis(coordinates_poly_two, axis, min_dotp_poly_two, max_dotp_poly_two);

        // Check if polygon projections overlap
        if (DistanceBetweenPolys(min_dotp_poly_one, max_dotp_poly_one, min_dotp_poly_two, max_dotp_poly_two) > 0) {
            collision = false;
            break;
        }
    }

    return collision;
}

std::vector<Point> TargetSystem::GetEdges(std::vector<Point>& coordinates) {
    std::vector<Point> edges;
    Point prevPoint = coordinates[0];
    for (std::size_t i = 1; i < coordinates.size(); i++) {
        edges.push_back(coordinates[i] - prevPoint);
        prevPoint = coordinates[i];
    }
    edges.push_back(coordinates[0] - prevPoint);

    return edges;
}

void TargetSystem::ProjectOnAxis(std::vector<Point>& coordinates, Point& axis, double& min, double& max) {
    double dotp = coordinates[0] >> axis;
    min = dotp;
    max = dotp;
    for (std::size_t i = 0; i < coordinates.size(); i++) {
        dotp = coordinates[i] >> axis;
        if (dotp < min) {
            min = dotp;
        }
        else if (dotp > max) {
            max = dotp;
        }
    }
}

double TargetSystem::DistanceBetweenPolys(double min_dotp_poly_one, double max_dotp_poly_one, double min_dotp_poly_two, double max_dotp_poly_two) {
    if (min_dotp_poly_one < min_dotp_poly_two) {
        return min_dotp_poly_two - max_dotp_poly_one;
    }
    else {
        return min_dotp_poly_one - max_dotp_poly_two;
    }
}
