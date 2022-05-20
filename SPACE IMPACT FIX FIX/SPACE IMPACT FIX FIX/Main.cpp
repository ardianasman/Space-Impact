#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <time.h>
#include "Button.h"
#include "Sounds.h"
using namespace sf;
using namespace std;

class Cobject {
protected:
    float _x, _y;
public:
    Cobject() {
        _x = _y = 0;
    }
    void set(float x, float y) {
        _x = x; _y = y;
    }
    float getx() {
        return _x;
    }
    float gety() {
        return _y;
    }
    virtual void setpos(float x, float y) { }
    virtual void scale(float x, float y) {}
    virtual void move(float x, float y) {}
};

class Cbullet : public Cobject {
    Texture bul;
    Sprite bullet;
public:
    Cbullet() {}
    void addbullet() {
        bul.loadFromFile("Graphics/laserRed07.png");
        bullet.setTexture(bul);
    }
    void setpos(float x, float y) {
        bullet.setPosition(x, y);
        _x = x; _y = y;
    }
    void scale(float x, float y) {
        bullet.setScale(x, y);
    }
    void moves(float x, float y) {
        bullet.move(x, y);
        _x += x;
        _y += y;
    }
    Sprite getb() {
        return bullet;
    }
};

class Cplayer : public Cobject {
    Texture pla;
    Sprite player;

public:
    Cplayer() {
        pla.loadFromFile("Graphics/playerShip1_red.png");
        player.setTexture(pla);
    }
    void setpos(float x, float y) {
        player.setPosition(x, y);
        _x = x; _y = y;
    }
    void scale(float x, float y) {
        player.setScale(x, y);
    }
    void moves(float x, float y) {
        player.move(x, y);
        _x += x;
        _y += y;
    }
    Sprite getplayer() {
        return player;
    }
};

class Cenemy : public Cobject {
protected:
    Texture ene;
    Sprite enemy;
    int lastdir, health;
public:
    Cenemy() {
        ene.loadFromFile("Graphics/enemyRed1.png");
        enemy.setTexture(ene);
        lastdir = 0;
        health = 0;
    }
    void addenemy() {
        enemy.setTexture(ene);
    }
    void setpos(float x, float y) {
        enemy.setPosition(x, y);
        _x = x; _y = y;
    }
    void scale(float x, float y) {
        enemy.setScale(x, y);
    }
    void moves(float x, float y) {
        enemy.move(x, y);
        _x += x;
        _y += y;
    }
    void setdir(int x) {
        lastdir = x;
    }
    void sethealth(int hp) {
        health = hp;
    }
    int gethealth() {
        return health;
    }
    virtual void update() {
        double x = 0;
        if (lastdir == 1) {
            if (_x == 270) {
                x = -0.5;
            }
            else if (_x == 0) {
                x = 0.5;
                setdir(2);
            }
            else {
                x = -0.5;
            }
            enemy.move(x, 0);
        }
        else if (lastdir == 2) {
            if (_x == 0) {
                x = 0.5;
            }
            else if (_x == 270) {
                x = -0.5;
                setdir(1);
            }
            else {
                x = 0.5;
            }
            enemy.move(x, 0);
        }
        _x += x;
    }
    Sprite getenemy() {
        return enemy;
    }
    virtual void launchshield(int a) {

    }
    virtual void decreasehealth(int a) {
        health = health - a;
    }
    virtual int getjenis() {
        return 1;
    }
    virtual bool getshield() {
        return 0;
    }
};

class Cenemyzigzag : public Cenemy {
public:
    void update() {
        double x = 0;
        if (lastdir == 1) {
            if (_x == 270) {
                x = -0.5;
            }
            else if (_x == 0) {
                x = 0.5;
                setdir(2);
            }
            else {
                x = -0.5;
            }
            enemy.move(x, 0.25);
        }
        else if (lastdir == 2) {
            if (_x == 0) {
                x = 0.5;
            }
            else if (_x == 270) {
                x = -0.5;
                setdir(1);
            }
            else {
                x = 0.5;
            }
            enemy.move(x, 0.25);
        }
        _x += x;
        _y += 0.25;
    }
    void decreasehealth(int a) {
        health = health - a;
    }
    int getjenis() {
        return 2;
    }
};

class Cenemyshield : public Cenemy {
protected:
    int temphealth, start = 0;
    bool shield, cek = false, checkshield;
public:
    void setshield(bool a) {
        shield = a;
    }
    bool getshield() {
        return checkshield;
    }
    void update() {
        double x = 0;
        if (shield) {
            x = 0;
        }
        else {
            if (lastdir == 1) {
                if (_x == 270) {
                    x = -0.5;
                }
                else if (_x == 0) {
                    x = 0.5;
                    setdir(2);
                }
                else {
                    x = -0.5;
                }
                enemy.move(x, 0);
            }
            else if (lastdir == 2) {
                if (_x == 0) {
                    x = 0.5;
                }
                else if (_x == 270) {
                    x = -0.5;
                    setdir(1);
                }
                else {
                    x = 0.5;
                }
                enemy.move(x, 0);
            }
            _x += x;
        }
    }
    void launchshield(int a) {
        double x;
        double y;
        if (!cek) {
            start = GetTickCount();
            cek = 1;
        }
        if (!shield) {
            checkshield = false;
            x = 0;
            y = 0;
            int seconds = GetTickCount() - start;
            if (seconds >= 5000) {
                shield = 1;
                cek = 0;
                start = 0;
            }

        }
        if (!cek) {
            start = GetTickCount();
            cek = 1;
        }
        if (shield) {
            checkshield = true;
            x = -0.5;
            y = 0;
            int seconds = GetTickCount() - start;
            if (seconds >= 5000) {
                shield = 0;
                cek = 0;
                start = 0;
            }

        }
    }
    void decreasehealth(int a) {
        health = health - a;
    }
    int getjenis() {
        return 3;
    }
};

class Cworld {
    Sprite world;
    Texture wor;
public:
    Cworld() {
        wor.loadFromFile("Graphics/darkPurple.png");
        world.setTexture(wor);
        world.scale(2.5, 3);
    }
    Sprite getworld() {
        return world;
    }
};


class Cmainmenu {
    Sprite mainmenu;
    Texture main;
public:
    Cmainmenu() {
        main.loadFromFile("Graphics/main.jpg");
        mainmenu.setTexture(main);
        mainmenu.scale(0.1, 0.2);
        mainmenu.setPosition(-50, -50);
    }
    Sprite getmenu() {
        return mainmenu;
    }
};

class Cgame {
    double x = 0, y = 0;
    bool over = false, lc = false;
    float dx = 0, dy = 0, shield = 0;
    int c = 0, start = 0, score = 0;
    vector <Cbullet*> bullet;
    Cplayer player;
    vector <Cenemy*>enemy;
    RenderWindow window;
    Cworld world;
    Cmainmenu mainmenu;
    Cbutton* startbtn, * exitbtn, * title, * back, * lose;
    Csound* song, * shoot;
    Event event;
    Clock clock;
    Time times;
public:
    void init() {
        startbtn = new Cstart;
        exitbtn = new Cexit;
        title = new Ctitle;
        back = new Cback;
        lose = new Close;
        song = new Csong;
        shoot = new Claser;
        srand(time(NULL));
        for (int i = 0; i < 3; i++) {
            addenemy();
        }
        player.setpos(125, 400);
        player.scale(0.7, 0.7);
        song->plays();
        cout << enemy.size();
    }
    void run() {
        window.create(VideoMode(320, 480), "Space Impact");
        window.setPosition(sf::Vector2i(10, 50));

        // RUN
        while (over != true) {
            for (int i = 0; i < enemy.size(); i++) {
                if (enemy[i]->getjenis() == 3) {
                    shield = rand() % 2 + 1;
                    enemy[i]->launchshield(shield);
                }
            }
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
            if (start == 0) {
                window.draw(mainmenu.getmenu());
                menu();
            }
            if (start == 1) {
                processinput();
                updates();
                draw();
            }
            if (start == 2) {
                window.clear(Color::White);
                window.setFramerateLimit(120);
                window.draw(world.getworld());
                losecheck();
            }
        }
    }
    void updates() {
        float x;
        int r;
        times = clock.getElapsedTime();
        x = times.asMilliseconds();
        x += 0.5;
        player.moves(dx * x, dy * x);
        for (int i = 0; i < enemy.size(); i++) {
            enemy[i]->update();
        }
        for (int i = 0; i < bullet.size(); i++) {
            bullet[i]->moves(0 * x, -0.1 * x);
        }
        bulletcheck();
        for (int i = 0; i < enemy.size(); i++) {
            planecheck(i);
        }
        clock.restart();
    }
    void draw() {
        window.clear(Color::White);
        window.setFramerateLimit(120);
        window.draw(world.getworld());
        window.draw(player.getplayer());
        for (int i = 0; i < enemy.size(); i++) {
            window.draw(enemy[i]->getenemy());
        }
        for (int i = 0; i < bullet.size(); i++) {
            window.draw(bullet[i]->getb());
        }
        window.draw(back->getbutton());
        printScore(200, 5);
        window.display();
        if (event.mouseMove.x < 50 && event.mouseMove.x > 5) {
            if (event.mouseMove.y < 40 && event.mouseMove.y > 5) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    start = 0;
                    score = 0;
                    shoot->plays();
                    enemy.clear();
                    for (int i = 0; i < 3; i++) {
                        addenemy();
                    }
                }
            }
        }
    }
    void bulletcheck() {
        for (int q = 0; q < enemy.size(); q++) {
            for (int j = 0; j < bullet.size(); j++) {
                if (bullet[j]->getx() >= enemy[q]->getx() - 33 && bullet[j]->getx() <= enemy[q]->getx() + 33) {
                    if (bullet[j]->gety() + 5 < enemy[q]->gety() + 50) {
                        delbullet(j);
                        if (enemy[q]->getjenis() == 3) {
                            if (enemy[q]->getshield() == true) {
                            }
                            else {
                                enemy[q]->decreasehealth(1);
                                if (enemy[q]->gethealth() == 0) {
                                    score++;
                                    delenemy(q);
                                    addenemy();
                                }
                            }
                        }
                        else {
                            enemy[q]->decreasehealth(1);
                            if (enemy[q]->gethealth() == 0) {
                                score++;
                                delenemy(q);
                                addenemy();
                            }
                        }
                    }
                }
            }
        }
    }
    void addenemy() {
        int rx, ry, r, hp, randomenemy, ty=0;
        rx = rand() % 200 + 50;
        ry = rand() % 300 + 10;
        r = rand() % 2 + 1;
        hp = rand() % 8 + 12;
        randomenemy = rand() % 3 + 1;
        shield = rand() % 2 + 1;
        for (int i = 0;i < enemy.size();i++) {
            if (ty  <= enemy[i]->gety() + 40 && ty >= enemy[i]->gety() - 40) {
                rx = rand() % 200 + 50;
                ry = rx + 15;
                cout << "sama" << endl;
                break;
            }
        }
        if (randomenemy == 1) {
            enemy.push_back(new Cenemy);
            enemy[enemy.size() - 1]->scale(0.6, 0.6);
            enemy[enemy.size() - 1]->addenemy();
            enemy[enemy.size() - 1]->setpos(rx, ry);
            enemy[enemy.size() - 1]->setdir(r);
            enemy[enemy.size() - 1]->sethealth(hp);
            ty = ry;
        }
        else if (randomenemy == 2) {
            enemy.push_back(new Cenemyzigzag);
            enemy[enemy.size() - 1]->scale(0.6, 0.6);
            enemy[enemy.size() - 1]->addenemy();
            enemy[enemy.size() - 1]->setpos(rx, ry);
            enemy[enemy.size() - 1]->setdir(r);
            enemy[enemy.size() - 1]->sethealth(hp);
            ty = ry;
        }
        else if (randomenemy == 3) {
            enemy.push_back(new Cenemyshield);
            enemy[enemy.size() - 1]->scale(0.6, 0.6);
            enemy[enemy.size() - 1]->addenemy();
            enemy[enemy.size() - 1]->setpos(rx, ry);
            enemy[enemy.size() - 1]->setdir(r);
            enemy[enemy.size() - 1]->sethealth(hp);
            enemy[enemy.size() - 1]->launchshield(shield);
            ty = ry;
        }
    }
    void planecheck(int q) {
        if (player.getx() + 33 >= enemy[q]->getx() - 13 && player.getx() + 33 <= enemy[q]->getx() + 33) {
            if (player.gety() - 15 <= enemy[q]->gety() + 40) {
                Sleep(300);
                start = 2;
            }
        }
        if (enemy[q]->gety() >= 430) {
            Sleep(300);
            start = 2;
        }
    }
    void delbullet(int ind) {
        bullet.erase(bullet.begin() + ind);
    }
    void delenemy(int ind) {
        enemy.erase(enemy.begin() + ind);
    }
    void menu() {
        window.draw(title->getbutton());
        window.draw(startbtn->getbutton());
        window.draw(exitbtn->getbutton());
        window.display();
        if (event.mouseMove.x < 215 && event.mouseMove.x > 110) {
            if (event.mouseMove.y < 296 && event.mouseMove.y > 273) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    start = 1;
                    shoot->plays();
                }
            }
        }
        if (event.mouseMove.x < 215 && event.mouseMove.x > 110) {
            if (event.mouseMove.y < 361 && event.mouseMove.y > 338) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    over = true;
                    shoot->plays();
                }
            }
        }
    }
    void printScore(int tx, int ty) {
        sf::Text text, angka;
        sf::Font font;
        font.loadFromFile("Graphics/1971.ttf");
        text.setFont(font);
        text.setCharacterSize(20);
        text.setPosition(tx, ty);
        text.setString("SCORE ");
        window.draw(text);

        stringstream ss;
        ss << score;
        angka.setFont(font);
        angka.setCharacterSize(20);
        angka.setPosition(tx + 90, ty);
        angka.setString(ss.str().c_str());
        window.draw(angka);
    }
    void losecheck() {
        window.draw(lose->getbutton());
        window.draw(back->getbutton());
        printScore(108, 168);
        window.display();
        if (event.mouseMove.x < 50 && event.mouseMove.x > 5) {
            if (event.mouseMove.y < 40 && event.mouseMove.y > 5) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    start = 0;
                    score = 0;
                    shoot->plays();
                    enemy.clear();
                    for (int i = 0; i < 3; i++) {
                        addenemy();
                    }
                }
            }
        }
    }
    void processinput() {
        if (add() && c > 10) {
            bullet.push_back(new Cbullet);
            bullet[bullet.size() - 1]->scale(0.5, 0.5);
            bullet[bullet.size() - 1]->addbullet();
            bullet[bullet.size() - 1]->setpos(player.getx() + 33, player.gety() - 15);
            c = 0;
            shoot->plays();
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            dy = -0.1;
            c++;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)) {
            dx = -0.1;
            c++;
        }
        else if (Keyboard::isKeyPressed(Keyboard::S)) {
            dy = 0.1;
            c++;
        }
        else if (Keyboard::isKeyPressed(Keyboard::D)) {
            dx = 0.1;
            c++;
        }
        else
            dx = dy = 0;
    }
    bool add() {
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            return true;
        }
        else
            return false;
    }
};
int main() {
    Cgame game;
    game.init();
    game.run();
}