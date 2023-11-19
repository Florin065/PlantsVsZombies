#pragma once

struct money {
    float x, y;
    bool collected;

    void spawn_random_money()
    {
        x = static_cast<float>(rand() % 800);  // NOLINT(concurrency-mt-unsafe)
        y = static_cast<float>(rand() % 600);  // NOLINT(concurrency-mt-unsafe)
        collected = false;
    }
};
