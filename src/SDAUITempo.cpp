#include "SDAUITempo.h"

using namespace VideoDromm;

SDAUITempo::SDAUITempo(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUITempo::~SDAUITempo() {
}

void SDAUITempo::Run(const char* title) {

	// Tempo
#pragma region Tempo
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow2), ImGuiSetCond_Once);

	ImGui::Begin("Tempo");
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
		// TODO if (ImGui::Button("Time tempo")) { mSDAAnimation->mUseTimeWithTempo = !mSDAAnimation->mUseTimeWithTempo; }

		// TODO ImGui::SliderFloat("time x", &mSDAAnimation->iTimeFactor, 0.0001f, 1.0f, "%.01f");
		ImGui::SameLine();
		ImGui::PopItemWidth();
	}
	ImGui::End();

#pragma endregion Tempo	

}
