#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"



//========================================================================
int main( ){
  int num_notes      = 16;
  int button_size    = 40;
  int button_padding = 5;
  int dim = num_notes * (button_size + button_padding) + button_padding;
  ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(dim,dim,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
