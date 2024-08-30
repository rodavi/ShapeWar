//
// Created by rodrigo on 20/08/24.
//

#include "Game.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <oneapi/tbb/profiling.h>
#include "read_file.h"

Game::Game(const std::string& config) {
    init(config);
}

void Game::run() {
//TODO: add pause functionality

    while (m_running) {
        m_entities.update();

        if(!m_pause) {
            sEnemySpawner();
            sMovement();
            sCollision();
            sUserInput();
            sLifespan();
            m_currentFrame++;
        }

        sRender();
    }
}

void Game::init(const std::string& path) {
    //TODO: read in config file here
    //      use the premade PlayerConfig, EnemyConfig, BulletConfig variables

    read_file r(path);
    r.get_config();

    win_con.width = r.m_config[cat_Window].values[0];
    win_con.height = r.m_config[cat_Window].values[1];
    win_con.fps = r.m_config[cat_Window].values[2];


    fon_con.font=r.m_config[cat_Font].values[0];
    fon_con.SF = r.m_config[cat_Font].values[1];
    fon_con.FR = r.m_config[cat_Font].values[2];
    fon_con.FG = r.m_config[cat_Font].values[3];
    fon_con.FB = r.m_config[cat_Font].values[4];

    player_con.SR = r.m_config[cat_Player].values[0];
    player_con.CR = r.m_config[cat_Player].values[1];
    player_con.FR = r.m_config[cat_Player].values[3];
    player_con.FG = r.m_config[cat_Player].values[4];
    player_con.FB = r.m_config[cat_Player].values[5];
    player_con.OR = r.m_config[cat_Player].values[6];
    player_con.OG = r.m_config[cat_Player].values[7];
    player_con.OB = r.m_config[cat_Player].values[8];
    player_con.OT = r.m_config[cat_Player].values[9];
    player_con.V = r.m_config[cat_Player].values[10];
    player_con.S = r.m_config[cat_Player].values[2];

    enemy_con.SR = r.m_config[cat_Enemy].values[0];
    enemy_con.CR = r.m_config[cat_Enemy].values[1];
    enemy_con.OR = r.m_config[cat_Enemy].values[4];
    enemy_con.OG = r.m_config[cat_Enemy].values[5];
    enemy_con.OB = r.m_config[cat_Enemy].values[6];
    enemy_con.OT = r.m_config[cat_Enemy].values[7];
    enemy_con.VMIN = r.m_config[cat_Enemy].values[8];
    enemy_con.VMAX = r.m_config[cat_Enemy].values[9];
    enemy_con.L = r.m_config[cat_Enemy].values[10];
    enemy_con.SI = r.m_config[cat_Enemy].values[11];
    enemy_con.SMIN = r.m_config[cat_Enemy].values[2];
    enemy_con.SMAX = r.m_config[cat_Enemy].values[3];

    bullet_con.SR = r.m_config[cat_Bullet].values[0];
    bullet_con.CR = r.m_config[cat_Bullet].values[1];
    bullet_con.FR = r.m_config[cat_Bullet].values[3];
    bullet_con.FG = r.m_config[cat_Bullet].values[4];
    bullet_con.FB = r.m_config[cat_Bullet].values[5];
    bullet_con.OR = r.m_config[cat_Bullet].values[6];
    bullet_con.OG = r.m_config[cat_Bullet].values[7];
    bullet_con.OB = r.m_config[cat_Bullet].values[8];
    bullet_con.OT = r.m_config[cat_Bullet].values[9];
    bullet_con.V = r.m_config[cat_Bullet].values[10];
    bullet_con.L = r.m_config[cat_Bullet].values[11];
    bullet_con.S = r.m_config[cat_Bullet].values[2];


    // set up default window parameters
    m_window.create(sf::VideoMode(win_con.width,win_con.height),
        "Assignment 2");
    m_window.setFramerateLimit(win_con.fps);

    scoreBoard();
    spawnPlayer();

}

void Game::scoreBoard() {
}

void Game::setPause(bool paused){}

void Game::sMovement() {

    for (auto e:m_entities.getEntities("enemy")) {

        e->cTransform->position.x += e->cTransform->velocity.x;
        e->cTransform->position.y += e->cTransform->velocity.y;
    }
    for(auto b:m_entities.getEntities("bullet")) {
        b->cTransform->position.x += b->cTransform->velocity.x;
        b->cTransform->position.y += b->cTransform->velocity.y;
    }

    for(auto se:m_entities.getEntities("smallEnemies")) {
        se->cTransform->position.x += se->cTransform->velocity.x;
        se->cTransform->position.y += se->cTransform->velocity.y;
    }

    m_player->cTransform->velocity = {0,0};
    if(m_player->cInput->up) {
        m_player->cTransform->velocity.y = -player_con.S;
    }
    if(m_player->cInput->down) {
        m_player->cTransform->velocity.y = player_con.S;
    }
    if(m_player->cInput->left) {
        m_player->cTransform->velocity.x = -player_con.S;
    }
    if(m_player->cInput->right) {
        m_player->cTransform->velocity.x = player_con.S;
    }


    m_player->cTransform->position.x += m_player->cTransform->velocity.x;
    m_player->cTransform->position.y += m_player->cTransform->velocity.y;
}

void Game::sUserInput() {

    sf::Event event;
    while (m_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    std::cout<<"W Key pressed"<<std::endl;
                    m_player->cInput->up = true;
                    break;
                case sf::Keyboard::S:
                    std::cout<<"S Key pressed"<<std::endl;
                m_player->cInput->down = true;
                    break;
                case sf::Keyboard::A:
                    std::cout<<"A Key pressed"<<std::endl;
                m_player->cInput->left = true;
                    break;
                case sf::Keyboard::D:
                    std::cout<<"D Key pressed"<<std::endl;
                m_player->cInput->right = true;
                    break;
                case sf::Keyboard::P:
                    std::cout<<"P Key pressed"<<std::endl;
                    break;
                case sf::Keyboard::Escape:
                    std::cout<<"ESC Key pressed"<<std::endl;
                    break;

                default: break;

            }
        }

        if (event.type == sf::Event::KeyReleased ) {
            switch (event.key.code) {
                case sf::Keyboard::W:
                    std::cout<<"W Key released"<<std::endl;
                m_player->cInput->up = false;
                break;
                case sf::Keyboard::S:
                    std::cout<<"S Key released"<<std::endl;
                m_player->cInput->down = false;
                break;
                case sf::Keyboard::A:
                    std::cout<<"A Key released"<<std::endl;
                m_player->cInput->left = false;
                break;
                case sf::Keyboard::D:
                    std::cout<<"D Key released"<<std::endl;
                m_player->cInput->right = false;
                break;
                case sf::Keyboard::P:
                    std::cout<<"P Key released"<<std::endl;
                break;
                case sf::Keyboard::Escape:
                    std::cout<<"ESC Key released"<<std::endl;
                break;

                default: break;

            }
        }

        if(event.type == sf::Event::MouseButtonPressed ) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                spawnBullet(m_player, Vec2(float(event.mouseButton.x), float(event.mouseButton.y)));
            }

            if(event.mouseButton.button == sf::Mouse::Right) {

            }
        }
    }
}

void Game::sLifespan() {
    for(auto e:m_entities.getEntities("enemy")) {

        int b_fading = 255.0f/e->cLifespan->total;

        sf::Color temp_color = e->cShape->circle.getFillColor();
        e->cShape->circle.setFillColor(sf::Color(temp_color.r,temp_color.g, temp_color.b,temp_color.a-b_fading));
        sf::Color temp_colorE = e->cShape->circle.getOutlineColor();
        e->cShape->circle.setOutlineColor(sf::Color(temp_colorE.r,temp_colorE.g, temp_colorE.b,temp_colorE.a-b_fading));


        --e->cLifespan->remaining;
        if(e->cLifespan->remaining < 0) {
        e->destroy();
        }
    }

    for(auto b:m_entities.getEntities("bullet")) {
        int b_fading = 255.0f/b->cLifespan->total;

        sf::Color temp_color = b->cShape->circle.getFillColor();
        b->cShape->circle.setFillColor(sf::Color(temp_color.r,temp_color.g, temp_color.b,temp_color.a-b_fading));
        b->cShape->circle.setOutlineColor(sf::Color(temp_color.r,temp_color.g, temp_color.b,temp_color.a-b_fading));


        --b->cLifespan->remaining;
        if(b->cLifespan->remaining < 0) {
            b->destroy();
        }
    }

    for(auto e:m_entities.getEntities("smallEnemies")) {
        float b_fading = 255.0f/(e->cLifespan->total);

        sf::Color temp_color = e->cShape->circle.getFillColor();
        std::cout<<temp_color.a<<std::endl;
        e->cShape->circle.setFillColor(sf::Color(temp_color.r,temp_color.g, temp_color.b,temp_color.a-b_fading));
        sf::Color temp_colorE = e->cShape->circle.getOutlineColor();
        e->cShape->circle.setOutlineColor(sf::Color(temp_colorE.r,temp_colorE.g, temp_colorE.b,temp_colorE.a-b_fading));


        --e->cLifespan->remaining;
        if(e->cLifespan->remaining <= 0) {
            e->destroy();
        }
    }
}

void Game::sRender() {
    m_window.clear();

    for(auto e:m_entities.getEntities()) {
        e->cShape->circle.setPosition(e->cTransform->position.x, e->cTransform->position.y);

        e->cTransform->angle+=1.0f;

        e->cShape->circle.setRotation(e->cTransform->angle);

        m_window.draw(e->cShape->circle);
    }
    m_window.display();
}

void Game::sEnemySpawner() {
    if((m_currentFrame -m_lastEnemySpawnTime)>enemy_con.SI) {
        spawnEnemy();
    }
}

void Game::sCollision() {
    for(auto e:m_entities.getEntities("enemy")) {
        for(auto b:m_entities.getEntities("bullet")) {
            // if the distance between both is smaller than 0
            if(b->cTransform->position.dist(e->cTransform->position)
                <=
                b->cCollision->radius+e->cCollision->radius) {
                b->destroy();
                e->destroy();
                m_score+=100;

                spawnSmallEnemies(e);

            }

        }

        if(e->cTransform->position.dist(m_player->cTransform->position)<=
            e->cCollision->radius+m_player->cCollision->radius) {
            e->destroy();
            m_player->destroy();
            spawnPlayer();
        }
    }
}

void Game::spawnPlayer() {

    auto entity = m_entities.addEntity("player");

    //TODO: read from config file

    float mx{m_window.getSize().x/2.0f};
    float my{m_window.getSize().y/2.0f};
    entity->cTransform = std::make_shared<CTransform>(Vec2(mx, my), Vec2(1.0f, 1.0f),0.0f);

    entity->cShape = std::make_shared<CShape>(player_con.SR, player_con.V, sf::Color(player_con.FR,player_con.FG,player_con.FB), sf::Color(player_con.OR,player_con.OG,player_con.OB), player_con.OT);

    entity->cInput = std::make_shared<CInput>();

    entity->cCollision = std::make_shared<CCollision>(player_con.CR);
    m_player = entity;
}

void Game::spawnEnemy() {
    auto entity =m_entities.addEntity("enemy");

    float ex = rand() % (m_window.getSize().x-enemy_con.CR-enemy_con.CR)+enemy_con.CR;
    float ey = rand() % (m_window.getSize().y-enemy_con.CR-enemy_con.CR)+enemy_con.CR;
    // rand()%(b-a)+a...[a,b)
    float err = rand()%(int(enemy_con.SMAX-enemy_con.SMIN))+enemy_con.SMIN;
    float exx = err*cos(6*rand()); //~2*pi
    float eyy = err*sin(6*rand());


    entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(exx, eyy), 0.0f);

    entity->cShape = std::make_shared<CShape>(enemy_con.SR*2, rand()%(enemy_con.VMAX-enemy_con.VMIN)+enemy_con.VMIN, sf::Color(rand()%255+1,rand()%255+1,rand()%255+1), sf::Color(enemy_con.OR,enemy_con.OG,enemy_con.OB), enemy_con.OT);

    entity->cCollision = std::make_shared<CCollision>(enemy_con.CR*2);

    entity->cLifespan = std::make_shared<CLifespan>(enemy_con.L);
    m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) {

    int n_sides = entity->cShape->circle.getPointCount();
    int ang_shape = 360/n_sides;

    for(int n=0;n<n_sides;++n) {
        auto se = m_entities.addEntity("smallEnemies");
        float sex = entity->cTransform->position.x;
        float sey = entity->cTransform->position.y;

        se->cTransform = std::make_shared<CTransform>(Vec2(sex,sey), Vec2(std::cos(n*ang_shape*3.1416/180), std::sin(n*ang_shape*3.1416/180)), 0.0f);
        se->cShape = std::make_shared<CShape>(entity->cShape->circle.getRadius()/2, entity->cShape->circle.getPointCount(), entity->cShape->circle.getFillColor(), entity->cShape->circle.getOutlineColor(), 4.0f);
        se->cLifespan = std::make_shared<CLifespan>(51);
    }
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos) {

    auto bullet = m_entities.addEntity("bullet");
    Vec2 bullet_speed = mousePos-m_player->cTransform->position;
    bullet_speed = bullet_speed.normalize()*bullet_con.S;

    bullet->cTransform = std::make_shared<CTransform>(m_player->cTransform->position, bullet_speed, 0.0f);
    bullet->cShape = std::make_shared<CShape>(bullet_con.SR, 100,
        sf::Color(bullet_con.FR,bullet_con.FG,bullet_con.FB),
        sf::Color(bullet_con.OR,bullet_con.OG,bullet_con.OB), bullet_con.OT);
    bullet->cCollision = std::make_shared<CCollision>(bullet_con.CR*2);
    bullet->cLifespan = std::make_shared<CLifespan>(bullet_con.L);

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity){}