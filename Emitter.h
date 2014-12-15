//
//  Emitter.h
//  FinalProject
//
//  Created by Nicholas Topping on 12/14/14.
//
//

#ifndef __FinalProject__Emitter__
#define __FinalProject__Emitter__

#include <stdio.h>
#include "ofMain.h"

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88

class Emitter {
public:
  //Emitter(int i);
  void audioOut(float *input, int bufferSize, int nChannles);
  void setUp(int i);
  void play();
  void stop();
  
private:
  ofSoundStream  m_soundStream;
  vector <float> mv_fLAudio;
  vector <float> mv_fRAudio;
  
  float m_fPan;
  int   m_iSampleRate;
  int   m_iBufferSize;
  bool  m_bNoise;
  float m_fVolume;
  
  float m_fPhase;
  float m_fTargetFrequency;
  float m_fPhaseAdder;
  float m_fPhaseAdderTarget;
  
  
};

#endif /* defined(__FinalProject__Emitter__) */
