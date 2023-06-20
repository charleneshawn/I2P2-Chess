#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move minmax::get_move(State *state, int depth){
  if(!state->legal_actions.size())//biar kek dia cek dulu klo empty hrs cari legal action spy ada yg dikerjain, disimpen semua legal actionnya di dlm array
    state->get_legal_actions();
  
  int bestVal;
  if (state->player==0){
    bestVal=-1000000;
  }else{
    bestVal=1000000;
  }
  int alpha=-1000000;
  int beta=1000000;
  Move bestMove;
  State* nextState;
  for (auto action:state->legal_actions){
    nextState=state->next_state(action);//next_state udh dibikinin
    int value=alphabeta_minimax(nextState, depth-1,alpha,beta,state->player);
    if (state->player==0 && value>bestVal){
      bestVal=value;
      bestMove=action;
    }else if (state->player==1 && value<bestVal){
      bestVal=value;
      bestMove=action;
    }
  }
  return bestMove;
}

int minmax::alphabeta_minimax(State* state, int depth, int alpha, int beta,bool maximizing){
  if(state->legal_actions.size()==0){
    state->get_legal_actions();
  }
  if (depth==0||state->legal_actions.empty()){
    return state->evaluate();
  }

  if (maximizing){
    int bestVal=-1000000;
    State* nextState;
    for (auto action: state->legal_actions){
      nextState= state->next_state(action);
      bestVal = std::max(bestVal,alphabeta_minimax(nextState, depth-1,alpha,beta,false));
      alpha = std::max(alpha, bestVal);
      if (beta <= alpha){
        break;
      }
    }
    return bestVal;
  }else{
    int bestVal = 1000000;
    State* nextState;
    for (auto action: state->legal_actions){
      nextState=state->next_state(action);
      bestVal=std::min(bestVal, alphabeta_minimax(nextState,depth-1, alpha,beta,true));
      delete nextState;
      beta = std::min(beta, bestVal);
      if (beta <= alpha){
        break;
      }
    }
    return bestVal;
  }
}