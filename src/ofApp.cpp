#include "ofApp.h"
#include <stdio.h>
#include <time.h>
#include <iostream>

//#define _USE_WEB_CAMERA

using namespace ofxCv;
using namespace cv;
using namespace std;

int mode = 10000;
float increment = 0.02;
float pasttime = -90;
ofColor c = ofColor(0);
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    //webカメラを自動的に選択
    #ifdef _USE_WEB_CAMERA
        if(cam.isInitialized() == false){
            cout << "Initalizing cam" << endl;
            int index = 0;
            vector<ofVideoDevice> devices = cam.listDevices();
            for(int i=0; i<devices.size(); i++){
                ofVideoDevice& device = devices.at(i);
                cout << i  << ":" << device.deviceName << ":" << endl;
                if(device.deviceName.find("C922") != std::string::npos){
                    index = i;
                }
            }
            cam.setDeviceID(index);
        }
    #else
        cam.setDeviceID(0);
    #endif
    cam.setup(640, 480);
    
    // Video
    vidPlayer.load("fingers.mov");
    //video.setLoopState(OF_LOOP_NORMAL);
    
    // Fonts
    ofTrueTypeFont::setGlobalDpi(72);
    din.load("URWDIN-Bold", 64); // フォントのデータを指定する
    din.setLineHeight(80);       // 行間を指定する
    din.setLetterSpacing(1.1);   // 文字間を指定する
    
    din_m.load("URWDIN-Bold", 40); // フォントのデータを指定する
    din_m.setLineHeight(40);       // 行間を指定する
    din_m.setLetterSpacing(1.1);   // 文字間を指定する
    
    s1.load("bg.jpg");
    s1.resize(1280, 800);
    s2.load("map0703-03.png");
    s2.resize(1280, 800);
 
    works = new Work*[12];
    works[0] = new Work(236, 437, 171, 102, 5); //Claffin
    works[1] = new Work(592, 456, 136, 83, 4); //Picture
    works[2] = new Work(453, 390, 89, 149, 3); //MovingArrow
    works[3] = new Work(662, 559, 102, 75, 2); //Marbling
    works[4] = new Work(738, 456, 115, 83, 4); //Knocking
    works[5] = new Work(860, 501, 115, 115, 5); //Dandelion
    works[6] = new Work(846, 339, 129, 81, 2); //Window
    works[7] = new Work(628, 282, 161, 138, 4); //Chillout
    works[8] = new Work(453, 185, 154, 128, 2); //Moja
    works[9] = new Work(662, 171, 102, 75, 2); //Baby
    works[10] = new Work(669, 889, 164, 97, 3); //Map
    works[11] = new Work(821, 185, 154, 128, 5); //ShapeSense
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();

    shader.load("shader");
    this->image.load("test.jpg");
    this->image.resize(1280, 800);
    this->imageMask.load("noise.jpg");
    this->chromaKey.keyColor = ofColor(0, 0, 0);
    
    open.load("paper-round1.mp3");
    open.setVolume(0.75f);
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()) {
        //顔検出
        finder.update(cam);
        //輪郭検出
        convertColor(cam, camDraw, CV_RGB2GRAY); //2値化
        autothreshold(camDraw); //自動で閾値を設定したい時
        Canny(camDraw, camDraw, 50, 200, 3); //キャニーのエッジ検出
        camDraw.update();
    }
    ofSoundUpdate();
    
    vidPlayer.update();
    
    for(int i=0; i < 12; i++){
        works[i]->update();
    }
}

void showDateandTime(ofTrueTypeFont f1, ofTrueTypeFont f2);
int checkGaze(ofxCv::ObjectFinder& finder);
void drawMask(ofShader& shader, float& pasttime, ofxChromaKey& chromaKey, ofImage im, ofImage mask);
void deleteMask(ofShader& shader, float& pasttime, ofxChromaKey& chromaKey, ofImage im, ofImage mask);
void playSound();

int soundCount = 0;
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofBackground(255);
    
    s2.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    for(int i=0; i < 12; i++){
        works[i]->display();
    }
    
    ofDrawBitmapString(mode, 15,15);
    string mouse = to_string(ofGetMouseX()) + ":" + to_string(ofGetMouseY());
    ofDrawBitmapString(mouse,200,15);
    showDateandTime(din, din_m);
    
    mode = checkGaze(finder);

    if(mode == 0){
        drawMask(shader, pasttime, chromaKey, image, imageMask);
        ofDrawBitmapString("Why??",400,400);
    }else if(mode == 1){
        deleteMask(shader, pasttime, chromaKey, image, imageMask);
    }

//    if(pasttime == 90 || pasttime == -90){
//        playSound(soundCount);
//    }
    //ofSetColor(255);
    //vidPlayer.draw(0, 0);
}

void showDateandTime(ofTrueTypeFont f1, ofTrueTypeFont f2){
    int d = ofGetDay();
    //int mon = ofGetMonth();
    char* mon = "JULY";
    int year = ofGetYear();
    int s = ofGetSeconds();
    int m = ofGetMinutes();
    int h = ofGetHours();
    string ampm;
    if (h>11) {
        h=h-12;
        ampm="PM";
    }else {
        ampm="AM";
    }
    
    //String t = ("%d\n%d\n%d\n%02d:%02d:%02d\n%d\n",d, mon, year, h, m ,s);
    char t[100];
    sprintf(t,"%d\n%s\n%d\n%02d:%02d:%02d\n",d, mon, year, h, m ,s);
    string str = t + ampm;
    //String t = to_string(d) + "\n%02d" + to_string(m)on) + "\n" + to_string(year) + "\n"
    //+ to_string(h) + ":" + to_string(m) + ":" + to_string(s) + "\n" + ampm;
    
    ofSetColor(c);
    f1.drawString(str, 30, 80); // 文字とポジションを指定して描画
    f2.drawString("enact one's self", 950, 780); // 文字とポジションを指定して描画
}

int checkGaze(ofxCv::ObjectFinder& finder){
    if(finder.size() > 0){ return 1; }
    else{ return 0; }
}

void ofApp::playSound(){
    open.setLoop(false);
    open.play();
}

void ofApp::stopSound(){
    open.setLoop(false);
    open.stop();
}

bool once = false;

void drawMask(ofShader& shader, float& pasttime, ofxChromaKey& chromaKey, ofImage im, ofImage mask){
//    if(!once){
//        playSound();
//        once = true;
//    }
    //std::call_once(once, do_once);
    ofSetColor(0, 0, 0);
    float threshold = ofMap(pasttime, -90, 90, 0.0, 2.0);
    im.resize(ofGetWidth(), ofGetHeight());
    
    shader.begin();
    shader.setUniformTexture("tex", mask.getTexture(), 0);
    shader.setUniformTexture("tex_show", im.getTexture(), 1 );
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("threshold", threshold);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    if(pasttime < -90  ){ pasttime = -90; }
    pasttime -= 2;
    
    ofDrawBitmapString(pasttime, 15,30);
    
}

void deleteMask(ofShader& shader, float& pasttime, ofxChromaKey& chromaKey, ofImage im, ofImage mask){
    ofSetColor(0, 0, 0);
    float threshold = ofMap(pasttime, -90, 90, 0.0, 2.0);
    im.resize(ofGetWidth(), ofGetHeight());
    
    shader.begin();
    shader.setUniformTexture("tex", mask.getTexture(), 0);
    shader.setUniformTexture("tex_show", im.getTexture(), 1 );
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniform1f("threshold", threshold);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    
    if(pasttime > 90){ pasttime = 90; }
    pasttime += 2;
    
    ofDrawBitmapString(pasttime, 15,30);
}

void ofApp::mousePressed(int x, int y, int button){
    open.setLoop(true);
    open.play();
    
    vidPlayer.play();
    
    if(x < ofGetWidth()/2){
        works[0]->addBall();
    }
    if(ofGetWidth()/2 < x){
        works[0]->destroyBall();
    }
    
//    if(x < 100){
//        works[0]->n ++;
//    }
//    Boid* b = new Boid(works[0]->startx + works[0]->w / 2 ,
//                       works[0]->starty + works[0]->h / 2 ,
//                       ofRandom(- Work::SPEED, Work::SPEED),
//                       ofRandom(- Work::SPEED, Work::SPEED), works[0]->n, works[0]->boids);
//    works[0]->boids.push_back(shared_ptr<Boid>(b));
}

