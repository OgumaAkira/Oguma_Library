//*****************************************************************************
//
// メイン処理 [main.h]
// Author : 小熊 朗
//
//*****************************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <windows.h>
#include <time.h>
#include "d3dx9.h"
#include "xaudio2.h" //サウンド処理で必要
#include <windows.h>
#define DIRECTINPUT_VERSION (0x0800) //警告対処用 dinput.hの直前に書く
#include "dinput.h"

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"										//ウインドウのクラス名
#define WINDOW_NAME		"DISK BREAK"									//ウインドウのキャプション名
#define SCREEN_WIDTH	(1910)											//ウィンドウの横
#define SCREEN_HEIGHT	(1060)											//ウィンドウの縦
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define NUM_VERTEX (4)													//頂点数
#define NUM_POLYGON (2)													//ポリゴン数
#define PRIORITY_MAX (15)												//優先順位
#define NUM_KEY_MAX (256)												//キーボードの最大数
#define NUM_MOUSE_MAX (4)												//マウスキーの最大数
#define BULLET_SIZEX (300.0f)											//弾Xの長さ
#define BULLET_SIZEY (300.0f)											//弾Yの長さ

//テクスチャマクロ
#define MAX_TEXTURE (516)												//テクスチャの最大枚数
#define PLAYER_TEXTURE ("data/TEXTURE/ターゲットマーカー.png")			//プレイヤーのTEXTURE
#define BULLET_TEXTURE ("data/TEXTURE/bullet000.png")					//弾のTEXTURE
#define BULLETUI_TEXTURE ("data/TEXTURE/弾丸(黄色).png")				//残弾のTEXTURE
#define BG_SPACE01_TEXTURE ("data/TEXTURE/bg100.png")					//宇宙1のTEXTURE
#define BG_SPACE02_TEXTURE ("data/TEXTURE/bg101.png")					//宇宙2のTEXTURE
#define BG_SPACE03_TEXTURE ("data/TEXTURE/bg102.png")					//宇宙3のTEXTURE
#define ENEMY_TEXTURE2 ("data/TEXTURE/敵　UFO１.png")					//敵のTEXTURE
#define TITELBUTTON_TEXTURE ("data/TEXTURE/SHOOT THE STARTBUTTON.png")	//Titleボタンのテクスチャ
#define RESULTBUTTON_TEXTURE ("data/TEXTURE/RETURN TO TITLE.png")		//Resultボタンのテクスチャ
#define GAMETITLE_TEXTURE ("data/TEXTURE/ゲームタイトル.png")			//タイトルテクスチャ
#define TUTORIAL_TEXTURE ("data/TEXTURE/チュートリアル.png")			//チュートリアルのテクスチャ
#define HISCOREUI_TEXTURE ("data/TEXTURE/HISCORE.png")					//ハイスコアのテクスチャ
#define MYSCOREUI_TEXTURE ("data/TEXTURE/YOURSCORE.png")				//ハイスコアのテクスチャ
#define SPEEDUP_TEXTURE ("data/TEXTURE/SPEEDUP!.png")					//スピードアップのテクスチャ
#define NUMBER_TEXTURE ("data/TEXTURE/number000.png")					//ナンバーのテクスチャ
//プレイヤーマクロ
#define PLAYER_SIZEX (150.0f)//プレイヤーのXの長さ
#define PLAYER_SIZEY (150.0f)//プレイヤーのYの長さ

//ボタンマクロ
#define BUTTON_POSX (940.0f)//ボタンのXの長さ
#define BUTTON_POSY (800.0f)//ボタンのYの長さ

//エネミーマクロ
#define ENEMY_SIZEX (250.0f)//敵のXの長さ
#define ENEMY_SIZEY (150.0f)//敵のYの長さ
#define ENEMY_POSX (150.0f)//敵のXの長さ
#define ENEMY_POSY (150.0f)//敵のYの長さ

//スコアナンバーマクロ
#define MAX_SCORE_NUMBER (10)		//スコアナンバーの最大数
#define SCORE_POS_X (35)			//スコア一桁のXの位置
#define SCORE_POS_Y (70)			//スコア一桁のYの位置
#define SCORE_SIZE_X (35)			//スコア一桁のXの大きさ
#define SCORE_SIZE_Y (70)			//スコア一桁のYの大きさ

//スコアナンバーマクロ
#define MAX_COMBO_NUMBER (2)		//スコアナンバーの最大数
#define COMBO_POS_X (35)			//スコア一桁のXの位置
#define COMBO_POS_Y (140)			//スコア一桁のYの位置
#define COMBO_SIZE_X (35)			//スコア一桁のXの大きさ
#define COMBO_SIZE_Y (70)			//スコア一桁のYの大きさ

//スピードアップのマクロ
#define SPEEDUP_POS_X (SCREEN_WIDTH / 2)			//スコア一桁のXの位置
#define SPEEDUP_POS_Y (SCREEN_HEIGHT / 2.5)			//スコア一桁のYの位置
#define SPEEDUP_SIZE_X (SCREEN_WIDTH / 2.5)			//スコア一桁のXの大きさ
#define SPEEDUP_SIZE_Y (1000.0f)					//スコア一桁のYの大きさ

//ウィンドウ用
#define WindowVersion (1)

//フルスクリーン用
#define FullScreenVersion (0)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標1
	float rhw;				//座標変換用係数(1.0で固定）
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ
}VERTEX_2D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int GetFPS(void);
#endif