#include "SDAUIOsc.h"

using namespace SophiaDigitalArt;

SDAUIOsc::SDAUIOsc(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIOsc::~SDAUIOsc() {

}

void SDAUIOsc::Run(const char* title) {
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiSmallH), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow1), ImGuiSetCond_Once);

	ImGui::Begin("Osc");
	{
		if (mSDASettings->mOSCEnabled) {
			ImGui::Text("OSC enabled");
			if (mSDASettings->mIsOSCSender) {
				/*ImGui::Text("Sending to host %s", mSDASettings->mOSCDestinationHost.c_str());
				ImGui::SameLine();
				ImGui::Text(" on port %d", mSDASettings->mOSCDestinationPort);
				static char str0[128] = "/live/play";
				static int i0 = 0;
				static float f0 = 0.0f;
				ImGui::InputText("address", str0, IM_ARRAYSIZE(str0));
				ImGui::InputInt("track", &i0);
				ImGui::InputFloat("clip", &f0, 0.01f, 1.0f);
				if (ImGui::Button("Send")) { mSDASession->sendOSCIntMessage(str0, i0); }*/
			}
			else {
				ImGui::Text(" Receiving on port %d", mSDASettings->mOSCReceiverPort);
			}
		}
		else {
			ImGui::Text("OSC disabled");

			if (mSDASettings->mIsOSCSender) {
				if (ImGui::Button("sender->receiver"))
				{
					mSDASettings->mIsOSCSender = false;
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Change to a OSC receiver");

				static char host[128] = "127.0.0.1";
				std::copy(mSDASettings->mOSCDestinationHost.begin(), (mSDASettings->mOSCDestinationHost.size() >= 128 ? mSDASettings->mOSCDestinationHost.begin() + 128 : mSDASettings->mOSCDestinationHost.end()), host);
				static int senderPort = mSDASettings->mOSCDestinationPort;
				ImGui::InputText("destination address", host, IM_ARRAYSIZE(host));
				if (ImGui::InputInt("destination port", &senderPort)) mSDASettings->mOSCDestinationPort = senderPort;
			}
			else {
				if (ImGui::Button("receiver->sender"))
				{
					mSDASettings->mIsOSCSender = true;
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Change to a OSC sender");

				static int receiverPort = mSDASettings->mOSCReceiverPort;
				if (ImGui::InputInt("receiver port", &receiverPort)) mSDASettings->mOSCReceiverPort = receiverPort;
			}
			if (ImGui::Button("Enable"))
			{
				mSDASettings->mOSCEnabled = true;
				/*if (mSDASettings->mIsOSCSender) {
					mSDASession->setupOSCSender();
				}
				else {
					mSDASession->setupOSCReceiver();
				}*/
			}
		}
		ImGui::Text(">%s", mSDASettings->mOSCMsg.c_str());

		/* TODO if useful ImGui::Text("Sending to 2nd host %s", mSDASettings->mOSCDestinationHost2.c_str());
		ImGui::SameLine();
		ImGui::Text(" on port %d", mSDASettings->mOSCDestinationPort2);*/
	}
	ImGui::End();
}
