#ifndef CHARACTER
#define CHARACTER

#include <Gamebuino-Meta.h>

#include "Constants.h"
#include "Actions.h"
#include "Item.h"

enum CharacterType {
  HERO,
  SLIME,
  BAT,      // LOW VISION
  SHOGGOTH, // SPAWNER
  GHOST,    // CURSE
  SCORPION, // STUN
  GOLEM,    // SLOW
  DEMON
};

enum Status {
  ATTACK,
  WAIT,
  PAUSE   // FOR SLOW MOB
};

class Character {
private:
  CharacterType type;
  Status status;
  int attack;
  int armor;
  int health;
  int maxHealth;

  void define(const CharacterType _type);

  int x;
  int y;
  int start_offset_x;
  int start_offset_y;
  int offset_x;
  int offset_y;
  int target_x;
  int target_y;

  int flip;
  int flash;

  int sight;

  int direction;
  Action action;

  void lookAt();
  void prepareMove();
  void prepareBump();
  void doMove(float timer_offset);
  void doBump(float timer_offset);
public:
  Character(const int _x, const int _y, const CharacterType _type);
  const int getX() const;
  const int getY() const;
  const int getOffsetX() const;
  const int getOffsetY() const;
  const int getTargetX() const;
  const int getTargetY() const;
  void setPosition(int _x, int _y);
  void setTarget(int _x, int _y);
  const int getSight() const;
  const CharacterType getType() const;
  const Status getStatus() const;
  void setStatus(Status _status);
  const int getFlip() const;
  void wantToGo(int direction);
  const int getNextX();
  const int getNextY();
  void setAction(Action _action);
  void computeNextAction();
  void doAction(float timer_offset);
  bool needToMove();
  bool hasInteracted();
  const int getPower() const;
  const int getHealth() const;
  const int getMaxHealth() const;
  const int getArmor() const;
  void updateStats(int weapon_attack, int armor_defense);
  void eat(int food);
  void beHit(const int atk);
  bool isAlive();
  bool isFlashed();
};

#endif
