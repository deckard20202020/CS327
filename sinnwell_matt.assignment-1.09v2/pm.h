// #ifndef PM_H
// #define PM_H

#include "db_parse.h"
#include "string"
#include <vector>
#include <cmath>

#ifndef PM_H
#define PM_H

using namespace std;

// int getRandomN(int n);
// int getRandomN(int n){

//   int r = rand() % n + 1;
//   return r;
// }
int getRandomNumber(int n);

int findMDistance(int worldX, int worldY);
// int findMDistance(int worldX, int worldY) {
//   //start at 200, 200
//   int x = abs(200 - worldX);
//   int y = abs(200 - worldY);
//   return x + y;
// }

int findOriginalPLevel(int dist);
// int findOriginalPLevel(int dist) {
//   int max;
//   int min;
//   int level = -1;

//   if (dist <= 200) {
//     min = 1;
//     max = std::max((dist / 2), 1);
//   } else {
//     min = ((dist - 200) / 2);
//     max = 100;
//   }

//   while(level < min || level > max) {
//     level = getRandomN(100);
//   }

//   return level;
// }

string convertToString(char* a, int size);
// string convertToString(char* a, int size)
// {
//     int i;
//     string s = "";
//     for (i = 0; i < size; i++) {
//         s = s + a[i];
//     }
//     return s;
// }

// int findNewHp(int hp, int level) {

//     return 1;
// }

class pokemon_class {
    public:
    int id;
    string identifier;
    int gender;
    int level;
    int hp;
    int currentHP;
    int attack;
    int defense;
    int speed;
    int specialAttack;
    int specialDefense;
    int minLevel;
    int maxLevel;
    int isShiny;
    pokemon_move_db move1;
    pokemon_move_db move2;

    pokemon_class(int worldX, int worldY) {

      bool goodPokemon = false;

      while  (!goodPokemon) {

      //select a pokemon
      //we have 1092 pokemon
      //vector<pokemon> pokeMon;
      int randPokemonIdRow = getRandomNumber(1092);
      int randPokemonId = pokemon[randPokemonIdRow].id;
      this->id = randPokemonId;

      this->identifier = convertToString(pokemon[randPokemonIdRow].identifier, 30);

      //select level
      int distance = findMDistance(worldX, worldY);
      int pokeLevel = findOriginalPLevel(distance);
      this->level = pokeLevel;

      //find min and max level
      int minLevel;
      int maxLevel;
      if (distance <= 200) {
        minLevel = 1;
        maxLevel = std::max((distance / 2), 1);
      } else {
        minLevel = ((distance - 200) / 2);
        maxLevel = 100;
      }

      this->maxLevel = maxLevel;
      this->minLevel = minLevel;

      //find an IV number
      int IVhealth = getRandomNumber(15);
      int IVattack = getRandomNumber(15);
      int IVdefense = getRandomNumber(15);
      int IVspeed = getRandomNumber(15);
      int IVspecialAttack = getRandomNumber(15);
      int IVspecialDefense = getRandomNumber(15);
      vector<pokemon_stats_db> currentStats;
      for (int i = 0; i < 6553; i++) {
        if (pokemon_stats[i].pokemon_id == randPokemonId) {
          currentStats.push_back(pokemon_stats[i]);
        }
      }

      int hp;
      int attack;
      int defense;
      int speed;
      int specialAttack;
      int specialDefense;
      for (pokemon_stats_db stat : currentStats) {
        if (stat.stat_id == 1) {
          hp = stat.base_stat + IVhealth;
        }
        if (stat.stat_id == 2) {
          attack = stat.base_stat + IVattack;
        }
        if (stat.stat_id == 3) {
          defense = stat.base_stat + IVdefense;
        }
        if (stat.stat_id == 6) {
          speed = stat.base_stat + IVspeed;
        }
        if (stat.stat_id == 4) {
          specialAttack = stat.base_stat + IVspecialAttack;
        }
        if (stat.stat_id == 5) {
          specialDefense = stat.base_stat + IVspecialDefense;
        }
      }

      this->hp = hp;
      this->currentHP = hp;
      this->attack = attack;
      this->defense = defense;
      this->speed = speed;
      this->specialAttack = specialAttack;
      this->specialDefense = specialDefense;

      //get the list of all pokemon moves
      // 1.get set from pokemon_moves where
      // pokemon_moves.pokemon_id = pokemon.species_id and 
      // pokemon_moves.pokemon_move_method_id == 1

      //create a vector of the moves
      vector<pokemon_move_db> possiblePmMoves;
      while (possiblePmMoves.empty() && pokeLevel <= maxLevel) {
        possiblePmMoves.clear();

        int pmSpeciesId = pokemon[randPokemonIdRow].species_id;
        for (int i = 0; i < 528239; i++) {
            if (pokemon_moves[i].pokemon_move_method_id == 1 &&
                pokemon_moves[i].pokemon_id == pmSpeciesId &&
                pokeLevel >= pokemon_moves[i].level) {
                possiblePmMoves.push_back(pokemon_moves[i]);
            }
        }

        //assign the moves
        int randFirst;
        if (possiblePmMoves.size() > 0) {
            randFirst = getRandomNumber(possiblePmMoves.size() - 1);
            this->move1 = possiblePmMoves.at(randFirst);
        }
        if (possiblePmMoves.size() > 1) {
            int randSecond = getRandomNumber(possiblePmMoves.size()) - 1;
            while (randSecond == randFirst) {
                randSecond = getRandomNumber(possiblePmMoves.size()) - 1;
            }
            this->move2 = possiblePmMoves.at(randSecond);
        }

        // check to see if we have a good pokemon
        int movesSize = possiblePmMoves.size();
        
        if (movesSize >= 1)  {
            goodPokemon = true;
        } else {
            //we have no moves so we need to level up
            pokeLevel++;
            this->level = pokeLevel;
            hp = floor((((hp + IVhealth) * 2) * pokeLevel) / 100) + pokeLevel + 10;
            this->hp = hp;
            attack = floor ((((attack + IVattack) * 2) * pokeLevel) / 100) + 5;
            this->attack = attack;
            defense = floor ((((defense + IVdefense) * 2) * pokeLevel) / 100) + 5;
            this->defense = defense;
            speed = floor ((((speed + IVspeed) * 2) * pokeLevel) / 100) + 5;
            this->speed = speed;
            specialAttack = floor ((((specialAttack + IVspecialAttack) * 2) * pokeLevel) / 100) + 5;
            this->specialAttack = specialAttack;
            specialDefense = floor ((((specialDefense + IVspecialDefense) * 2) * pokeLevel) / 100) + 5;
            this->specialDefense = specialDefense;

        }

        // goodPokemon = true;
        

      }




      int isShine = getRandomNumber(8192);
      if (isShine == 1) {
        this->isShiny = 1;
      } else {
        this->isShiny = 0;
      }

      //select gender
      int pokeGender;
      int randGender = getRandomNumber(2);
      if (randGender == 1) {
        pokeGender = 1;
      } else {
        pokeGender = 0;
      }

      this->gender = pokeGender;        

      }




    }

};

#endif