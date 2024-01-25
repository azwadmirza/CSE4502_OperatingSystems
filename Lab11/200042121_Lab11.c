#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<string.h>

#define N 5
#define MAX_SIZE 1000

int arrival[N] = {3, 0, 1, 4, 5};
int burst[N] = {10, 1, 2, 7, 5};
int start[N], finish[N];
int priority[N] = {3, 1, 3, 4, 2};
int arrived[N],visited[N];
int current_process[MAX_SIZE];
int remaining_time[N];
const int quantum=4;

int min(int num1,int num2){
    if(num1<num2){
        return num1;
    }
    return num2;
}

void premptivesjf(int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst[i];
    }
    int queue_pointer=0;
    for (int current_time = 0; current_time < total_time; current_time++) {
        for (int j = 0; j < n; j++) {
            if (arrival[j] <= current_time && !arrived[j]) {
                arrived[j] = 1;
                remaining_time[j] = burst[j];
            }
        }

        int min_remaining_time = INT_MAX;
        int min_index = -1;
        for (int j = 0; j < n; j++) {
            if (remaining_time[j] < min_remaining_time && remaining_time[j] > 0) {
                min_remaining_time = remaining_time[j];
                min_index = j;
            }
        }

        if (min_index != -1) {
            if (start[min_index] == -1) {
                start[min_index] = current_time;
            }
            remaining_time[min_index]--;
            if (remaining_time[min_index] == 0) {
                finish[min_index] = current_time + 1;
            }
            if(current_process[queue_pointer]!=min_index+1){
                current_process[queue_pointer+1]=min_index+1;
                queue_pointer++;
            }
            else{
                current_process[queue_pointer]=min_index+1;
            }
        }
        else{
            break;
        }
    }
}

void nonpremptive_sjf(int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst[i];
    }

    int current_time = 0;
    int process_pointer=0;
    while (current_time < total_time) {
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= current_time && !arrived[i]) {
                arrived[i] = 1;
            }
        }

        int min_burst = INT_MAX;
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (arrived[i] && !visited[i] && burst[i] < min_burst) {
                min_burst = burst[i];
                min_index = i;
            }
        }

        if (min_index != -1) {
            current_process[process_pointer] = min_index + 1;
            process_pointer++;
            start[min_index] = current_time;
            current_time += burst[min_index];
            finish[min_index] = current_time;
            visited[min_index] = 1;
        } else {
            break;
        }
    }
}

void premptive_priority(int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst[i];
    }
    int queue_pointer=0;
    for (int current_time = 0; current_time <= total_time; current_time++) {
        for (int j = 0; j < n; j++) {
            if (arrival[j] <= current_time && !arrived[j]) {
                arrived[j] = 1;
                remaining_time[j] = burst[j];
            }
        }
        int max_priority = INT_MAX;
        int max_index = -1;
        for (int i = 0; i < n; i++) {
            if (arrived[i] && !visited[i] && priority[i] < max_priority) {
                max_priority = priority[i];
                max_index = i;
            }
        }

        if (max_index != -1) {
            if (start[max_index] == -1) {
                start[max_index] = current_time;
            }
            remaining_time[max_index]--;
            if (remaining_time[max_index] == 0) {
                visited[max_index]=1;
                finish[max_index] = current_time + 1;
                priority[max_index]=-1;
            }
            if(current_process[queue_pointer]!=max_index+1){
                current_process[queue_pointer+1]=max_index+1;
                queue_pointer++;
            }
            else{
                current_process[queue_pointer]=max_index+1;
            }
        }
        else{
            break;
        }
    }
}

void nonpremptive_priority(int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst[i];
    }

    int current_time = 0,process_pointer=0;
    while (current_time < total_time) {
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= current_time && !arrived[i]) {
                arrived[i] = 1;
            }
        }

        int max_priority = INT_MAX;
        int max_index = -1;
        for (int i = 0; i < n; i++) {
            if (arrived[i] && !visited[i] && priority[i] < max_priority) {
                max_priority = priority[i];
                max_index = i;
            }
        }
        if (max_index != -1) {
            current_process[process_pointer] = max_index + 1;
            process_pointer++;
            start[max_index] = current_time;
            visited[max_index]=1;
            current_time += burst[max_index];
            finish[max_index] = current_time;
            priority[max_index]=-1;
        }
        else{
            break;
        }
    }
}



void round_robin(int n) {
    int total_time = 0;
    for (int i = 0; i < n; i++) {
        total_time += burst[i];
    }

    int current_time = 0,process_pointer=0;
    int current_process_ix=0;
    while (current_time < total_time) {
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= current_time && !arrived[i]) {
                arrived[i] = 1;
                remaining_time[i] = burst[i];
            }
        }
        int i;
        for (i = 0; i < n; i++) {
            if (arrived[i] && !visited[i] && remaining_time[i] > 0) {
                if(i!=n-1){
                    visited[i] = 1;
                }
                else{
                    memset(visited,0,sizeof(visited));
                }
                current_process[process_pointer] = i + 1;
                process_pointer++;
                if(start[i]==-1){
                    start[i]=current_time;
                }
                current_time += min(remaining_time[i],quantum);
                remaining_time[i] -= min(remaining_time[i],quantum);
                if(remaining_time[i]==0){
                    finish[i]=current_time;
                }
                break;
            }
        }
        if(i==n){
            break;
        }
    }


}

void nonpremptive_sjf_solve(){
    int n = N;
    for (int i = 0; i < N; i++) {
        start[i] = -1;
        finish[i] = 0;
        arrived[i] = 0;
        visited[i] = 0;
        current_process[i] = 0;
        remaining_time[i]=INT_MAX;
    }

    memset(current_process,-1,sizeof(current_process));
    nonpremptive_sjf(n);
    int i;
    for (i = 0;; i++) {
        if (current_process[i+1]==-1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);

    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < N; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start[i]);
        printf("Finish Time: %d\n", finish[i]);
        printf("Waiting Time: %d\n", finish[i] - arrival[i] - burst[i]);
        printf("Response Time: %d\n", start[i] - arrival[i]);

        waiting_times += finish[i] - arrival[i] - burst[i];
        response_times += start[i] - arrival[i];
    }

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / N);
    printf("Average Response Time: %.2lf\n", (double)response_times / N);
}


void premptive_priority_solve(){
    int n = N;
    for (int i = 0; i < N; i++) {
        start[i] = -1;
        finish[i] = 0;
        arrived[i] = 0;
        current_process[i] = 0;
        visited[i]=0;
        remaining_time[i]=INT_MAX;
    }
    memset(current_process,-1,sizeof(current_process));
    premptive_priority(n);
    int i;
    for (i = 1;; i++) {
        if (current_process[i+1]==-1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);

    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < N; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start[i]);
        printf("Finish Time: %d\n", finish[i]);
        printf("Waiting Time: %d\n", finish[i] - arrival[i] - burst[i]);
        printf("Response Time: %d\n", start[i] - arrival[i]);

        waiting_times += finish[i] - arrival[i] - burst[i];
        response_times += start[i] - arrival[i];
    }

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / N);
    printf("Average Response Time: %.2lf\n", (double)response_times / N);
}

void non_premptive_priority_solve(){
    int n = N;
    priority[0]=3;
    priority[1]=1;
    priority[2]=3;
    priority[3]=4;
    priority[4]=2;
    for (int i = 0; i < N; i++) {
        start[i] = -1;
        finish[i] = 0;
        arrived[i] = 0;
        visited[i]=0;
        current_process[i] = 0;
        remaining_time[i]=INT_MAX;
    }

    memset(current_process,-1,sizeof(current_process));
    nonpremptive_priority(n);
    int i;
    for (i = 0;; i++) {
        if (current_process[i+1]==-1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);

    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < N; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start[i]);
        printf("Finish Time: %d\n", finish[i]);
        printf("Waiting Time: %d\n", finish[i] - arrival[i] - burst[i]);
        printf("Response Time: %d\n", start[i] - arrival[i]);

        waiting_times += finish[i] - arrival[i] - burst[i];
        response_times += start[i] - arrival[i];
    }

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / N);
    printf("Average Response Time: %.2lf\n", (double)response_times / N);
}


void round_robin_solve(){
    int n = N;
    for (int i = 0; i < N; i++) {
        start[i] = -1;
        finish[i] = 0;
        arrived[i] = 0;
        visited[i]= 0;
        current_process[i] = 0;
    }

    memset(current_process,-1,sizeof(current_process));
    round_robin(n);
    int i;
    for (i = 0;; i++) {
        if (current_process[i+1]==-1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);

    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < N; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start[i]);
        printf("Finish Time: %d\n", finish[i]);
        printf("Waiting Time: %d\n", finish[i] - arrival[i] - burst[i]);
        printf("Response Time: %d\n", start[i] - arrival[i]);

        waiting_times += finish[i] - arrival[i] - burst[i];
        response_times += start[i] - arrival[i];
    }

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / N);
    printf("Average Response Time: %.2lf\n", (double)response_times / N);
}

void premptive_sjf_solve(){
    int n = N;
    for (int i = 0; i < N; i++) {
        start[i] = -1;
        finish[i] = 0;
        visited[i]=0;
        arrived[i] = 0;
        current_process[i] = 0;
        remaining_time[i]=INT_MAX;
    }
    memset(current_process,-1,sizeof(current_process));
    premptivesjf(n);
    int i;
    for (i = 1;; i++) {
        if (current_process[i+1]==-1) {
            break;
        }
        printf("P%d->", current_process[i]);
    }
    printf("P%d\n", current_process[i]);

    int waiting_times = 0;
    int response_times = 0;

    for (int i = 0; i < N; i++) {
        printf("P%d:\n", i + 1);
        printf("Start Time: %d\n", start[i]);
        printf("Finish Time: %d\n", finish[i]);
        printf("Waiting Time: %d\n", finish[i] - arrival[i] - burst[i]);
        printf("Response Time: %d\n", start[i] - arrival[i]);

        waiting_times += finish[i] - arrival[i] - burst[i];
        response_times += start[i] - arrival[i];
    }

    printf("Average Waiting Time: %.2lf\n", (double)waiting_times / N);
    printf("Average Response Time: %.2lf\n", (double)response_times / N);
}


int main() {
    printf("Premptive SJF:\n");
    premptive_sjf_solve();
    printf("\n\n");
    printf("Non-Premptive SJF:\n");
    nonpremptive_sjf_solve();
    printf("\n\n");
    printf("Premptive Priority:\n");
    premptive_priority_solve();
    printf("\n\n");
    printf("Non-Premptive Priority:\n");
    non_premptive_priority_solve();
    printf("\n\n");
    printf("Round Robin(Quantum=4):\n");
    round_robin_solve();
    printf("\n\n");
}
