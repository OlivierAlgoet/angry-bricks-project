#include "Game.h"

bool Game::Run() {
    ak_->StartTimer();
    bool exit_=false;
    context_.changing=true;
    while(!exit_){
        exit_=context_.end_game;  
        ak_->NextEvent();
        if (ak_->IsWindowClosed()) {
            exit_ = true;
        }
        if (ak_->IsTimerEvent()){
            engine_.Update();
        }else{
            Inputcapture_();
        } 
    }
    return true;
    
}
Game::~Game(){
    // start by deleting the systems
    std::vector<System*> systems= engine_.GetSystem();
    std::vector<System*>::iterator it=systems.begin();
    for(;it!=systems.end();it++){
        engine_.RemoveSystem((*it)); // I don't use the output of RemoveSystem
        delete (*it);
    }
    // Delete all the enities and there components
    std::vector<Entity*> entities=engine_.GetEntities();
    std::vector<Entity*>::iterator it_ent=entities.begin();
    std::vector<Component*> components;
    std::vector<Component*>::iterator it_c;
    for(; it_ent!=entities.end();it_ent++){
        engine_.UpdateEntity((*it_ent),(*it_ent)->GetTags(), true);
        components=(*it_ent)->GetComponents();
        it_c=components.begin();
        for(;it_c!=components.end();it_c++){
            (*it_ent)->Remove(*it_c);
            delete (*it_c);
        }
        delete (*it_ent);


    }

}
void Game::init_Systems(){
    // initialize all the systems in the right order
    MissileSystem* msys=new MissileSystem(context_,engine_);
    RenderSystem* rsys=new RenderSystem(context_,engine_);
    LauncherSystem* lsys=new LauncherSystem(context_,engine_);
    TargetSystem* tsys=new TargetSystem(context_,engine_);
    engine_.AddSystem(lsys);
    engine_.AddSystem(msys);
    engine_.AddSystem(tsys);
    engine_.AddSystem(rsys);
    
}
Point Game::CoordinateTransform_(Point& p){
    // Used for transforming the allkit mouse coordinates to our coordinate system
    Point transformer=Point(p.x_,SCREEN_HEIGHT-p.y_);
    return transformer;
}
void Game::Inputcapture_(){
    // Captures all input
    
    if(ak_->IsSpaceBarPushed()){
        context_.spacebar=true;
    }
    if(ak_->IsMouseClicked()){
        context_.clicked=true;
    }
    if (ak_->HasMouseMoved())
        context_.mouse=CoordinateTransform_(ak_->GetMouse());
    if (ak_->IsMouseReleased()){
        context_.released=true;
    }
    
    
}
void Game::init_Entities(char ** level){
    // initialize all level entities
    Component* cmp;
    Component* sprt;
    Component* pg;
    double x;
    double y;
    Point p;
    for (int i=0;i<LEVEL_SIZE;i++){
        for(int j=0;j<LEVEL_SIZE;j++){
            // switch hier!
            Entity *ent= new Entity;
            x=j*MISSILE_DST_WIDTH+(SCREEN_WIDTH-LEVEL_SIZE*MISSILE_DST_WIDTH);
            y=(LEVEL_SIZE-1)*MISSILE_DST_HEIGHT-i*MISSILE_DST_HEIGHT+Y_OFFSET;
            switch(level[i][j]){
                case 'T':
                    cmp=new TargetComponent;
                    sprt= new SpriteComponent(SPRT_TARGET);
                    p=Point(x,y);
                    pg=new PolygonComponent(p,dynamic_cast<TargetComponent*>(cmp)->rel_poly); 
                    break;
                case 'B':
                    cmp=new BoxComponent;
                    sprt= new SpriteComponent(SPRT_BOX);
                    p=Point(x,y);
                    pg=new PolygonComponent(p,dynamic_cast<BoxComponent*>(cmp)->rel_poly);
                    break;
                case 'S': // STONE chosen as default
                    cmp= new StoneComponent;
                    sprt= new SpriteComponent(SPRT_STONE);
                    p=Point(x,y);
                    pg=new PolygonComponent(p,dynamic_cast<StoneComponent*>(cmp)->rel_poly);
                    break;
            }
            ent->Add(cmp);
            ent->Add(sprt);
            ent->Add(pg);
            engine_.AddEntity(ent);
        }
    }
    for(int i=0;i<MISSILES;i++){
        Entity *ent= new Entity;
        x=i*(MISSILE_DST_WIDTH+MISSILE_SPACING);
        y=Y_OFFSET;
        if(i==3){ 
            CurrentMissileComponent * curr=new CurrentMissileComponent;
            ent->Add(curr);
            x=MISSILEX;  // Heuristically determined 
            y=MISSILEY;
        }
       RandomMissile(x,y,ent); // An external function is used since we will also need it in the Launcher system
       engine_.AddEntity(ent);
    }
    
}