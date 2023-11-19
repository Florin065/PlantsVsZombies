#pragma once

enum class weed_type {
    weed1,
    weed2,
    weed3,
    weed4,
    weed5,
    weed6,
    weed7,
    weed8,
    weed9,
    count
};

class weed
{
public:
    float x;
    float y;
    weed_type type;
    bool placed;

    weed() : x(0), y(0), type(), placed(false) { }

    void init_weed(const int nr, const float x1, const float y1)
    {
        x = x1;
        y = y1;

        switch (nr) {
            case 0:
                type = weed_type::weed1;
                break;
            case 1:
                type = weed_type::weed2;
                break;
            case 2:
                type = weed_type::weed3;
                break;
            case 3:
                type = weed_type::weed4;
                break;
            case 4:
                type = weed_type::weed5;
                break;
            case 5:
                type = weed_type::weed6;
                break;
            case 6:
                type = weed_type::weed7;
                break;
            case 7:
                type = weed_type::weed8;
                break;
            case 8:
                type = weed_type::weed9;
                break;
            default:
                break;
        }
    }
};
