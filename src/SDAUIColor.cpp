#include "SDAUIColor.h"

using namespace SophiaDigitalArt;

SDAUIColor::SDAUIColor(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
	for (int c = 0; c < 28; c++)
	{
		localValues[c] = 1.0f;
	}

}
SDAUIColor::~SDAUIColor() {

}
float SDAUIColor::getValue(unsigned int aCtrl) {
	return mSDASession->getFloatUniformValueByIndex(aCtrl);
}
void SDAUIColor::setValue(unsigned int aCtrl, float aValue) {
	mSDASession->setFloatUniformValueByIndex(aCtrl, aValue);
}
void SDAUIColor::toggleAuto(unsigned int aCtrl) {
	mSDASession->toggleAuto(aCtrl);
}
void SDAUIColor::toggleTempo(unsigned int aCtrl) {
	mSDASession->toggleTempo(aCtrl);
}
void SDAUIColor::resetAutoAnimation(unsigned int aCtrl) {
	mSDASession->resetAutoAnimation(aCtrl);
}
float SDAUIColor::getMinUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMinUniformValueByIndex(aIndex);
}
float SDAUIColor::getMaxUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMaxUniformValueByIndex(aIndex);
}
void SDAUIColor::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);

	ImGui::Begin("Color");
	{
		ImGui::PushItemWidth(200.0f);
		// foreground color
		color[0] = getValue(mSDASettings->IFR);
		color[1] = getValue(mSDASettings->IFG);
		color[2] = getValue(mSDASettings->IFB);
		color[3] = getValue(mSDASettings->IFA);
		ImGui::ColorEdit4("f", color);
		for (int i = 0; i < 4; i++)
		{
			if (getValue(i + mSDASettings->IFR) != color[i])
			{
				setValue(i + mSDASettings->IFR, color[i]);
			}
		}
	
		// background color
		backcolor[0] = getValue(mSDASettings->IBR);
		backcolor[1] = getValue(mSDASettings->IBG);
		backcolor[2] = getValue(mSDASettings->IBB);
		ImGui::ColorEdit3("g", backcolor);
		for (int i = 0; i < 3; i++)
		{
			if (getValue(i + mSDASettings->IBR) != backcolor[i])
			{
				setValue(i + mSDASettings->IBR, backcolor[i]);
			}

		}
		ImGui::PopItemWidth();
		ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
		// color multipliers
		// red x
		ctrl = 5;
		if (ImGui::Button("a##redx")) { toggleAuto(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("t##redx")) { toggleTempo(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("x##redx")) { resetAutoAnimation(ctrl); }
		ImGui::SameLine();
		localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("red x", &localValues[ctrl], 0.01f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, localValues[ctrl]);
		}
		// green x
		ctrl = 6;
		if (ImGui::Button("a##greenx")) { toggleAuto(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("t##greenx")) { toggleTempo(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("x##greenx")) { resetAutoAnimation(ctrl); }
		ImGui::SameLine();
		localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("green x", &localValues[ctrl], 0.01f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, localValues[ctrl]);
		}
		// blue x
		ctrl = 7;
		if (ImGui::Button("a##bluex")) { toggleAuto(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("t##bluex")) { toggleTempo(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("x##bluex")) { resetAutoAnimation(ctrl); }
		ImGui::SameLine();
		localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("blue x", &localValues[ctrl], 0.01f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, localValues[ctrl]);
		}

		ImGui::PopItemWidth();
	}
	ImGui::End();
}
