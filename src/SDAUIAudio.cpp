#include "SDAUIAudio.h"

using namespace SophiaDigitalArt;

SDAUIAudio::SDAUIAudio(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIAudio::~SDAUIAudio() {

}

void SDAUIAudio::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH * 1.3), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);
	sprintf(buf, "%s##inpt", mSDASession->getInputTextureName(0).c_str());
	ImGui::Begin(buf);
	{
		if (ImGui::CollapsingHeader("Audio", NULL, true, true))
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
		if (ImGui::CollapsingHeader("Tempo", NULL, true, true))
		{

			ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
			if (ImGui::Button("x##spdx")) { mSDASettings->iSpeedMultiplier = 1.0; }
			ImGui::SameLine();
			ImGui::SliderFloat("speed x", &mSDASettings->iSpeedMultiplier, 0.01f, 5.0f, "%.1f");
			/* TODO
			ImGui::Text("Beat %d ", mSDASettings->iBeat);
			ImGui::SameLine();
			ImGui::Text("Beat Idx %d ", mSDAAnimation->iBeatIndex);
			//ImGui::SameLine();
			//ImGui::Text("Bar %d ", mSDAAnimation->iBar);
			if (ImGui::Button("x##bpbx")) { mSDASession->setControlValue("iBeat", 1); }
			ImGui::SameLine();
	 */
			ImGui::Text("beat %d ", mSDASession->getIntUniformValueByName("iBeat"));
			ImGui::SameLine();
			ImGui::Text("beats/bar %d ", mSDASession->getIntUniformValueByName("iBeatsPerBar"));

			ImGui::Text("Time %.2f", mSDASession->getFloatUniformValueByName("iTime"));
			ImGui::SameLine();
			ImGui::Text("Tempo Time %.2f", mSDASession->getFloatUniformValueByName("iTempoTime"));

			ImGui::Text("Trk %s %.2f", mSDASettings->mTrackName.c_str(), mSDASettings->liveMeter);
			ImGui::SameLine();
			//			ImGui::Checkbox("Playing", &mSDASettings->mIsPlaying);
			ImGui::Text("Tempo %.2f ", mSDASession->getBpm());

			if (ImGui::Button("Tap tempo")) { mSDASession->tapTempo(); }
			if (ImGui::Button("Time tempo")) { mSDASession->toggleUseTimeWithTempo(); }

			// TODO ImGui::SliderFloat("time x", &mSDAAnimation->iTimeFactor, 0.0001f, 1.0f, "%.01f");
			ImGui::SameLine();
			ImGui::PopItemWidth();
		}

#pragma endregion Tempo	

	}
	ImGui::End();

}
