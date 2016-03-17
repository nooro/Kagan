#ifndef ENTITY_H
#define ENTITY_H

/*
    Class for the Entities
    Every game object with which the user can interact
*/

#include "LGTexture.h" // include light game texture class
#include <vector> // include the vectors

class Entity
{
    private:

        //a struct for the center of our entity
        struct point
        {
            int x;
            int y;
        }center;

        //a struct for the stats of our entity
        struct statistics
        {
            int hp;
            int stamina;
            int xp;
            int lvl;
            int str;
            int dex;
        }stats;

        //a struct for the rect of our entity
        struct position
        {
            float x;
            float y;
            int w;
            int h;
        }rect;

    public:
        Entity(); // Constructor
        Entity(const Entity &other); // Copy constructor
        virtual ~Entity(); // Destructor

        //Creates the Entity with a given name, rect, window size, renderer and path to the texture
        void createEntity(std::string name_, float x_, float y_, int w_, int h_, int window_x, int window_y,
                          SDL_Renderer *Rend, char *FILE);
        void render(SDL_Renderer *Rend); // Render the entity
        void moveTo(float x_, float y_); // Move to given coordinates
        bool atack(); // Atack
        bool collision(); // Check if there is collision with another entity
        bool takeDmg(int dmg); // Damages the entity with given value
        bool isHover(); // Check if the mouse is over the entity

        statistics getStats(); // Returns the stats of the entity
        position getRect(); // Returns the rect of the entity
        bool getState(); // Return if the entity is alive or not
        void respawn(); // Respawns the entity to full health

        static std::vector<Entity*> entities; // vector for keeping pointers to all entities
        static Entity *getEntity(std::string name_); // returns an entity by name

        int screen_x; // keeps the window width
        int screen_y; // keeps the window height

    protected:
    private:

        LGTexture Texture; // the entity texture
        std::string name; // our entity name

        bool alive; // keeps if its alive or not

        //Gets the stats from the server
        void loadStats();
};

#endif // ENTITY_H
