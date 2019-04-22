#include "ofApp.h"
#include <iostream>
using namespace ofxCv;
using namespace cv;
using namespace std;
//--------------------------------------------------------------
void ofApp::setup(){

    cam.setVerbose(true);
    
    
    cam.initGrabber(640,480);
    
    //shader
    fbo.allocate(640, 480);
    
    shader.load("hexagon.vert", "hexagon.frag");
    len = 8.0f;
    bAdd = false;
    
    ofSetVerticalSync(true);


    finder.setup("haarcascade_frontalface_default.xml");

    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(1);
    cropped.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
//    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);


  
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){

        
        ofxCv::copy(cam, img);


        img.update();
        
        finder.update(img);
      
        for(int i = 0; i < finder.size(); i++) {
        if(finder.size() > 0) {
            cv::Rect roi = toCv(finder.getObject(0));

            Mat camMat = toCv(cam);
            Mat croppedCamMat(camMat, roi);

            resize(croppedCamMat,cropped);
            cropped.update();

            }
        }
    
    }
    //shader
    if(len < 10.0f)
        bAdd = true;
    if(len > 20.0f)
        bAdd = false;
    len += bAdd ? (0.005f):(-0.005f);
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.draw(0,0);

    finder.draw();

    ofEnableAlphaBlending();

    fbo.begin();
    cropped.draw(0, 0);
        img.draw(0,0);

    fbo.end();
  //  fbo.draw(0,0,cropped.getWidth(), cropped.getHeight());

    shader.begin();
    shader.setUniform1f("len", len);
    shader.setUniformTexture("colorTex0", fbo.getTextureReference(), 0);
  
    for(int i = 0; i < finder.size(); i++) {
        ofRectangle object= finder.getObjectSmoothed(i);
        cropped.resize(object.getWidth(),object.getHeight());
        
        cropped.setAnchorPercent(.5, .5);
        
        float scaleAmount =  object.width/cropped.getWidth();
        
        ofPushMatrix();
        ofTranslate(object.x + object.width / 2., object.y + object.height/2);
        ofScale(scaleAmount, scaleAmount);
        cropped.draw(scaleAmount, scaleAmount);
        ofPopMatrix();
        ofPushMatrix();
        ofTranslate(object.getPosition());
        
        ofPushMatrix();
        ofTranslate(0, cam.getHeight());
        fbo.draw(0,0,cropped.getWidth(), cropped.getHeight());
        shader.end();
        ofPopMatrix();
        ofPushMatrix();
        
        ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
        ofDrawLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
        ofPopMatrix();
        
    }
    
    ofDisableAlphaBlending();

  


    
    
    


}
void ofApp::keyPressed(int key){
 
    
}

