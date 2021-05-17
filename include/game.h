//define header file if not done so previously.
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <cstdlib> //contains the rand functions
#include <ctime> //contians time functions
#include <vector> //c++ vectors as alternative to arrays.

class Minesweeper
{
  public:
    Minesweeper();

    void mine_init();
    int element(int i, int j, std::vector<std::vector<int>> &arr);
    void win_loss();
    void replay();
    void update(int i, int j);
    void hints();
    void init_minefield();
    void disp_minefield();
    int user_input(int &i, int &j);
    void zero(std::vector<std::vector<int>> &arr);
    void reveal_zeros(int i, int j);
// y grid length, x grid length, #mines, x input, y input
    int imx, jmx, N, x, y, play, safe;
    bool again,win;
    std::vector<std::vector<int>> mfld; //initiates the mine field to zero
    std::vector<std::vector<int>> dsp; //initiates the displayed mine field to zero

  private:
//gaming running int, warning flage, #non-mine elements remaining    
    int flag;
//lose boolean
    bool unravel;
    //std::vector<std::vector<int>> mfld(imx,std::vector<int>(jmx,0)); //initiates the mine field to zero
    //std::vector<std::vector<int>> dsp(imx,std::vector<int>(jmx,0)); //initiates the displayed mine field to zero

};
#endif
