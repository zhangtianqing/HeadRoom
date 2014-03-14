#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"
#include "ofxMatrixNetworkServer.h"
#include "BlobTracker.h"
#include "Planef.h"
#include "Linef.h"
#include "Grid.h"
#include "OrthoCamera.h"

#include <ofMatrix4x4.h>

#define N_CAMERAS 6

#define VIEWGRID_WIDTH  105
#define MENU_WIDTH      200
#define VIEWPORT_HEIGHT 480

#define KINECT_IMG_WIDTH   640
#define KINECT_IMG_HEIGHT  480

#define N_MEASURMENT_CYCLES 10


#define EYE_DIFF_TO_HEADTOP 160 //the eyes are 130 mm below the top of the head


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
        
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

        ofxMatrixNetworkServer rgbaMatrixServer;
        ofxMatrixNetworkServer depthMatrixServer;
        ofxMatrixNetworkServer rawMatrixServer;

        vector <string> storeText;
		
        //ofxUDPManager udpConnection;

		ofTrueTypeFont  mono;
		ofTrueTypeFont  monosm;
		vector<ofPoint> stroke;
    

    bool bShowVisuals = false;

    
    //////////////////
    //OPENGL CAMERAS//
    //////////////////

    //viewports
    void setupViewports();
    
    ofRectangle viewMain;
    ofRectangle viewGrid[N_CAMERAS];

    //camera pointers
    ofCamera * cameras[N_CAMERAS];
    int iMainCamera;

    ofEasyCam cam;
    
    grid mainGrid;
    
    //////////
    //KINECT//
    //////////
        
    ofxKinect kinect;
    
    ofMatrix4x4 unprojection;
    
    #ifdef USE_TWO_KINECTS
        ofxKinect kinect2;
    #endif

    bool dispRaw;

    bool bPreviewPointCloud;
    
    ofVboMesh previewmesh, capturemesh;
    
    ofVboMesh frustum;
    
    void updatePointCloud(ofVboMesh & mesh, int step, bool useFrustumCone, bool useVideoColor);
    void drawPreviewPointCloud();
    void drawCapturePointCloud();

    void createFrustumCone();
    void updateFrustumCone(int & value);

    /////////////////
    //COLOR CONTOUR//
    /////////////////
    
    BlobTracker blobTracker;
            
    // used for viewing the point cloud
    ofEasyCam previewCam;
 
    // used for viewing the point cloud
    orthoCamera captureCam;
    
    ofImage capturedImage;
    ofFbo captureFBO;
    
    ///////////////
    //CALCUALTION//
    ///////////////
    void updateCalc();
    void updateMatrix();
    void measurementCycleRaw();
    void measurementCycleFine();

    void drawCalibrationPoints();
    ofVec3f calcPlanePoint(ofParameter<ofVec2f> & cpoint, int _size, int _step);
    
    bool bUpdateCalc = false;
    bool bUpdateMeasurment = false;
    bool bUpdateMeasurmentFine = false;
    
    int cycleCounter = 0;
   
    ofVec3f planePoint1Meas[N_MEASURMENT_CYCLES];
    ofVec3f planePoint2Meas[N_MEASURMENT_CYCLES];
    ofVec3f planePoint3Meas[N_MEASURMENT_CYCLES];
    
    ofVec3f planePoint1;
    ofVec3f planePoint2;
    ofVec3f planePoint3;

    ofVec3f planeCenterPoint;

    ofSpherePrimitive sphere1;
    ofSpherePrimitive sphere2;
    ofSpherePrimitive sphere3;
    
    ofSpherePrimitive frustumCenterSphere;
    ofSpherePrimitive frustumTopSphere;

    ofVboMesh geometry;
        
    ofMatrix4x4 kinectRransform;

    string calcdata;
    
    bool bShowCalcData;

    //////////////
    //PROPERTIES//
    //////////////
    ofxPanel gui;
    
    ofParameter<ofVec2f> calibPoint1;
    ofParameter<ofVec2f> calibPoint2;
    ofParameter<ofVec2f> calibPoint3;
    
    ofParameter<ofVec3f> transformation;
    
    ofParameterGroup frustumGuiGroup;

    ofParameter<int> nearFrustum;
    ofParameter<int> farFrustum;

    ofParameterGroup intrinsicGuiGroup;

    ofParameter<float> depthCorrectionBase;
    ofParameter<float> depthCorrectionDivisor;
    ofParameter<float> pixelSizeCorrector;

    //////////
    // HELP //
    //////////
    string help;

    bool bShowHelp = true;

    void createHelp();

};

