#include "Context.h"
#include "Game.h"
#include "Menu.h"
#include <fstream>
void Menu::Run()
{
    exit_ = false;
    // Menu loop
    Menu::_RenderMenu(current_screen);
    while (!exit_) {
        ak_->NextEvent();
        if (ak_->IsArrowKeyUpPushed()){
            iter-=1;
            if (iter>current_screen->size())
                iter=(*current_screen).size()-1;
            Menu::_RenderMenu(current_screen);
        }
        if (ak_->IsArrowKeyDownPushed()){
            iter=(iter+1)%(*current_screen).size();
            Menu::_RenderMenu(current_screen);
        }
        if (ak_->IsEnterKeyPushed()){
            Menu::_Selector();
            Menu::_RenderMenu(current_screen);
        }
        if (ak_->IsWindowClosed()) {
            exit_ = true;
        }
    }
}

void Menu::_RenderMenu(std::vector<std::string>* options)
{   
    /* This is the base function that does the rendering for the menu
        input: string with menu options
        The function renders these strings along with the menu screen */
    double x=SCREEN_WIDTH/2;
    double y=PADY; // chosen constant
    double y_inc=(SCREEN_HEIGHT-2*PADY)/((*options).size()-1);
    bool big;
    // if there are more than 4 options in the menu they have to be small in order not to overlap
    if ((*options).size()>4)
        big=false;
    else
        big=true;
    
    ak_->DrawScaledBitmap(background, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    for (unsigned i=0; i < (*options).size()-1; i++) {
        Point p(x,y);
        Color c(255,255,255);
        if (i==iter){
            //color red if current option
            c.g_=0;
            c.b_=0;
        }
        ak_->DrawString((*options)[i],p,c,Allkit::ALIGN_CENTER,big);
        y+=y_inc;
    }
    Point p(x,SCREEN_HEIGHT-PADY);
    Color c(255,255,255);
    if ((*options).size()-1==iter){
        c.g_=0;
        c.b_=0;
    }
    ak_->DrawString((*options)[(*options).size()-1],p,c,Allkit::ALIGN_CENTER,true);

    ak_->DrawOnScreen();
}

char ** Menu::_readLevel(std::string& file){
    /*Read the level from a text file*/
    std::ifstream in(file);
    //bool error_occurence=false;
    if (in.fail()){
        std::cout<< "error occurred";
        return NULL; // First safety if the file is not available
    }
    std::vector<char> interm;
    char c;
    while(in>>c){
        if (c!='\n'){
            if (c!='S'&& c!='T'&& c!='B'){
                std::cout<< "break";
                break;
            }
            interm.push_back(c);
        }
    }
    if(interm.size()!=LEVEL_SIZE*LEVEL_SIZE){
        std::cout<< "some error occurred";
        return NULL;
        
    }
    else{
        /* I could actually just return a heap vector list since the LEVEL_SIZE is known
            realized this later and didn't want to change the already available code for creating the entities*/
        char ** level=new char* [LEVEL_SIZE];
        for(std::size_t i=0;i<LEVEL_SIZE;i++){
            level[i]=new char[LEVEL_SIZE];
            if(DEBUG_MODE)
                std::cout<<std::endl;
            for(std::size_t j=0;j<LEVEL_SIZE;j++){
                if(DEBUG_MODE)
                    std::cout<<interm[i*LEVEL_SIZE+j];
                level[i][j]=interm[i*LEVEL_SIZE+j];
            }
        }
        return level;
    }
    return NULL;
}


void Menu::_deleteLevel(char ** level){
    /*delete the assigned memory from the level function*/
    for(std::size_t i=0;i<LEVEL_SIZE;i++){
            delete [] level[i];
        }
        delete [] level;
}

void Menu::_Selector(){
    /*The selector makes sure the right functions are activated on enter press
     (Not the cleanest code)*/
    if ((*current_screen)[iter]=="START"){
        current_screen=&levelScreen;
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="REPLAY"){
        current_screen=&higscoreScreen;
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="LEVEL 1"){
        
        std::string Levelfile="./assets/levels/level1.txt";
        char ** level=_readLevel(Levelfile);
        if (level!=NULL){
            StartGame(level);
            _deleteLevel(level);
            current_screen=&startScreen;
        }else{
            current_screen=&error_occurence;
        }
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="LEVEL 2"){
        std::string Levelfile="./assets/levels/level2.txt";
        char ** level=_readLevel(Levelfile);
        if (level!=NULL){
            StartGame(level);
            _deleteLevel(level);
            current_screen=&startScreen;
        }else{
            current_screen=&error_occurence;
        }
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="LEVEL 3"){
        std::string Levelfile="./assets/levels/level3.txt";
        char ** level=_readLevel(Levelfile);
        if (level!=NULL){
            StartGame(level);
            _deleteLevel(level);
            current_screen=&startScreen;
        }else{
            current_screen=&error_occurence;
        }
        iter=0;
        return;
    }
    // If a wrong level file occurred one can go back to start screen by pressing enter
    if ((*current_screen)[iter]=="ERROR IN FILE"){
        current_screen=&startScreen;
        iter=0;
        return;
    }
    // Hiscore not implemented due to time shortage, chosen to go back to the start screen
    /*The approach would simply be to read all the data in several files, use a boolean in the run game and context to show that it is a replay
        Propagate this boolean to all "random choices" and change these random choices to the appropriate ones
        Instead of the "inputCapture function" in Game.cpp use a filecapture function to give the x,y, clicked released,... booleans */
    if ((*current_screen)[iter]=="HIGHSCORE 1"){
        current_screen=&startScreen;
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="HIGHSCORE 2"){
        current_screen=&startScreen;
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="HIGHSCORE 3"){
        current_screen=&startScreen;
        iter=0;
        return;
    }
    if ((*current_screen)[iter]=="HIGHSCORE 4"){
        current_screen=&startScreen;
        iter=0;
        return;
    }
    //Exit here
    if ((*current_screen)[iter]=="QUIT"){
        exit_=true;
        return;
    }
}
void Menu::StartGame(char ** level)
{   
    /* Function to start the game */
    Context context;
    Game game(context);
    /* init entities and init systems added to game attributes */
    game.init_Entities(level);
    game.init_Systems();
    game.Run();
}