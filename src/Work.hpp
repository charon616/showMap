#pragma once

#include "ofMain.h"
#include <stdio.h>
#include <vector>
#include "ofxBox2d.h"

using namespace std;

struct Boid : public ofBaseApp{
    
    Boid(float _x, float _y, float _vx, float _vy, int _id, vector<shared_ptr<Boid>> _others);
    Boid(const Boid& rhs);
    void move();
    void draw();
    void drawShapeLeft();
    void drawShapeRight();
    void clearVector();
    void check();

    float x, y;
    float vx, vy;

    ofVec2f v1;
    ofVec2f v2;
    ofVec2f v3;

    float w, h;
    float startx, starty;
    int n;
    int id;
    vector<shared_ptr<Boid>> others;
    
    static constexpr float r1 = 1.0;
    static constexpr float r2 = 0.8;
    static constexpr float r3 = 0.1;
    static constexpr float SPEED = 4;
    static constexpr float R = 5;
    
    static constexpr int CENTER_PULL_FACTOR = 300;
    static constexpr int  DIST_THRESHOLD = 30;
    
    private:

        void rule1();
        void rule2();
        void rule3();
    
//        int display_num = 3;
//        int weight = 50; //線の太さ
};

struct Work : public ofBaseApp{
    
    Work(int _startx, int _starty, int _w, int _h, int _n);
    void update();
    void display();
    void addBall();
    void destroyBall();

    static constexpr float r1 = 1.0;
    static constexpr float r2 = 0.8;
    static constexpr float r3 = 0.1;
    static constexpr float SPEED = 4;
    static constexpr float R = 10;
    
    int startx, starty, w, h, n;
    //ArrayList<Agent> agents = new ArrayList<Agent>(0);
    vector<shared_ptr<Boid>> boids;
    
    ofxBox2d box2d; // box2dのインスタンス変数
    std::vector<ofxBox2dCircle*> circles;
    
    private:
        ofTrueTypeFont din;
        ofImage snow;
    
};
