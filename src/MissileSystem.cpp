#include "MissileSystem.h"
/* Could have used more private help functions to make the code cleaner and more organized
    It does the job however*/
void MissileSystem::Update(){
    // get the current missile if there is one and it is fired continue, else stop
    std::set<Entity*> current_missile=engine_.GetEntityStream().WithTag(Component::Tag::CURRENTMISSILE);
    std::set<Entity*>::iterator it=current_missile.begin();
    if (!current_missile.empty()){ // Security check but normally Launchersystem will create one before the missilesystem
        CurrentMissileComponent * Cm=(CurrentMissileComponent*)(*it)->GetComponent(Component::Tag::CURRENTMISSILE);
        if(Cm->fired){
            // get current missile position
            PolygonComponent * pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
            Point current_pos=pg->get_position();

            if (context_.spacebar){
                if (DEBUG_MODE)
                    std::cout<<"Spacebar pressed!"<<Cm->speed.y_<<std::endl;
                MissileOneComponent* c1=(MissileOneComponent*)(*it)->GetComponent(Component::Tag::MISSILE1);
                if(c1!=NULL && !c1->activated){
                    c1->activated=true;
                    Cm->speed.y_=Cm->speed.y_*-3; // reverse Y speed and speed times 3
                }
                 MissileTwoComponent* c2=(MissileTwoComponent*)(*it)->GetComponent(Component::Tag::MISSILE2);
                if(c2!=NULL && !c2->activated){
                    c2->activated=true;
                    Cm->speed.x_=Cm->speed.x_*2; // increase x speed
                }
                MissileThreeComponent* c3=(MissileThreeComponent*)(*it)->GetComponent(Component::Tag::MISSILE3);
                if(c3!=NULL && !c3->activated){
                    c3->activated=true;
                    Cm->destroy_rocks=true;
                }

            }
            // Check if the ground is hit, if so change the y velocity direction
            if (current_pos.y_<Y_OFFSET && current_pos.x_ >MISSILEX){
                Cm->speed.x_=(BOUNCELOSS*Cm->speed.x_);
                Cm->speed.y_=(-BOUNCELOSS*Cm->speed.y_);
                if (DEBUG_MODE)
                    std::cout<<"[+] Bounced: changing the speed"<<std::endl;
                current_pos.y_=Y_OFFSET; // Makes sure that we are not vibrating since we won't be directly above Y_OFFSET
                pg->set_position(current_pos);
            }else{
                // gravity
                Cm->speed.y_=Cm->speed.y_+Cm->accel.y_/FPS;
                // increment position
                current_pos.x_=current_pos.x_+Cm->speed.x_/FPS;
                current_pos.y_=current_pos.y_+Cm->speed.y_/FPS;
                pg->set_position(current_pos);
                context_.changing=true; // This is used for the render system
                
                // Some rules on when to delete the Missile
                if(current_pos.y_>SCREEN_HEIGHT || Cm->speed.x_<SPEED_THRESHOLD || current_pos.x_>SCREEN_WIDTH){
                    // Delete the memory allocated to it
                    engine_.UpdateEntity((*it),(*it)->GetTags(), true);
                    std::vector<Component*> components=(*it)->GetComponents();
                    std::vector<Component*>::iterator it_c=components.begin();
                    for(;it_c!=components.end();it_c++){
                        (*it)->Remove(*it_c);
                        delete (*it_c);
                    }
                    delete (*it);
                    
                }
            }
        }
        
    }

}