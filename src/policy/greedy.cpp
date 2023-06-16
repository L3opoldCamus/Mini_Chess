#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./greedy.hpp"


/**
 * @brief 1 step best sol
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move RandomValid::get_move(State *state, int depth){
  if(!state->legal_actions.size())//Legal action exists
    state->get_legal_actions();
  
  auto actions = state->legal_actions;
  int chosen=0;
  int minval = state->next_state(actions[0])->evaluate();
  for (int i = chosen+1; i < actions.size(); i++){
    int tem = state->next_state(actions[i])->evaluate();
    if (minval>tem){
      chosen = i;
      minval=tem;
    } 
  }
  return actions[chosen];
}