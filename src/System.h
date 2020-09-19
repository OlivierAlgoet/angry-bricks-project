#ifndef SYSTEM_H
#define SYSTEM_H

class System {
    public:
        virtual void Update() = 0;
        virtual ~System(){};
};

#endif