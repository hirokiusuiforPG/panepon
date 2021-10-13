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

	void fps_wait();	//FPSä÷åWÇÕó¥ê_ò^ÇÃÇ‡ÇÃÇÇªÇÃÇ‹Ç‹égóp
	void draw_fps();
public:
	CSysMgr();
	~CSysMgr();

	void MainLoop();
};