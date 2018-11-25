#include "SDAUIWebsockets.h"

using namespace SophiaDigitalArt;

SDAUIWebsockets::SDAUIWebsockets(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIWebsockets::~SDAUIWebsockets() {

}

void SDAUIWebsockets::Run(const char* title) {
	#if (defined(  CINDER_MSW) ) || (defined( CINDER_MAC ))
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);

	ImGui::Begin("Websockets");
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
	ImGui::End();
	#endif
}
