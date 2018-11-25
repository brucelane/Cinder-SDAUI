#include "SDAUIShaders.h"

using namespace SophiaDigitalArt;

SDAUIShaders::SDAUIShaders(SDASettingsRef aSDASettings, SDASessionRef aSDASession) {
	mSDASettings = aSDASettings;
	mSDASettings = aSDASettings;
	mSDASession = aSDASession;
	try
	{
		fs::path vertexFile = getAssetPath("") / "passthru.vert";
		if (fs::exists(vertexFile)) {
			mPassthruVextexShaderString = loadString(loadAsset("passthru.vert"));
			CI_LOG_V("passthru.vert loaded");
		}
		else
		{
			CI_LOG_V("passthru.vert does not exist, should quit");
		}
	}
	catch (gl::GlslProgCompileExc &exc)
	{
		mError = string(exc.what());
		CI_LOG_V("unable to load passthru vertex shader file:" + string(exc.what()));
	}
	catch (const std::exception &e)
	{
		mError = string(e.what());
		CI_LOG_V("unable to load passthru vertex shader:" + string(e.what()));
	}
}
SDAUIShaders::~SDAUIShaders() {

}

void SDAUIShaders::Run(const char* title) {
	static int shaderToEdit = -1;

	xPos = mSDASettings->uiMargin;
	yPos = mSDASettings->uiYPosRow4;
	for (int s = 0; s < mSDASession->getShadersCount(); s++) {
		//ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiLargePreviewH), ImGuiSetCond_Once);
		//ImGui::SetNextWindowPos(ImVec2((t * (mSDASettings->uiLargePreviewW + mSDASettings->uiMargin)) + mSDASettings->uiMargin + mSDASettings->uiXPosCol1, mSDASettings->uiYPosRow2), ImGuiSetCond_Once);

		ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargePreviewW, mSDASettings->uiLargePreviewH), ImGuiSetCond_Once);
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiSetCond_Once);
		//int hue = 0;
		sprintf(buf, "%s##sh%d", mSDASession->getShaderName(s).c_str(), s);
		ImGui::Begin(buf, NULL, ImVec2(0, 0), ImGui::GetStyle().Alpha, ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::PushItemWidth(mSDASettings->mPreviewFboWidth);
			ImGui::PushID(s);
			ImGui::Image((void*)mSDASession->getShaderThumb(s)->getId(), ivec2(mSDASettings->mPreviewFboWidth, mSDASettings->mPreviewFboHeight));
			if (ImGui::IsItemHovered()) mSDASession->getShaderThumb(s);
			// edit
			if (shaderToEdit == s) {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.8f, 1.0f, 0.5f));
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
			}
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.8f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.8f, 0.8f, 0.8f));
			sprintf(buf, "E##se%d", s);
			if (ImGui::Button(buf)){
				if (s == shaderToEdit) {
					// if the same button pressed we hide the editor
					shaderToEdit = -1;
				}
				else{
					shaderToEdit = s;
				}
			}
			ImGui::PopStyleColor(3);
			if (ImGui::IsItemHovered()) ImGui::SetTooltip("Edit shader");
			ImGui::SameLine();

			if (s > 2)
			{
				sprintf(buf, "X##del%d", s);
				if (ImGui::Button(buf)) mSDASession->removeShader(s);
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Remove shader");
				ImGui::SameLine();
			}

			// thumb
			sprintf(buf, "T##st%d", s);
			if (ImGui::Button(buf)){
				mSDASession->updateShaderThumbFile(s);
			}
			if (ImGui::IsItemHovered()) ImGui::SetTooltip("Create thumb");
			ImGui::SameLine();

            // send with websocket
			sprintf(buf, "WS##ws%d", s);
			if (ImGui::Button(buf)) mSDASession->sendFragmentShader(s);

			for (unsigned int f = 0; f < 4; f++) {//mSDASession->getFboListSize()
				if (f > 0 && (f % 6 != 0)) ImGui::SameLine();
				if (mSDASession->getFboFragmentShaderIndex(f) == s) {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 1.0f, 0.5f));
				}
				else {
					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.0f, 0.1f, 0.1f));
				}
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.0f, 0.7f, 0.7f));
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.0f, 0.8f, 0.8f));
				sprintf(buf, "%d##sf%d", f, s);
				if (ImGui::Button(buf)) mSDASession->setFboFragmentShaderIndex(f, s);
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("Set shader to fbo");
				ImGui::PopStyleColor(3);
			}
			ImGui::PopID();
			ImGui::PopItemWidth();
		}
		ImGui::End();
		xPos += mSDASettings->uiLargePreviewW + mSDASettings->uiMargin;
		if (xPos > mSDASettings->mRenderWidth + mSDASettings->uiLargePreviewW)
		{
			xPos = mSDASettings->uiMargin;
			yPos += mSDASettings->uiLargePreviewH + mSDASettings->uiMargin;
		}
		// editor
#pragma region Editor
		if (shaderToEdit == s) {
			mSDASettings->mMsg = "Editing shader " + toString(shaderToEdit) + " name " + mSDASession->getShaderName(shaderToEdit);
			ImGui::SetNextWindowPos(ImVec2(mSDASettings->uiXPosCol2, mSDASettings->uiYPosRow2), ImGuiSetCond_Once);
			ImGui::SetNextWindowSize(ImVec2(mSDASettings->uiLargeW * 3, mSDASettings->uiLargeH), ImGuiSetCond_FirstUseEver);
			sprintf(buf, "Editor - %s - %d##edit%d", mSDASession->getShaderName(shaderToEdit).c_str(), shaderToEdit, shaderToEdit);
			ImGui::Begin(buf);
			{
				size_t const MAX = 32768; // maximum number of chars
				static char mShaderText[MAX] =
					"uniform vec3 iResolution;\n"
					"uniform vec3 iColor;\n"
					"uniform float iTime;\n"
					"uniform sampler2D iChannel0;\n"
					"uniform sampler2D iChannel1;\n"
					"uniform sampler2D iChannel2;\n"
					"uniform vec3 spectrum;\n"
					"\n"
					"out vec4 oColor;\n"
					"void main(void) {\n"
					"\tvec2 uv = gl_FragCoord.xy / iResolution.xy;\n"
					"\tvec4 t0 = texture(iChannel0, uv);\n"
					"\tvec4 t1 = texture(iChannel1, uv);\n"
					"\tvec4 t2 = texture(iChannel2, uv);\n"
					"\toColor = vec4(t0.x, t1.y, cos(iTime), 1.0);\n"
					"}\n";
				// check if shader text needs to be loaded in the editor
				if (mSDASettings->shaderEditIndex != shaderToEdit) {
					/* ptr error
					
					mFboTextureFragmentShaderString = mSDASession->getFragmentShaderString(shaderToEdit);
					mSDASettings->shaderEditIndex = shaderToEdit;
					// delete content
					memset(&mShaderText[0], 0, sizeof(mShaderText));
					// copy content from string
					std::copy(mFboTextureFragmentShaderString.begin(), (mFboTextureFragmentShaderString.size() >= MAX ? mFboTextureFragmentShaderString.begin() + MAX : mFboTextureFragmentShaderString.end()), mShaderText);
				*/
				}

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
				ImGui::PopStyleVar();
				ImGui::TextColored(ImColor(255, 0, 0), mError.c_str());
				//ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "uniform");
				sprintf(buf, "Src - %s##src%d", mSDASession->getShaderName(shaderToEdit).c_str(), shaderToEdit);
				if (ImGui::InputTextMultiline(buf, mShaderText, IM_ARRAYSIZE(mShaderText), ImVec2(-1.0f, -1.0f), ImGuiInputTextFlags_AllowTabInput)) {
					// text changed // TODO height ? mSDASettings->uiYPosRow2 - 200.0f
					CI_LOG_V("text changed");
					try
					{
						aShader = gl::GlslProg::create(mPassthruVextexShaderString, mShaderText);
						// 20161209 problem on Mac aShader->setLabel("live");
						CI_LOG_V("live.frag loaded and compiled");
						mFboTextureFragmentShaderString = mShaderText;
						stringstream sParams;
						sParams << "/*{ \"title\" : \"" << getElapsedSeconds() << "\" }*/ " << mFboTextureFragmentShaderString;
						mSDASession->wsWrite(sParams.str());
						//OK mSDARouter->wsWrite("/*{ \"title\" : \"live\" }*/ " + mFboTextureFragmentShaderString);
						mError = "";
						// compiles, update the shader for display
						mSDASession->setFragmentShaderString(shaderToEdit, mFboTextureFragmentShaderString);
					}
					catch (gl::GlslProgCompileExc &exc)
					{
						mError = string(exc.what());
						CI_LOG_V("unable to load/compile live fragment shader:" + string(exc.what()));
					}
					catch (const std::exception &e)
					{
						mError = string(e.what());
						CI_LOG_V("unable to load live fragment shader:" + string(e.what()));
					}
				}
				else {
					// nothing changed 
				}
			}
			ImGui::End();
		}
#pragma endregion Editor
	}

}
