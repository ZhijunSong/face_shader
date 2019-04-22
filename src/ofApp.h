#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void keyPressed(int key);
    ofVideoGrabber cam;
    ofxCv::ObjectFinder finder;
    ofImage cropped;
    ofImage cropped2;
//    ofVideoGrabber video;
    
    ofImage img;
    
    
    //Shader
    ofShader shader;
    ofFbo fbo;
    
    float len;
    bool bAdd;

};
