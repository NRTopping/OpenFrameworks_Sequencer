#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"
#include <stdio.h>

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(20,20,20);
  
  m_fCounter = 0.0F;
  
  ofSetFrameRate(60);
  
  // load the tones
  string path = "tones";
  
  ofDirectory dir(path);
  dir.allowExt("mp3");
  dir.listDir();
  for (int i = 0; i < dir.numFiles(); i++) {
    std::cout << dir.getPath(i) << std::endl;
    ma_sounds[i].loadSound(dir.getPath(i)); // load the sound.
    ma_sounds[i].setMultiPlay(true); // allow multiple play copies.
  }
  
  
  // set up the audio files
  for (int i=0; i < NUM_NOTES; i++) {
   // m_aNotes[i].setUp(i);
  }
  
  resetSequencer();
  
  m_iBPM = 440;
  
  prevDragJ = -1;
  prevDragI = -1;
}

void ofApp::resetSequencer() {
  // set sequencer to start over, all notes off, start from first index
  for (int i = 0; i < NUM_NOTES; i++) {
    for (int j = 0; j < NUM_NOTES; j++) {
      m_aButtons[i][j].turnOff();
    }
  }
  m_fLastStartTime  = ofGetElapsedTimef();
  m_iSequencerPos   = 0;
  m_iMovedThisFrame = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
  // check to see if it is time to play the next notes
  
  if (ofGetElapsedTimef() > m_fLastStartTime + (60.0f / ((float) m_iBPM))) {
    m_iSequencerPos++;
    m_fLastStartTime = ofGetElapsedTimef();
    
    // Make sure position doesn't go out of bounds
    if (m_iSequencerPos >= NUM_NOTES) {
      m_iSequencerPos = 0;
    }
    
    // check which notes should play
    for (int i = 0; i < NUM_NOTES; i++) {
      if (m_aButtons[m_iSequencerPos][i].isOn()) {
        ma_sounds[i].play();
      }
    }
    
    m_iMovedThisFrame = 0;
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  // shader background
  ofEnableAlphaBlending();
  
  for (int i = 0; i < NUM_NOTES; i++) {
    for (int j = 0; j < NUM_NOTES; j++) {
      // if in sequencer row, and note is on, do THE THING
      if (i == m_iSequencerPos && m_aButtons[i][j].isOn()) {
        // sequencer and is on
        // set color
        ofSetColor(255, 255, 255, 255);
      } else if (m_aButtons[i][j].isOn()) {
        // no sequencer and is on
        // set color
        ofSetColor(200, 200, 200, 125);
      } else {
        // no sequencer and is off
        // set color
        ofSetColor(100, 100, 100, 80);
      }
      
      // draw rounded rect
      ofRectangle myRect;
      myRect.x = i * (BUTTON_DIM + BUTTON_PAD) + BUTTON_PAD;
      myRect.y = j * (BUTTON_DIM + BUTTON_PAD) + BUTTON_PAD;
      myRect.width  = BUTTON_DIM;
      myRect.height = BUTTON_DIM;
      
      ofRectRounded(myRect, 5.0f); // radius of 5.
    }
  }
  ofSetColor(20, 20, 20);
  ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  if (key == ']') {
    m_iBPM += 10;
  } else if (key == '[') {
    m_iBPM -= 10;
    if (m_iBPM < 40) {
      m_iBPM = 40;
    }
  } else if (key == 'c') {
    resetSequencer();
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
  // turn buttons on
  int i = -1;
  int j = -1;
  
  // determine i and j
  for (int p = 0; p < NUM_NOTES; p++) {
    int startCoord = p * (BUTTON_DIM + BUTTON_PAD) + BUTTON_PAD;
    // determines x
    if (x >= startCoord && x <= startCoord + BUTTON_DIM) {
      i = p;
    }
    // determines y
    if (y >= startCoord && y <= startCoord + BUTTON_DIM) {
      j = p;
    }
  }
  
  if (button == 0 && (i > -1 && j > -1) && (i != prevDragI && j != prevDragJ)) {
    m_aButtons[i][j].toggleOffOn();
    prevDragI = i;
    prevDragJ = j;
  }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  int i = -1;
  int j = -1;
  
  // determine i and j
  for (int p = 0; p < NUM_NOTES; p++) {
    int startCoord = p * (BUTTON_DIM + BUTTON_PAD) + BUTTON_PAD;
    // determines x
    if (x >= startCoord && x <= startCoord + BUTTON_DIM) {
      i = p;
    }
    // determines y
    if (y >= startCoord && y <= startCoord + BUTTON_DIM) {
      j = p;
    }
  }
  
  if (button == 0 && (i > -1 && j > -1)) {
    m_aButtons[i][j].toggleOffOn();
  }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
