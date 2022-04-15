#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

struct character {
    std::string name = "unknown";
    int health = 0;
    int armor = 0;
    int damage = 0;
};

struct position {
    int x;
    int y;
};

void take_damage (character& person, int damage) {
    std::cout << person.name << " took damage - " << damage << std::endl;
    person.armor -= damage;
    if (person.armor < 0) {
        person.health += person.armor;
        person.armor = 0;
    }
}

int main() {

    int winC = 0;
    std::srand(std::time(nullptr));
    character players[6];
    position coords[6];
    char map[40][40];

    for (int i = 0; i < 40; i++) {
        for (int f = 0; f < 40; f++) {
            map[i][f] = '.';
        }
    }

    std::cout << "This is primitive turn-based role playing game=)" << std::endl;
    std::cout << "Kill all bots or be killed by them like little noob!" << std::endl;
    std::cout << "Map marks: B - bots. P - you" << std::endl;
    std::cout << "Input your name, health, armor and damage (separate by ENTER): ";
    std::cin >> players[0].name >> players[0].health >> players[0].armor >> players[0].damage;

    for (int i = 1; i < 6; i++) {
        players[i].name = "Enemy Bot #" + std::to_string(i);
        players[i].health = (rand() % 100) + 50;
        players[i].armor = (rand() % 50) + 1;
        players[i].damage = (rand() % 15) + 15;
    }

    for (int i = 0; i < 6; i++) {
        coords[i].x = (rand() % 40);
        coords[i].y = (rand() % 40);
        if (i == 0) {
            map[coords[i].x][coords[i].y] = 'P';
        } else {
            map[coords[i].x][coords[i].y] = 'E';
        }
    }

    while (winC == 0) {

        std::string command;
        std::cout << "Input command (bottom, top, left or right): ";
        std::cin >> command;

        if (command == "bottom") {
            if (coords[0].x + 1 > 40) {
                std::cout << "Out of field!" << std::endl;
            } else {
                if (map[coords[0].x + 1][coords[0].y] == 'E') {
                    int n;
                    for (int i = 1; i < 6; i++) {
                        if (coords[0].x + 1== coords[i].x && coords[0].y == coords[i].y) {
                            n = i;
                            break;
                        }
                    }
                    take_damage (players[n], players[0].damage);
                }
                if (map[coords[0].x + 1][coords[0].y] == '.') {
                    coords[0].x = coords[0].x + 1;
                    map[coords[0].x - 1][coords[0].y] = '.';
                    map[coords[0].x][coords[0].y] = 'P';
                }
            }
        }

        if (command == "top") {
            if (coords[0].x - 1 < 0) {
                std::cout << "Out of field!" << std::endl;
            } else {
                if (map[coords[0].x - 1][coords[0].y] == 'E') {
                    int n;
                    for (int i = 1; i < 6; i++) {
                        if (coords[0].x - 1== coords[i].x && coords[0].y == coords[i].y) {
                            n = i;
                            break;
                        }
                    }
                    take_damage (players[n], players[0].damage);
                }
                if (map[coords[0].x - 1][coords[0].y] == '.') {
                    coords[0].x = coords[0].x - 1;
                    map[coords[0].x + 1][coords[0].y] = '.';
                    map[coords[0].x][coords[0].y] = 'P';
                }
            }
        }

        if (command == "right") {
            if (coords[0].y + 1 > 40) {
                std::cout << "Out of field!" << std::endl;
            } else {
                if (map[coords[0].x][coords[0].y + 1] == 'E') {
                    int n;
                    for (int i = 1; i < 6; i++) {
                        if (coords[0].x == coords[i].x && coords[0].y + 1 == coords[i].y) {
                            n = i;
                        }
                    }
                    take_damage (players[n], players[0].damage);
                }
                if (map[coords[0].x][coords[0].y + 1] == '.') {
                    coords[0].y = coords[0].y + 1;
                    map[coords[0].x][coords[0].y - 1] = '.';
                    map[coords[0].x][coords[0].y] = 'P';
                }
            }
        }

        if (command == "left") {
            if (coords[0].y - 1 < 0) {
                std::cout << "Out of field!" << std::endl;
            } else {
                if (map[coords[0].x][coords[0].y - 1] == 'E') {
                    int n;
                    for (int i = 1; i < 6; i++) {
                        if (coords[0].x == coords[i].x && coords[0].y - 1 == coords[i].y) {
                            n = i;
                        }
                    }
                    take_damage (players[n], players[0].damage);
                }
                if (map[coords[0].x][coords[0].y - 1] == '.') {
                    coords[0].y = coords[0].y - 1;
                    map[coords[0].x][coords[0].y + 1] = '.';
                    map[coords[0].x][coords[0].y] = 'P';
                }
            }
        }

        if (command != "load" && command != "save") {
            for (int i = 1; i < 6; i++) {
                int x = (rand() % 4) + 1;
                if (x == 1) {
                    if (map[coords[i].x + 1][coords[i].y] == 'P') {
                        take_damage (players[0], players[i].damage);
                    }
                    if (map[coords[i].x + 1][coords[i].y] == '.' && coords[i].x + 1 >= 0) {
                        coords[i].x = coords[i].x + 1;
                        map[coords[i].x - 1][coords[i].y] = '.';
                        map[coords[i].x][coords[i].y] = 'E';
                    }
                }
                if (x == 2) {
                    if (map[coords[i].x - 1][coords[i].y] == 'P') {
                        take_damage (players[0], players[i].damage);
                    }
                    if (map[coords[i].x - 1][coords[i].y] == '.' && coords[i].x - 1 <= 40) {
                        coords[i].x = coords[i].x - 1;
                        map[coords[i].x + 1][coords[i].y] = '.';
                        map[coords[i].x][coords[i].y] = 'E';
                    }
                }
                if (x == 3) {
                    if (map[coords[i].x][coords[i].y + 1] == 'P') {
                        take_damage (players[0], players[i].damage);
                    }
                    if (map[coords[i].x][coords[i].y + 1] == '.' && coords[i].y + 1 <= 40) {
                        coords[i].y = coords[i].y + 1;
                        map[coords[i].x][coords[i].y - 1] = '.';
                        map[coords[i].x][coords[i].y] = 'E';
                    }
                }
                if (x == 4) {
                    if (map[coords[i].x][coords[i].y - 1] == 'P') {
                        take_damage (players[0], players[i].damage);
                    }
                    if (map[coords[i].x][coords[i].y - 1] == '.' && coords[i].y - 1 >= 0) {
                        coords[i].y = coords[i].y - 1;
                        map[coords[i].x][coords[i].y + 1] = '.';
                        map[coords[i].x][coords[i].y] = 'E';
                    }
                }
                if (players[i].health <= 0) {
                    map[coords[i].x][coords[i].y] = '.';
                }
            }
        }

        for (int i = 0; i < 40; i++) {
            for (int f = 0; f < 40; f++) {
                std::cout << map[i][f];
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < 6; i++) {
            std::cout << players[i].name << " Health: " << players[i].health << " Armor: " << players[i].armor << " Damage: " << players[i].damage << std::endl;
        }

        if (players[0].health <= 0) {
            winC = 1;
        }
        if (players[1].health <= 0 &&
            players[2].health <= 0 &&
            players[3].health <= 0 &&
            players[4].health <= 0 &&
            players[5].health <= 0) {
            winC = 2;
        }
    }
    std::cout << "-----------------------------" << std::endl;
    if (winC == 1) {
        std::cout << "You lose, noob!";
    } else if (winC == 2) {
        std::cout << "Congrats, you win!";
    }
}
