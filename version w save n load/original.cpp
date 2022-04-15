#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
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

void save_character (std::ofstream& file, character& person, position& dot) {
  int len = person.name.size();
  file.write((char*)&len, sizeof(len));
  file.write(person.name.c_str(), len);
  file.write((char*)&person.health, sizeof(person.health));
  file.write((char*)&person.armor, sizeof(person.armor));
  file.write((char*)&dot.x, sizeof(dot.x));
  file.write((char*)&dot.y, sizeof(dot.y));
}

void load_character (std::ifstream& file, character& person, position& dot) {
  int len;
  file.read((char*)&len, sizeof(len));
  person.name.resize(len);
  file.read((char*)person.name.c_str(), len);
  file.read((char*)&person.health, sizeof(person.health));
  file.read((char*)&person.armor, sizeof(person.armor));
  file.read((char*)&dot.x, sizeof(dot.x));
  file.read((char*)&dot.y, sizeof(dot.y));
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

  std::cout << "Input your name, health, armor and damage: ";
  std::cin >> players[0].name >> players[0].health >> players[0].armor >> players[0].damage;

    for (int i = 1; i < 6; i++) {
      players[i].name = "Enemy #" + std::to_string(i);
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
    std::cout << "Input command: ";
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

      // BOT STEP
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

      if (command == "save") {
        std::ofstream file("save.bin", std::ios::binary);
        file.write(map[0], sizeof(map));
          for (int i = 0; i < 6; i++) {
            save_character(file, players[i], coords[i]);
          }
      }

      if (command == "load") {
        std::ifstream file2("save.bin", std::ios::binary);
        file2.read(map[0], sizeof(map));
          for (int i = 0; i < 6; i++) {
            load_character(file2, players[i], coords[i]);
          }
      }

    // SHOW MAP
      for (int i = 0; i < 40; i++) {
        for (int f = 0; f < 40; f++) {
          std::cout << map[i][f];
        }
        std::cout << std::endl;
      }

    // CHECK
    for (int i = 0; i < 6; i++) {
        std::cout << players[i].name << " Health: " << players[i].health << " Armor: " << players[i].armor << " Damage: " << players[i].damage << std::endl;
    }

    //WIN CHECK
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
      std::cout << "You lose!";
    } else if (winC == 2) {
      std::cout << "You win!";
    }
}
