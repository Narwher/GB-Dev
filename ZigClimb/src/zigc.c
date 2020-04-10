/*

ZigClimb by flend - flend.net
Nintendo Game Boy port by Narwher - legitvidya@gmail.com

*/

#include <ncurses.h> // might remove for GB compatibility
#include <gb/gb.h>

//'for' short form
#define F(v,h)for(v=0;v<h;v++)
//launch instruction 'i' for every tile in the dungeon
#define D(i)F(y,T)F(x,S){i;}

//short form for dungeon tile at position x,y
#define G M[x][y]
//target of a move
#define H M[x+a][y+b]
//find a direction from 2 coords on an axis (-1,0,1)
#define Z(n)n<0?-1:(n>0?1:0)

//random number
#define r rand()

//gb initialize
void init();
void checkInput();

//x,y: For variables
//f,g: PC's location
//c: Input character
//q: Temp variable for loops & weapon strength
//S,T: Size of dungeon
//M: Map
//e: empty square ASCII code
//o: PC code '@' 64 + 128 'has moved' flag = 192
//l: level count
//w: weapon value
//s: armour value
//h: hp
//z: gems

//L: Dungeon features inc PC

int x,y,f,g,c=53,q,S=40,T=20,M[40][20],e=46,o=192,l=0,w=1,s=1,h=10,z=0;
char L[]="@<!%(";

// find a random empty position and insert t in it
E(t){while(M[x=r%S][y=r%T]-e);G=t;}

// escape level
i(){D(G=x+y?e:64)}

//Dig recursively
d(x,y) {

  //Location variables, used recursively so have to be local
  int i,j;

  //Bounds checking - don't dig out right to the edge of the screen
  if(x>0&&y>0&&x<S-1&&y<T-1&&G-e){
    //Dig out this area
    G=e;
    //Dig out surrounding areas (3x3 grid). Dig chance 80%
    F(i,3)F(j,3)r%5<4||d(x+i-1,y+j-1);
  }
}

//Generate dungeon
n(){

  //Need 200 out of 800 blocks open to make an acceptable, nice-looking level
  //Sum of level must be < 30200
  //200 * '.' [46] + 600 * '#' [35] = 30200

  q=0;

  while(q<30200){

    //All blocks
    D(G=35)
    //Dig at a random start position
    d(r%S,r%T);

    //Calculate the sum of the level
    q=0;
    D(q+=G)
  }

  //Add features and items at random positions
  F(q,5)E(L[q]);
  //Add monsters. Strength (a) + level + 0-7
  F(q,2*l+r%9)E(97+r%7+l);
}

//Move an actor by offset x:a, y:b
m(a,b){
  
  //Check PC or monster
  G-64?
    
    //Actor: Monster

    //Store monster strength
    q=G-97,

    //Target: Player
    //Hit chance: level (x-a) + 0-4 - s(armor) >= 3 for hit
    H^o||(q+r%5-s<3||h--)

    :
    
    //PC
    
    (
     //Store weapon strength
     q=w,
     //! potion - restore HP
     H^33||(h=10,H=e),
     //< upstaircase, new level, if at 10 then escape
     H^60||(l++,l<10?n():i(),clear()),
     //% armour, change armor value
     H^37||(s=l+r%7,H=e),
     //( weapon, change weapon value
     H^40||(w=l+r%5,H=e),
     //* gems, random amount based on dungeon level
     H^42||(z+=l+r%3,H=e)
     ),

    //Actor: PC or monster
    
    //Target: Monster

    //Don't make the player hit himself he doesn't move
    H^o&&
    //Hit chance: weapon/level + 0-4 >= monster level (x-a)
    //Monster that haven't moved don't have the flag so H&127
    (H<96||(q+r%5<((H&127)-97)||(H=42)));

  //Set 'have been moved' flag
  G|=128;

  //Move into (now) empty space
  H-e||(H=G,G=e);

}


main(){

  //Setup random
  srand(time(0));
  
  //Setup curses
  initscr();

  //Generate dungeon
  n();
 
  //Run main loop until player presses 'Q' or dies
  while(c-81&&h>0){

    //Move PC if required
    D(
      //Numeric key pressed
      c<49||c>57||
      //@
      G-64||
      //Translates number ASCII codes into -1,-1 -> +1,+1 directions
      m((c-1)%3-1,(49-c)/3+1)
      )

    //Find PC's location
    //The PC might not have the move flag set when moving to a new level
    D((G&127)-64||(f=x,g=y))
    
    //Move monsters
    D(
      //Monster range a=97, z=122
      G<97||G>122||
      //Movement direction
      m(Z(f-x),Z(g-y))
    )

    //Reset 'has moved' flag on all actors
    D(G&=127)

    //Only draw squares within 5 radius circle
    D(
      //Circular LOS
      (f-x)*(f-x)+(g-y)*(g-y)>25||
      //Draw LOS
      mvaddch(y,x,G)
      )

    //Status line
    mvprintw(T,0,"H:%d L:%d WA:%d/%d *:%d %s%s",h,l,w,s,z,h?"":";(",l>9?"OUT":"");

    //Get input
    c=getch();
   }
  
  //End curses mode
  endwin();
}

//gb functions
void init() {
	
	DISPLAY_ON;		// Turn on the display
	NR52_REG = 0x8F;	// Turn on the sound
	NR51_REG = 0x11;	// Enable the sound channels
	NR50_REG = 0x77;	// Increase the volume to its max
}

void checkInput() {

   // if (joypad() & J_B) {
	// The B button was pressed!
    //}

}
