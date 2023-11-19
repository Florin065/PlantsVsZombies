#pragma once
#include <cstdlib>
#include <glm/vec3.hpp>

enum class enemy_type {
    enemy1,
    enemy2,
    enemy3,
    enemy4,
    count
};

class enemy
{
public:
    glm::vec3 bg;
    int health;
    float x;
    float y;
    enemy_type type;
    float death_animation_time;

    enemy() : bg(), health(3), x(0), y(0), type(), death_animation_time(1) { }
    
    void spawn_random_enemy()
    {
        // Generate a random enemy type
        const auto random_type = static_cast<enemy_type>(rand() % static_cast<int>(enemy_type::count));  // NOLINT(concurrency-mt-unsafe)
        
        // Generate a random row (1 => y = 60, 2 => y = 220, or 3 => y = 380)
        const float random_row = rand() % 3 * 160 + 60;  // NOLINT(bugprone-narrowing-conversions, concurrency-mt-unsafe, cppcoreguidelines-narrowing-conversions)

        switch (random_type) {
            case enemy_type::enemy1:
                bg = glm::vec3(153.f / 255.f, 1/255.f, 0);
                type = enemy_type::enemy1;
                break;
            case enemy_type::enemy2:
                bg = glm::vec3(0, 204.f / 255.f, 0);
                type = enemy_type::enemy2;
                break;
            case enemy_type::enemy3:
                bg = glm::vec3(0, 128.f / 255.f, 1);
                type = enemy_type::enemy3;
                break;
            case enemy_type::enemy4:
                bg = glm::vec3(102.f / 255.f, 51.f / 255.f, 0);
                type = enemy_type::enemy4;
                break;
            case enemy_type::count:
                break;
        }

        // Set the position of the enemy
        x = 1350;       // Starting x position
        y = random_row; // Random y position (60, 220, or 380)
    }
};
