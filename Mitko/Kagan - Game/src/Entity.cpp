#include "Entity.h"

//initialize the vector
std::vector<Entity*> Entity::entities;

Entity::Entity()
{
    //ctor
}

Entity::Entity(const Entity &other)
{
    //cpy ctor
}

//Destructor
Entity::~Entity()
{
    delete(&Texture);
    this->alive = false;
}

//Return the entity with a given name
Entity *Entity::getEntity(std::string name_)
{
    //Iterate trough all of the entities
    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        //if its the name we are looking for return it
        if((*it)->name == name_)
            return *it;
    }
}

//Creates an entity with given parameters // read header for more info
void Entity::createEntity(std::string name_, float x_, float y_, int w_, int h_, int window_x, int window_y,
                          SDL_Renderer *Rend, char *FILE)
{
    this->alive = true; // set alive to true
    this->stats.hp = 100; // set hp to 100

    this->name = name_; // name him

    this->rect.x = x_; // set position x
    this->rect.y = y_; // set position y
    this->rect.w = w_; // set the width
    this->rect.h = h_; // set the height

    this->center.x = rect.w / 2; // calculate center
    this->center.y = rect.h / 2; // calculate center

    this->screen_x = window_x; // give him the window width
    this->screen_y = window_y; // give him the window height

    this->Texture = LGTexture(); // Creates a LGTexture // read LGTexture.h for more info

    this->Texture.load(Rend, FILE, window_x, window_y); // Load the texture with give path and window size

    Entity::entities.push_back(this); // save this entity to the vector of pointers
}

//Render the entity
void Entity::render(SDL_Renderer *Rend)
{
    // if its alive render
    if(this->alive == true)
        this->Texture.render(Rend, this->rect.x, this->rect.y);
}

//Move to x | y
void Entity::moveTo(float x_, float y_)
{
    // if its death don't move
    if(this->alive == false)
        return;

    this->rect.x += x_;
    this->rect.y += y_;
}


//Deal dmg to the entity
bool Entity::takeDmg(int dmg)
{
    // if its death don't deal dmg
    if(this->alive == false)
        return false; // return that damaging was impossible

    this->stats.hp -= dmg; // gets the dmg out of his hp

    if(this->stats.hp <= 0) // if hp is lower than 0
    {
        this->stats.hp = 0; // set hp to 0 so you don't overkill
        this->alive = false; // set him to death
    }

    return true; // return that damaging was fine
}

//Check if the mouse is over the entity
bool Entity::isHover()
{
    int x, y; // integers to store our mouse position
    SDL_GetMouseState(&x , &y); // gets the mouse position on the window

    if(x < this->rect.x * this->screen_x) // if mouse is on the left side return false
        return false;
    if(x > (this->rect.x * this->screen_x) + this->Texture.getWidth()) // if mouse is on the right side return false
        return false;
    if(y < this->rect.y * this->screen_y) // if mouse is above return false
        return false;
    if(y > (this->rect.y * this->screen_y) + this->Texture.getHeight()) // if mouse is below return false
        return false;

    return true; // return true if non of the above returned false ... its over the entity
}

//Respawn the entity
void Entity::respawn()
{
    stats.hp = 100; // set hp to 100
    alive = true; // set alive to true
}

//Return if the entity is alive
bool Entity::getState()
{
    return alive;
}

//Return the entity stats
Entity::statistics Entity::getStats()
{
    return stats;
}

//Return the entity rectangle
Entity::position Entity::getRect()
{
    return rect;
}

