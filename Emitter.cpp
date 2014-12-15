//
//  Emitter.cpp
//  FinalProject
//
//  Created by Nicholas Topping on 12/14/14.
//
//

#include "Emitter.h"

void Emitter::setUp(int i) {
  m_bNoise      = false;
  
  m_iSampleRate = 44100;
  m_iBufferSize = 512;
  m_fPhase      = 0.0f;
  m_fPhaseAdder = 0.0f;
  m_fPhaseAdderTarget = 0.0f;
  m_fVolume     = 0.01f;
  
  mv_fLAudio.assign(m_iBufferSize, 0.0);
  mv_fRAudio.assign(m_iBufferSize, 0.0);
  
  m_soundStream.setup(2, 0, m_iSampleRate, m_iBufferSize, 4);
  // may need to add 'this' as first arg, which is ofApp instance, so pass in as setup arg.
  
  // determine frequency, i is 0 throuh 15, 0 should be highest, 15 lowest (C4)
  // set the base frequency, based on
  int index = 15 - i; // Number of Notes - 1
  switch (index % 7) {
    case 0:
      m_fTargetFrequency = C4;
      break;
    case 1:
      m_fTargetFrequency = D4;
      break;
    case 2:
      m_fTargetFrequency = E4;
      break;
    case 3:
      m_fTargetFrequency = F4;
      break;
    case 4:
      m_fTargetFrequency = G4;
      break;
    case 5:
      m_fTargetFrequency = A4;
      break;
    default:
      m_fTargetFrequency = B4;
      break;
  }
  
  // Determine octave
  int octaveMult = 1;
  int numOctaves = index / 7;
  for (int i = 0; i < numOctaves; i++) octaveMult *= 2;
  
  m_fTargetFrequency *= octaveMult; // now final frequency
  m_fPhaseAdderTarget = (m_fTargetFrequency / (float) m_iSampleRate) * TWO_PI;
}

void Emitter::audioOut(float *output, int bufferSize, int nChannels) {
  float leftScale  = 1 - m_fPan;
  float rightScale = m_fPan;
  
  while (m_fPhase > TWO_PI) {
    m_fPhase -= TWO_PI;
  }
  
  if (m_bNoise) {
    for (int i = 0; i < bufferSize; i++) {
      mv_fLAudio[i] = output[i * nChannels    ] = ofRandom(0,1) * m_fVolume * leftScale;
      mv_fRAudio[i] = output[i * nChannels + 1] = ofRandom(0,1) * m_fVolume * rightScale;
    }
  } else {
    m_fPhaseAdder = 0.95f * m_fPhaseAdder + 0.05f * m_fPhaseAdderTarget;
    for (int i = 0; i < bufferSize; i++) {
      m_fPhase += m_fPhaseAdder;
      float sample = 0.0;
      for (int j = 0; j *  0.05 < m_fPan; j++) {
        sample += (1/(float)(j+1))*sin((j+1)*m_fPhase);
      }
      mv_fLAudio[i] = output[i * nChannels    ] = sample * m_fVolume;
      mv_fRAudio[i] = output[i * nChannels + 1] = sample * m_fVolume;
    }
  }
}

void Emitter::play() {
  
}

void Emitter::stop() {
  
}
