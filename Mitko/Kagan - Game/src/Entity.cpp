#include "Entity.h"

std::vector<Entity*> Entity::entities;

Entity::Entity()
{
    //ctor
}

Entity::Entity(const Entity &other)
{
    //cpy ctor
}

Entity::~Entity()
{
    delete(&Texture);
    this->alive = false;
}

Entity *Entity::getEntity(std::string name_)
{
    for(std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
    {
        if((*it)->name == name_)
            return *it;
    }
}

void Entity::createEntity(std::string name_, float x_, float y_, int w_, int h_, int window_x, int window_y,
                          SDL_Renderer *Rend, char *FILE)
{
    this->alive = true;
    this->stats.hp = 100;

    this->name = name_;

    this->rect.x = x_;
    this->rect.y = y_;
    this->rect.w = w_;
    this->rect.h = h_;

    this->center.x = rect.w / 2;
    this->center.y = rect.h / 2;

    this->Texture = LGTexture();

    this->Texture.load(Rend, FILE, window_x, window_y);

    Entity::entities.push_back(this);
}

void Entity::render(SDL_Renderer *Rend)
{
    if(this->alive == true)
        this->Texture.render(Rend, this->rect.x, this->rect.y);
}

void Entity::moveTo(float x_, float y_)
{
    if(this->alive == false)
        return;

    this->rect.x += x_;
    this->rect.y += y_;
}

bool Entity::takeDmg(int dmg)
{
    if(this->alive == false)
        return false;

    this->stats.hp -= dmg;

    if(this->stats.hp <= 0)
    {
        this->stats.hp = 0;
        this->alive = false;
    }

    return true;
}
