#include "SDAUITempo.h"

using namespace SophiaDigitalArt;

SDAUITempo::SDAUITempo(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUITempo::~SDAUITempo() {
}

void SDAUITempo::Run(const char* title) {


	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH * 1.3), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);

	ImGui::Begin("todo");
	{
		
	}
	ImGui::End();


}
