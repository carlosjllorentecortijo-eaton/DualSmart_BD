/**
 * @file Fsm.h
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the datatype definitions and functions related to the Mealy FSM implementation.
 * @version 0.1
 * @date 2023-11-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CE4FDAF6_73E2_4FB0_8523_41BCDA517BAB
#define CE4FDAF6_73E2_4FB0_8523_41BCDA517BAB

typedef struct fsm_s fsm_t;

typedef int (*fsm_input_func_t) (fsm_t*);
typedef void (*fsm_output_func_t) (fsm_t*);

/**
 * @brief Type representing each of the transitions of the FSM.
 * 
 */
typedef struct fsm_trans_s {
  int orig_state;
  fsm_input_func_t in;
  int dest_state;
  fsm_output_func_t out;
} fsm_trans_t;

/**
 * @brief Type representing the FSM.
 * 
 */
struct fsm_s {
  int current_state;
  fsm_trans_t* tt;
  void* user_data;
};

fsm_t* fsm_new (int state, fsm_trans_t* tt, void* user_data);
void fsm_init (fsm_t* this, int state, fsm_trans_t* tt, void* user_data);
void fsm_fire (fsm_t* this);
void fsm_destroy (fsm_t* this);


#endif /* CE4FDAF6_73E2_4FB0_8523_41BCDA517BAB */
