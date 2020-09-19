#include "LauncherSystem.h"

void LauncherSystem::Update(){
    std::set<Entity*> current_missile=engine_.GetEntityStream().WithTag(Component::Tag::CURRENTMISSILE); // ask for sprites, all entities containing a sprite have to use a scaled bitmap
    if (current_missile.empty()){
        context_.changing=true;
        std::set<Entity*> missiles;
        PolygonComponent * pg;
        Point increment=Point((MISSILE_DST_WIDTH+MISSILE_SPACING),0);
        Point new_pos;
        for(int i=0;i<MISS_NR;i++){
            missiles=engine_.GetEntityStream().WithTag(missile_list[i]);
            std::set<Entity*>::iterator it=missiles.begin();
            for(;it!=missiles.end();it++){
                pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
                new_pos=pg->get_position()+increment;
                pg->set_position(new_pos);
                if(pg->get_position().x_>((MISS_NR-1)*(MISSILE_SPACING+MISSILE_DST_WIDTH))){
                    Point current=Point(MISSILEX,MISSILEY);
                    CurrentMissileComponent * curr=new CurrentMissileComponent;
                    (*it)->Add(curr);
                    engine_.UpdateEntity((*it),(*it)->GetTags(),false);
                    pg->set_position(current);
                    CircleComponent * circle =(CircleComponent*)(*it)->GetComponent(Component::Tag::CIRCLE);
                    if (circle!=NULL){
                        circle->set_pos(current);
                    }
                }
                   
            }
        }
        Entity * ent=new Entity;
        RandomMissile(0,Y_OFFSET,ent);
        engine_.AddEntity(ent);   
    }
    // TODO click release check & zo ja positie van muis gelijkstellen aan x,y
    // als het gereleased is snelheid bepalen!
    else{
        std::set<Entity*>::iterator it=current_missile.begin();// onlyone missile
        CurrentMissileComponent * Cm=(CurrentMissileComponent*)(*it)->GetComponent(Component::Tag::CURRENTMISSILE);
        if(!Cm->fired){
            PolygonComponent * pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
            if(!Cm->selected){
                bool collision;
                CircleComponent * cr=(CircleComponent*)(*it)->GetComponent(Component::Tag::CIRCLE);
                // Check for collision
                if (cr!=NULL){
                    collision=CircleCollision_(context_.mouse,cr->get_center(),cr->radius);
                }else{
                    collision=PolyCollision_(context_.mouse,pg->get_polygon());
                }
                // check if we clicked
                if (collision and context_.clicked){
                    Cm->selected=true;
                    Cm->ClickCorrect=context_.mouse-pg->get_position();
                }
            

            }else{
                context_.changing=true;
                if (context_.mouse.x_<MISSILEX){                    
                Point current_pos=context_.mouse-Cm->ClickCorrect;
                pg->set_position(current_pos); //Only set position of the polygon, the circle will only be used for the collision check so no sets are required here
                }
                
                //std::cout<<"selected!!"<<std::endl;
                if(context_.released){
                    //std::cout<<"changing the status to fired"<<std::endl;
                    Cm->fired=true;
                    Point speed_vector=Point(MISSILEX,MISSILEY)-(context_.mouse-Cm->ClickCorrect);
                    Cm->speed.x_=KSPEED*speed_vector.x_;
                    Cm->speed.y_=KSPEED*speed_vector.y_; //KSPEED is a proportional value to play with
                }
            }
            


        }

    } 
    

}

bool LauncherSystem::CircleCollision_(Point& mouse,Point& center,double radius){
    double length=mouse*center;
    //std::cout<<"the length is"<<length<<std::endl;
    bool collision=length<radius;
    //std::cout<<"collision"<<collision<<std::endl;
    return collision;
}
bool LauncherSystem::PolyCollision_(Point& mouse,std::vector<Point>& poly){
    /* Some ugly copy and paste was done here, not using the functions directly from TargetSystems with the goal to
        keep the systems seperated for  readability + future work*/
    bool collision = true;

    std::vector<Point> edges_poly = GetEdges(poly);
    Point edge;
    std::vector<Point> mouse_point{mouse}; // made a vector such that the functions don't have to be changed

    // Loop through all the edges of both polygons
    for (std::size_t edge_id = 0; edge_id < edges_poly.size(); edge_id++) {
        edge = edges_poly[edge_id];
        // Find perpendicular axis to current edge
        Point axis(-edge.y_, edge.x_);
        axis.Normalize();

        // Find projection of polygon on current axis
        double min_dotp_poly = 0;
        double max_dotp_poly = 0;
        double dotp_mouse = 0;
        
        ProjectOnAxis(poly, axis, min_dotp_poly, max_dotp_poly);
        ProjectOnAxis(mouse_point, axis, dotp_mouse, dotp_mouse); // dotp_mouse in twice for function compatibility

        // Check if polygon projections overlap
        if (DistanceBetweenPolys(min_dotp_poly, max_dotp_poly, dotp_mouse) > 0) {
            collision = false;
            break;
        }
    }

    return collision;
}

std::vector<Point> LauncherSystem::GetEdges(std::vector<Point>& coordinates) {
    std::vector<Point> edges;
    Point prevPoint = coordinates[0];
    for (std::size_t i = 1; i < coordinates.size(); i++) {
        edges.push_back(coordinates[i] - prevPoint);
        prevPoint = coordinates[i];
    }
    edges.push_back(coordinates[0] - prevPoint);

    return edges;
}

void LauncherSystem::ProjectOnAxis(std::vector<Point>& coordinates, Point& axis, double& min, double& max) {
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

double LauncherSystem::DistanceBetweenPolys(double min_dotp_poly, double max_dotp_poly, double dotp_mouse) {
    if (min_dotp_poly < dotp_mouse) {
        return dotp_mouse - max_dotp_poly;
    }
    else {
        return min_dotp_poly - dotp_mouse;
    }
}

