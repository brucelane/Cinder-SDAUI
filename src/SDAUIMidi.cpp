#include "SDAUIMidi.h"

using namespace SophiaDigitalArt;

SDAUIMidi::SDAUIMidi(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUIMidi::~SDAUIMidi() {

}

void SDAUIMidi::Run(const char* title) {
#if defined( CINDER_MSW )
	ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW, mSDASettings->uiLargeH/2), ImGuiSetCond_Once);
	ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiMargin, mSDASettings->uiYPosRow2 + mSDASettings->uiMargin + mSDASettings->uiLargeH / 2 ), ImGuiSetCond_Once);

	ImGui::Begin("MIDI");
	{
		sprintf(buf, "Enable");
		if (ImGui::Button(buf)) mSDASession->midiSetup();
		if (ImGui::CollapsingHeader("MidiIn", "20", true, true))
		{
			ImGui::Columns(2, "datain", true);
			ImGui::Text("Name"); ImGui::NextColumn();
			ImGui::Text("Connect"); ImGui::NextColumn();
			ImGui::Separator();
			for (int i = 0; i < mSDASession->getMidiInPortsCount(); i++)
			{
				if (mSDASession->getMidiInPortName(i) != "Ableton Push 2 1") {
					ImGui::Text(mSDASession->getMidiInPortName(i).c_str()); ImGui::NextColumn();

					if (mSDASession->isMidiInConnected(i))
					{
						sprintf(buf, "Disconnect %d", i);
					}
					else
					{
						sprintf(buf, "Connect %d", i);
					}

					if (ImGui::Button(buf))
					{
						if (mSDASession->isMidiInConnected(i))
						{
							mSDASession->closeMidiInPort(i);
						}
						else
						{
							mSDASession->openMidiInPort(i);
						}
					}
					ImGui::NextColumn();
					ImGui::Separator();
				}
			}
			ImGui::Columns(1);
		}
		// Midi out
		if (ImGui::CollapsingHeader("MidiOut", "20", true, true))
		{
			ImGui::Columns(2, "dataout", true);
			ImGui::Text("Name"); ImGui::NextColumn();
			ImGui::Text("Connect"); ImGui::NextColumn();
			ImGui::Separator();
			for (int i = 0; i < mSDASession->getMidiOutPortsCount(); i++)
			{
				ImGui::Text(mSDASession->getMidiOutPortName(i).c_str()); ImGui::NextColumn();

				if (mSDASession->isMidiOutConnected(i))
				{
					sprintf(buf, "Disconnect  %d", i);
				}
				else
				{
					sprintf(buf, "Connect  %d", i);
				}

				if (ImGui::Button(buf))
				{
					if (mSDASession->isMidiOutConnected(i))
					{
						mSDASession->closeMidiOutPort(i);
					}
					else
					{
						mSDASession->openMidiOutPort(i);
					}
				}
				ImGui::NextColumn();
				ImGui::Separator();
			}
			ImGui::Columns(1);
		}
		ImGui::TextWrapped(">%s", mSDASettings->mMidiMsg.c_str());
	}
	ImGui::End();
#endif
}
