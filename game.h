#pragma once

#include "enemy.h"
#include "hero.h"
#include "money.h"
#include "mower.h"
#include "projectile.h"
#include "weed.h"
#include "components/simple_scene.h"

struct offset {
    float x1, x2, y1, y2;
};

namespace pvz
{
    class game final : public gfxc::SimpleScene
    {
    public:
        // Constructor and destructor
        game() = default;
        ~game() override = default;
        
        // Copy constructor
        game(const game& other) : SimpleScene(other), model_matrix_(), hero_selection_()
        {
            // Perform copy of data members or resource ownership logic
        }

        // Copy assignment operator
        game& operator=(const game& other) {
            if (this != &other) {
                // Perform assignment of data members or resource ownership logic
            }
            return *this;
        }

        // Move constructor
        game(game&&) noexcept: model_matrix_(), hero_selection_()
        {
            // Perform move of data members or resource ownership logic
        }

        // Move assignment operator
        game& operator=(game&& other) noexcept {
            if (this != &other) {
                // Perform move assignment of data members or resource ownership logic
            }
            return *this;
        }

        void Init() override;
        
    private:
        void FrameStart() override;
        void Update(float delta_time_seconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float delta_time, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouse_x, int mouse_y, int delta_x, int delta_y) override;
        void OnMouseBtnPress(int mouse_x, int mouse_y, int button, int mods) override;
        void OnMouseBtnRelease(int mouse_x, int mouse_y, int button, int mods) override;
        void OnMouseScroll(int mouse_x, int mouse_y, int offset_x, int offset_y) override;
        void OnWindowResize(int width, int height) override;

        void click_handler();
        void collision();
        void spawn_enemies(float delta_time_seconds);
        hero_type select_hero(float x, float y) const;
        void spawn_heroes(float delta_time_seconds);
        void fire(float delta_time_seconds);
        void spawn_money_and_collect(float delta_time_seconds);
        void spawn_mowers(float delta_time_seconds);

    protected:
        glm::mat3 model_matrix_;
        std::vector<enemy> enemies_;
        std::vector<hero> heroes_;
        std::vector<projectile> projectiles_;
        std::vector<weed> smoked_weed_;
        std::vector<money> money_to_be_collected_;
        std::vector<mower> mowers_;

        float mouse_x_pos_ = 0.f;
        float mouse_y_pos_ = 0.f;
        float mouse_x_pos2_ = 0.f;
        float mouse_y_pos2_ = 0.f;
        
        hero_type hero_selection_;
        
        bool click1_ = false;
        bool click2_ = false;
        
        float time_since_last_spawn_      = 0.f;
        float time_since_last_star_spawn_ = 0.f;
        
        int hearts_ = 3;
        int money_  = 5;
    };
}   // namespace pvz