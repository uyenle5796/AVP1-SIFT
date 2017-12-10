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
 - Image from Google https://i.pinimg.com/736x/10/05/22/100522600659b975cba50e4a3a508b60--london-covent-garden-covent-garden-market.jpg
 - SIFT Implementation Tutotials:
        http://www.tylerhenry.com/sift-implementation-in-openframeworks-part-1/
        http://www.tylerhenry.com/sift-implementation-in-openframeworks-part-2/
 - Tyle Henry's SIFTtest source code: https://github.com/tyhenry/opencv-oF-experiments/blob/master/SIFTtest/src/ofApp.cpp
 - Wikipedia: https://en.wikipedia.org/wiki/Scale-invariant_feature_transform
 - OpenCV documentations: https://docs.opencv.org/2.4/modules/features2d/doc/common_interfaces_of_descriptor_matchers.html
 */

//--------------------------------------------------------------
void ofApp::setup() {
    
    //Load the original image (called "train" in OpenCV)
    findImg.load("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AVP1-SIFT/bin/data/goldsmiths-text-2.jpg");
    
    //Load the cropped image that is used to train OpenCV (called "query" in OpenCV)
    //This image is known as the 'feature description' of the original image
    //Following the tutorial, I've chosen this text because of the high contrast and clear edges which will make keypoints detection easier.
    fieldImg.load("/Users/uyenle/Desktop/AudioVisual/AVPCoursework_tle004/AVP1-SIFT/bin/data/Richard-Hoggart-Building_411.jpg");
    
    
    // convert images to grayscale for SIFT
    fieldImg.setImageType(OF_IMAGE_GRAYSCALE);
    findImg.setImageType(OF_IMAGE_GRAYSCALE);
    
    //Wrap images in Mat class for use with SIFT
    fieldMat = toCv(fieldImg);
    findMat = toCv(findImg);
    
    //SIFT Feature Detector object
    SiftFeatureDetector detector(100000); //2000 is number of keypoints to find

    // KeyPoint vectors to store keypoints detected per image
    vector<KeyPoint> findKeypoints, fieldKeypoints;
    
    // run the detector on each image
    detector.detect(fieldMat, findKeypoints);
    detector.detect(findMat, fieldKeypoints);
    
    //SIFT descriptor object
    SiftDescriptorExtractor extractor; //ERROR: Variable type 'SiftDescriptorExtractor' (aka 'cv::SIFT') is an abstract class
    
    //run descriptor
    extractor.compute(findMat, findKeypoints, findDescriptors);
    extractor.compute(fieldMat, fieldKeypoints, fieldDescriptors);
    
    // Brute-force Descriptor Matcher object
    // For each descriptor in the first set, this matcher finds the closest descriptor in the second set by trying each one.
    BFMatcher matcher(NORM_L1, true);
    // normType is NORM_L1: specifies the distance measurement to be used
    // crossMatch is true
    // reference: https://docs.opencv.org/2.4/modules/features2d/doc/common_interfaces_of_descriptor_matchers.html

    
    // Vectors of matches found
    vector<DMatch> matches;
    // DMatch: Class for matching keypoint descriptors: query descriptor index, train descriptor index, train image index, and distance between descriptors.

    // run the matcher
    matcher.match(findDescriptors, fieldDescriptors, matches);

    
    // DRAW RESULTS

    // drawMatches() displays the images side by side
    // with coloured circles at each keypoint and lines connecting the matched keypoints.
    // then it draws into Mat.
    drawMatches(findMat, findKeypoints, fieldMat, fieldKeypoints, matches, matchMat, Scalar::all(-1), Scalar::all(170), vector<char>(), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    toOf(matchMat, matchImg); //wraps matchMat to matchImg

    matchImg.update(); //updates matchImg texture on GPU
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    // draw both cropped and original images side by side
    //with matching points and edges
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
