#include "Player.h"

Player::Player(float x, float y, int health, Vector2 speed, int projDmg)
    : pl_pos({x, y}), pl_health(health), pl_speed(speed), pl_projdmg(projDmg) {}

Player::~Player() {}

//set
void Player::setPLHealth(int health) {pl_health = health;}
void Player::setPLSpeed(Vector2& speed) {pl_speed = speed;}
void Player::setPLProjDmg(int projDmg) {pl_projdmg = projDmg;}

//get
Vector2 Player::getPLPos()  {return pl_pos;}
Vector2 Player::getPLSpeed()  {return pl_speed;}
int Player::getPLHealth() {return pl_health;}
int Player::getPLProjDmg()  {return pl_projdmg;}    