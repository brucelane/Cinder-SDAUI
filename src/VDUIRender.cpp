#include "VDUIRender.h"

using namespace videodromm;

VDUIRender::VDUIRender(VDSettingsRef aVDSettings, VDSessionRef aVDSession) {
	mVDSettings = aVDSettings;
	mVDSession = aVDSession;
	
	// contour
	minContour = getMinUniformValueByIndex(mVDSettings->ICONTOUR);
	maxContour = getMaxUniformValueByIndex(mVDSettings->ICONTOUR);
	iResolutionX = (int)mVDSession->getUniformValue(mVDSettings->IRESOLUTIONX);//(int)getFloatValueByName("iResolutionX");
	iResolutionY = (int)mVDSession->getUniformValue(mVDSettings->IRESOLUTIONY);//(int)getFloatValueByName("iResolutionY");
	iOutW = getIntValue(mVDSettings->IOUTW);
	iOutH = getIntValue(mVDSettings->IOUTH);
}


void VDUIRender::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mVDSettings->uiLargeW, mVDSettings->uiLargeH * 1.76), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mVDSettings->uiMargin, mVDSettings->uiYPosRow1), ImGuiSetCond_Once);

#pragma region render

	ImGui::Begin("Render");
	{
		int hue = 0;
		ImGui::PushItemWidth(mVDSettings->mPreviewFboWidth);
		// output resolution
		ctrl = mVDSettings->IOUTW;
		if (ImGui::Button("x##ioutw")) { iOutW = 1280; setIntValue(ctrl, 1280); }
		ImGui::SameLine();
		if (ImGui::SliderInt("iOutW", &iOutW, 320, 5000))
		{
			setIntValue(ctrl, iOutW);
		}
		ctrl = mVDSettings->IOUTH;
		if (ImGui::Button("x##iouth")) { iOutH = 720; setIntValue(ctrl, iOutH); }
		ImGui::SameLine();
		if (ImGui::SliderInt("iOutH", &iOutH, 480, 2000))
		{
			setIntValue(ctrl, iOutH);
		}
		// iResolution
		ctrl = mVDSettings->IRESOLUTIONX;
		//iResolutionX = getValueByName("iResolutionX");
		if (ImGui::Button("x##IRESOLUTIONX")) { iResolutionX = 1280; setFloatValue(ctrl, 1280); }
		ImGui::SameLine();
		if (ImGui::SliderInt("iResolutionX", &iResolutionX, (int)getMinUniformValueByIndex(ctrl), (int)getMaxUniformValueByIndex(ctrl)))
		{
			setFloatValue(ctrl, (float)iResolutionX);
		}
		ctrl = mVDSettings->IRESOLUTIONY;
		//iResolutionY = getValueByName("iResolutionY");
		if (ImGui::Button("x##IRESOLUTIONY")) { iResolutionY = 720; setFloatValue(ctrl, 720); }
		ImGui::SameLine();
		if (ImGui::SliderInt("iResolutionY", &iResolutionY, (int)getMinUniformValueByIndex(ctrl), (int)getMaxUniformValueByIndex(ctrl)))
		{
			setFloatValue(ctrl, (float)iResolutionY);
		}
		// post flip		
		ctrl = mVDSettings->IFLIPPOSTH;
		(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 16.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 16.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 16.0f, 0.8f, 0.8f));
		if (ImGui::Button("flipPostH")) {
			toggleValue(ctrl);
		}
		ImGui::PopStyleColor(3);
		hue++;
		ImGui::SameLine();
		ctrl = mVDSettings->IFLIPPOSTV;
		(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 16.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 16.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 16.0f, 0.8f, 0.8f));
		if (ImGui::Button("flipPostV")) {
			toggleValue(ctrl);
		}
		ImGui::PopStyleColor(3);
		hue++;
		// mRenderXY
		static float mx = mVDSettings->mRenderXY.x;
		if (ImGui::SliderFloat("mx", &mx, 0.01, 1.0))
		{
			mVDSettings->mRenderXY.x = mx;
		}
		ImGui::SameLine();
		static float my = mVDSettings->mRenderXY.y;
		if (ImGui::SliderFloat("my", &my, 0.01, 1.0))
		{
			mVDSettings->mRenderXY.y = my;
		}

		// mRenderXY
		static float texMultW = mVDSettings->mTexMult.x;
		if (ImGui::SliderFloat("texWx", &texMultW, 0.2, 4.0))
		{
			mVDSettings->mTexMult.x = texMultW;
		}
		ImGui::SameLine();
		static float texMultH = mVDSettings->mTexMult.y;
		if (ImGui::SliderFloat("texHx", &texMultH, 0.2, 4.0))
		{
			mVDSettings->mTexMult.x = texMultH;
		}


		// rect mxLeft
		static int mxLeft = mVDSettings->mxLeft;
		if (ImGui::SliderInt("mxL", &mxLeft, 0, 2280))
		{
			mVDSettings->mxLeft = mxLeft;
		}
		ImGui::SameLine();
		// rect myLeft
		static int myLeft = mVDSettings->myLeft;
		if (ImGui::SliderInt("myL", &myLeft, 0, 2280))
		{
			mVDSettings->myLeft = myLeft;
		}
		// rect mxRight
		static int mxRight = mVDSettings->mxRight;
		if (ImGui::SliderInt("mxR", &mxRight, 0, 2280))
		{
			mVDSettings->mxRight = mxRight;
		}
		ImGui::SameLine();
		// rect myRight
		static int myRight = mVDSettings->myRight;
		if (ImGui::SliderInt("myR", &myRight, 0, 2280))
		{
			mVDSettings->myRight = myRight;
		}
		
		// debug
		/*ctrl = mVDSettings->IDEBUG;
		(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 16.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 16.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 16.0f, 0.8f, 0.8f));
		if (ImGui::Button("debug")) {
			toggleValue(ctrl);
		}
		ImGui::PopStyleColor(3);
		hue++;*/

		// iVignette
		ctrl = mVDSettings->IVIGN;
		(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 16.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 16.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 16.0f, 0.8f, 0.8f));
		if (ImGui::Button("vignette")) {
			toggleValue(ctrl);
		}
		ImGui::PopStyleColor(3);
		hue++;
		ctrl = mVDSettings->IVAMOUNT;
		iVAmount = mVDSession->getUniformValue(ctrl);
		if (ImGui::DragFloat("Amount", &iVAmount, 0.001f, 0.0f, 1.0f))
		{
			setFloatValue(ctrl, iVAmount);
		}
		ctrl = mVDSettings->IVFALLOFF;
		iVFallOff = mVDSession->getUniformValue(ctrl);
		if (ImGui::DragFloat("FallOff", &iVFallOff, 0.001f, 0.0f, 0.99f))
		{
			setFloatValue(ctrl, iVFallOff);
		}

		// iContour
		ctrl = mVDSettings->ICONTOUR;
		if (ImGui::Button("a##contour")) { toggleAuto(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("t##contour")) { toggleTempo(ctrl); }
		ImGui::SameLine();
		if (ImGui::Button("x##contour")) { resetAutoAnimation(ctrl); }
		ImGui::SameLine();
		contour = mVDSession->getUniformValue(ctrl);
		if (ImGui::DragFloat("contour", &contour, 0.001f, minContour, maxContour))
		{
			setFloatValue(ctrl, contour);
		}
		ImGui::DragFloat("mincr", &minContour, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl));
		ImGui::SameLine();
		ImGui::DragFloat("maxcr", &maxContour, 0.001f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl));
        // windows
		ImGui::Text("render window %dx%d", mVDSettings->mRenderWidth, mVDSettings->mRenderHeight);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.9f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.9f, 0.8f, 0.8f));

		if (ImGui::Button("Auto Layout")) {
			mVDSession->toggleAutoLayout();
		}
		if (ImGui::IsItemHovered()) ImGui::SetTooltip("Auto Layout for render window");

		// Auto Layout for render window
		if (mVDSession->isAutoLayout()) {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.9f, 1.0f, 0.5f));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
			// render window width
			static int rw = mVDSettings->mRenderWidth;
			if (ImGui::SliderInt("rdr w", &rw, 640, 4080))
			{
				//mVDSession->setRenderWidth(rw);
				mVDSettings->mRenderWidth = rw;
			}
			ImGui::SameLine();
			// render window height
			static int rh = mVDSettings->mRenderHeight;
			if (ImGui::SliderInt("rdr h", &rh, 480, 1280))
			{
				//mVDSession->setRenderHeight(rh);
				mVDSettings->mRenderHeight = rh;
			}
		}
		ImGui::PopStyleColor(3);

		/*if (ImGui::Button("Create Window")) {
			mVDSession->createWindow();
		}
		ImGui::SameLine();
		if (ImGui::Button("Delete Window")) {
			mVDSession->deleteWindow();
		}*/

		ImGui::Text("fp %dx%d f %dx%d", mVDSettings->mPreviewFboWidth, mVDSettings->mPreviewFboHeight, mVDSettings->mFboWidth, mVDSettings->mFboHeight);
		ImGui::Text("main %dx%d", mVDSettings->mMainWindowWidth, mVDSettings->mMainWindowHeight);
		//ImGui::SameLine();
		//ImGui::Text("solo %d", mVDSession->getSolo());
		
		ImGui::PopItemWidth();
	}
	ImGui::End();

#pragma endregion render

}
