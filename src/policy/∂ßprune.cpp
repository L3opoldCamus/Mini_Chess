#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./∂ßprune.hpp"

int alphabeta(State *state, int depth, bool myself,int alpha,int beta);

/**
 * @brief Use Minimax to choose next move
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBetaPrune::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;
    int chosen=0;
    int minval = 100000000;
    int maxval = -100000000;
    bool flag = depth%2;
    for (unsigned long i = 0; i < actions.size(); i++){
        int tem = alphabeta(state->next_state(actions[i]),depth,flag,-100000000,100000000);
        if (flag){
            if (maxval < tem){
                chosen = i;
                maxval = tem;
            }
        }
        else {
            if (minval>tem){
                chosen = i;
                minval=tem;
            } 
        }
    }
    return actions[chosen];
}

int alphabeta(State *state, int depth, bool myself,int alpha,int beta){//myself if state is player take action
    if (!depth) return state->evaluate();
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;

    if (myself){
        int minval=100000000;    
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = alphabeta(state->next_state(actions[i]),depth-1,false,alpha,beta);
            minval = std::min(minval,tem);
            beta = std::min(beta,minval);
            if (beta <= alpha) break;
        }
        return minval;
    }
    else {
        int maxval=-100000000;
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = alphabeta(state->next_state(actions[i]),depth-1,true,alpha,beta);
            if (maxval<tem) maxval = tem;
            alpha = std::max(alpha,maxval);
            if (alpha >= beta) break;
        }
        return maxval;
    }
}