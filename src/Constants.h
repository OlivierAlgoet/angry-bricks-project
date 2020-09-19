#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FPS 60.0

#define DEBUG_MODE false

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 450

#define BACKGROUND_WIDTH 1200
#define BACKGROUND_HEIGHT 600

#define MISSILE_SRC_WIDTH 375
#define MISSILE_SRC_HEIGHT 375
#define MISSILE_DST_WIDTH 35
#define MISSILE_DST_HEIGHT 35

#define LAUNCHER_SRC_WIDTH 152
#define LAUNCHER_SRC_HEIGHT 214
#define LAUNCHER_DST_WIDTH 114
#define LAUNCHER_DST_HEIGHT 161

#define MAX_HIGHSCORES 4
#define MISSILES 4
#define LEVEL_SIZE 8

//OWN DEFINED CONSTANTS
#define PADY 80
#define TRG 'T' // chars for the levels
#define ST 'S'
#define BX 'B'
#define MISS_NR 3 // NR of missiles and there numbers
#define Missile_1 0
#define Missile_2 1
#define Missile_3 2
// SPACING COORDINATES
#define MISSILE_SPACING 10
#define Y_OFFSET 90 // offset equals to brown ground
#define XLAUNCH ((MISS_NR-1)*(MISSILE_SPACING+MISSILE_DST_WIDTH+5)) // 5 trial error constant
//BOWSTRING
#define BOWSTRINGX1 (XLAUNCH+15)
#define BOWSTRINGY1 (LAUNCHER_DST_HEIGHT+Y_OFFSET-15)
#define BOWSTRINGX2 (BOWSTRINGX1+LAUNCHER_DST_WIDTH-30)
#define BOWSTRINGY2 (BOWSTRINGY1-20)
//CURRENTMISSILE
#define MISSILEX (BOWSTRINGX1+(LAUNCHER_DST_WIDTH-30)/2-MISSILE_DST_WIDTH/2) //Missile placement
#define MISSILEY (BOWSTRINGY1-MISSILE_DST_HEIGHT-10)
#define BOUNCELOSS 0.5 // On bounce elasticity is not assumed, loss of velocity
#define SPEED_THRESHOLD 1 // If speed is lower then 1 missile will dissapear
//OTHER
#define ZERO_PAD 3 // for rendering the score max 3 zeros
#define KSPEED 2 // Multiplication factor for missile speed Kspeed* Launcher stretch --> missile system
#define LEVEL_NR 3 // Number of levels
#define SCORE_X 10 // Score string position in allkit coordinates
#define SCORE_Y 10
#define COLLISION_THRESHOLD (2*(MISSILE_DST_WIDTH+MISSILE_DST_HEIGHT)) // we take this as threshold distance
// speed definitions to delete one extra or 2 extra missiles
#define SPEED1  140
#define SPEED2  240

#endif