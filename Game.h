//
// Created by rodrigo on 20/08/24.
//
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EntityManager.h"
#ifndef GAME_H
#define GAME_H

struct WindowConfig{int width, height, fps, d, dd;};
struct FontConfig{std::string font; int SF, FR, FG, FB;};
struct PlayerConfig{ int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S;};
struct EnemyConfig{ int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX;};
struct BulletConfig{ int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S;};

class Game {
    enum Category{Window=0, Font, Player, Enemy, Bullet};

    Category cat_Window = Window;
    Category cat_Font = Font;
    Category cat_Player = Player;
    Category cat_Enemy = Enemy;
    Category cat_Bullet = Bullet;

    WindowConfig win_con;
    FontConfig fon_con;
    PlayerConfig player_con;
    EnemyConfig enemy_con;
    BulletConfig bullet_con;

    std::vector<std::vector<std::string>> data_file;
    sf::RenderWindow m_window;
    EntityManager m_entities;
    sf::Font m_font;
    sf::Text m_text;
    PlayerConfig m_playerConfig;
    EnemyConfig m_enemyConfig;
    BulletConfig m_bulletConfig;
    int m_score{0};
    int m_currentFrame{0};
    int m_lastEnemySpawnTime{0};
    bool m_pause{false};
    bool m_running{true};

    std::shared_ptr<Entity> m_player;

    void init(const std::string& config);
    void setPause(bool paused);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

    void scoreBoard();
    public:

    Game(const std::string& config);

    void run();
};



#endif //GAME_H
