#ifndef ENEMIES_H
#define ENEMIES_H

#include "Includes.h"
#include "Entity.h"

class Enemies : Entity
{
    public:
        Enemies();
        virtual ~Enemies();

        float health;
        float speed;
        float dmg;

    protected:
    private:
};

#endif // ENEMIES_H
