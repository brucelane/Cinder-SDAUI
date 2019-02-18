#include "SDAUI.h"

using namespace SophiaDigitalArt;

SDAUI::SDAUI(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
	// UITextures
	mUITextures = SDAUITextures::create(mSDASettings, mSDASession);
	// UIFbos
	mUIFbos = SDAUIFbos::create(mSDASettings, mSDASession);
	// UIAnimation
	mUIAnimation = SDAUIAnimation::create(mSDASettings, mSDASession);
	// UIMidi
	mUIMidi = SDAUIMidi::create(mSDASettings, mSDASession);
	// UIAudio
	mUIAudio = SDAUIAudio::create(mSDASettings, mSDASession);
	// UIColor
	mUIColor = SDAUIColor::create(mSDASettings, mSDASession);
	// UITempo
	mUITempo = SDAUITempo::create(mSDASettings, mSDASession);
	// UIBlend
	mUIBlend = SDAUIBlend::create(mSDASettings, mSDASession);
	// UIOsc
	mUIOsc = SDAUIOsc::create(mSDASettings, mSDASession);
	// UIWebsockets
	mUIWebsockets = SDAUIWebsockets::create(mSDASettings, mSDASession);
	// UIMouse
	mUIMouse = SDAUIMouse::create(mSDASettings, mSDASession);
	// UIShaders
	mUIShaders = SDAUIShaders::create(mSDASettings, mSDASession);
	// UIRender
	mUIRender = SDAUIRender::create(mSDASettings, mSDASession);
	// imgui
	mouseGlobal = false;
	mIsResizing = true;
}
void SDAUI::setValue(unsigned int aCtrl, float aValue) {
	mSDASession->setFloatUniformValueByIndex(aCtrl, aValue);
}
float SDAUI::getMinUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMinUniformValueByIndex(aIndex);
}
float SDAUI::getMaxUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMaxUniformValueByIndex(aIndex);
}
void SDAUI::resize() {
	mIsResizing = true;
	// disconnect ui window and io events callbacks
	ImGui::disconnectWindow(getWindow());
}
void SDAUI::Run(const char* title, unsigned int fps) {
	static int currentWindowRow1 = 1;
	static int currentWindowRow2 = 0;

	ImGuiStyle& style = ImGui::GetStyle();

	if (mIsResizing) {
		mIsResizing = false;

		// set ui window and io events callbacks 
		ImGui::connectWindow(getWindow());
		ImGui::initialize();

#pragma region style
		// our theme variables
		style.WindowRounding = 4;
		style.WindowPadding = ImVec2(3, 3);
		style.FramePadding = ImVec2(2, 2);
		style.ItemSpacing = ImVec2(3, 3);
		style.ItemInnerSpacing = ImVec2(3, 3);
		style.WindowMinSize = ImVec2(mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight);
		style.Alpha = 0.85f;
		style.Colors[ImGuiCol_Text] = ImVec4(0.89f, 0.92f, 0.94f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.38f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.4f, 0.0f, 0.21f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.97f, 0.0f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		// style.Colors[ImGuiCol_ComboBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.99f, 0.22f, 0.22f, 0.50f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.65f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.8f, 0.35f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.04f, 0.04f, 0.04f, 0.22f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.65f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.8f, 0.35f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.9f, 0.45f, 0.45f, 1.00f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.65f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.8f, 0.35f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.65f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.8f, 0.35f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
#pragma endregion style
	}
#pragma region menu
	if (ImGui::BeginMainMenuBar()) {

		if (ImGui::BeginMenu("Options"))
		{
			ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f");
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

#pragma endregion menu
	//ImGui::SetNextWindowSize(ImVec2(mSDASettings->mRenderWidth - 20, uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(800, mSDASettings->uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiXPosCol1, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);
	sprintf(buf, "Fps %c %d (%.2f)###fps", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3], fps, mSDASession->getTargetFps());
	ImGui::Begin(buf);
	{
		// line 1
		ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
		// fps
		static ImVector<float> values; if (values.empty()) { values.resize(100); memset(&values.front(), 0, values.size() * sizeof(float)); }
		static int values_offset = 0;
		static float refresh_time = -1.0f;
		if (ImGui::GetTime() > refresh_time + 1.0f / 6.0f)
		{
			refresh_time = ImGui::GetTime();
			values[values_offset] = mSDASession->getFloatUniformValueByIndex(mSDASettings->IFPS);
			values_offset = (values_offset + 1) % values.size();
		}
		if (mSDASession->getFloatUniformValueByIndex(mSDASettings->IFPS) < 12.0) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
		ImGui::PlotLines("F", &values.front(), (int)values.size(), values_offset, mSDASettings->sFps.c_str(), 0.0f, mSDASession->getTargetFps(), ImVec2(0, 30));
		if (mSDASession->getFloatUniformValueByIndex(mSDASettings->IFPS) < 12.0) ImGui::PopStyleColor();
		// audio
		ImGui::SameLine();
		static ImVector<float> timeValues; if (timeValues.empty()) { timeValues.resize(40); memset(&timeValues.front(), 0, timeValues.size() * sizeof(float)); }
		static int timeValues_offset = 0;
		// audio maxVolume
		static float tRefresh_time = -1.0f;
		if (ImGui::GetTime() > tRefresh_time + 1.0f / 20.0f)
		{
			tRefresh_time = ImGui::GetTime();
			timeValues[timeValues_offset] = mSDASession->getMaxVolume();
			timeValues_offset = (timeValues_offset + 1) % timeValues.size();
		}
		
		ImGui::PlotHistogram("H", mSDASession->getFreqs(), mSDASession->getWindowSize(), 0, NULL, 0.0f, 255.0f, ImVec2(0, 30));
		ImGui::SameLine();
		if (mSDASession->getMaxVolume() > 240.0) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
		ImGui::PlotLines("V", &timeValues.front(), (int)timeValues.size(), timeValues_offset, toString(int(mSDASession->getMaxVolume())).c_str(), 0.0f, 255.0f, ImVec2(0, 30));
		if (mSDASession->getMaxVolume() > 240.0) ImGui::PopStyleColor();
		

		// crossfade
		ImGui::SameLine();
		float xFade = mSDASession->getCrossfade();
		sprintf(buf, "xfade##xfd");
		if (ImGui::SliderFloat(buf, &xFade, 0.0f, 1.0f))
		{
			mSDASession->setCrossfade(xFade);
		}
		ImGui::SameLine();
		// flip vertically
		int hue = 0;
		mSDASession->isFlipV() ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("FlipV")) {
			mSDASession->flipV();
		}
		ImGui::PopStyleColor(3);
		hue++;
		ImGui::SameLine();
		// flip horizontally
		mSDASession->isFlipH() ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
		if (ImGui::Button("FlipH")) {
			mSDASession->flipH();
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::TextWrapped("Msg: %s", mSDASettings->mMsg.c_str());

		// line 2
		
		multx = mSDASession->getFloatUniformValueByIndex(mSDASettings->IAUDIOX); // 13
		if (ImGui::SliderFloat("mult x", &multx, 0.01f, 12.0f)) {
			mSDASession->setFloatUniformValueByIndex(13, multx);
		}
		ImGui::SameLine();
		(mSDASession->isAudioBuffered()) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3.0f, 0.8f, 0.8f));
		if (ImGui::Button("Wave")) {
			mSDASession->toggleAudioBuffered();
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		(mSDASession->getUseLineIn()) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(4.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(4.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(4.0f, 0.8f, 0.8f));
		if (ImGui::Button("LineIn")) {
			mSDASession->toggleUseLineIn();
		}
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::TextWrapped("WS Msg: %s", mSDASettings->mWebSocketsMsg.c_str());


		ImGui::RadioButton("Tempo", &currentWindowRow1, 0); ImGui::SameLine();
		ImGui::RadioButton("Anim", &currentWindowRow1, 1); ImGui::SameLine();
		ImGui::RadioButton("Mouse", &currentWindowRow1, 2);  ImGui::SameLine();
		ImGui::RadioButton("Blend", &currentWindowRow1, 3); ImGui::SameLine();
		ImGui::RadioButton("Audio", &currentWindowRow1, 4); ImGui::SameLine();
		ImGui::RadioButton("Color", &currentWindowRow1, 5); ImGui::SameLine();
		ImGui::RadioButton("Osc", &currentWindowRow1, 6); ImGui::SameLine();
		ImGui::RadioButton("Ws", &currentWindowRow1, 7); ImGui::SameLine();
		ImGui::RadioButton("Midi", &currentWindowRow1, 8); ImGui::SameLine();
		ImGui::RadioButton("Render", &currentWindowRow1, 9); ImGui::SameLine();
		ImGui::SameLine();
		ImGui::TextWrapped("OSC Msg: %s", mSDASettings->mOSCMsg.c_str());


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

		/*hue++;

		ImGui::RadioButton("Textures", &currentWindowRow2, 0); ImGui::SameLine();
		ImGui::RadioButton("Fbos", &currentWindowRow2, 1); ImGui::SameLine();
		ImGui::RadioButton("Shaders", &currentWindowRow2, 2); ImGui::SameLine();
		ImGui::RadioButton("Blend", &currentWindowRow2, 3); */




		ImGui::PopItemWidth();
	}
	ImGui::End();


	switch (currentWindowRow1) {
	case 0:
		// Tempo
		mUITempo->Run("Tempo");
		break;
	case 1:
		// Animation
		mUIAnimation->Run("Animation");
		break;
	case 2:
		// Mouse
		mUIMouse->Run("Mouse");
		break;
	case 3:
		// Blend
		mUIBlend->Run("Blend");
		break;
	case 4:
		// Audio
		mUIAudio->Run("Audio");
		break; 
	case 5:
		// Color
		mUIColor->Run("Color");
		break;
	case 6:
		// Osc
		mUIOsc->Run("Osc");
		break;
	case 7:
		// Websockets
		mUIWebsockets->Run("Websockets");
		break;
	case 8:
		// Midi
		mUIMidi->Run("Midi");
		break;
	case 9:
		// Render
		mUIRender->Run("Render");

		break;
	}
	mSDASession->blendRenderEnable(currentWindowRow1 == 3);

	// textures
	mUITextures->Run("Textures");
	// Fbos
	mUIFbos->Run("Fbos");
	// Shaders
	mUIShaders->Run("Shaders");


}
