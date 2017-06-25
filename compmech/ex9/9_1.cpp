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
    double alpha;
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
// alphaに関する微分方程式
double f3(double theta, double omega, ModelInfo model){
	return (-(omega*model.gravity/model.length)*cos(theta));
}

// 状態量の表示
void PrintState(State state)
{
    printf("%5.3f    \t%6.4f    \t%6.4f  \t%6.4f\n", state.time, state.theta, state.omega, state.alpha);
}

int main(void)
{

    SimCondition sim_condition = {0.0, 5.0, 0.001, 1000000};
    ModelInfo model = {0.50, 9.81};
    InitState init_state = {0.57, 0.0};
    State state = {sim_condition.StartTime, init_state.theta, init_state.omega,0.0};
    int i = 0;
    double k1_theta,k1_omega,k2_theta,k2_omega,k3_theta,k3_omega,k4_theta,k4_omega,k1_alpha,k2_alpha,k3_alpha,k4_alpha;
    // 表示画面の初期化
    printf("Time[s] \tTheta[rad]\tOmega[rad/s]\tAlpha[rad/s^2]\n");

    while (state.time <= sim_condition.EndTime && i < sim_condition.MaxIteration)
    {
        // 表示データの間引き
        if (i % 1000 == 0)PrintState(state);

        k1_theta = f1(state.omega);
        k1_omega = f2(state.theta, model);
	    k1_alpha = f3(state.theta,state.omega,model);

        k2_theta = f1(state.omega+0.5*k1_omega*sim_condition.TimeStep);
        k2_omega = f2(state.theta+0.5*k1_theta*sim_condition.TimeStep, model);
		k2_alpha = f3(state.theta+0.5*k1_theta*sim_condition.TimeStep, state.omega + 0.5*k1_omega*sim_condition.TimeStep, model);

        k3_theta = f1(state.omega+0.5*k2_omega*sim_condition.TimeStep);
        k3_omega = f2(state.theta+0.5*k2_theta*sim_condition.TimeStep, model);
		k3_alpha = f3(state.theta+0.5*k2_theta*sim_condition.TimeStep, state.omega + 0.5*k2_omega*sim_condition.TimeStep, model);

        k4_theta = f1(state.omega+k3_omega*sim_condition.TimeStep);
        k4_omega = f2(state.theta+k3_theta*sim_condition.TimeStep, model);
		k4_alpha = f3(state.theta+k3_theta*sim_condition.TimeStep, state.omega + k3_omega*sim_condition.TimeStep, model);

        // 4次のRunge-Kutta法
        double k_theta = (k1_theta + 2*k2_theta + 2*k3_theta + k4_theta) /6.0;
        double k_omega = (k1_omega + 2*k2_omega + 2*k3_omega + k4_omega) /6.0;
		double k_alpha = (k1_alpha + 2*k2_alpha + 2*k3_alpha + k4_alpha)/6.0;

        state.theta += k_theta * sim_condition.TimeStep;
        state.omega += k_omega * sim_condition.TimeStep;
		state.alpha += k_alpha * sim_condition.TimeStep;

        state.time += sim_condition.TimeStep;
        i++;
    }

    // 終了時刻の状態を表示
    PrintState(state);

    return 0;
}