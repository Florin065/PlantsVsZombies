#pragma once

#include <string>

#include "game.h"
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object_2d_pvz
{
    Mesh *create_square(const std::string &name, glm::vec3 left_bottom_corner, float length, glm::vec3 color, bool fill = false);
    Mesh *create_mower(const std::string &name, glm::vec3 left_bottom_corner, float length, glm::vec3 color, bool fill = false);
    Mesh *create_hero(const std::string &name, float length, glm::vec3 color);
    Mesh *create_enemy(const ::std::string& name, const float length, const glm::vec3 bg);
    Mesh *create_money(const std::string &name, float length, glm::vec3 color, float rotation_angle);
    Mesh *create_heart(const std::string &name, float size, glm::vec3 color);
    Mesh *create_projectile(const std::string& name, float radius, glm::vec3 color);
} // namespace object2D
