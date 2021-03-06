/*
 Copyright (c) 2013-2020, Bruce Lane - All rights reserved.
 This code is intended for use with the Cinder C++ library: http://libcinder.org

 Using Cinder-Warping from Paul Houx.

 Cinder-Warping is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Cinder-Warping is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Cinder-Warping.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// Animation
#include "VDAnimation.h"
// Session Facade
#include "VDSessionFacade.h"
// Spout
#include "CiSpoutOut.h"
// Video
//#include "ciWMFVideoPlayer.h"

// UI
#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS 1
#include "VDUI.h"
#define IM_ARRAYSIZE(_ARR)			((int)(sizeof(_ARR)/sizeof(*_ARR)))
using namespace ci;
using namespace ci::app;
using namespace videodromm;

class _TBOX_PREFIX_App : public App {
public:
	_TBOX_PREFIX_App();
	void cleanup() override;
	void update() override;
	void draw() override;
	void resize() override;
	void mouseMove(MouseEvent event) override;
	void mouseDown(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void fileDrop(FileDropEvent event) override;
private:
	// Settings
	VDSettingsRef					mVDSettings;
	// Animation
	VDAnimationRef					mVDAnimation;
	// Session
	VDSessionFacadeRef				mVDSessionFacade;
	// UI
	VDUIRef							mVDUI;
	// video
	/*ciWMFVideoPlayer				mVideo;
	float							mVideoPos;
	float							mVideoDuration;
	bool							mIsVideoLoaded;*/

	bool							mFadeInDelay = true;
	void							toggleCursorVisibility(bool visible);
	SpoutOut 						mSpoutOut;
};


_TBOX_PREFIX_App::_TBOX_PREFIX_App() : mSpoutOut("VDUI", app::getWindowSize())
{

	// Settings
	mVDSettings = VDSettings::create("VDUI");
	// Animation
	mVDAnimation = VDAnimation::create(mVDSettings);
	// Session
	mVDSessionFacade = VDSessionFacade::createVDSession(mVDSettings, mVDAnimation)
		->setUniformValue(mVDSettings->IBPM, 160.0f)
		->setUniformValue(mVDSettings->IMOUSEX, 0.27710f)
		->setUniformValue(mVDSettings->IMOUSEY, 0.5648f)
		->setMode(8)
		->loadFromJsonFile("fbo0.json")
		->loadFromJsonFile("fbo1.json")
		//->setupOSCReceiver()
		//->addOSCObserver(mVDSettings->mOSCDestinationHost, mVDSettings->mOSCDestinationPort)
		->addUIObserver(mVDSettings, mVDAnimation)
		->toggleValue(mVDSettings->IFLIPV);

	// sos only mVDSession->setUniformValue(mVDSettings->IEXPOSURE, 1.93f);
	mFadeInDelay = true;
	// UI
	ImGui::Initialize();
	mVDUI = VDUI::create(mVDSettings, mVDSessionFacade);
	/*fs::path texFileOrPath = getAssetPath("") / mVDSettings->mAssetsPath / "accueil.mp4";
	if (fs::exists(texFileOrPath)) {
		string ext = "";
		int dotIndex = texFileOrPath.filename().string().find_last_of(".");
		if (dotIndex != std::string::npos) ext = texFileOrPath.filename().string().substr(dotIndex + 1);
		if (ext == "mp4" || ext == "wmv" || ext == "avi" || ext == "mov") {
			if (!mVideo.isStopped()) {
				mVideo.stop();
			}

			mIsVideoLoaded = mVideo.loadMovie(texFileOrPath);

			mVideoDuration = mVideo.getDuration();
			mVideoPos = mVideo.getPosition();
			mVideo.play();

		}
	}*/
}

void _TBOX_PREFIX_App::toggleCursorVisibility(bool visible)
{
	if (visible)
	{
		showCursor();
	}
	else
	{
		hideCursor();
	}
}

void _TBOX_PREFIX_App::fileDrop(FileDropEvent event)
{
	mVDSession->fileDrop(event);
}

void _TBOX_PREFIX_App::mouseMove(MouseEvent event)
{
	if (!mVDSession->handleMouseMove(event)) {

	}
}

void _TBOX_PREFIX_App::mouseDown(MouseEvent event)
{

	if (!mVDSession->handleMouseDown(event)) {

	}
}

void _TBOX_PREFIX_App::mouseDrag(MouseEvent event)
{

	if (!mVDSession->handleMouseDrag(event)) {

	}
}

void _TBOX_PREFIX_App::mouseUp(MouseEvent event)
{

	if (!mVDSession->handleMouseUp(event)) {

	}
}

void _TBOX_PREFIX_App::keyDown(KeyEvent event)
{

	// warp editor did not handle the key, so handle it here
	if (!mVDSession->handleKeyDown(event)) {
		switch (event.getCode()) {
		case KeyEvent::KEY_F12:
			// quit the application
			quit();
			break;
		case KeyEvent::KEY_f:
			// toggle full screen
			setFullScreen(!isFullScreen());
			break;

		case KeyEvent::KEY_l:
			mVDSession->createWarp();
			break;
		}
	}
}

void _TBOX_PREFIX_App::keyUp(KeyEvent event)
{

	// let your application perform its keyUp handling here
	if (!mVDSession->handleKeyUp(event)) {
		/*switch (event.getCode()) {
		default:
			CI_LOG_V("main keyup: " + toString(event.getCode()));
			break;
		}*/
	}
}
void _TBOX_PREFIX_App::cleanup()
{
	CI_LOG_V("cleanup and save");
	ui::Shutdown();

	mVDSettings->save();
	CI_LOG_V("quit");
}

void _TBOX_PREFIX_App::update()
{
	switch (mVDSession->getCmd()) {
	case 0:
		//createControlWindow();
		break;
	case 1:
		//deleteControlWindows();
		break;
	}
	mVDSessionFacade->setUniformValue(mVDSettings->IFPS, getAverageFps());
	mVDSessionFacade->update();
	/*mVideo.update();
	mVideoPos = mVideo.getPosition();
	if (mVideo.isStopped() || mVideo.isPaused()) {
		mVideo.setPosition(0.0);
		mVideo.play();
	}*/
}


void _TBOX_PREFIX_App::resize()
{
	mVDUI->resize();
}
void _TBOX_PREFIX_App::draw()
{
	// clear the window and set the drawing color to black
	gl::clear();
	gl::color(Color::white());
	if (mFadeInDelay) {
		mVDSettings->iAlpha = 0.0f;
		if (getElapsedFrames() > 10.0) {// mVDSession->getFadeInDelay()) {
			mFadeInDelay = false;
			timeline().apply(&mVDSettings->iAlpha, 0.0f, 1.0f, 1.5f, EaseInCubic());
		}
	}
	else {
		gl::setMatricesWindow(mVDSettings->mFboWidth, mVDSettings->mFboHeight, false);
		//gl::setMatricesWindow(mVDSession->getIntUniformValueByIndex(mVDSettings->IOUTW), mVDSession->getIntUniformValueByIndex(mVDSettings->IOUTH), true);
		/*int m = mVDSession->getMode();
		if (m < mVDSession->getModesCount() && m < mVDSession->getFboListSize()) {
			gl::draw(mVDSession->getFboTexture(m), Area(0, 0, mVDSettings->mFboWidth, mVDSettings->mFboHeight));
			//mSpoutOut.sendTexture(mVDSession->getFboRenderedTexture(m));
		}
		else {
			gl::draw(mVDSession->getPostFboTexture(), Area(0, 0, mVDSettings->mFboWidth, mVDSettings->mFboHeight));
			//gl::draw(mVDSession->getRenderedMixetteTexture(0), Area(0, 0, mVDSettings->mFboWidth, mVDSettings->mFboHeight));
			// ok gl::draw(mVDSession->getWarpFboTexture(), Area(0, 0, mVDSettings->mFboWidth, mVDSettings->mFboHeight));//getWindowBounds()
			//mSpoutOut.sendTexture(mVDSession->getRenderedMixetteTexture(0));
		}
		gl::draw(mVDSessionFacade->buildFboTexture(0), Area(0, 0, mVDSettings->mFboWidth, mVDSettings->mFboHeight));
		*/
		gl::draw(mVDSessionFacade->buildRenderedMixetteTexture(0), Area(50, 50, mVDSettings->mFboWidth, mVDSettings->mFboHeight));

		/*vec2 videoSize = vec2(mVideo.getWidth(), mVideo.getHeight());
		mGlslVideoTexture->uniform("uVideoSize", videoSize);
		videoSize *= 0.25f;
		videoSize *= 0.5f;
		ciWMFVideoPlayer::ScopedVideoTextureBind scopedVideoTex(mVideo, 0);
		gl::scale(vec3(videoSize, 1.0f));*/

		//gl::draw(mPostFbo->getColorTexture());
		//gl::draw(mVDSession->getFboRenderedTexture(0));
	}
	// Spout Send
	// KO mSpoutOut.sendViewport();
	// OK
	 mSpoutOut.sendTexture(mVDSession->getFboRenderedTexture(1));

	// imgui
	if (mVDSession->showUI()) {
		mVDUI->Run("UI", (int)getAverageFps());
		if (mVDUI->isReady()) {
		}
	}
	getWindow()->setTitle(mVDSettings->sFps + " fps");
}
void prepareSettings(App::Settings *settings)
{
	settings->setWindowSize(1280, 720);
}
CINDER_APP(_TBOX_PREFIX_App, RendererGl(RendererGl::Options().msaa(8)),  prepareSettings)
