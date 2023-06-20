#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./minimax.hpp"

// int count1;

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
    int maxval = -100000000;//Add
    bool flag = depth%2;//Add
    for (unsigned long i = 0; i < actions.size(); i++){
        int tem = Minimax::minimax(state->next_state(actions[i]),depth,flag);//Add
        if (flag){//Add
            if (maxval < tem){//
                chosen = i;//
                maxval = tem;//
            }//
        }//
        else {
            if (minval>tem){
                chosen = i;
                minval=tem;
            } 
        }
    }
    // std::cout<<"Step Count: "<<count1<<"\n";
    return actions[chosen];
}

int Minimax::minimax(State *state, int depth, bool myself){//myself if state is player take action
    // count1++;
    if (!depth) return state->evaluate();
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;

    if (myself){
        int minval=100000000;    
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = minimax(state->next_state(actions[i]),depth-1,false);
            minval = std::min(minval,tem);
        }
        return minval;
    }
    else {
        int maxval=-100000000;
        for (unsigned long i = 0; i < actions.size(); i++){
            int tem = minimax(state->next_state(actions[i]),depth-1,true);
            maxval = std::max(maxval,tem);
        }
        return maxval;
    }
}