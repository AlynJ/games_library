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

    void set_int(const int imx, const int jmx, const int N);
    void mine_init();
    int display_el(const int i, const int j);
    int minefield_el(const int i, const int j);
    int get_play();
    int get_imx();
    int get_jmx();
    int get_N();
    void set_play(const int play);
    int get_safe();
    bool get_again();
    void set_win(const bool win);
    void win_loss();
    void replay();
    void update(const int i, const int j);
    void hints();
    void init_minefield();
    void disp_minefield();
    int user_input(int &i, int &j);
    void zero(std::vector<std::vector<int>> &arr);
    void reveal_zeros(const int i, const int j);

  private:
    int _imx=9;
    int _jmx=9;
    int _N=10;
// y grid length, x grid length, #mines, x input, y input
    int _play=1; 
    int _safe=_imx*_jmx-_N;
    bool _again=false;
    bool _win=false;
    std::vector<std::vector<int>> _mfld; //initiates the mine field
    std::vector<std::vector<int>> _dsp; //initiates the displayed mine field 
    //std::vector<std::vector<int>> _mfld(_imx,std::vector<int>(_jmx,0)); //initiates the mine field to zero
    //std::vector<std::vector<int>> _dsp(_imx,std::vector<int>(_jmx,0)); //initiates the displayed mine field to zero
//lose boolean
    bool _unravel=false;

};
#endif
