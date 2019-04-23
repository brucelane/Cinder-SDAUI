#include "SDAUIBlend.h"

using namespace SophiaDigitalArt;

SDAUIBlend::SDAUIBlend(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIBlend::~SDAUIBlend() {

}

void SDAUIBlend::Run(const char* title) {
	const char* blendModes[] = { "mix", "multiply", "colorBurn", "linearBurn", "darkerColor", "lighten", "screen", "colorDodge", "linearDodge", "lighterColor", "overlay", "softLight", "hardLight", "vividLight", "linearLight", "pinLight", "hardMix", "difference", "exclusion", "subtract", "divide", "hue", "color", "saturation", "luminosity", "darken", "left", "right" };

	xPos = mSDASettings->uiMargin;
	yPos = mSDASettings->uiYPosRow4;// 5;
	for (int s = 0; s < mSDASession->getFboBlendCount(); s++) {
		ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiPreviewH + 10.0f), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
		sprintf(buf, "%s", blendModes[s]);
		ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
			ImGui::PushID(s);
			ImGui::Image((void*)mSDASession->getFboThumb(s)->getId(), ivec2(mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight));

			// select blend mode
			if (mSDASettings->iBlendmode == s) {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.3f, 1.0f, 0.5f));
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
			}
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.3f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.3f, 0.8f, 0.8f));

			sprintf(buf, "B##s%d", s);
			if (ImGui::Button(buf)){
				mSDASession->useBlendmode(s);
			}
			if (ImGui::IsItemHovered()) ImGui::SetTooltip("Use this blend");
			ImGui::PopStyleColor(3);

			ImGui::PopID();
			ImGui::PopItemWidth();
		}
		ImGui::End();
		xPos += mSDASettings->uiLargePreviewW + mSDASettings->uiMargin;
		//if (xPos > (mSDASettings->mRenderWidth - mSDASettings->uiLargePreviewW))
		if (s % 13 == 12)
		{
			xPos = mSDASettings->uiMargin;
			yPos += mSDASettings->uiPreviewH + 10.0f + mSDASettings->uiMargin;
		}
	}
}
