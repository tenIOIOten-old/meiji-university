// Euler Method
#include <stdio.h>
#include <math.h>

typedef struct
{
    double StartTime; // シミュレーションの開始時間
    double EndTime;   // シミュレーションの終了時間
    double TimeStep;  // 時間刻み幅
    int MaxIteration; // 最大繰り返し回数
} const SimCondition; // シミュレーション条件に関する構造体

typedef struct
{
    double length;  // 振り子のひもの⻑さ
    double gravity; // 振り子のひもの⻑さ
} const ModelInfo;  // 解析モデルに関する構造体

typedef struct
{

    double theta;  // 角度
    double omega;  // 角速度
} const InitState; // 初期条件

typedef struct
{

    double time;  // 時間
    double theta; // 角度
    double omega; // 角速度
} State;          // 時間変数に関する構造体

// thetaに関する微分方程式
double f1(double omega)
{
    return omega;
}

// omegaに関する微分方程式
double f2(double theta, ModelInfo model)
{
    return -model.gravity / model.length * sin(theta);
}

// 状態量の表示
void PrintState(State state)
{
    printf("%5.3f\t% 6.4f\t% 6.4f\n", state.time, state.theta, state.omega);
    41
}

int main(void)
{

    SimCondition sim_condition = {0.0, 5.0, 0.0001, 1000000};
    ModelInfo model = {0.50, 9.81};
    InitState init_state = {0.57, 0.0};
    State state = {sim_condition.StartTime, init_state.theta, init_state.omega};
    int i = 0;
    // 表示画面の初期化
    printf("Time\tTheta\tOmega\n");

    while (state.time <= sim_condition.EndTime && i < sim_condition.MaxIteration)
    {
        // 表示データの間引き
        if (i % 1000 == 0)
            PrintState;
        // Euler法
        double k1 = f1(state.omega);
        double l1 = f2(state.theta, model);
        state.theta += k1 * sim_condition.TimeStep;
        state.omega += l1 * sim_condition.TimeStep;

        state.time += sim_condition.TimeStep;
        i++;
    }

    // 終了時刻の状態を表示
    PrintState;

    return 0;
}
