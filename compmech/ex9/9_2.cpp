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
    double mass;
    double gravity; // 振り子のひもの⻑さ
    double k_const;
    double damping_const;
} const ModelInfo;  // 解析モデルに関する構造体

typedef struct
{
    double x; 
    double velocity;  
    double acceleration;
} const InitState; // 初期条件

typedef struct
{
    double time;
    double x;  
    double velocity; 
    double acceleration; 
} State;          // 時間変数に関する構造体

// xに関する微分方程式
double f1(double velocity)
{
    return velocity;
}

// velocityに関する微分方程式
double f2(double x,double velocity, ModelInfo model)
{
    return ( -model.k_const*x - model.mass*model.gravity + x/fabs(x)*model.damping_const*velocity)/model.mass;
}
// accelerationに関する微分方程式
double f3(double x,double velocity, double acceleration, ModelInfo model){
    return ( -model.k_const*velocity - model.mass*model.gravity + x/fabs(x)*model.damping_const*acceleration)/model.mass;	
}

// 状態量の表示
void PrintState(State state)
{
    printf("%5.3f    \t%6.4f    \t   %6.4f  \t\t%6.4f\n", state.time, state.x, state.velocity, state.acceleration);
}

void Simulation(double c, FILE *ofp)
{

    SimCondition sim_condition = {0.0, 5.0, 0.001, 1000000};
    ModelInfo model = {2.0, 9.81, 1800, c};
    InitState init_state = {0.015, 0.0, f2(0.015, 0.0, model)};
    State state = {sim_condition.StartTime, init_state.x, init_state.velocity,init_state.acceleration};
    int i = 0;
    // 表示画面の初期化
    printf("Time[s] \tDisplacement[rad]  Velocity[rad/s]\tAcceleration[rad/s^2]\n");

    while (state.time <= sim_condition.EndTime && i < sim_condition.MaxIteration)
    {
        // 表示データの間引き
        if (i % 1000 == 0)PrintState(state);
	fprintf(ofp,"%f,%f,%f,%f\n",state.time,state.x*1000,state.velocity*1000,state.acceleration*1000);

        double k1_x = f1(state.velocity);
		double k1_v = f2(state.x,state.velocity,model);
		double k1_a = f3(state.x,state.velocity,state.acceleration,model);
		
		double k2_x = f1(state.velocity + 0.5*k1_v*sim_condition.TimeStep);
		double k2_v = f2(state.x + 0.5*k1_x*sim_condition.TimeStep,state.velocity + 0.5*k1_v*sim_condition.TimeStep, model);
		double k2_a = f3(state.x + 0.5*k1_x*sim_condition.TimeStep,state.velocity + 0.5*k1_v*sim_condition.TimeStep, state.acceleration + 0.5*k1_a*sim_condition.TimeStep, model);
		
		double k3_x = f1(state.velocity + 0.5*k2_v*sim_condition.TimeStep);
		double k3_v = f2(state.x + 0.5*k2_x*sim_condition.TimeStep,state.velocity + 0.5*k2_v*sim_condition.TimeStep, model);
		double k3_a = f3(state.x + 0.5*k2_x*sim_condition.TimeStep,state.velocity + 0.5*k2_v*sim_condition.TimeStep, state.acceleration + 0.5*k2_a*sim_condition.TimeStep, model);
		
		double k4_x = f1(state.velocity + k3_v*sim_condition.TimeStep);
		double k4_v = f2(state.x + k3_x*sim_condition.TimeStep,state.velocity + k3_v*sim_condition.TimeStep,model);
		double k4_a = f3(state.x + 0.5*k3_x*sim_condition.TimeStep,state.velocity + k3_v*sim_condition.TimeStep, state.acceleration + k3_a*sim_condition.TimeStep, model);
		
        // 4次のRunge-Kutta法
		double k_x = (k1_x + 2*k2_x + 2*k3_x + k4_x)/6.0;
		double k_v = (k1_v + 2*k2_v + 2*k3_v + k4_v)/6.0;
		double k_a = (k1_a + 2*k2_a + 2*k3_a + k4_a)/6.0;
		
		state.x += k_x*sim_condition.TimeStep;
		state.velocity += k_v*sim_condition.TimeStep;
		state.acceleration += k_a*sim_condition.TimeStep;

        state.time += sim_condition.TimeStep;
        i++;
    }

    // 終了時刻の状態を表示
    PrintState(state);

}



int main(void)
{
	FILE* ofp_10 = NULL;
	FILE* ofp_30 = NULL;
	FILE* ofp_120 = NULL;
	
	char* ofile_10 = "./output_10.csv";
	char* ofile_30 = "./output_30.csv";
	char* ofile_120 = "./output_120.csv";
	
	if( (ofp_10 = fopen(ofile_10,"wt")) == NULL ){
		fprintf(stderr, "Can't open output file %s\a\n", ofile_10);
		return 1;
	}
	if( (ofp_30 = fopen(ofile_30,"wt")) == NULL ){
		fprintf(stderr, "Can't open output file %s\a\n", ofile_30);
		return 2;
	}
	if( (ofp_120 = fopen(ofile_120,"wt")) == NULL ){
		fprintf(stderr, "Can't open output file %s\a\n", ofile_120);
		return 3;
	}
	
	printf("\nc = 10.0\n");
	Simulation(10.0,ofp_10);
	
	printf("\nc = 30.0\n");
	Simulation(30.0,ofp_30);
	
	printf("\nc = 120.0\n");
	Simulation(120.0,ofp_120);
	
	fclose(ofp_10);
	fclose(ofp_30);
	fclose(ofp_120);
	
	return 0;
}