#pragma once

namespace transform_2d
{
    // Translate matrix
    inline glm::mat3 translate(const float translate_x, const float translate_y)
    {
        return transpose(glm::mat3(1, 0, translate_x,
										0, 1, translate_y,
										0, 0,          1));

    }

    // Scale matrix
    inline glm::mat3 scale(const float scale_x, const float scale_y)
    {
        return transpose(glm::mat3(scale_x,      0, 0,
                                             0, scale_y, 0,
                                             0,      0, 1));

    }

    // Rotate matrix
    inline glm::mat3 rotate(const float radians)
    {
        return transpose(glm::mat3(cos(radians), -sin(radians), 0,
                                        sin(radians),  cos(radians), 0,
                                                   0,             0, 1));

    }
}   // namespace transform2D
