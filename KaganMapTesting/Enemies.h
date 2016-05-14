#ifndef ENEMIES_H
#define ENEMIES_H

#include "Includes.h"
#include "Entity.h"

class Enemies : public Entity
{
    public:
        Enemies();
        virtual ~Enemies();

        float health;
        float speed;
        float dmg;

        int atack_speed;
        int cd;
        int range;

        void CreateEnemy(float hp_, float sp_, float dmg_, int range, int as_);
        void Aggro(float x_, float y_, Camera* cam);
        bool Atack(Entity target);

    protected:
    private:
};

#endif // ENEMIES_H
