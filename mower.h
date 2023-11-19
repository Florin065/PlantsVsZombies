#pragma once

enum class mower_type {
    mower1,
    mower2,
    mower3,
    count
};

struct mower {
    float x;
    float y;
    mower_type type;
    bool is_active;
    bool init;

    void init_mower(const int nr, const float x1)
    {
        x = x1;
        is_active = false;
        init = true;

        switch (nr) {
            case 0:
                type = mower_type::mower1;
                y = 60;
                break;
            case 1:
                type = mower_type::mower2;
                y = 220;
                break;
            case 2:
                type = mower_type::mower3;
                y = 380;
                break;
            default:
                break;
        }
    }
};
