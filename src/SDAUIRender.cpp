#include "SDAUIRender.h"

using namespace SophiaDigitalArt;

SDAUIRender::SDAUIRender(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
	
	// contour
	minContour = getMinUniformValueByIndex(26);
	maxContour = getMaxUniformValueByIndex(26);
	iResolutionX = (int)getValueByName("iResolutionX");
	iResolutionY = (int)getValueByName("iResolutionY");

}
float SDAUIRender::getValueByName(string aCtrlName) {
	return mSDASession->getFloatUniformValueByName(aCtrlName);
}
float SDAUIRender::getValue(unsigned int aCtrl) {
	return mSDASession->getFloatUniformValueByIndex(aCtrl);
}
void SDAUIRender::setValue(unsigned int aCtrl, float aValue) {
	mSDASession->setFloatUniformValueByIndex(aCtrl, aValue);
}
void SDAUIRender::toggleAuto(unsigned int aCtrl) {
	mSDASession->toggleAuto(aCtrl);
}
void SDAUIRender::toggleTempo(unsigned int aCtrl) {
	mSDASession->toggleTempo(aCtrl);
}
void SDAUIRender::toggleSpoutSender() {
	//mSDASettings->mSpoutSender = !mSDASettings->mSpoutSender;
}
bool SDAUIRender::getBoolValue(unsigned int aCtrl) {
	return mSDASession->getBoolUniformValueByIndex(aCtrl);
}
void SDAUIRender::toggleValue(unsigned int aCtrl) {
	mSDASession->toggleValue(aCtrl);
}
void SDAUIRender::resetAutoAnimation(unsigned int aCtrl) {
	mSDASession->resetAutoAnimation(aCtrl);
}
float SDAUIRender::getMinUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMinUniformValueByIndex(aIndex);
}
float SDAUIRender::getMaxUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMaxUniformValueByIndex(aIndex);
}
void SDAUIRender::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow2), ImGuiSetCond_Once);
#pragma region render

	ImGui::Begin("Render");
	{
		int hue = 0;
		ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
		// iResolution
		ctrl = mSDASettings->IRESX;
		//iResolutionX = getValueByName("iResolutionX");
		if (ImGui::DragInt("iResolutionX", &iResolutionX, 1.0f, (int)getMinUniformValueByIndex(ctrl), (int)getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, (float)iResolutionX);
		}
		ctrl = mSDASettings->IRESY;
		//iResolutionY = getValueByName("iResolutionY");
		if (ImGui::DragInt("iResolutionY", &iResolutionY, 1.0f, (int)getMinUniformValueByIndex(ctrl), (int)getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, (float)iResolutionY);
		}

		// iVignette
		ctrl = mSDASettings->IVIGN;
		(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("vignette")) {
			toggleValue(ctrl);
		}
		ImGui::PopStyleColor(3);
		hue++;
		ctrl = mSDASettings->IVAMOUNT;
		iVAmount = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("Amount", &iVAmount, 0.001f, 0.0f, 1.0f))
		{
			setValue(ctrl, iVAmount);
		}
		ctrl = mSDASettings->IVFALLOFF;
		iVFallOff = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("FallOff", &iVFallOff, 0.001f, 0.0f, 0.99f))
		{
			setValue(ctrl, iVFallOff);
		}

		// iContour
		ctrl = mSDASettings->ICONTOUR;
		if (ImGui::Button("a##contour")) { toggleAuto(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("t##contour")) { toggleTempo(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("x##contour")) { resetAutoAnimation(ctrl); }
		ImGui::SameLine();
		contour = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("contour", &contour, 0.001f, minContour, maxContour))
		{
			setValue(ctrl, contour);
		}
		ImGui::DragFloat("mincr", &minContour, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl));
		ImGui::SameLine();
		ImGui::DragFloat("maxcr", &maxContour, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl));
        // windows
		ImGui::Text("render window %dx%d", mSDASettings->mRenderWidth, mSDASettings->mRenderHeight);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.9f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.9f, 0.8f, 0.8f));

		if (ImGui::Button("Auto Layout")) {
			mSDASession->toggleAutoLayout();
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Auto Layout for render window");

		// Auto Layout for render window
		if (mSDASession->isAutoLayout()) {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.9f, 1.0f, 0.5f));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
			// render window width
			static int rw = mSDASettings->mRenderWidth;
			if (ImGui::SliderInt("rdr w", &rw, 640, 4080))
			{
				//mSDASession->setRenderWidth(rw);
				mSDASettings->mRenderWidth = rw;
			}
			ImGui::SameLine();
			// render window height
			static int rh = mSDASettings->mRenderHeight;
			if (ImGui::SliderInt("rdr h", &rh, 480, 1280))
			{
				//mSDASession->setRenderHeight(rh);
				mSDASettings->mRenderHeight = rh;
			}
		}
		ImGui::PopStyleColor(3);

		/*if (ImGui::Button("Create Window")) {
			mSDASession->createWindow();
		}
		ImGui::SameLine();
		if (ImGui::Button("Delete Window")) {
			mSDASession->deleteWindow();
		}*/

		ImGui::Text("fp %dx%d f %dx%d", mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight, mSDASettings->mFboWidth, mSDASettings->mFboHeight);
		ImGui::Text("main %dx%d", mSDASettings->mMainWindowWidth, mSDASettings->mMainWindowHeight);
		//ImGui::SameLine();
		//ImGui::Text("solo %d", mSDASession->getSolo());
		ctrl = mSDASettings->IWEIGHT0;
		iWeight0 = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("Weight0", &iWeight0, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, iWeight0);
		}
		ctrl = mSDASettings->IWEIGHT1;
		iWeight1 = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("Weight1", &iWeight1, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, iWeight1);
		}
		ctrl = mSDASettings->IWEIGHT2;
		iWeight2 = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("Weight2", &iWeight2, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, iWeight2);
		}
		ctrl = mSDASettings->IWEIGHT3;
		iWeight3 = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("Weight3", &iWeight3, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, iWeight3);
		}
		ctrl = mSDASettings->IWEIGHT4;
		iWeight4 = mSDASession->getFloatUniformValueByIndex(ctrl);
		if (ImGui::DragFloat("Weight4", &iWeight4, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
		{
			setValue(ctrl, iWeight4);
		}
		ImGui::PopItemWidth();
	}
	ImGui::End();

#pragma endregion render

}
