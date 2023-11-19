#pragma once
#include <glm/vec3.hpp>

#include "weed.h"

enum class hero_type
{
    hero1,
    hero2,
    hero3,
    hero4,
    count = 100
};

class hero
{
public:
    glm::vec3 color;
    float x;
    float y;
    hero_type type;
    bool dead;
    bool is_shooting;
    float cooldown;
    weed_type weed_type;
    float death_animation_time;

    hero() : color(), x(0), y(0), type(), dead(false), is_shooting(false), cooldown(100), weed_type(), death_animation_time(1) { }

    void reset_shooting(const float delta_time_seconds)
    {
        if (is_shooting) {
            cooldown -= 50 * delta_time_seconds;
            if (cooldown <= 0) {
                is_shooting = false;
                cooldown = 100;
            }
        }
    }

    void hero_init(const hero_type type1, const float x1, const float y1, const enum weed_type weed)
    {
        switch (type1) {
            case hero_type::hero1:
                color = glm::vec3(153.f / 255.f, 1/255.f, 0);
                type = hero_type::hero1;
                break;
            case hero_type::hero2:
                color = glm::vec3(0, 204.f / 255.f, 0);
                type = hero_type::hero2;
                break;
            case hero_type::hero3:
                color = glm::vec3(0, 128.f / 255.f, 1);
                type = hero_type::hero3;
                break;
            case hero_type::hero4:
                color = glm::vec3(102.f / 255.f, 51.f / 255.f, 0);
                type = hero_type::hero4;
                break;
            case hero_type::count:
                break;
        }

        x = x1;
        y = y1;
        weed_type = weed;
    }
};
