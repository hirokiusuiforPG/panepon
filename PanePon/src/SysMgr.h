#pragma once

#include <DxLib.h>
#include "define.h"
#include "SceneMgr.h"
#include "key.h"

class CSysMgr{
	CSceneMgr SceneMgr;

	int fps_count, count0t;
	int f[FLAME];
	double ave;
	int term, i, gnt;
	int t;

	char title[32];

	void fps_wait();	//FPS関係は龍神録のものをそのまま使用
	void draw_fps();
public:
	CSysMgr();
	~CSysMgr();

	void MainLoop();
};