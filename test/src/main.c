#include <gb/gb.h>
#include "tiles.c"
#include "sprites.c"
#include "dungeon.c"


void init();
void checkInput();
void updateSwitches();
UINT8 collisionCheck(UINT8, UINT8, UINT8, UINT8, UINT8, UINT8, UINT8, UINT8);

// The player array will hold the player's position as X ([0]) and Y ([1])
UINT8 player[2];

//The enemy array will hold the enemy position as X ([0]) and Y ([1])
UINT8 enemy[2];

extern void update();

void main() {

	init();
	
	SWITCH_ROM_MBC1(1);
	update();
	
}

void init() {
	
	DISPLAY_ON;						// Turn on the display
	set_bkg_data(0, 23, tiles);		// Load 23 tiles into background memory
	
	set_bkg_tiles(0,0,20,18, dungeon);	
	
	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 2, sprites);
	
	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	set_sprite_tile(0,0);
	
	// Set the second movable sprite (1) to be the second tile in the sprite memory (1)
	set_sprite_tile(1,1);
	
	player[0] = 64;
	player[1] = 64;
	
	enemy[0] = 128;
	enemy[1] = 128;

}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

void checkInput() {

    if (joypad() & J_B) {
		
    }
	
	// UP
	if (joypad() & J_UP) {
				
		if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
			player[1]+=2; 
		} else {
			player[1]--;
		}
	}

	// DOWN
	if (joypad() & J_DOWN) {
			
		if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
			player[1]-=2; 
		} else {
			player[1]++;
		}
		
	}

	// LEFT
	if (joypad() & J_LEFT) {
		
		if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
			player[0]+=2; 
		} else {
			player[0]--;
		}
		
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		
		if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
			player[0]-=2; 
		} else {
			player[0]++;
		} 
		
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  to the position of X (player[0]) and y (player[1])
	move_sprite(0, player[0], player[1]);
	
	// Move the sprite in the second movable sprite list (1)
	//  to the position of X (enemy[0]) and y (enemy[1])
	move_sprite(1, enemy[0], enemy[1]);
	
	// Is the player colliding with the enemy?
	if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
		set_sprite_tile(0,1);
	} else {
		set_sprite_tile(1,0);
	}
	

}

// Check if two rectangles from x1,y1, and extending out h1, h2, 
//  overlap with another, x2,y2, and extending out w2, h2
UINT8 collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {

	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		
		return 1;
	
	} else {
		
		return 0;
	
	}

}