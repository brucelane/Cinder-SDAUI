#include "SDAUIMouse.h"

using namespace SophiaDigitalArt;

SDAUIMouse::SDAUIMouse(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIMouse::~SDAUIMouse() {
	
}
float SDAUIMouse::getValue(unsigned int aCtrl) {
	return mSDASession->getFloatUniformValueByIndex(aCtrl);
}
void SDAUIMouse::setValue(unsigned int aCtrl, float aValue) {
	mSDASession->setFloatUniformValueByIndex(aCtrl, aValue);
}
void SDAUIMouse::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);
	// Mouse
#pragma region mouse

	ImGui::Begin("Mouse");
	{
		ImGui::Text("Position: %.1f,%.1f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		ImGui::Text("Clic %d", ImGui::GetIO().MouseDown[0]);
		/* mouseGlobal ^= ImGui::Button("mouse gbl");
		if (mouseGlobal)
		{
			mSDASettings->mRenderPosXY.x = ImGui::GetIO().MousePos.x; ImGui::SameLine();
			mSDASettings->mRenderPosXY.y = ImGui::GetIO().MousePos.y;
		} */
		// mouse
		mouseX = getValue(35);
		if (ImGui::SliderFloat("MouseX", &mouseX, 0.0f, mSDASettings->mFboWidth, "%.4f", 3.0f))
		{
			setValue(35, mouseX);
		}
		mouseY = getValue(36);
		if (ImGui::SliderFloat("MouseY", &mouseY, 0.0f, mSDASettings->mFboHeight, "%.4f", 0.3f))
		{
			setValue(36, mouseY);
		}
		mouseZ ^= ImGui::Button("mouse click");
		if (mouseZ)
		{
			setValue(37, 1.0f);
		}
		else
		{
			setValue(37, 0.0f);
		}
	}
	ImGui::End();
#pragma endregion mouse
}
