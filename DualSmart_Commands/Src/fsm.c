/**
 * @file fsm.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief Mealy state machine implementation
 * @version 0.1
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "fsm.h"
#include "mem_pool.h"

/**
 * @brief This function allocates a new FSM.
 * 
 * @param state initial state
 * @param tt transition table
 * @param user_data additional user_data
 * @return fsm_t* pointer to state machine
 */
fsm_t* fsm_new (int state, fsm_trans_t* tt, void* user_data){
  fsm_t* this = (fsm_t*) MEMPOOL_MALLOC (sizeof (fsm_t));
  fsm_init (this, state, tt, user_data);
  return this;
}

/**
 * @brief This function initializes a new FSM.
 * 
 * @param this state machine object
 * @param state initial state
 * @param tt transition table defining the machine's behavior
 * @param user_data additional user data
 */
void fsm_init (fsm_t* this, int state, fsm_trans_t* tt, void* user_data){
  this->current_state = state;
  this->tt = tt;
  this->user_data = user_data;
}

/**
 * @brief This function frees an FSM.
 * 
 * @param this state machine object to be deleted
 */
void fsm_destroy (fsm_t* this){
  MEMPOOL_FREE(this);
}

/**
 * @brief This function evaluates the possible check functions and triggers the related activation function.
 * 
 * @param this state machine object
 */
void fsm_fire (fsm_t* this){
  fsm_trans_t* t;
  for (t = this->tt; t->orig_state >= 0; ++t) {
    if ((this->current_state == t->orig_state) && t->in(this)) {
      this->current_state = t->dest_state;
      if (t->out)
        t->out(this);
      break;
    }
  }
}
