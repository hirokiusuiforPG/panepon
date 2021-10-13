#pragma once

#include "DxLib.h"
#include "Singleton.h"

class CKey : public CSingleton<CKey>
{
	int m_Key[256];
public:
	CKey();
	void Update();
	int GetKey(int KeyCode);
};