// A minesweeper game made with c++
#include <iostream>
#include <cstdlib> //contains the rand functions
#include <ctime> //contians time functions
#include <vector> //c++ vectors as alternative to arrays.

#include "game.h"


int main() {
/* 
 main code
*/
// define the minesweeper object
// This initialises variables and grid within the game
  Minesweeper minesweeper;
  int flag=0;
  int x=-1;
  int y=-1;

  minesweeper.disp_minefield(); 
//the game loop
  while(minesweeper.get_play()==1){
//user input
    std::cout << std::endl;
    flag=minesweeper.user_input(y, x); 
//restart loop if a non-zero flag was returned	    
    if(flag!=0) {continue;}
//check if coordinate has a mine
    if(minesweeper.minefield_el(x,y)==9){
//end the game if the mine was hit
      minesweeper.win_loss(); 
      minesweeper.replay(); 
    }
    else{
//element has now been revealed
//if element is zero, reveal all nearest neighbour zero elements (execpt for diagonals)    
      minesweeper.update(x,y);
      std::cout << "There are " << minesweeper.get_safe() << " number of safe points left." << std::endl;
      std::cout << std::endl;
//win condition
      if (minesweeper.get_safe()==0){
	minesweeper.set_win(true);
        minesweeper.win_loss(); 
        minesweeper.replay(); 
      }
      else{
// continue the game and display the new partially covered mine field
        minesweeper.disp_minefield(); 
      }
    }
//play again condition    
    if(minesweeper.get_again()){ 
      minesweeper.mine_init(); 
      minesweeper.disp_minefield(); 
    }
  }
  return 0;
}
