#pragma once
#include <glm/vec3.hpp>

enum class projectile_type
{
    projectile1,
    projectile2,
    projectile3,
    projectile4,
    count
};

class projectile
{
public:
    glm::vec3 color;
    float x;
    float y;
    projectile_type type;
    float radius;

    projectile() : color(), x(0), y(0), type(), radius(0) { }

    void spawn_projectile(const hero_type type1, const float x1, const float y1)
    {
        switch (type1) {
            case hero_type::hero1:
                color = glm::vec3(153.f / 255.f, 1/255.f, 0);
                type = projectile_type::projectile1;
                break;
            case hero_type::hero2:
                color = glm::vec3(0, 204.f / 255.f, 0);
                type = projectile_type::projectile2;
                break;
            case hero_type::hero3:
                color = glm::vec3(0, 128.f / 255.f, 1);
                type = projectile_type::projectile3;
                break;
            case hero_type::hero4:
                color = glm::vec3(102.f / 255.f, 51.f / 255.f, 0);
                type = projectile_type::projectile4;
                break;
            case hero_type::count:
                break;
        }

        x = x1;
        y = y1;
    }
};
