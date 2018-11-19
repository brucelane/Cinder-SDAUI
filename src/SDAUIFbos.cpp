#include "SDAUIFbos.h"

using namespace SophiaDigitalArt;

SDAUIFbos::SDAUIFbos(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
}

void SDAUIFbos::Run(const char* title) {

	/*
	** textures
	*/
	static int XLeft[64];
	static int YTop[64];
	static int XRight[64];
	static int YBottom[64];
	static bool rnd[64];
	static bool anim[64];
	/*
	for (int t = 0; t < mSDASession->getInputTexturesCount(); t++) {
		xPos = mSDASettings->uiMargin + mSDASettings->uiXPosCol1 + ((mSDASettings->uiLargePreviewW + mSDASettings->uiMargin) * t);
		yPos = mSDASettings->uiYPosRow2;

		ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiLargePreviewH), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
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

			//for (unsigned int f = 0; f < mSDAMix->getWarpCount(); f++) {
			//if (f > 0) ImGui::SameLine();
			////int ti = mSDAMix->getFboInputTextureIndex(f);
			////CI_LOG_V("fbo" + toString(f) + " t" + toString(t) + " ti" + toString(ti));
			//if (mSDAMix->getWarpATextureIndex(f) == t) {
			//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 1.0f, 1.0f));
			//}
			//else {
			//ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 0.1f, 0.1f));
			//}
			//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(t / 7.0f, 0.7f, 0.7f));
			//ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(t / 7.0f, 0.8f, 0.8f));
			//sprintf(buf, "%d##fboinputtex%d%d", f, t, f);
			//if (ImGui::Button(buf)) mSDAMix->setFboInputTexture(f, t);
			//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set input texture for warp");
			//ImGui::PopStyleColor(3);
			//}

			//sprintf(buf, "WS##s%d", i);
			//if (ImGui::Button(buf))
			//{
			//sprintf(buf, "IMG=%d.jpg", i);
			////mSDARouter->wsWrite(buf);
			//}
			//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Send texture file name via WebSockets");
			//

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
				if (ImGui::SliderFloat(buf, &speeds[t], 0.0f, 1.0f))
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
	*/

#pragma region mix
int w = 0;
xPos = mSDASettings->uiMargin + mSDASettings->uiXPosCol1;
yPos = mSDASettings->uiYPosRow3;// - mSDASettings->uiLargePreviewH

ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiLargePreviewH), ImGuiSetCond_Once);
ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);

sprintf(buf, "%s##sh%d", "mix", 0);
ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
{
	ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
	ImGui::Image((void*)mSDASession->getMixTexture(w)->getId(), ivec2(mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight));
	// crossfade
	float xFade = mSDASession->getCrossfade();// getWarpCrossfade(w);
	sprintf(buf, "xfade##xf%d", w);
	if (ImGui::SliderFloat(buf, &xFade, 0.0f, 1.0f))
	{
		mSDASession->setCrossfade(xFade);
	}
	ImGui::PopItemWidth();
}
ImGui::End();
#pragma endregion mix
#pragma region fbos

	/*
	** fbos
	*/
	for (unsigned int f = 0; f < 2; f++) {//mSDASession->getFboListSize()
		xPos = mSDASettings->uiMargin + mSDASettings->uiXPosCol1 + ((mSDASettings->uiLargePreviewW + mSDASettings->uiMargin) * (f+1));
		yPos = mSDASettings->uiYPosRow3;
		ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiLargePreviewH), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
		sprintf(buf, "%s##fbolbl%d", mSDASession->getFboName(f).c_str(), f);
		ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::PushID(f);
			ImGui::Image((void*)mSDASession->getFboRenderedTexture(f)->getId(), ivec2(mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight));
			// causes loss of resolution: 
			//if (ImGui::IsItemHovered()) mSDASession->getFboTexture(f);
			for (unsigned int t = 0; t < mSDASession->getInputTexturesCount(); t++) {
				if (t > 0 && (t % 6 != 0)) ImGui::SameLine();
				if (mSDASession->getFboInputTextureIndex(f) == t) {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 1.0f, 1.0f));
				}
				else {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(t / 7.0f, 0.1f, 0.1f));
				}
				sprintf(buf, "%d##fboit%d%d", t, f, t);
				if (ImGui::Button(buf)) mSDASession->setFboInputTexture(f, t);

				sprintf(buf, "Set input texture to %s", mSDASession->getInputTextureName(t).c_str());
				if (ImGui::IsItemHovered()) ImGui::SetTooltip(buf);
				ImGui::PopStyleColor(1);
			}
			if (mSDASession->isFboFlipV(f)) {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(f / 7.0f, 1.0f, 1.0f));
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(f / 7.0f, 0.1f, 0.1f));
			}
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(f / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(f / 7.0f, 0.8f, 0.8f));
			sprintf(buf, "FlipV##fboflipv%d", f);
			if (ImGui::Button(buf)) mSDASession->fboFlipV(f);
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			sprintf(buf, "T##fboupd%d", f);
			if (ImGui::Button(buf)) mSDASession->updateShaderThumbFile(f);
			ImGui::Text("wh %dx%d", mSDASession->getFboRenderedTexture(f)->getWidth(), mSDASession->getFboRenderedTexture(f)->getHeight());
			ImGui::PopID();
		}
		ImGui::End();
	}
	
#pragma endregion fbos

}
