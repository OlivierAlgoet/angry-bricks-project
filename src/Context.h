#ifndef CONTEXT_H
#define CONTEXT_H
#include "Point.h"
class Context {
    public:
        // These are the important values to share between the systems
        unsigned score=0;
        Point mouse=Point(0,0);
        bool clicked=false;
        bool released=false;
        bool spacebar=true;
        bool changing=false;
        bool end_game=false;
};

#endif