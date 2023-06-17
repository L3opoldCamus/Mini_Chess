#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./minimax.hpp"

int minimax(State *state, int depth, bool myself);

/**
 * @brief Use Minimax to choose next move
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;
    int chosen=0;
    int minval = 100000000;
    for (unsigned long i = 0; i < actions.size(); i++){
        int tem = minimax(state->next_state(actions[i]),depth,false);
        if (minval>tem){
            chosen = i;
            minval=tem;
        } 
    }
    // std::cout<<chosen<<"Test\n";
    return actions[chosen];
}

int minimax(State *state, int depth, bool myself){//myself if state is player take action
    if (!depth) return state->evaluate();
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;

    if (myself){
        int minval=100000000;    
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = minimax(state->next_state(actions[i]),depth-1,!myself);
            if (minval>tem) minval = tem;
        }
        return minval;
    }
    else {
        int maxval=-100000000;
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = minimax(state->next_state(actions[i]),depth-1,!myself);
            if (maxval<tem) maxval = tem;
        }
        return maxval;
    }
}