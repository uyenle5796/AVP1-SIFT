#include "ofApp.h"

/*
 
 Advanced Audio-Visual Processing Coursework
 Project 1: Image Processing with SIFT
 
 by Uyen Le
 tle004@gold.ac.uk
 
 ----------------
 A simple implementation of SIFT feature extraction.
 
 Scale Invariant Feature Transform (SIFT) finds the closest matching keypoints in both grayscale images.
 SIFT algorithm should be able to detect the same keypoints no matter how the image has been modified (ie. scaled, rotated, etc).
 
 In this program, I've chosen to train OpenCV to look for the text 'Punch' in the original image of Covent Garden.
 ----------------
 Credits:
 - Image from Google.com 'Covent Garden'
 - SIFT Implementation Tutotials: http://www.tylerhenry.com/sift-implementation-in-openframeworks-part-1/,
 - SIFT from Wikipedia: https://en.wikipedia.org/wiki/Scale-invariant_feature_transform
 - OpenCV Documentation: https://docs.opencv.org/2.4/modules/features2d/doc/common_interfaces_of_descriptor_matchers.html
 */

//--------------------------------------------------------------
void ofApp::setup() {
    
    //Load the original image of Covent garden
    //(called "train" in OpenCV)
    fieldImg.load("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AVP1-SIFT/bin/data/covent-garden.jpg");
    
    //Load the cropped image of the text 'Punch' (called "query" in OpenCV)
    //This image is known as the 'feature description' of the original image
    //This image is used to train OpenCV
    //therefore I've chosen the text 'Punch' because of the high contrast and clear edges, which will make keypoints detection easier.
    findImg.load("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AVP1-SIFT/bin/data/punch-text.jpg");
    
    // convert images to grayscale for SIFT
    fieldImg.setImageType(OF_IMAGE_GRAYSCALE);
    findImg.setImageType(OF_IMAGE_GRAYSCALE);
    
    
    //Wrap images in Mat class for use with SIFT
    fieldMat = toCv(fieldImg);
    findMat = toCv(findImg);
    
    //SIFT Feature Detector object
    //with maximum of 10000 keypoints it should find.
    SiftFeatureDetector detector(2000);
    
    //since OpenCV 3.0 this cannot be used anymore as it's an abstract class
    //so I Googled and found the substitution here https://docs.opencv.org/3.0-beta/doc/py_tutorials/py_feature2d/py_sift_intro/py_sift_intro.html#sift-intro
    //following this, this is is used instead:
//    Ptr<SIFT> detector = SIFT::create(2000);

    // KeyPoint vectors to store keypoints detected per image
    vector<KeyPoint> findKeypoints, fieldKeypoints;
    
    // run the detector on each image
    detector->detect(fieldMat, findKeypoints);
    detector->detect(findMat, fieldKeypoints);
    
    //SIFT descriptor object
    SiftDescriptorExtractor extractor; //same error as SiftFeatureDetector - also an abstract class
//    Ptr<SIFT> extractor = SIFT::create(...);
    
    //run descriptor
    extractor->compute(findMat, findKeypoints, findDescriptors);
    extractor->compute(fieldMat, fieldKeypoints, fieldDescriptors);
    
    // Brute-force Descriptor Matcher object
    // For each descriptor in the first set, this matcher finds the closest descriptor in the second set by trying each one.
    // normType is NORM_L2: specifies the distance measurement to be used
    BFMatcher matcher(NORM_L2);
    
    // Vectors of matches found
    // DMatch: Class for matching keypoint descriptors: query descriptor index, train descriptor index, train image index, and distance between descriptors.
    vector<DMatch> matches;
    
    // run the matcher
    matcher.match(findDescriptors, fieldDescriptors, matches);
    
    // DRAW RESULTS
    
    // visualize matches in new image-matrix
    Mat matchMat;
    
    // drawMatches() displays the images side by side
    // with coloured circles at each keypoint and lines connecting the matched keypoints.
    // then it draws into Mat.
    drawMatches(findMat, findKeypoints, fieldMat, fieldKeypoints, matches, matchMat);
    
    toOf(matchMat, matchImg); //wraps matchMat to matchImg
    
    matchImg.update(); //updates matchImg texture on GPU
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    // draw matchImg
    matchImg.draw(0,0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
