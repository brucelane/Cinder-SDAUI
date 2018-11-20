#include "SDAUIAnimation.h"

using namespace SophiaDigitalArt;

SDAUIAnimation::SDAUIAnimation(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
	// zoom
	minZoom = getMinUniformValueByIndex(12);
	maxZoom = getMaxUniformValueByIndex(12);
	for (int c = 0; c < 128; c++)
	{
		localValues[c] = mSDASession->getFloatUniformValueByIndex(c);
	}
}
SDAUIAnimation::~SDAUIAnimation() {

}
float SDAUIAnimation::getValue(unsigned int aCtrl) {
	return mSDASession->getFloatUniformValueByIndex(aCtrl);
}
void SDAUIAnimation::setValue(unsigned int aCtrl, float aValue) {
	mSDASession->setFloatUniformValueByIndex(aCtrl, aValue);
}
bool SDAUIAnimation::getBoolValue(unsigned int aCtrl) {
	return mSDASession->getBoolUniformValueByIndex(aCtrl);
}
void SDAUIAnimation::toggleValue(unsigned int aCtrl) {
	mSDASession->toggleValue(aCtrl);
}
void SDAUIAnimation::toggleAuto(unsigned int aCtrl) {
	mSDASession->toggleAuto(aCtrl);
}
void SDAUIAnimation::toggleTempo(unsigned int aCtrl) {
	mSDASession->toggleTempo(aCtrl);
}
void SDAUIAnimation::toggleBass(unsigned int aCtrl) {
	//mSDASession->toggleBass(aCtrl);
}
void SDAUIAnimation::toggleMid(unsigned int aCtrl) {
	//mSDASession->toggleMid(aCtrl);
}
void SDAUIAnimation::toggleTreble(unsigned int aCtrl) {
	//mSDASession->toggleTreble(aCtrl);
}
void SDAUIAnimation::resetAutoAnimation(unsigned int aCtrl) {
	mSDASession->resetAutoAnimation(aCtrl);
}
float SDAUIAnimation::getMinUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMinUniformValueByIndex(aIndex);
}
float SDAUIAnimation::getMaxUniformValueByIndex(unsigned int aIndex) {
	return mSDASession->getMaxUniformValueByIndex(aIndex);
}
void SDAUIAnimation::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow2), ImGuiSetCond_Once);
	ImGui::Begin("Animation", NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
	{
		ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
		if (ImGui::CollapsingHeader("Effects", NULL, true, true))
		{
			int hue = 0;

			ctrl = mSDASettings->IGLITCH;
			(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("glitch")) {
				toggleValue(ctrl);
			}
			ImGui::PopStyleColor(3);
			hue++;
			ImGui::SameLine();

			ctrl = mSDASettings->ITOGGLE;
			(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("toggle")) {
				toggleValue(ctrl);
			}
			ImGui::PopStyleColor(3);
			hue++;
			ImGui::SameLine();

			ctrl = mSDASettings->IINVERT;
			(getBoolValue(ctrl)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("invert")) {
				toggleValue(ctrl);
			}
			ImGui::PopStyleColor(3);
			hue++;

			(mSDASettings->iGreyScale) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			mSDASettings->iGreyScale ^= ImGui::Button("greyscale");
			ImGui::PopStyleColor(3);
			hue++;
			ImGui::SameLine();

			if (ImGui::Button("blackout"))
			{
				setValue(1, 0.0);
				setValue(2, 0.0);
				setValue(3, 0.0);
				setValue(4, 0.0);
			}
		}
		if (ImGui::CollapsingHeader("Animation", NULL, true, true))
		{
			// iChromatic
			ctrl = mSDASettings->ICHROMATIC;
			if (ImGui::Button("a##chromatic")) {
				toggleAuto(ctrl);
			}
			ImGui::SameLine();
			if (ImGui::Button("f##chromatic")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("b##chromatic")) { toggleBass(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("m##chromatic")) { toggleMid(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("t##chromatic")) { toggleTreble(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##chromatic")) {
				resetAutoAnimation(ctrl);
			}
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("chromatic", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				mSDASession->setFloatUniformValueByIndex(ctrl, localValues[ctrl]);
			}

			// ratio
			ctrl = mSDASettings->IRATIO;
			if (ImGui::Button("a##ratio")) { toggleAuto(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("f##ratio")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("b##ratio")) { toggleBass(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("m##ratio")) { toggleMid(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("t##ratio")) { toggleTreble(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##ratio")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("ratio/min/max", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}

			// sobel
			ctrl = mSDASettings->ISOBEL;
			if (ImGui::Button("a##sobel")) { toggleAuto(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("f##sobel")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("b##sobel")) { toggleBass(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("m##sobel")) { toggleMid(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("t##sobel")) { toggleTreble(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##sobel")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("sobel/min/max", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// exposure
			ctrl = mSDASettings->IEXPOSURE;
			if (ImGui::Button("a##exposure")) { toggleAuto(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("f##exposure")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("b##exposure")) { toggleBass(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("m##exposure")) { toggleMid(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("t##exposure")) { toggleTreble(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##exposure")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::DragFloat("exposure", &localValues[ctrl], 0.1f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// zoom
			ctrl = mSDASettings->IZOOM;
			if (ImGui::Button("a##zoom"))
			{
				toggleAuto(ctrl);
			}
			ImGui::SameLine();
			if (ImGui::Button("f##zoom")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("b##zoom")) { toggleBass(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("m##zoom")) { toggleMid(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("t##zoom")) { toggleTreble(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##zoom")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::DragFloat("zoom", &localValues[ctrl], 0.1f, minZoom, maxZoom))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			ImGui::DragFloat("minzm", &minZoom, 0.1f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl));
			ImGui::SameLine();
			ImGui::DragFloat("maxzm", &maxZoom, 0.1f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl));

			// rotation speed 
			/*ctrl = mSDASettings->IROTATIONSPEED;
			if (ImGui::Button("a##rotationspeed")) { toggleAuto(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("f##rotationspeed")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##rotationspeed")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::DragFloat("rotationSpeed", &localValues[ctrl], 0.01f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}*/
			// badTv
			ctrl = mSDASettings->IBADTV;
			if (ImGui::Button("a##badtv")) { toggleAuto(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("f##badtv")) { toggleTempo(ctrl); }
			ImGui::SameLine();
			if (ImGui::Button("x##badtv")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::DragFloat("badTv", &localValues[ctrl], 0.01f, getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// param1
			ctrl = mSDASettings->IPARAM1;
			if (ImGui::Button("x##param1")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("param1/min/max", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// param2
			ctrl = mSDASettings->IPARAM2;
			if (ImGui::Button("x##param2")) { resetAutoAnimation(ctrl); }
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("param2/min/max", &localValues[ctrl], getMinUniformValueByIndex(ctrl), getMaxUniformValueByIndex(ctrl)))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			sprintf(buf, "XorY");
			mSDASettings->iXorY ^= ImGui::Button(buf);

			// steps
			ctrl = mSDASettings->ISTEPS;
			if (ImGui::Button("x##steps")) { localValues[ctrl] = 16.0f; setValue(ctrl, localValues[ctrl]);}
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("steps", &localValues[ctrl], 1.0f, 128.0f))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// pixelate
			ctrl = mSDASettings->IPIXELATE;
			if (ImGui::Button("x##pixelate")) { localValues[ctrl] = 1.0f; setValue(ctrl, localValues[ctrl]);}
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("pixelate", &localValues[ctrl], 0.01f, 1.0f))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			// trixels
			ctrl = mSDASettings->ITRIXELS;
			if (ImGui::Button("x##trixels")) { localValues[ctrl] = 0.0f; setValue(ctrl, localValues[ctrl]);}
			ImGui::SameLine();
			localValues[ctrl] = mSDASession->getFloatUniformValueByIndex(ctrl);
			if (ImGui::SliderFloat("trixels", &localValues[ctrl], 0.00f, 1.0f))
			{
				setValue(ctrl, localValues[ctrl]);
			}
			ImGui::SliderFloat("ABP Bend", &mSDASettings->mBend, -20.0f, 20.0f);
		}
		ImGui::PopItemWidth();
	}
	ImGui::End();
}
