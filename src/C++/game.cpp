//define what variables and methods are in this class.
#include "game.h"

#include <iostream>
#include <cstdlib> //contains the rand functions
#include <ctime> //contians time functions
#include <vector> //c++ vectors as alternative to arrays.


Minesweeper::Minesweeper() {
  
  _mfld.resize(_imx,std::vector<int>(_jmx,0)); //initiates the mine field to zero
  _dsp.resize(_imx,std::vector<int>(_jmx,0)); //initiates the displayed mine field to zero
  mine_init();//initialise the game
}

void Minesweeper::set_int(const int imx, const int jmx, const int N) {
//set the variables for the grid size and number of mines
  _imx=imx;
  _jmx=jmx;
  _N=N;
  _mfld.resize(_imx,std::vector<int>(_jmx,0)); //initiates the mine field to zero
  _dsp.resize(_imx,std::vector<int>(_jmx,0)); //initiates the displayed mine field to zero
//EOF
}

void Minesweeper::mine_init(){
//initialises the game
  zero(_mfld); //initiates the mine field to zero
  zero(_dsp); //initiates the displayed mine field to zero
  _safe=_imx*_jmx-_N;
  _again=false;
  _win=false;
  _unravel=false;
//initialise the minefield
  init_minefield();
// display the covered mine field
//  disp_minefield();
//EOF
}

int Minesweeper::display_el(const int i, const int j) {
/*
return the dsp matrix element (i,j)
*/
  return _dsp[i][j];
//EOF
}

int Minesweeper::minefield_el(const int i, const int j) {
/*
return the mfld matrix element (i,j)
*/
  return _mfld[i][j];
//EOF
}

int Minesweeper::get_play() {
/*
return _play
*/
  return _play;
//EOF
}

int Minesweeper::get_imx() {
/*
return _imx
*/
  return _imx;
//EOF
}

int Minesweeper::get_jmx() {
/*
return _imx
*/
  return _jmx;
//EOF
}

int Minesweeper::get_N() {
/*
return _imx
*/
  return _N;
//EOF
}

void Minesweeper::set_play(const int play) {
/*
return _play
*/
  _play=play;
//EOF
}

int Minesweeper::get_safe() {
/*
return _safe
*/
  return _safe;
//EOF
}

bool Minesweeper::get_again() {
/*
return _safe
*/
  return _again;
//EOF
}

void Minesweeper::set_win(const bool win) {
/*
set _win
*/
  _win=win;
//EOF
}


void Minesweeper::win_loss(){
//win/lose end game message
  _unravel=true;
  disp_minefield();
  if(_win){
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
  std::cin >> _play;
  if(_play==1){_again=true;}
//EOF
}

void Minesweeper::update(const int i, const int j){
//updates displayed mine field

//if element is zero, reveal all nearest neighbour zero elements (execpt for diagonals)    
  if(_dsp[i][j]==0) {
    reveal_zeros(i,j);
//otherwise reveal element.
  }
  else {
    _dsp[i][j] = 1;
//decrease number of safe elements left to guess
    _safe--;
  }
//EOF
}

void Minesweeper::hints() {
/*
This function generates the numbered hints of the nearest neighbour mines
As per C++, the reference of the mine field vector has been passed through,
*/
//determine the hints
  for (int i=0; i<_imx; i++){
    for (int j=0; j<_jmx; j++){
//skip if that element is a mine. Note that we are going through the address
      if(_mfld[i][j]==9) {continue;}
//loop around nearest neighbours to look for mines
      for(int di=-1; di<=1; di++){
        for(int dj=-1; dj<=1; dj++){
//skip (i,j) coordinate
          if((di==0)&&(dj==0)){continue;}
          else if((i+di<0)||(i+di>=_imx)){continue;}
          else if((j+dj<0)||(j+dj>=_jmx)){continue;}
//add 1 if a mine is present in the nearest neighbour array element
          if(_mfld[i+di][j+dj]==9) {_mfld[i][j]+=1;}
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

// initialise the random number seed
  std::srand(std::time(nullptr));
// place mines in field
  for (int n=0; n<_N; n++) {
// randomly generate coordinates          
    int mi = (int) _imx * static_cast<float>(std::rand()) / RAND_MAX;
    int mj = (int) _jmx * static_cast<float>(std::rand()) / RAND_MAX;
// place mine at coordinates in field array. Note that "9" represents a mine
    if (_mfld[mi][mj]!=9) {
      _mfld[mi][mj]=9;
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

  std::cout << std::endl;
//loop over the array
  for (int i=0; i<_imx; i++){
    for (int j=0; j<_imx; j++){
//print y coordinates       
      if(j==0){std::cout << _imx-1-i << "  ";}
//print masked or revealed element or mine position if the game was lost 
//reveal mine position
      if(_unravel){
        if(_mfld[i][j]==9){std::cout << "x ";}
        else{std::cout << _mfld[i][j] << " ";}
      }
//display revealed non-mine element
      else if(_dsp[i][j]==1){
        std::cout << _mfld[i][j] << " ";
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
  for (int i=0; i<_imx; i++){
    std::cout << i << " ";
  }
  std::cout << std::endl;
//EOF
}

int Minesweeper::user_input(int &i, int &j) {
/*
This function manages the user inputs.
*/

//user input
  std::cout << "Please input your integer guess coordinates" << std::endl;
  std::cout << "(x, y) coordiates in that order: ";
  std::cin >> i >> j;
  std::cout << std::endl;
//due to the display, the input row index will be imax - *i
  j=_jmx-1-j;
//outputs warning and returns "flag" for main code to deal with this
  if((i>_imx)||(i<0)||(j>_jmx)||(j<0)){
    std::cout << "Your (x, y) input coordinates are not within the following bounds:" << std::endl;
    std::cout << "0 <= x <= " << _imx-1 <<" and 0 <= y <= " << _jmx-1 << "." << std::endl;
    std::cout << "Please enter new coordinates." << std::endl;
    return 1;
  }
// i and j positions flips as i refers to x coordinate (column) and j is y (row).
  else if(_dsp[j][i]==1){
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

void Minesweeper::reveal_zeros(const int i, const int j){
/*
Function which reveals region of zeros (elements with no hints) after
user's guess reveals one zero element.
*/

//return if the value is already being displayed
  if(_dsp[i][j]==1){return;}
//add element to display array
  _dsp[i][j]=1;
//decreases the number of non-mine unrevealled elements
  _safe--;
//do not look at nearest neighbours if element has a hint
  if(_mfld[i][j]!=0){return;}
//find nearest neighbours and display if they have no hints
  for(int di=-1; di<=1; di++){
//skip if the indices go beyond the boundary
    if((i+di<0)||(i+di>=_imx)){continue;}
//same for j index
    for(int dj=-1; dj<=1; dj++){
//skip if the indices go beyond the boundary
      if((j+dj<0)||(j+dj>=_jmx)){continue;}
//call function recursively to find next nearest neighbour display element with no hints
      reveal_zeros(i+di,j+dj);
    }
//
  }
//EOF
}

