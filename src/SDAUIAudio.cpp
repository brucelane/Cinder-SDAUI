#include "SDAUIAudio.h"

using namespace SophiaDigitalArt;

SDAUIAudio::SDAUIAudio(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIAudio::~SDAUIAudio() {

}

void SDAUIAudio::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);
	sprintf(buf, "%s##inpt", mSDASession->getInputTextureName(0).c_str());
	ImGui::Begin(buf);
	{
		ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth*2);
		ImGui::Text("Position %d", mSDASession->getPosition(0));

		static int iFreq0 = mSDASession->getFreqIndex(0);
		sprintf(buf, "f0 %4.2f##f0", mSDASession->getFreq(0));
		if (ImGui::SliderInt(buf, &iFreq0, 0, mSDASession->getWindowSize()))
		{
			mSDASession->setFreqIndex(0, iFreq0);
		}
		static int iFreq1 = mSDASession->getFreqIndex(1);
		sprintf(buf, "f1 %4.2f##f1", mSDASession->getFreq(1));
		if (ImGui::SliderInt(buf, &iFreq1, 0, mSDASession->getWindowSize()))
		{
			mSDASession->setFreqIndex(1, iFreq1);
		} 

		static int iFreq2 = mSDASession->getFreqIndex(2);
		sprintf(buf, "f2 %4.2f##f2", mSDASession->getFreq(2));
		if (ImGui::SliderInt(buf, &iFreq2, 0, mSDASession->getWindowSize()))
		{
			mSDASession->setFreqIndex(2, iFreq2);
		}

		static int iFreq3 = mSDASession->getFreqIndex(3);
		sprintf(buf, "f3 %4.2f##f3", mSDASession->getFreq(3));
		if (ImGui::SliderInt(buf, &iFreq3, 0, mSDASession->getWindowSize()))
		{
			mSDASession->setFreqIndex(3, iFreq3);
		}

		(mSDASession->getFreqWSSend()) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4.0f, 0.8f, 0.8f));
		if (ImGui::Button("Send WS Freqs")) {
			mSDASession->toggleFreqWSSend();
		}
		ImGui::PopStyleColor(3);
		
		ImGui::PopItemWidth();
	}
	ImGui::End();

}
