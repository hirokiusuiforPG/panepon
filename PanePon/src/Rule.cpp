#include "Rule.h"

CRule::CRule()
{
}

CRule::~CRule()
{
}

void CRule::Initialize() {
	TimeKeeper.Initialize(120);
}

void CRule::Update() {
	TimeKeeper.Update();
}

void CRule::Draw() {
	TimeKeeper.Draw();
}

void CRule::Finalize() {

}