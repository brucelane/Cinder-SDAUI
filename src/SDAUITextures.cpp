#include "SDAUITextures.h"

using namespace SophiaDigitalArt;

SDAUITextures::SDAUITextures(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}
SDAUITextures::~SDAUITextures() {

}

void SDAUITextures::Run(const char* title) {

	static int XLeft[64];
	static int YTop[64];
	static int XRight[64];
	static int YBottom[64];
	static bool rnd[64];
	static bool anim[64];

	for (int t = 0; t < mSDASession->getInputTexturesCount(); t++) {
		ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiLargePreviewH), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2((t * (mSDASettings->uiLargePreviewW + mSDASettings->uiMargin)) + mSDASettings->uiMargin, mSDASettings->uiYPosRow3), ImGuiSetCond_Once);
		int hue = 0;
		sprintf(buf, "%s##s%d", mSDASession->getInputTextureName(t).c_str(), t);
		ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
			ImGui::PushID(t);
			ImGui::Image((void*)mSDASession->getInputTexture(t)->getId(), ivec2(mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight));
			ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth * 0.7);
			// flip vertically
			mSDASession->isFlipVInputTexture(t) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			sprintf(buf, "FlipV##vd%d", t);
			if (ImGui::Button(buf)) {
				mSDASession->inputTextureFlipV(t);
			}
			ImGui::PopStyleColor(3);
			hue++;
			ImGui::SameLine();
			// flip horizontally
			mSDASession->isFlipHInputTexture(t) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
			sprintf(buf, "FlipH##hd%d", t);
			if (ImGui::Button(buf)) {
				mSDASession->inputTextureFlipH(t);
			}
			ImGui::PopStyleColor(3);
			hue++;

			/* obsolete? 
			for (unsigned int f = 0; f < mSDAMix->getWarpCount(); f++) {
				if (f > 0) ImGui::SameLine();
				//int ti = mSDAMix->getFboInputTextureIndex(f);
				//CI_LOG_V("fbo" + toString(f) + " t" + toString(t) + " ti" + toString(ti));
				if (mSDAMix->getWarpATextureIndex(f) == t) {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 1.0f, 1.0f));
				}
				else {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 0.1f, 0.1f));
				}
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(t / 7.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(t / 7.0f, 0.8f, 0.8f));
				sprintf(buf, "%d##fboinputtex%d%d", f, t, f);
				if (ImGui::Button(buf)) mSDAMix->setFboInputTexture(f, t);
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set input texture for warp");
				ImGui::PopStyleColor(3);
			}

			sprintf(buf, "WS##s%d", i);
			if (ImGui::Button(buf))
			{
			sprintf(buf, "IMG=%d.jpg", i);
			//mSDARouter->wsWrite(buf);
			}
			if (ImGui::IsItemHovered()) ImGui::SetTooltip("Send texture file name via WebSockets");
			*/
			
			if (mSDASession->isSequence(t) || mSDASession->isMovie(t)) {
				sprintf(buf, "p##s%d", t);
				if (ImGui::Button(buf))
				{
					mSDASession->togglePlayPause(t);
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Play/Pause");
			}
			if (mSDASession->isSequence(t)) {
				ImGui::SameLine();
				sprintf(buf, "b##sqs%d", t);
				if (ImGui::Button(buf))
				{
					mSDASession->syncToBeat(t);
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Sync to beat");

				ImGui::SameLine();
				sprintf(buf, "r##rs%d", t);
				if (ImGui::Button(buf))
				{
					mSDASession->reverse(t);
				}
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Reverse");

				if (mSDASession->isLoadingFromDisk(t)) {
					ImGui::SameLine();
					sprintf(buf, "l##ts%d", t);
					if (ImGui::Button(buf))
					{
						mSDASession->toggleLoadingFromDisk(t);
					}
					if (ImGui::IsItemHovered()) ImGui::SetTooltip("Pause loading from disk");
				}
				speeds[t] = mSDASession->getSpeed(t);
				sprintf(buf, "speed##spd%d", t);
				if (ImGui::DragFloat(buf, &speeds[t], 0.01f, 0.0f, 1.0f))
				{
					mSDASession->setSpeed(t, speeds[t]);
				}

				playheadPositions[t] = mSDASession->getPosition(t);
				sprintf(buf, "scrub##srb%d", t);
				if (ImGui::SliderInt(buf, &playheadPositions[t], 0, mSDASession->getMaxFrame(t)))
				{
					mSDASession->setPlayheadPosition(t, playheadPositions[t]);
				}


			}
			else {
				if (!mSDASession->isMovie(t)) {
					// not a sequence nor video, animate x y...
					XLeft[t] = mSDASession->getInputTextureXLeft(t);
					if (anim[t]) {
						if (rnd[t]) {
							XLeft[t] += xStep * Rand::randBool();
						}
						else {
							XLeft[t] += xStep;
						}
						// check bounds 
						if (XLeft[t] < 1) {
							xStep = -xStep;
						}
						if (XLeft[t] > mSDASession->getInputTextureOriginalWidth(t) - mSDASettings->mFboWidth - 1) {
							xStep = -xStep;
						}
					}
					sprintf(buf, "XL##xl%d", t);
					ImGui::SliderInt(buf, &XLeft[t], 0, mSDASession->getInputTextureOriginalWidth(t));// CHECK - mSDASettings->mFboWidth
					mSDASession->setInputTextureXLeft(t, XLeft[t]);

					YTop[t] = mSDASession->getInputTextureYTop(t);
					if (anim[t]) {
						if (rnd[t]) {
							YTop[t] += yStep * Rand::randBool();
						}
						else {
							YTop[t] += yStep;
						}
						// check bounds
						if (YTop[t] < 1) {
							yStep = -yStep;
						}
						if (YTop[t] > mSDASession->getInputTextureOriginalHeight(t) - mSDASettings->mFboHeight - 1) {
							yStep = -yStep;
						}
					}
					sprintf(buf, "YT##yt%d", t);
					ImGui::SliderInt(buf, &YTop[t], 0, mSDASession->getInputTextureOriginalHeight(t));// - mSDASettings->mFboHeight
					mSDASession->setInputTextureYTop(t, YTop[t]);


					ImGui::SameLine();
					(mSDASession->getInputTextureLockBounds(t)) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
					sprintf(buf, "8##lk%d", t);
					if (ImGui::Button(buf)) {
						mSDASession->toggleInputTextureLockBounds(t);
					}
					ImGui::PopStyleColor(3);
					hue++;

					XRight[t] = mSDASession->getInputTextureXRight(t);
					sprintf(buf, "XR##xr%d", t);
					if (ImGui::SliderInt(buf, &XRight[t], 0, mSDASession->getInputTextureOriginalWidth(t))) {
						mSDASession->setInputTextureXRight(t, XRight[t]);
					}
					ImGui::SameLine();
					(anim[t]) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
					sprintf(buf, "ani##r%d", t);
					anim[t] ^= ImGui::Button(buf);
					ImGui::PopStyleColor(3);
					hue++;

					YBottom[t] = mSDASession->getInputTextureYBottom(t);
					sprintf(buf, "YB##yb%d", t);
					if (ImGui::SliderInt(buf, &YBottom[t], 0, mSDASession->getInputTextureOriginalHeight(t))) {
						mSDASession->setInputTextureYBottom(t, YBottom[t]);
					}

					ImGui::SameLine();
					(rnd[t]) ? ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue / 7.0f, 1.0f, 0.5f)) : ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.1f, 0.1f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue / 7.0f, 0.7f, 0.7f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue / 7.0f, 0.8f, 0.8f));
					sprintf(buf, "rnd##r%d", t);
					rnd[t] ^= ImGui::Button(buf);
					ImGui::PopStyleColor(3);
					hue++;
				}
			}
			ImGui::PopItemWidth();
			ImGui::PopID();
			ImGui::PopItemWidth();
		}
		ImGui::End();
	}

}
