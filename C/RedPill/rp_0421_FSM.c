#include <stdio.h>

typedef enum { STATE_IDLE, STATE_RUN, STATE_ERROR, STATE_MAX } State_t;
typedef enum { EVT_BUTTON_PRESS, EVT_TIMEOUT, EVT_RESET, EVT_MAX } Event_t;

const char* STATE_NAMES[] = { "IDLE", "RUN", "ERROR" };
const char* EVENT_NAMES[] = { "EVT_BUTTON_PRESS", "EVT_TIMEOUT", "EVT_RESET" };

typedef struct {
    State_t nextState;
    void (*action)(void);
} Transition_t;

void act_running() { printf("   (Running... Motor spinning ⚙️)\n"); }
void act_waiting() { printf("   (Waiting... ⚠️ System Halted)\n"); }

Transition_t fsmTable[STATE_MAX][EVT_MAX] = {
    [STATE_IDLE] = {
        [EVT_BUTTON_PRESS] = {STATE_RUN, act_running}
    },
    [STATE_RUN] = {
        [EVT_TIMEOUT] = {STATE_IDLE, NULL},
        [EVT_RESET]   = {STATE_ERROR, act_waiting}
    },
    [STATE_ERROR] = {
        [EVT_RESET]   = {STATE_IDLE, NULL}
    }
};

State_t g_currentState = STATE_IDLE;

void process_event(Event_t event) {
    Transition_t trans = fsmTable[g_currentState][event];

    printf("--------------------------------------------------\n");
    printf("[TRANSITION] %s --(%s)--> %s\n", 
           STATE_NAMES[g_currentState], 
           EVENT_NAMES[event], 
           STATE_NAMES[trans.nextState]);
    printf("--------------------------------------------------\n");

    g_currentState = trans.nextState;

    if (trans.action) {
        trans.action();
    }
}

int main() {
    printf("=== Day 21: Visual FSM Implementation ===\n");
    printf("Initial State: [%s]\n\n", STATE_NAMES[g_currentState]);

    process_event(EVT_BUTTON_PRESS); // IDLE -> RUN (모터 가동)    //act_running
    process_event(EVT_TIMEOUT);      // RUN -> IDLE (복귀)
    process_event(EVT_BUTTON_PRESS); // IDLE -> RUN (재가동)       //act_running
    process_event(EVT_RESET);        // RUN -> ERROR (시스템 정지)  //act_waiting
    process_event(EVT_RESET);        // ERROR -> IDLE (초기화 복구) 

    printf("\n>> Simulation Ended.\n");
    return 0;
}