#ifndef ENTITY_H
#define ENTITY_H

#include "LGTexture.h"
#include <vector>

class Entity
{
    public:
        Entity();
        Entity(const Entity &other);
        virtual ~Entity();

        void createEntity(std::string name_, float x_, float y_, int w_, int h_, int window_x, int window_y,
                          SDL_Renderer *Rend, char *FILE);
        void render(SDL_Renderer *Rend);
        void moveTo(float x_, float y_);
        bool atack();
        bool collision();
        bool takeDmg(int dmg);

        int getHp()
        {
            return stats.hp;
        }


        void respawn()
        {
            stats.hp = 100;
            alive = true;
        }

        static std::vector<Entity*> entities;
        static Entity *getEntity(std::string name_);



    protected:
    private:

        LGTexture Texture;
        std::string name;

        bool alive;

        struct position
        {
            float x;
            float y;
            int w;
            int h;
        }rect;

        struct point
        {
            int x;
            int y;
        }center;

        struct statistics
        {
            int hp;
            int stamina;
            int xp;
            int lvl;
            int str;
            int dex;
        }stats;

        //Gets the stats from the server
        void loadStats();
};

#endif // ENTITY_H
