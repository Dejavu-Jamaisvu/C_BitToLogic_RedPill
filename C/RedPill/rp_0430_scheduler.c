#include <stdio.h>
#include <setjmp.h>

#define MAX_TASKS 3
jmp_buf sched_env;

int state_A = 0, state_C = 0; // 각 태스크의 내부 상태 (FSM)
int done_A = 0, done_B = 0, done_C = 0; // 각 태스크 실행 횟수

void yield() { longjmp(sched_env, 1); }
void taskA() {
    if (state_A == 0) {
        printf("[Task A] Start working... (Step 1)\n");
        state_A = 1;
    } else {
        printf("[Task A] Resumed working... (Step 2)\n");
        state_A = 0;
    }
    done_A++;
    yield();
}

void taskB() {
    printf("  [Task B] Processing Data...\n");
    done_B++;
    yield();
}

void taskC() {
    if (state_C == 0) {
        printf("    [Task C] Initialization\n");
        state_C = 1;
    } else if (state_C == 1) {
        printf("    [Task C] Calculation\n");
        state_C = 2;
    } else {
        printf("    [Task C] Finalize\n");
        state_C = 0;
    }
    done_C++;
    yield();
}

int main() {
    printf("=== Day 29: Simple Sum-Check Scheduler ===\n\n");

    int total_step_idx = 0;

    // 모든 태스크 최소 1회씩은 실행되고, 
    // 각 태스크의 내부 스탭도 완료되어 실행 횟수가 스탭의 배수일 때 탈출
    while (!(done_A >= 2 && done_A % 2 == 0 && done_B >= 1 && done_C >= 3 && done_C % 3 == 0)) {
        
        if (setjmp(sched_env) == 0) {
            int current = total_step_idx % MAX_TASKS;
            total_step_idx++;

            if (current == 0) taskA();
            else if (current == 1) taskB();
            else if (current == 2) taskC();
        }
    }

    printf("\n>> Simulation Finished.\n");
    return 0;
}