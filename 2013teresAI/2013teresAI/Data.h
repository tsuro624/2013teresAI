#pragma once

#include "DxLib.h"
#include <string.h>
#include <iostream>
#include <math.h>
using namespace std;

#define AI_NUM 3
#define TAGGER_NUM 2
#define ROUND_MAX 100
#define TIME_LIMIT 20
//ステージの規模
#define WIDTH 32
#define HEIGHT 24
//1マスの大きさ
#define BOX (640/WIDTH)
//AIの視界#
#define VISIBLE 10
#define CENTER VISIBLE
//AIの移動速度
#define AI_SPEED 4
//AIの宝を持った時の速度
#define AI_TAKARA_SPEED 2
//鬼の移動速度
#define TAGGER_SPEED 3
typedef enum{
	OPENING,
	SETTING,
	RUNNING,
	ENDING,
} Mode;

typedef enum{
	N,
	E,
	S,
	W,
	STOP,
} Action;

typedef struct{
	char name[100];//名前
	int Graph;//AIの画像
	Action (*moveFunc)(int view[2*VISIBLE+1][2*VISIBLE+1]);		// 行動を返す関数
	int x;//座標x
	int y;//座標y
	int s_x;//ドットレベルの座標(滑らかな動き）
	int s_y;//ドットレベルの座標(滑らかな動き）
	int step;//何歩移動したか
	Action act;//AIの行動
	int life;//
	int view[2*VISIBLE+1][2*VISIBLE+1];//
	int entry;
	int takara_flag;
} AI_T;

typedef struct{
	char name[100];//名前
	int Graph;
	Action (*moveFunc)(int tagger_x , int tagger_y,int Stage[WIDTH][HEIGHT]);		// 行動を返す関数
	int x;
	int y;
	int s_x;
	int s_y;
	int step;
	Action act;
} Tagger;

typedef struct{
	int x;
	int y;
	int drop;
}Takara;

#define STACK_MAX 100
typedef struct{
	Action a[STACK_MAX];
	unsigned int count;
}stack;

void push(stack *s, Action dir);
Action pop(stack *s);




int intro(AI_T *ai);
void make_Stage(int Stage[WIDTH][HEIGHT],Takara takara);
int init_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT]);
void init_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
void draw(int stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger,Takara takara);
Action next_Ai(int view[2*VISIBLE+1][2*VISIBLE+1]);
Action next_Tagger(Tagger tagger,int Stage[WIDTH][HEIGHT],AI_T ai[]);//toshi:引数AI_T ai[]追加
void update_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT],Takara *takara);
void update_Tagger(Tagger *tagger,int Stage[WIDTH][HEIGHT],int speed);
void setview_Ai(AI_T *ai,int Stage[WIDTH][HEIGHT]);
int death_Ai(AI_T ai,Tagger tagger);
void result(AI_T ai[],int death[]);
void update_stage(int Stage[WIDTH][HEIGHT],AI_T ai[],Tagger tagger,Takara takara);
int ranking(AI_T ai[],int deth[]);//7/23 tao31 追加