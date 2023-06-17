#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for Minimax policy, 
 * your policy class should have get_move method
 */
class AlphaBetaPrune{
public:
  static Move get_move(State *state, int depth);
};