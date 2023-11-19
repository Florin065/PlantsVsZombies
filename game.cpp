#include "game.h"

#include <random>

#include "enemy.h"
#include "hero.h"
#include "money.h"
#include "projectile.h"
#include "PlantsVsZombies/transform2D.h"
#include "PlantsVsZombies/object2D.h"

using namespace std;
using namespace pvz;

constexpr offset offsets[weed_type::count] = {
    { 20, 145, 0, 125 },
    { 51, 176, 0, 125 },
    { 83, 208, 0, 125 },
    { 20, 145, 31, 156 },
    { 51, 176, 31, 156 },
    { 83, 208, 31, 156 },
    { 20, 145, 63, 188 },
    { 51, 176, 63, 188 },
    { 83, 208, 63, 188 }
};
const float y_values[9] = {60, 60, 60, 220, 220, 220, 380, 380, 380};

constexpr int instances_per_group[] = { 1, 2, 2, 3 };

void game::Init()
{
    const glm::ivec2 resolution = window->GetResolution();
    const auto camera = GetSceneCamera();
    camera->SetOrthographic(0, static_cast<float>(resolution.x), 0, static_cast<float>(resolution.y), 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    constexpr auto corner = glm::vec3(0, 0, 0);
    constexpr float square_side = 100;

    Mesh *weed = object_2d_pvz::create_square("weed", corner, square_side, glm::vec3(51.f / 255.f, 102.f / 255.f, 0), true);
    Mesh *home = object_2d_pvz::create_square("home", corner, square_side, glm::vec3(1,  204.f / 255.f, 153.f / 255.f), true);
    
    Mesh *hero1 = object_2d_pvz::create_hero("hero1", 60, glm::vec3(153.f / 255.f, 0, 0));
    Mesh *hero2 = object_2d_pvz::create_hero("hero2", 60, glm::vec3(0, 204.f / 255.f, 0));
    Mesh *hero3 = object_2d_pvz::create_hero("hero3", 60, glm::vec3(0, 128.f / 255.f, 1));
    Mesh *hero4 = object_2d_pvz::create_hero("hero4", 60, glm::vec3(102.f / 255.f, 51.f / 255.f, 0));
    
    Mesh *enemy1 = object_2d_pvz::create_enemy("enemy1", 50, glm::vec3(153.f / 255.f, 0, 0));
    Mesh *enemy2 = object_2d_pvz::create_enemy("enemy2", 50, glm::vec3(0, 204.f / 255.f, 0));
    Mesh *enemy3 = object_2d_pvz::create_enemy("enemy3", 50, glm::vec3(0, 128.f / 255.f, 1));
    Mesh *enemy4 = object_2d_pvz::create_enemy("enemy4", 50, glm::vec3(102.f / 255.f, 51.f / 255.f, 0));

    Mesh *money = object_2d_pvz::create_money("money", 50, glm::vec3(1, 1, 0), -60);
    Mesh *fallen_money = object_2d_pvz::create_money("fallen_money", 50, glm::vec3(102.f / 255.f, 0, 102.f / 255.f), -60);

    Mesh *heart = object_2d_pvz::create_heart("heart", 3, glm::vec3(1, 0, 0));

    Mesh *hero_square = object_2d_pvz::create_square("hero_square", corner, square_side, glm::vec3(0, 0, 0), false);

    Mesh *projectile1 = object_2d_pvz::create_projectile("projectile1", 10, glm::vec3(153.f / 255.f, 0, 0));
    Mesh *projectile2 = object_2d_pvz::create_projectile("projectile2", 10, glm::vec3(0, 204.f / 255.f, 0));
    Mesh *projectile3 = object_2d_pvz::create_projectile("projectile3", 10, glm::vec3(0, 128.f / 255.f, 1));
    Mesh *projectile4 = object_2d_pvz::create_projectile("projectile4", 10, glm::vec3(102.f / 255.f, 51.f / 255.f, 0));

    Mesh *mower = object_2d_pvz::create_mower("mower", corner, square_side, glm::vec3(153.f/255.f, 0, 76.f/255.f), true);
    
    AddMeshToList(weed);
    AddMeshToList(home);
    
    AddMeshToList(hero1);
    AddMeshToList(hero2);
    AddMeshToList(hero3);
    AddMeshToList(hero4);
    
    AddMeshToList(enemy1);
    AddMeshToList(enemy2);
    AddMeshToList(enemy3);
    AddMeshToList(enemy4);
    
    AddMeshToList(money);
    AddMeshToList(fallen_money);
    
    AddMeshToList(heart);
    
    AddMeshToList(hero_square);
    
    AddMeshToList(projectile1);
    AddMeshToList(projectile2);
    AddMeshToList(projectile3);
    AddMeshToList(projectile4);

    AddMeshToList(mower);

    smoked_weed_.resize(9);
    money_to_be_collected_.resize(3);
    mowers_.resize(3);
}

void game::FrameStart()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const glm::ivec2 resolution = window->GetResolution();

    glViewport(0, 0, resolution.x, resolution.y);
}

void game::Update(const float delta_time_seconds)
{
    for (int i = 0; i < static_cast<int>(weed_type::count); i++) {
        smoked_weed_[i].init_weed(i, static_cast<float>(std::fmod(i, 3)) * 125 + 85, static_cast<float>(i / 3 * 125)); // NOLINT(bugprone-integer-division)
        
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::scale(1.25, 1.25);
        model_matrix_ *= transform_2d::translate(smoked_weed_[i].x, smoked_weed_[i].y);
        RenderMesh2D(meshes["weed"], shaders["VertexColor"], model_matrix_);
    }

    for (int i = 0; i < static_cast<int>(mower_type::count); i++) {
        if (mowers_[i].x > 1350) continue;
        
        if (!mowers_[i].init) mowers_[i].init_mower(i, 25);
        
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(mowers_[i].x, 30 + static_cast<float>(i) * 150);
        model_matrix_ *= transform_2d::scale(0.4f, 0.7f);
        RenderMesh2D(meshes["mower"], shaders["VertexColor"], model_matrix_);
    }

    spawn_mowers(delta_time_seconds);

    model_matrix_ = glm::mat3(1);
    model_matrix_ *= transform_2d::translate(10, 0);
    model_matrix_ *= transform_2d::scale(0.7f, 4.4f);
    RenderMesh2D(meshes["home"], shaders["VertexColor"], model_matrix_);

    for (int i = 0; i < 3; i++) {
        if (i < hearts_) {
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform_2d::translate(900 + static_cast<float>(i) * 125, 650);
            RenderMesh2D(meshes["heart"], shaders["VertexColor"], model_matrix_);
        }
    }

    int dummy = 0;
    float offset_y = 0;
    for (int i = 0; i < money_; i++) {
        dummy++;
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(840 + static_cast<float>(dummy) * 40, 575 - offset_y);
        model_matrix_ *= transform_2d::scale(0.3f, 0.3f);
        RenderMesh2D(meshes["money"], shaders["VertexColor"], model_matrix_);

        if (dummy == 8) {
            dummy = 0;
            offset_y += 40;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(70 + static_cast<float>(i) * 190, 550);
        model_matrix_ *= transform_2d::scale(1.25f, 1.25f);
        RenderMesh2D(meshes["hero_square"], shaders["VertexColor"], model_matrix_);
    }

    for (int i = 0; i < 4; i++) {
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(130 + static_cast<float>(i) * 190, 612.5);
        RenderMesh2D(meshes["hero" + std::to_string(i + 1)], shaders["VertexColor"], model_matrix_);
    }


    for (int group_index = 0; group_index < 4; group_index++) {
        for (int i = 0; i < instances_per_group[group_index]; i++) {
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform_2d::translate(90 + static_cast<float>(group_index) * 190 + static_cast<float>(i) * 40, 525);
            model_matrix_ *= transform_2d::scale(0.3f, 0.3f);
            RenderMesh2D(meshes["money"], shaders["VertexColor"], model_matrix_);
        }
    }

    click_handler();
    spawn_enemies(delta_time_seconds);
    spawn_heroes(delta_time_seconds);
    collision();
    fire(delta_time_seconds);
    spawn_money_and_collect(delta_time_seconds);

    if (hearts_ == 0) exit(0); // NOLINT(concurrency-mt-unsafe)
}

void game::FrameEnd()
{
    DrawCoordinateSystem();
}

void game::OnInputUpdate(const float delta_time, const int mods) { }

void game::OnKeyPress(const int key, const int mods) { }

void game::OnKeyRelease(const int key, const int mods) { }

void game::OnMouseMove(const int mouse_x, const int mouse_y, const int delta_x, const int delta_y)
{
    if (click1_) {
        mouse_x_pos_ = static_cast<float>(mouse_x);
        mouse_y_pos_ = 720 - static_cast<float>(mouse_y);
    }

    if (click2_) {
        mouse_x_pos2_ = static_cast<float>(mouse_x);
        mouse_y_pos2_ = 720 - static_cast<float>(mouse_y);
    }
}

void game::OnMouseBtnPress(const int mouse_x, const int mouse_y, const int button, const int mods)
{
    const float y_pos = 720 - static_cast<float>(mouse_y);

    // Left click to place a hero
    if (button == 1) {
        click1_ = true;
        mouse_x_pos_ = static_cast<float>(mouse_x);
        mouse_y_pos_ = y_pos;
        hero_selection_ = select_hero(static_cast<float>(mouse_x), y_pos);
    }

    // Right click to remove a hero
    if (button == 2) {
        click2_ = true;
        mouse_x_pos2_ = static_cast<float>(mouse_x);
        mouse_y_pos2_ = y_pos;
    }
}

void game::OnMouseBtnRelease(const int mouse_x, const int mouse_y, const int button, const int mods)
{
    // If left click was released, place the hero
    if (click1_) {
        for (int i = 0; i < static_cast<int>(weed_type::count); i++) {
            const auto &weed = smoked_weed_[i];
            const bool in_range = mouse_x_pos_ > weed.x + offsets[i].x1 &&
                                  mouse_x_pos_ < weed.x + offsets[i].x2 &&
                                  mouse_y_pos_ > weed.y + offsets[i].y1 &&
                                  mouse_y_pos_ < weed.y + offsets[i].y2 &&
                                  !weed.placed;
            if (in_range && hero_selection_ != hero_type::count) {
                smoked_weed_[i].placed = true;
                hero new_hero;
                new_hero.hero_init(hero_selection_, weed.x + 75 + static_cast<float>(std::fmod(i, 3)) * 30, y_values[i], weed.type);
                heroes_.push_back(new_hero);

                if (hero_selection_ == hero_type::hero1) money_ -= 1;
                if (hero_selection_ == hero_type::hero2 || hero_selection_ == hero_type::hero3) money_ -= 2;
                if (hero_selection_ == hero_type::hero4) money_ -= 3;
            }
        }
        click1_ = false;
    }
    // If right click was released, remove the hero
    else if (click2_) {
        for (int i = 0; i < static_cast<int>(weed_type::count); i++) {
            const auto &weed = smoked_weed_[i];
            const bool in_range = mouse_x_pos2_ > weed.x + offsets[i].x1 &&
                                  mouse_x_pos2_ < weed.x + offsets[i].x2 &&
                                  mouse_y_pos2_ > weed.y + offsets[i].y1 &&
                                  mouse_y_pos2_ < weed.y + offsets[i].y2 &&
                                  weed.placed;
            if (in_range) {
                smoked_weed_[i].placed = false;
                
                for (auto &hero : heroes_) {
                    if (hero.x == weed.x + 75 + static_cast<float>(std::fmod(i, 3)) * 30  // NOLINT(clang-diagnostic-float-equal)
                        && hero.y == y_values[i]) hero.dead = true; // NOLINT(clang-diagnostic-float-equal)
                }
            }
        }
        click2_ = false;
    }
}

void game::OnMouseScroll(const int mouse_x, const int mouse_y, const int offset_x, const int offset_y) { }

void game::OnWindowResize(const int width, const int height) { }

void game::click_handler()
{
    // Render the hero that is being placed
    if (click1_ && hero_selection_ != hero_type::count) {
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(mouse_x_pos_, mouse_y_pos_);
        RenderMesh2D(meshes["hero" + std::to_string(static_cast<int>(hero_selection_) + 1)], shaders["VertexColor"], model_matrix_);
    }
}

hero_type game::select_hero(const float x, const float y) const
{
    // Check if the mouse is in the hero selection area
    if (y >= 550 && y <= 650) {
        if (money_ >= 1 && x >=  70 && x <= 170) return hero_type::hero1;
        if (money_ >= 2 && x >= 260 && x <= 360) return hero_type::hero2;
        if (money_ >= 2 && x >= 450 && x <= 550) return hero_type::hero3;
        if (money_ >= 3 && x >= 640 && x <= 740) return hero_type::hero4;
    }
    return hero_type::count;
}

void game::collision()
{
    // Check for enemy-projectile collision or enemy-hero collision
    for (auto &hero : heroes_) {
        for (auto &enemy : enemies_) {
            for (auto &projectile : projectiles_) {
                if (enemy.x <= projectile.x && enemy.y == projectile.y && enemy.bg == projectile.color && enemy.health > 0) { // NOLINT(clang-diagnostic-float-equal)
                    enemy.health--;
                    projectiles_.erase(projectiles_.begin());
                }
            }
            if (enemy.x <= hero.x && enemy.x >= hero.x - 50 && enemy.y == hero.y) { // NOLINT(clang-diagnostic-float-equal)
                hero.dead = true;
                smoked_weed_[static_cast<int>(hero.weed_type)].placed = false;
            }
        }
    }
}

void game::spawn_enemies(const float delta_time_seconds)
{
    std::default_random_engine generator;  // NOLINT(cert-msc51-cpp)
    std::uniform_real_distribution<float> distribution(1.0f, 5.0f);
    
    time_since_last_spawn_ += delta_time_seconds;

    if (time_since_last_spawn_ >= distribution(generator)) {
        // Spawn a random enemy
        enemy new_enemy;
        new_enemy.spawn_random_enemy();

        // Add the new enemy to the list of enemies
        enemies_.push_back(new_enemy);

        // Reset the timer
        time_since_last_spawn_ = 0.f;
    }

    std::vector<enemy> new_enemies;
    // Update and render existing enemies
    for (auto &enemy : enemies_) {
        // Update enemy position, rotation, etc.
        // Move the enemy towards x = 0
        if (enemy.health > 0) enemy.x -= delta_time_seconds * 100;

        // Render the enemy
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(enemy.x, enemy.y); // Translate the enemy to its position

        // If the enemy is dead, scale it down until it disappears
        if (enemy.health == 0) {
            enemy.death_animation_time -= delta_time_seconds;
            model_matrix_ *= transform_2d::scale(enemy.death_animation_time, enemy.death_animation_time);
        }
        
        switch (enemy.type) {
            case enemy_type::enemy1:
                RenderMesh2D(meshes["enemy1"], shaders["VertexColor"], model_matrix_);
                break;
            case enemy_type::enemy2:
                RenderMesh2D(meshes["enemy2"], shaders["VertexColor"], model_matrix_);
                break;
            case enemy_type::enemy3:
                RenderMesh2D(meshes["enemy3"], shaders["VertexColor"], model_matrix_);
                break;
            case enemy_type::enemy4:
                RenderMesh2D(meshes["enemy4"], shaders["VertexColor"], model_matrix_);
                break;
            case enemy_type::count:
                break;
        }

        // Add the enemy to the list of enemies if it is not dead
        if (enemy.death_animation_time > 0) new_enemies.push_back(enemy);
    }
    enemies_ = std::move(new_enemies);

    if (!enemies_.empty() && enemies_[0].x < 0) {
        // Remove the enemy from the list of enemies
        enemies_.erase(enemies_.begin());
        hearts_--;
    }
}

void game::spawn_heroes(const float delta_time_seconds)
{
    // Update and render existing heroes
    std::vector<hero> new_heroes;
    for (auto &hero : heroes_) {
        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(hero.x, hero.y);

        // If the hero is dead, scale it down until it disappears
        if (hero.dead) {
            hero.death_animation_time -= delta_time_seconds;
            model_matrix_ *= transform_2d::scale(hero.death_animation_time, hero.death_animation_time);
        }

        switch (hero.type) {
            case hero_type::hero1:
                RenderMesh2D(meshes["hero1"], shaders["VertexColor"], model_matrix_);
                break;
            case hero_type::hero2:
                RenderMesh2D(meshes["hero2"], shaders["VertexColor"], model_matrix_);
                break;
            case hero_type::hero3:
                RenderMesh2D(meshes["hero3"], shaders["VertexColor"], model_matrix_);
                break;
            case hero_type::hero4:
                RenderMesh2D(meshes["hero4"], shaders["VertexColor"], model_matrix_);
                break;
            case hero_type::count:
                break;
        }

        // Add the hero to the list of heroes if it is not dead
        if (hero.death_animation_time > 0) new_heroes.push_back(hero);
    }
    heroes_ = std::move(new_heroes);
}

void game::fire(const float delta_time_seconds)
{
    // Check if any hero is shooting
    for (auto &hero : heroes_) {
        hero.reset_shooting(delta_time_seconds);
        
        for (auto &enemy : enemies_) {
            if (hero.y == enemy.y && !hero.dead && hero.color == enemy.bg // NOLINT(clang-diagnostic-float-equal)
                && !hero.is_shooting && enemy.health > 0) {
                projectile new_projectile;
                new_projectile.spawn_projectile(hero.type, hero.x, hero.y);
                projectiles_.push_back(new_projectile);
                hero.is_shooting = true;
            }
        }
    }

    // Update and render existing projectiles
    for (auto &projectile : projectiles_) {
        projectile.radius -= delta_time_seconds * 40;
        projectile.x += delta_time_seconds * 200;

        model_matrix_ = glm::mat3(1);
        model_matrix_ *= transform_2d::translate(projectile.x, projectile.y);
        
        model_matrix_ *= transform_2d::rotate(projectile.radius);
        model_matrix_ *= transform_2d::scale(1.5f, 1.5f);
                        
        switch (projectile.type) {
        case projectile_type::projectile1:
            RenderMesh2D(meshes["projectile1"], shaders["VertexColor"], model_matrix_);
            break;
        case projectile_type::projectile2:
            RenderMesh2D(meshes["projectile2"], shaders["VertexColor"], model_matrix_);
            break;
        case projectile_type::projectile3:
            RenderMesh2D(meshes["projectile3"], shaders["VertexColor"], model_matrix_);
            break;
        case projectile_type::projectile4:
            RenderMesh2D(meshes["projectile4"], shaders["VertexColor"], model_matrix_);
            break;
        case projectile_type::count:
            break;
        }
    }
}

void game::spawn_money_and_collect(const float delta_time_seconds)
{
    std::default_random_engine generator;  // NOLINT(cert-msc51-cpp)
    std::uniform_real_distribution<float> distribution(5.0f, 10.0f);

    // Update and render existing fallen money
    for (auto &money : money_to_be_collected_) {
        if (!money.collected) {
            model_matrix_ = glm::mat3(1);
            model_matrix_ *= transform_2d::translate(money.x, money.y);

            // Render the fallen money
            RenderMesh2D(meshes["fallen_money"], shaders["VertexColor"], model_matrix_);

            // Check for left click to collect the fallen money
            if (click1_ && mouse_x_pos_ > money.x - 50 && mouse_x_pos_ < money.x + 50
                       && mouse_y_pos_ > money.y - 50 && mouse_y_pos_ < money.y + 50) {
                money.collected = true;
                money_++;

                break;
            }
        }
    }

    // Spawn a new fallen money

    time_since_last_star_spawn_ += delta_time_seconds;
    if (time_since_last_star_spawn_ >= distribution(generator)) {
        for (auto &money : money_to_be_collected_) {
            money.spawn_random_money();
        }
        time_since_last_star_spawn_ = 0.f;
    }
}

void game::spawn_mowers(const float delta_time_seconds)
{
    for (int i = 0; i < static_cast<int>(mower_type::count); i++) {
        // Check if the mower is not already active and if there is an enemy touching it
        if (!mowers_[i].is_active) {
            for (auto &enemy : enemies_) {
                if (enemy.x >= mowers_[i].x && enemy.x <= mowers_[i].x + 50
                    && enemy.y == mowers_[i].y) {  // NOLINT(clang-diagnostic-float-equal)
                    // Enemy touches the mower, so the mower should start moving
                    mowers_[i].is_active = true;
                    enemy.health = 0;
                    break;
                }
            }
        }

        // Move the mower if it is active and within bounds
        if (mowers_[i].is_active && mowers_[i].x <= 1350) mowers_[i].x += delta_time_seconds * 100;

        // Check for enemy-mower collision and update enemy status
        for (auto &enemy : enemies_) {
            if (enemy.x >= mowers_[i].x && enemy.x <= mowers_[i].x + 25
                && enemy.y == mowers_[i].y) {  // NOLINT(clang-diagnostic-float-equal)
                // Enemy intersects with the mower, so it should die
                enemy.health = 0;
            }
        }
    }
}


