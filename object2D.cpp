#include "object2D.h"

#include <vector>

#include "game.h"

Mesh *object_2d_pvz::create_square(
    const std::string &name,
    const glm::vec3 left_bottom_corner,
    const float length,
    const glm::vec3 color,
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;

    const std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color), // 0
        VertexFormat(corner + glm::vec3(length, 0, -1), color), // 1
        VertexFormat(corner + glm::vec3(length, length, -1), color), // 2 
        VertexFormat(corner + glm::vec3(0, length, -1), color) // 3
    };

    const auto square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh *object_2d_pvz::create_mower(
    const std::string &name,
    const glm::vec3 left_bottom_corner,
    const float length,
    const glm::vec3 color,
    const bool fill)
{
    const glm::vec3 corner = left_bottom_corner;

    const std::vector<VertexFormat> vertices = {
        VertexFormat(corner + glm::vec3(0, 0, 15), color), // 0
        VertexFormat(corner + glm::vec3(length, 0, 15), color), // 1
        VertexFormat(corner + glm::vec3(length, length, 15), color), // 2 
        VertexFormat(corner + glm::vec3(0, length, 15), color) // 3
    };

    const auto square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(4);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh *object_2d_pvz::create_hero(
    const std::string& name,
    const float length,
    const glm::vec3 color)
{
    
    const std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(0, 0, 0), color), // 0
        VertexFormat(glm::vec3(-length / 2, 0, 0), color), // 1
        VertexFormat(glm::vec3(0, length, 0), color), // 2
        VertexFormat(glm::vec3(0, -length, 0), color), // 3
        VertexFormat(glm::vec3(length / 2, 0, 0), color), // 4

        VertexFormat(glm::vec3(length / 3, 0.3 * length, 0), color), // 5
        VertexFormat(glm::vec3(length / 3, -0.3 * length, 0), color), // 6
        VertexFormat(glm::vec3(length, 0.3 * length, 0), color), // 7
        VertexFormat(glm::vec3(length, -0.3 * length, 0), color), // 8
    };

    const std::vector<unsigned int> indices = {
        // rhombus
        2, 1, 3,
        2, 3, 4,

        // rectangle
        5, 6, 7,
        7, 6, 8
    };

    const auto rhombus = new Mesh(name);
    rhombus->SetDrawMode(GL_TRIANGLES);
    rhombus->InitFromData(vertices, indices);
    return rhombus;
}

Mesh *object_2d_pvz::create_enemy(
    const std::string& name,
    const float length,
    const glm::vec3 bg)
{
    const std::vector<VertexFormat> vertices = {
        // first hexagon
        VertexFormat(glm::vec3(0, 0, 0), bg),   // 0
        VertexFormat(glm::vec3(-length, 0, 0), bg),  // 1
        VertexFormat(glm::vec3(length * cos(RADIANS(120)), length * sin(RADIANS(120)), 0), bg),  // 2
        VertexFormat(glm::vec3(length * cos(RADIANS(60)), length * sin(RADIANS(60)), 0), bg),   // 3
        VertexFormat(glm::vec3(length, 0, 0), bg),  // 4
        VertexFormat(glm::vec3(length * cos(RADIANS(300)), length * sin(RADIANS(300)), 0), bg),  // 5
        VertexFormat(glm::vec3(length * cos(RADIANS(240)), length * sin(RADIANS(240)), 0), bg), // 6

        // second hexagon
        VertexFormat(glm::vec3(-2 * length / 3, 0, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f)), // 7
        VertexFormat(glm::vec3(2 * length * cos(RADIANS(120)) / 3, 2 * length * sin(RADIANS(120)) / 3, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f)),  // 8
        VertexFormat(glm::vec3(2 * length * cos(RADIANS(60)) / 3, 2 * length * sin(RADIANS(60)) / 3, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f)),   // 9
        VertexFormat(glm::vec3(2 * length / 3, 0, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f)),  // 10
        VertexFormat(glm::vec3(2 * length * cos(RADIANS(300)) / 3, 2 * length * sin(RADIANS(300)) / 3, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f)),  // 11
        VertexFormat(glm::vec3(2 * length * cos(RADIANS(240)) / 3, 2 * length * sin(RADIANS(240)) / 3, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f)), // 12
        VertexFormat(glm::vec3(0, 0, 10), glm::vec3(1, 153.f / 255.f, 102.f / 255.f))    // 13
        
    };

    const std::vector<unsigned int> indices = {
        // first hexagon
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1,

        // second hexagon
        13, 7, 8,
        13, 8, 9,
        13, 9, 10,
        13, 10, 11,
        13, 11, 12,
        13, 12, 7,
    };

    const auto hexagon = new Mesh(name);
    hexagon->SetDrawMode(GL_TRIANGLES);
    hexagon->InitFromData(vertices, indices);
    
    return hexagon;
}

Mesh *object_2d_pvz::create_money(
    const std::string& name,
    const float length,
    const glm::vec3 color,
    const float rotation_angle)
{
    constexpr int num_points = 5;
    constexpr float angle_increment = RADIANS(360.0f / (2 * num_points));

    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < 2 * num_points; i++) {
        constexpr float y = 0.0f;
        constexpr float x = 0.0f;
        const float radius = i % 2 == 0 ? length : length / 2.0f; 
        const float angle = angle_increment * static_cast<float>(i);
        const float x_pos = x + radius * cos(angle + rotation_angle); 
        const float y_pos = y + radius * sin(angle + rotation_angle); 

        vertices.emplace_back(glm::vec3(x_pos, y_pos, 0), color);
    }

    // Connect the vertices to form triangles
    for (int i = 0; i < 2 * num_points; ++i) {
        indices.push_back(i);         // center of the star
        indices.push_back((i + num_points) % (2 * num_points)); 
        indices.push_back((i + 1) % (2 * num_points)); 
    }

    const auto star = new Mesh(name);
    star->SetDrawMode(GL_TRIANGLES); // GL_TRIANGLES creates filled triangles
    star->InitFromData(vertices, indices);

    return star;
}

Mesh *object_2d_pvz::create_heart(
    const std::string& name,
    const float size,
    const glm::vec3 color)
{
    constexpr int num_points = 100;
    constexpr float theta_increment = glm::radians(360.0f / num_points);
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    for (int i = 0; i < num_points; i++) {
        const float theta = static_cast<float>(i) * theta_increment;
        const float x = size * 16 * static_cast<float>(pow(sin(theta), 3)); 
        const float y = size * (13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta));
        
        vertices.emplace_back(glm::vec3(x, y, 0), color);
    }

    // Connect the vertices to form triangles
    for (int i = 0; i < num_points - 2; ++i) {
        indices.push_back(0);          // center of the heart
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }

    const auto heart = new Mesh(name);
    heart->SetDrawMode(GL_TRIANGLES);  // GL_TRIANGLES creates filled triangles
    heart->InitFromData(vertices, indices);

    return heart;
}

Mesh *object_2d_pvz::create_projectile(
    const std::string& name,
    const float radius,
    const glm::vec3 color)
{
    constexpr int segments = 20;
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    // Center of the sphere
    vertices.emplace_back(glm::vec3(0, 0, 0), color);

    // Vertices for the sphere
    for (int i = 0; i <= segments; i++) {
        const float theta = static_cast<float>(i) / static_cast<float>(segments) * glm::two_pi<float>();
        const float x = radius * cos(theta);
        const float y = radius * sin(theta);

        // Adjust alpha based on the vertex position to create shading
        const float alpha = 1.0f - static_cast<float>(i) / static_cast<float>(segments);
        glm::vec3 shaded_color = glm::vec3(color.r, color.g, color.b) * alpha;

        vertices.emplace_back(glm::vec3(x, y, 0), shaded_color);
    }

    // Indices for the sphere
    for (int i = 1; i <= segments; ++i) {
        indices.push_back(0); // Center of the sphere
        indices.push_back(i);
        indices.push_back(i % segments + 1);
    }

    const auto projectile = new Mesh(name);
    projectile->SetDrawMode(GL_TRIANGLES);
    projectile->InitFromData(vertices, indices);

    return projectile;
}
