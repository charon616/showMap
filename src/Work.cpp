#include "Work.hpp"
#include <vector>

using namespace std;

Boid::Boid(float _x, float _y, float _vx, float _vy, int _id, vector<shared_ptr<Boid>> _others)
:x(_x), y(_y), vx(_vx), vy(_vy), id(_id), others(_others){
}
// コピーコンストラクタ
Boid::Boid(const Boid& rhs) : x(rhs.x), y(rhs.y), vx(rhs.vx), vy(rhs.vy), id(rhs.id), others(rhs.others)
{
    w = rhs.w;
    h = rhs.h;
    startx = rhs.startx;
    starty = rhs.starty;
    n = rhs.n;
    v1 = rhs.v1;
    v2 = rhs.v2;
    v3 = rhs.v3;
}

void Boid::move() {
    
    this->vx += r1 * v1.x + r2 * v2.x + r3 * v3.x;
    this->vy += r1 * v1.y + r2 * v2.y + r3 * v3.y;

    float vVector = sqrt(vx * vx + vy * vy);
    if (vVector > SPEED) {
        this->vx = (vx / vVector) * SPEED;
        this->vy = (vy / vVector) * SPEED;
    }
    
    this->x += vx;
    this->y += vy;
    
    if (x - R <= startx) {
        this->x = R + startx;
        this->vx *= -1;
    }
    if (x + R >= w + startx) {
        this->x = w - R + startx;
        this->vx *= -1;
    }
    
    if (y - R <= starty) {
        this->y = R + starty;
        this->vy *= -1;
    }
    if (y + R >= h + starty) {
        this->y = h - R + starty;
        this->vy *= -1;
    }
}

void Boid::draw() {
    ofDrawCircle(this->x, this->y, R*2);
    
    ofPushMatrix();
    ofTranslate(x, y);
    float a = atan2(y- y + vy * 3, x-x + vx * 3);
    ofRotateDeg(ofDegToRad(a));
    //境界のぼかしをグラデーションでつくる
    drawShapeRight();
    ofPopMatrix();
    
    //    //最新の５歩を表示
    //int c = 5;
    //if(this.counter > 5){
    //  for (int i = this.track.size() - display_num; i < this.track.size(); i++) {
    //    fill(clr, c); stroke(clr, 0.2*c);
    //    if( i % 2 == 0){
    //      this.drawShape(this.track.get(i), this.track.get(i -1), "right");
    //    }else{
    //      this.drawShape(this.track.get(i), this.track.get(i -1), "left");
    //    }
    //    fill(clr); stroke(clr, 10);
    //    c += 5;
    //  }
    //}
}

//ArrayList<PVector> track = new ArrayList<PVector>(0);
////int pace = 20; //表示する移動量の閾値


//void display() {
//  //  //移動量が歩幅paceより大きければpに追加
//  //if(dist(this.px, this.py , this.x, this.y) > pace){
//  //  this.counter++;
//  //  PVector tmp = new PVector(this.x, this.y);
//  //  this.track.add(tmp);
//  //}
//  //最新の５歩を表示
//  int c = 5;
//  if(this.counter > 5){
//    for (int i = this.track.size() - display_num; i < this.track.size(); i++) {
//      fill(clr, c); stroke(clr, 0.2*c);
//      if( i % 2 == 0){
//        this.drawShape(this.track.get(i), this.track.get(i -1), "right");
//      }else{
//        this.drawShape(this.track.get(i), this.track.get(i -1), "left");
//      }
//      fill(clr); stroke(clr, 10);
//      c += 5;
//    }
//  }

//void Boid::drawShape(PVector pos, PVector p_pos, String type) {
//    pushMatrix();
//    translate(pos.x, pos.y);
//    float a = atan2(pos.y- p_pos.y, pos.x- p_pos.x);
//    rotate(a);
//    //境界のぼかしをグラデーションでつくる
//    for(int i = weight; i > 0; i--){
//        strokeWeight(i);
//        switch (type){
//            case "right":
//                drawShapeRight();
//                break;
//            case "left":
//                drawShapeLeft();
//                break;
//        }
//    }
//    popMatrix();
//}

//足の形を描く
//左足
void Boid::drawShapeLeft(){
    ofPushMatrix();
    ofRotateDeg(ofDegToRad(90));
    ofRotateDeg(ofDegToRad(-5));
    ofScale(0.07);
    ofBeginShape();
    ofVertex(-94, 11); // first point
    ofBezierVertex(-154, 11, -176, 131, -176, 171);
    ofBezierVertex(-176, 211, -168, 301, -90, 293);
    ofBezierVertex(-62, 290, -16, 293, -16, 211);
    ofBezierVertex(-16, 129, -34, 11, -94, 11);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(-80, 335);
    ofBezierVertex(-127, 338, -135, 334, -128, 362);
    ofBezierVertex(-116, 409, -103, 447, -64, 443);
    ofBezierVertex(-25, 439, -24, 411, -20, 365);
    ofBezierVertex(-16, 326, -32, 332, -80, 335);
    ofEndShape();
    ofPopMatrix();
}
//右足
void Boid::drawShapeRight(){
    ofPushMatrix();
    ofRotateDeg(ofDegToRad(90));
    ofRotateDeg(ofDegToRad(5));
    ofScale(0.07);
    ofBeginShape();
    ofVertex(94, 11); // first point
    ofBezierVertex(154, 11, 176, 131, 176, 171);
    ofBezierVertex(176, 211, 168, 301, 90, 293);
    ofBezierVertex(62, 290, 16, 293, 16, 211);
    ofBezierVertex(16, 129, 34, 11, 94, 11);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(80, 335);
    ofBezierVertex(127, 338, 135, 334, 128, 362);
    ofBezierVertex(116, 409, 103, 447, 64, 443);
    ofBezierVertex(25, 439, 24, 411, 20, 365);
    ofBezierVertex(16, 326, 32, 332, 80, 335);
    ofEndShape();
    ofPopMatrix();
}


void Boid::clearVector() {
    this->v1.x = 0;
    this->v1.y = 0;
    this->v2.x = 0;
    this->v2.y = 0;
    this->v3.x = 0;
    this->v3.y = 0;
}

void Boid::check() {
    this->rule1();
    this->rule2();
    this->rule3();
}//end

void Boid::rule1() {
    for (int i = 0; i < n; i++) {
        shared_ptr<Boid> otherBoid = others[i];
        if (this != otherBoid.get())   {
            this->v1.x += otherBoid->x;
            this->v1.y += otherBoid->y;
            std::cout << otherBoid->x << " " << otherBoid->y << endl;
        } // end if
    } // end for
    
    this->v1.x /= (n - 1);
    this->v1.y /= (n - 1);
    
    this->v1.x = (v1.x - x) / CENTER_PULL_FACTOR;
    this->v1.y = (v1.y - y) / CENTER_PULL_FACTOR;
    
    
    
}//end rule1


void Boid::rule2() {
    for (int i = 0; i < n; i++) {
        shared_ptr<Boid> otherBoid = others[i];
        if (this != otherBoid.get()) {
            if (ofDist(x, y, otherBoid->x, otherBoid->y) < DIST_THRESHOLD) {
                this->v2.x -= otherBoid->x - x;
                this->v2.y -= otherBoid->y - y;
            } // end if
        } // end if
    }
}// end rule2

void Boid::rule3() {
    for (int i = 0; i < n; i++) {
        shared_ptr<Boid> otherBoid = others[i];
        if (this != otherBoid.get()) {
            this->v3.x += otherBoid->vx;
            this->v3.y += otherBoid->vy;
        } // end if
    } // end for
    
    this->v3.x /= (n - 1);
    this->v3.y /= (n - 1);
    
    this->v3.x = (v3.x - vx)/2;
    this->v3.y = (v3.y - vy)/2;
}// end rule3

//初期化用メソッド（コンストラクタ）
Work::Work (int _startx, int _starty, int _w, int _h, int _n)
    :startx(_startx), starty(_starty), w(_w), h(_h), n(_n)  {
    
//
//    for (int i = 0; i < this->n; i++) {
//        agents.add(new Agent(startx, starty, w, h));
//    }
    //boids.resize(n);
    boids.reserve(n);
//    boids = new Boid[n];
//
    float angle = TWO_PI / n;
    for (int i = 1; i <= n; i++) {
        float addx = cos(angle * i);
        float addy = sin(angle * i);
        
        Boid* b = new Boid(startx + w / 2 + addx * 50, starty + h / 2 + addy * 50,
                           ofRandom(- SPEED, SPEED) * addx, ofRandom(- SPEED, SPEED) * addy, i - 1, boids);
        boids.push_back(shared_ptr<Boid>(b));
        
        boids[i-1]->n = n;
        boids[i-1]->w = w;
        boids[i-1]->h = h;
        boids[i-1]->startx = startx;
        boids[i-1]->starty = starty;
    }
        
    // Fonts
    ofTrueTypeFont::setGlobalDpi(72);
    din.load("URWDIN-Bold", 64); // フォントのデータを指定する
    din.setLineHeight(80);       // 行間を指定する
    din.setLetterSpacing(1.1);   // 文字間を指定する
    
    ofBackground(0, 0, 0);
    box2d.init();
    box2d.setGravity(0, 0);
    box2d.createBounds(startx, starty, w, h);
    box2d.setFPS(30);
        
    snow.load("snow.png");
    snow.setAnchorPercent(0.5, 0.5);
    
    for(int i = 0; i<n; i++){
        ofxBox2dCircle* circle = new ofxBox2dCircle();
        circle->setPhysics(10.0, 0.8, 0);
        circle->setup(box2d.getWorld(), ofRandom(startx, startx+w), ofRandom(starty, starty+h), 10);
        circles.push_back(circle);
    }
}

//円の位置を更新するメソッド
void Work::update() {
//    for (int i=0; i < agents.size(); i++){
//        agents.get(i).update();
//    }
    box2d.update();
}
    
void Work::display() {
    ofSetColor(0, 0, 255, 10);
    ofDrawRectangle(startx, starty, w, h); //領域の枠を表示
    
    ofSetColor(110, 35, 40);
    
    //ofDrawBitmapString(n, startx,starty);
    this->din.drawString(to_string(n), startx, starty + 40); // 文字とポジションを指定して描画
    
    for (int i = 0; i < n; i++) {
        boids[i]->clearVector();
    }

//    for (int i = 0; i < n; i++) {
//        //boids[i]->check();
//        boids[i]->move();
//        boids[i]->draw();
//    }
//
//    for (auto it = circles.begin(); it != circles.end(); ++it) {
//        ofSetColor(ofColor(255, 255, 255));
//        (*it)->draw();
//    }
    for (auto it = circles.begin(); it != circles.end(); ++it) {
        ofPoint pos = (*it)->getPosition();
        float size = (*it)->getRadius() * 10.0;
        ofSetColor(ofColor(255, 255, 255));
        snow.draw(pos, size, size);
    }
    
    //    for (int i=0; i < agents.size(); i++){
    //      agents.get(i).display();
    //    }
}

void Work::addBall(){
    ofxBox2dCircle* circle = new ofxBox2dCircle();
    circle->setPhysics(10.0, 0.8, 0);
    circle->setup(box2d.getWorld(), ofRandom(startx, startx+w), ofRandom(starty, starty+h), 10);
    circles.push_back(circle);
}


void Work::destroyBall(){
//    for (auto it = circles.begin(); it != circles.end(); ++it) {
//        (*it)->destroy();
//        delete *it;
//        it = circles.erase(it);
//    }

    for (auto it = circles.begin(); it !=  std::next(circles.begin()); ++it) {
        (*it)->destroy();
        delete *it;
        it = circles.erase(it);
    }

}
