//
//  BlobTracker.h
//  kinectTCPServer
//
//  Created by maybites on 14.02.14.
//
//
#pragma once

#include "ofMain.h"
#include "ofConstants.h"
#include "TrackedBlob.h"

#include <cmath>
#include <vector>
#include <iterator>

//defines after how many frames without update a Blob dies.
#define N_EMPTYFRAMES 10
#define EYE_DIFF_TO_HEADTOP 160 //the eyes are 130 mm below the top of the head


class BlobTracker {
    
public:
    BlobTracker(ofRectangle _rect);
    
    bool hasDied();
    
    bool finder(ofRectangle _rect);
    
    void updateStart();
    void updateBody(ofRectangle _rect, ofVec3f _bodyBlobCenter, ofVec2f _bodyBlobSize, ofVec3f _headTop);
    void updateHead(ofVec3f _headBlobCenter, ofVec2f _headBlobSize, ofVec3f _eyeCenter);
    void updateEnd();
    
    void drawBodyBox();
    void drawHeadTop();
    void drawHeadBlob();
    void drawEyeCenter();
    
    bool hasBodyUpdated;
    bool hasHeadUpdated;

    bool valid;

    ofBoxPrimitive bodyBox;
    ofPlanePrimitive headBlob;
    
    ofSpherePrimitive bodyHeadTopSphere;
    ofSpherePrimitive headCenterSphere;
    ofSpherePrimitive eyeCenterSphere;
    
    ofRectangle baseRectangle2d;
    
    ofVec3f     bodyBlobCenter;
    ofVec2f     bodyBlobSize;
    
    ofVec3f     headTop;

    ofVec3f     headCenter;

    ofVec3f     headBlobCenter;
    ofVec2f     headBlobSize;
    
    ofVec3f     eyeCenter;
 
    int trackerSize;
    vector <TrackedBlob> tracker;
    
    ofVboMesh contourMesh;
    vector <ofVec3f> countour;

    int lastUpdateFrame;
    
};


