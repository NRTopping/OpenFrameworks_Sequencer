#pragma once

#include "ofMain.h"
#include "NoteButton.h"
#include "Emitter.h"

#define NUM_NOTES 16
#define BUTTON_DIM 40
#define BUTTON_PAD 5

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
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  
  void resetSequencer();
  
private:
  NoteButton m_aButtons[NUM_NOTES][NUM_NOTES];
  Emitter    m_aNotes[NUM_NOTES];
  
  int m_iSequencerPos;
  int m_iBPM;
  
  float m_fLastStartTime;
  bool m_bSetVal;
  int m_iMovedThisFrame;
  float m_fCounter;
  
  int prevDragI;
  int prevDragJ;
  ofShader shader;
  ofPlanePrimitive plane;
};
