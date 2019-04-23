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
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH * 1.3), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);

	ImGui::Begin("Color Ws", NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
	{
		if (ImGui::CollapsingHeader("Color", NULL, true, true))
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
			ctrl = mSDASettings->IFRX;
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
			ctrl = mSDASettings->IFGX;
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
			ctrl = mSDASettings->IFBX;
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
		if (ImGui::CollapsingHeader("Websockets", NULL, true, true))
		{
			// websockets
			if (mSDASettings->mIsWebSocketsServer)
			{
				ImGui::Text("WS Server %s%s:%d", mSDASettings->mWebSocketsProtocol.c_str(), mSDASettings->mWebSocketsHost.c_str(), mSDASettings->mWebSocketsPort);
				if (ImGui::Button("srv->clt"))
				{
					mSDASettings->mIsWebSocketsServer = false;
					mSDASession->wsConnect();
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Change to a WS client");
			}
			else
			{
				ImGui::Text("WS Client %s%s:%d", mSDASettings->mWebSocketsProtocol.c_str(), mSDASettings->mWebSocketsHost.c_str(), mSDASettings->mWebSocketsPort);
				if (ImGui::Button("clt->srv"))
				{
					mSDASettings->mIsWebSocketsServer = true;
					mSDASession->wsConnect();
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Change to a WS server");
			}
			ImGui::SameLine();
			// toggle secure protocol
			sprintf(buf, "%s", mSDASettings->mWebSocketsProtocol.c_str());
			if (ImGui::Button(buf))
			{
				if (mSDASettings->mWebSocketsProtocol == "ws://") {
					mSDASettings->mWebSocketsProtocol = "wss://";
				}
				else {
					mSDASettings->mWebSocketsProtocol = "ws://";
				}
				mSDASession->wsConnect();
			}
			if (ImGui::IsItemHovered()) ImGui::SetTooltip("Change WS protocol");
			ImGui::SameLine();
			if (ImGui::Button("Connect")) { mSDASession->wsConnect(); }
			ImGui::SameLine();
			if (ImGui::Button("Ping")) { mSDASession->wsPing(); }
			static char host[128] = "127.0.0.1";
			std::copy(mSDASettings->mWebSocketsHost.begin(), (mSDASettings->mWebSocketsHost.size() >= 128 ? mSDASettings->mWebSocketsHost.begin() + 128 : mSDASettings->mWebSocketsHost.end()), host);

			static int port = mSDASettings->mWebSocketsPort;
			if (ImGui::InputText("address", host, IM_ARRAYSIZE(host)))
			{
				mSDASettings->mWebSocketsHost = host; // CHECK if ok
			}
			if (ImGui::InputInt("port", &port)) mSDASettings->mWebSocketsPort = port;
			//ImGui::PushItemWidth(mSDASettings->uiLargeW/3); // useless?
			ImGui::TextWrapped(">%s", mSDASettings->mWebSocketsMsg.c_str());
			//ImGui::PopItemWidth();

		}
	}
	ImGui::End();
}
