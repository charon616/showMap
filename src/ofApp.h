#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Work.hpp"
#include "ofxGui.h"
#include "ofxChromaKey.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void mousePressed(int x, int y, int button);
    
        void playSound();
        void stopSound();
    
        ofVideoGrabber cam;
        ofVideoPlayer vidPlayer;
    
        ofxCv::ObjectFinder finder;
        ofTrueTypeFont din, din_m;
    
        Work** works; //作品ごとのインスタンスを生成
    
        ofImage s1, s2;
    
        ofImage camDraw;
        ofParameter<float> camThresholdValue;
    
        ofImage image, imageMask;
        ofShader shader;
        ofFbo fbo;
        ofxChromaKey chromaKey;
    
        ofSoundPlayer  open;

};
