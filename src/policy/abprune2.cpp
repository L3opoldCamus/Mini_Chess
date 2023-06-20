#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./abprune2.hpp"

// int count2;

/**
 * @brief Use Minimax to choose next move
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AlphaBetaPrune2::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->ordered_legal_actions;
    auto choose = actions.begin();
    int minval = 100000000;
    int maxval = -100000000;
    bool flag = depth%2;
    for (auto it = choose; it!=actions.end(); it++){
        int tem = AlphaBetaPrune2::alphabeta(state->next_state((*it).second),depth,flag,-100000000,100000000);
        if (flag){
            if (maxval < tem){
                choose = it;
                maxval = tem;
            }
        }
        else {
            if (minval>tem){
                choose = it;
                minval=tem;
            } 
        }
    }
    // std::cout<<"Step Count: "<<count2<<"\n";
    return (*choose).second;
}

int AlphaBetaPrune2::alphabeta(State *state, int depth, bool myself,int alpha,int beta){//myself if state is player take action
    // count2++;
    if (!depth) return state->evaluate();
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->ordered_legal_actions;

    if (myself){
        int minval=100000000;    
        for (auto it = actions.begin(); it!=actions.end(); it++){
            int tem = alphabeta(state->next_state((*it).second),depth-1,false,alpha,beta);
            minval = std::min(minval,tem);
            beta = std::min(beta,minval);
            if (beta <= alpha) break;
        }
        return minval;
    }
    else {
        int maxval=-100000000;
        for (auto it = actions.begin(); it!=actions.end(); it++){
            int tem = alphabeta(state->next_state((*it).second),depth-1,true,alpha,beta);
            maxval = std::max(maxval,tem);
            alpha = std::max(alpha,maxval);
            if (alpha >= beta) break;
        }
        return maxval;
    }
}