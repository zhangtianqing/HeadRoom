//
//  BlobTracker.cpp
//  kinectTCPServer
//
//  Created by maybites on 14.02.14.
//
//

#include "BlobTracker.h"

BlobTracker::BlobTracker(ofRectangle _rect){
    baseRectangle2d = _rect;
    trackerSize = 5;
    headBlob.setResolution(1, 1);
    lastUpdateFrame = 0;
}

bool BlobTracker::hasDied(){
    if(lastUpdateFrame > N_EMPTYFRAMES)
        return true;
    
    return false;
}

bool BlobTracker::finder(ofRectangle _rect){
    if(baseRectangle2d.inside(_rect.getCenter()))
        return true;
    return false;
}

void BlobTracker::updateStart(){
    lastUpdateFrame++;
    hasBodyUpdated = false;
    hasHeadUpdated = false;
}

void BlobTracker::updateBody(ofRectangle _rect, ofVec3f _bodyBlobCenter, ofVec2f _bodyBlobSize, ofVec3f _headTop){
    baseRectangle2d = _rect;
    tracker.insert(tracker.begin(), TrackedBlob());
    
    tracker[0].bodyBlobCenter = _bodyBlobCenter;
    tracker[0].bodyBlobSize = _bodyBlobSize;
    tracker[0].headTop = _headTop;
    
    while(tracker.size() > trackerSize)
        tracker.pop_back();
    
    hasBodyUpdated = true;
}

void BlobTracker::updateHead(ofVec3f _headBlobCenter, ofVec2f _headBlobSize, ofVec3f _eyeCenter){
    tracker[0].headBlobCenter = _headBlobCenter;
    tracker[0].headBlobSize = _headBlobSize;
    tracker[0].eyeCenter = _eyeCenter;
    
    hasHeadUpdated = true;
}

void BlobTracker::updateEnd(){
    if(hasBodyUpdated && hasHeadUpdated){
        bodyBlobCenter = ofVec3f();
        bodyBlobSize = ofVec3f();
        headTop = ofVec3f();
        headBlobCenter = ofVec3f();
        headBlobSize = ofVec3f();
        eyeCenter = ofVec3f();
        
        for (int i = 0; i < tracker.size(); i++){
            bodyBlobCenter += tracker[i].bodyBlobCenter;
            bodyBlobSize += tracker[i].bodyBlobSize;
            headTop += tracker[i].headTop;
            headBlobCenter += tracker[i].headBlobCenter;
            headBlobSize += tracker[i].headBlobSize;
            eyeCenter += tracker[i].eyeCenter;
        }
        
        bodyBlobCenter /= tracker.size();
        bodyBlobSize /= tracker.size();
        headTop /= tracker.size();
        headBlobCenter /= tracker.size();
        headBlobSize /= tracker.size();
        eyeCenter /= tracker.size();
        
        headCenter = ofVec3f(headTop.x, headTop.y, headTop.z - EYE_DIFF_TO_HEADTOP);
        

        lastUpdateFrame = 0;
        valid = true;
    } else {
        valid = false;
    }
}

void BlobTracker::drawBodyBox(){
    //ofLog(OF_LOG_NOTICE, "bodyBox.size : " + ofToString(bodyBox.getSize()));
    //ofLog(OF_LOG_NOTICE, "bodyBox.pos : " + ofToString(bodyBox.getPosition()));
    if(valid){
        bodyBox.set(bodyBlobSize.x, bodyBlobSize.y, bodyBlobCenter.z);
        bodyBox.setPosition(bodyBlobCenter.x, bodyBlobCenter.y, bodyBlobCenter.z / 2);
        bodyBox.drawWireframe();
        
    }
}

void BlobTracker::drawHeadTop(){
    if(valid){
        bodyHeadTopSphere.setRadius(20);
        bodyHeadTopSphere.setPosition(headTop.x, headTop.y, headTop.z);
        bodyHeadTopSphere.drawWireframe();
    }
}

void BlobTracker::drawHeadBlob(){
    if(valid){
        headBlob.set(headBlobSize.x, headBlobSize.y);
        headBlob.setPosition(headBlobCenter);
        headBlob.drawWireframe();
        
        headCenterSphere.setRadius(20);
        headCenterSphere.setPosition(headCenter);
        headCenterSphere.draw();
    }
}

void BlobTracker::drawEyeCenter(){
    if(valid){
        eyeCenterSphere.setRadius(20);
        eyeCenterSphere.setPosition(eyeCenter);
        eyeCenterSphere.draw();
        
        contourMesh.clear();
        contourMesh.setMode(OF_PRIMITIVE_LINES);
        
        for(int i = 0; i < countour.size(); i++){
            contourMesh.addVertex(countour[i]);
        }
        contourMesh.draw();
    }
}
