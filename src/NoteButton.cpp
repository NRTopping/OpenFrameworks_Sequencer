//
//  NoteButton.cpp
//  FinalProject
//
//  Created by Nicholas Topping on 12/13/14.
//
//

#include "NoteButton.h"
void NoteButton::toggleOffOn() {
  m_bIsOn = !m_bIsOn;
}

void NoteButton::turnOff() {
  m_bIsOn = false;
}

void NoteButton::turnOn() {
  m_bIsOn = true;
}

bool NoteButton::isOn() {
  return m_bIsOn;
}