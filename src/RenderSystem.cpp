#include "RenderSystem.h"

void RenderSystem::Update(){
    // Hier nog boolean toevoegen indien update nodig is!
    // Base screen first!
    if (context_.changing){
        ak_->DrawScaledBitmap(SPRT_BACKGROUND, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        ak_->DrawScaledBitmap(SPRT_LAUNCHER,0,0,LAUNCHER_SRC_WIDTH,LAUNCHER_SRC_HEIGHT,XLAUNCH,SCREEN_HEIGHT-LAUNCHER_DST_HEIGHT-Y_OFFSET,LAUNCHER_DST_WIDTH,LAUNCHER_DST_HEIGHT);
        std::set<Entity*> render_items=engine_.GetEntityStream().WithTag(Component::Tag::SPRITE); // ask for sprites, all entities containing a sprite have to use a scaled bitmap
        std::set<Entity*>::iterator it=render_items.begin();
        PolygonComponent * pg;
        SpriteComponent * sprt;
        for(;it!=render_items.end();it++){
            pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
            sprt=(SpriteComponent*)(*it)->GetComponent(Component::Tag::SPRITE);
            ak_->DrawScaledBitmap(sprt->sprt,0,0,MISSILE_SRC_WIDTH,MISSILE_SRC_HEIGHT,pg->get_position().x_,SCREEN_HEIGHT-pg->get_position().y_-MISSILE_DST_HEIGHT,
                                MISSILE_DST_WIDTH,MISSILE_DST_HEIGHT);

            if(DEBUG_MODE){
                std::vector<Point> interm;
                std::vector<Point>::iterator it=pg->get_polygon().begin();
                for(;it!=pg->get_polygon().end();it++){
                    interm.push_back(Point(it->x_,SCREEN_HEIGHT-it->y_));  // shallow copy constructor of point used in vector
                }

                ak_->DrawPoly(interm);
            }
        }
        // Render afschiet mechanisme hier
        
        // later Later andere punten toevoegen
        // get Entities with current missile
        render_items=engine_.GetEntityStream().WithTag(Component::Tag::CURRENTMISSILE);
        if (!render_items.empty()){
            it=render_items.begin();
            pg=(PolygonComponent*)(*it)->GetComponent(Component::Tag::POLYGON);
        }
        Point p1;
        Point p2;
        // Render the shooting strings
        if(render_items.empty() || pg->get_position().x_>MISSILEX){ // short circuit of or
            p1 =Point(BOWSTRINGX1,SCREEN_HEIGHT-BOWSTRINGY1);
            p2 =Point(BOWSTRINGX2,SCREEN_HEIGHT-BOWSTRINGY2);
            ak_->DrawLine(p1,p2);
            p1 =Point(BOWSTRINGX1,SCREEN_HEIGHT-BOWSTRINGY1+MISSILE_DST_HEIGHT);
            p2 =Point(BOWSTRINGX2-10,SCREEN_HEIGHT-BOWSTRINGY2+MISSILE_DST_HEIGHT-2.5);
            ak_->DrawLine(p1,p2);
        }else{ 
            p1 =Point(BOWSTRINGX1,SCREEN_HEIGHT-BOWSTRINGY1);
            p2 =Point(pg->get_position().x_+MISSILE_DST_WIDTH/2,SCREEN_HEIGHT-(pg->get_position().y_+MISSILE_DST_HEIGHT));
            ak_->DrawLine(p1,p2);
            p1 =Point(BOWSTRINGX2,SCREEN_HEIGHT-BOWSTRINGY2);
            ak_->DrawLine(p1,p2);
            p1 =Point(BOWSTRINGX1,SCREEN_HEIGHT-BOWSTRINGY1+MISSILE_DST_HEIGHT);
            p2 =Point(pg->get_position().x_+MISSILE_DST_WIDTH/2,SCREEN_HEIGHT-pg->get_position().y_);
            ak_->DrawLine(p1,p2);
            p1 =Point(BOWSTRINGX2-10,SCREEN_HEIGHT-BOWSTRINGY2+MISSILE_DST_HEIGHT-2.5);
            ak_->DrawLine(p1,p2);
        }

        // Hier score nog zetten!
        std::string score=std::to_string(context_.score);
        std::string to_print = std::string(ZERO_PAD - score.length(), '0') + score;
        Point p(SCORE_X,SCORE_Y); // hard coded position
        Color c(255,0,0);
        ak_->DrawString(to_print,p,c,Allkit::ALIGN_LEFT,false);

        ak_->DrawOnScreen();
        // Use this for stability otherwise the action really has to occur on the right game tick
        context_.changing=false;
        context_.spacebar=false;
        context_.clicked=false;
        context_.released=false;
       
        

        

    }
}