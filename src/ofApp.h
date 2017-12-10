#pragma once

#include "ofMain.h"

//include addons
#include "ofxOpenCv.h"
#include "ofxCv.h"

//include non-free OpenCV modules
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

using namespace cv;
using namespace ofxCv;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofImage fieldImg;
    ofImage findImg;
    ofImage matchImg;
    
    //OpenCV's matrix class - known as 'Mat'
    Mat fieldMat;
    Mat findMat;
    
    // visualize matches in new image-matrix
    Mat matchMat;
    
    // matrices to hold all features per keypoint in image
    Mat findDescriptors;
    Mat fieldDescriptors;
    // i.e. in each matrix, row 'i' is the list of features for keypoint 'i'

};
