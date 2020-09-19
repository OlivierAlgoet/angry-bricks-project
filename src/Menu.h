#ifndef MENU_H
#define MENU_H

#include "Sprite.h"
#include "Allkit.h"
#include "Constants.h"
#include <vector>
#include "Point.h"

class Menu
{
public:
    Menu() :
        ak_(& Allkit::Get()){};

    // Start the menu loop
    void Run();

    void StartGame(char ** level);

private:
    void _RenderMenu(std::vector<std::string>*);
    void _Selector();
    char ** _readLevel(std::string&);
    void _deleteLevel(char ** level);
    Allkit* ak_ = NULL;
    static const Sprite background=SPRT_MENU_BACKGROUND;
    //Initialize all the screens!
    std::vector<std::string> startScreen{"START","REPLAY","QUIT"};
    std::vector<std::string> levelScreen{"LEVEL 1","LEVEL 2","LEVEL 3","QUIT"};
    std::vector<std::string> higscoreScreen{"HIGHSCORE 1","HIGHSCORE 2","HIGHSCORE 3","HIGHSCORE 4","QUIT"};
    std::vector<std::string> error_occurence{"ERROR IN FILE","QUIT"};
    unsigned iter=0;
    std::vector<std::string> *current_screen=&startScreen;
    
    
protected:
    bool exit_ = false;

};

#endif