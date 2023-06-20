#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class minmax{
public:
  static Move get_move(State *state, int depth);
  static int alphabeta_minimax(State *state, int depth,int alpha, int beta, bool maximizing);
  /*static int myMin(int a, int b);
  static int myMax(int a, int b);*/
};