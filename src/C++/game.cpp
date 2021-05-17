//define what variables and methods are in this class.
#include "game.h"

#include <iostream>
#include <cstdlib> //contains the rand functions
#include <ctime> //contians time functions
#include <vector> //c++ vectors as alternative to arrays.


Minesweeper::Minesweeper() {
//initialise the variables	
  this->N=10;
  this->imx=9;
  this->jmx=9;
  this->play=1;
  this->mfld.resize(this->imx,std::vector<int>(this->jmx,0)); //initiates the mine field to zero
  this->dsp.resize(this->imx,std::vector<int>(this->jmx,0)); //initiates the displayed mine field to zero

  mine_init();//initialise the game
}

void Minesweeper::mine_init(){
//initialises the game
  zero(this->mfld); //initiates the mine field to zero
  zero(this->dsp); //initiates the displayed mine field to zero
  this->safe=this->imx*this->jmx-N;
  this->again=false;
  this->win=false;
  this->unravel=false;
//initialise the minefield
  init_minefield();
// display the covered mine field
//  disp_minefield();
//EOF
}

int Minesweeper::element(int i, int j, std::vector<std::vector<int>> &arr) {
/*
return the 2D vector element at arr[i][j]
*/
  return arr[i][j];
//EOF
}



void Minesweeper::win_loss(){
//win/lose end game message
  this->unravel=true;
  disp_minefield();
  if(this->win){
    std::cout << "Congratulations! You won!" << std::endl;
  }
  else{
    std::cout << "Mine hit! Game Over." << std::endl;
  }
  std::cout << "x shows the position of the mines." << std::endl;
//EOF
}

void Minesweeper::replay(){
//play again
  std::cout << "Enter 1 to play again" << std::endl;
  std::cin >> this->play;
  if(this->play==1){this->again=true;}
//EOF
}

void Minesweeper::update(int i, int j){
//updates displayed mine field

//if element is zero, reveal all nearest neighbour zero elements (execpt for diagonals)    
  if(this->dsp[i][j]==0) {
    reveal_zeros(i,j);
//otherwise reveal element.
  }
  else {
    this->dsp[i][j] = 1;
//decrease number of safe elements left to guess
    this->safe--;
  }
//EOF
}

void Minesweeper::hints() {
/*
This function generates the numbered hints of the nearest neighbour mines
As per C++, the reference of the mine field vector has been passed through,
*/
  int imax=this->imx;
  int jmax=this->jmx;
  int i, j, N=imax*jmax;
//determine the hints
  for (i=0; i<imax; i++){
    for (j=0; j<jmax; j++){
//skip if that element is a mine. Note that we are going through the address
      if(this->mfld[i][j]==9) {continue;}
      int di,dj;
//loop around nearest neighbours to look for mines
      for(di=-1; di<=1; di++){
        for(dj=-1; dj<=1; dj++){
//skip (i,j) coordinate
          if((di==0)&&(dj==0)){continue;}
          else if((i+di<0)||(i+di>=imax)){continue;}
          else if((j+dj<0)||(j+dj>=jmax)){continue;}
//add 1 if a mine is present in the nearest neighbour array element
          if(this->mfld[i+di][j+dj]==9) {this->mfld[i][j]+=1;}
        }
      }
    }
  }
//EOF
}

void Minesweeper::init_minefield() {
/*
This function constructs mine field by (psuedo) randomly generating
the mines' coordinates.
*/

//mine position indices
  int imax=this->imx;
  int jmax=this->jmx;
  int Nmines=this->N;
  int n;
// initialise the random number seed
  std::srand(std::time(nullptr));
// place mines in field
  for (n=0; n<Nmines; n++) {
    int mi, mj;
// randomly generate coordinates          
    mi= (int) imax * static_cast<float>(std::rand()) / RAND_MAX;
    mj= (int) jmax * static_cast<float>(std::rand()) / RAND_MAX;
// place mine at coordinates in field array. Note that "9" represents a mine
    if (this->mfld[mi][mj]!=9) {
      this->mfld[mi][mj]=9;
    }
// If a mine is already present, redo the loop by reducing loop counter
    else {
      n--;
    }
  }
//add nearest neighbour hints
  hints();
//EOF
}

void Minesweeper::disp_minefield() {
/*
This function displays the obscured mine field.
*/
  int i,j;
  int imax=this->imx;
  int jmax=this->jmx;

  std::cout << std::endl;
//loop over the array
  for (i=0; i<imax; i++){
    for (j=0; j<imax; j++){
//print y coordinates       
      if(j==0){std::cout << imax-1-i << "  ";}
//print masked or revealed element or mine position if the game was lost 
//reveal mine position
      if(this->unravel){
        if(this->mfld[i][j]==9){std::cout << "x ";}
        else{std::cout << this->mfld[i][j] << " ";}
      }
//display revealed non-mine element
      else if(this->dsp[i][j]==1){
        std::cout << this->mfld[i][j] << " ";
      }
//display masked element
      else{
        std::cout << "* ";
      }
    }
    std::cout << std::endl;
  }
// output x-grid coordinates
  std::cout << std::endl;
  std::cout << "   ";
  for (i=0; i<imax; i++){
    std::cout << i << " ";
  }
  std::cout << std::endl;
//EOF
}

int Minesweeper::user_input(int &i, int &j) {
/*
This function manages the user inputs.
*/
  int imax=this->imx;
  int jmax=this->jmx;

//user input
  std::cout << "Please input your integer guess coordinates" << std::endl;
  std::cout << "(x, y) coordiates in that order: ";
  std::cin >> i >> j;
  std::cout << std::endl;
//due to the display, the input row index will be imax - *i
  j=jmax-1-j;
//outputs warning and returns "flag" for main code to deal with this
  if((i>imax)||(i<0)||(j>jmax)||(j<0)){
    std::cout << "Your (x, y) input coordinates are not within the following bounds:" << std::endl;
    std::cout << "0 <= x <= " << imax-1 <<" and 0 <= y <= " << jmax-1 << "." << std::endl;
    std::cout << "Please enter new coordinates." << std::endl;
    return 1;
  }
// i and j positions flips as i refers to x coordinate (column) and j is y (row).
  else if(this->dsp[j][i]==1){
    std::cout << "Your (x, y) input coordinates have been entered previously." << std::endl;
    std::cout << "Please enter new coordinates." << std::endl;
    return 2;
  }
//return default "flag"
  return 0;
//EOF
}

void Minesweeper::zero(std::vector<std::vector<int>> &arr) {
/*
Setting the vectors to zero if user plays the game again
*/
  for (auto &i : arr) {
    std::fill(i.begin(), i.end(), 0);
  }
//EOF
}

void Minesweeper::reveal_zeros(int i, int j){
/*
Function which reveals region of zeros (elements with no hints) after
user's guess reveals one zero element.
*/
  int imax=this->imx;
  int jmax=this->jmx;

  int di, dj;
//return if the value is already being displayed
  if(this->dsp[i][j]==1){return;}
//add element to display array
  this->dsp[i][j]=1;
//decreases the number of non-mine unrevealled elements
  this->safe--;
//do not look at nearest neighbours if element has a hint
  if(this->mfld[i][j]!=0){return;}
//find nearest neighbours and display if they have no hints
  for(di=-1; di<=1; di++){
//skip if the indices go beyond the boundary
    if((i+di<0)||(i+di>=imax)){continue;}
//same for j index
    for(dj=-1; dj<=1; dj++){
//skip if the indices go beyond the boundary
      if((j+dj<0)||(j+dj>=jmax)){continue;}
//call function recursively to find next nearest neighbour display element with no hints
      reveal_zeros(i+di,j+dj);
    }
//
  }
//EOF
}

