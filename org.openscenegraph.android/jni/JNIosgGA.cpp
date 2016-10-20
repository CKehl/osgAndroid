/* @License
 -------------------------------------------------------------------------------
 | osgAndroid - Copyright (C) 2014 Rafael Gait�n, Mirage Technologies S.L.     |
 |                                                                             |
 | This library is free software; you can redistribute it and/or modify        |
 | it under the terms of the GNU Lesser General Public License as published    |
 | by the Free Software Foundation; either version 3 of the License, or        |
 | (at your option) any later version.                                         |
 |                                                                             |
 | This library is distributed in the hope that it will be useful, but         |
 | WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  |
 | or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public     |
 | License for more details.                                                   |
 |                                                                             |
 | You should have received a copy of the GNU Lesser General Public License    |
 | along with this software; if not, write to the Free Software Foundation,    |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.               |
 ---------------------------------------------------------------------------- */

#include <jni.h>
#include <android/log.h>

#include "JNIUtils.h"

#include <osg/Camera>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Matrixf>
#include <osgGA/GUIEventAdapter>
#include <osgGA/OrbitManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/CameraManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/MultiTouchTrackballManipulator>
#include <osgViewer/Viewer>

#include "GLES2ShaderGenVisitor.h"

#define  LOG_TAG    "org.openscenegraph.osg.ga"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern "C"
{

///////////////////////////////////////////////////////////////////////////////
// GUIEventAdapter
///////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_GUIEventAdapter_nativeDispose(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::GUIEventAdapter* ea = reinterpret_cast<osgGA::GUIEventAdapter*>(cptr);
	if(ea == NULL)
		return;
	ea->unref();
}


///////////////////////////////////////////////////////////////////////////////
// Orbit Manipulator
///////////////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeCreateManipulator(JNIEnv *env, jclass)
{
	osgGA::OrbitManipulator* om = new osgGA::OrbitManipulator();
	om->ref();
	return reinterpret_cast<jlong>(om);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeDispose(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om == NULL)
		return;
	om->unref();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetByMatrix(JNIEnv *env, jclass, jlong cptr, jlong matptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(matptr);
	if((om==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	om->setByMatrix(mat);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetByInverseMatrix(JNIEnv *env, jclass, jlong cptr, jlong matptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(matptr);
	if((om==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	om->setByInverseMatrix(mat);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0l;

	osg::Matrixd mat = om->getMatrix();
	osg::RefMatrixf* result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetInverseMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0l;

	osg::RefMatrixf *result = NULL;
	osg::Matrixd mat = om->getInverseMatrix();
	result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetHeading(JNIEnv *env, jclass, jlong cptr, jdouble azimuth )
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return;
	om->setHeading((double)azimuth);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetHeading(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0;
	return om->getHeading();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetElevation(JNIEnv *env, jclass, jlong cptr, jdouble elevation )
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return;
	om->setElevation((double)elevation);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetElevation(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0;
	return om->getElevation();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetCenter(JNIEnv *env, jclass, jlong cptr, jlong center_ptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return;
	RefVec3* v = reinterpret_cast<RefVec3*>(center_ptr);
	if(v==NULL)
		return;
	om->setCenter(*v);
}

//const osg::Vec3d& getCenter() const;
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetCenter(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0l;
	osg::Vec3 v = om->getCenter();
	RefVec3 *r = new RefVec3();
	r->set(v);
	r->ref();
	return reinterpret_cast<jlong>(r);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetRotation(JNIEnv *env, jclass, jlong cptr, jlong rotation_ptr )
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return;
	RefQuat *q = reinterpret_cast<RefQuat *>(rotation_ptr);
	if(q==NULL)
		return;
	om->setRotation(*q);
}

//const osg::Quat& getRotation() const;
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetRotation(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0l;
	osg::Quat Q = om->getRotation();
	RefQuat *q = new RefQuat();
	q->set(Q.asVec4());
	q->ref();
	return reinterpret_cast<jlong>(q);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeSetDistance(JNIEnv *env, jclass, jlong cptr, jdouble distance )
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return;
	om->setDistance((double)distance);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_OrbitManipulator_nativeGetDistance(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::OrbitManipulator* om = reinterpret_cast<osgGA::OrbitManipulator*>(cptr);
	if(om==NULL)
		return 0;
	return om->getDistance();
}

//set/get transformation

///////////////////////////////////////////////////////////////////////////////
// First-Person Manipulator
///////////////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeCreateManipulator(JNIEnv *env, jclass)
{
	osgGA::FirstPersonManipulator* fpm = new osgGA::FirstPersonManipulator();
	fpm->ref();
	return reinterpret_cast<jlong>(fpm);
}

///////////////////////////////////////////////////////////////////////////////
// Terrain Manipulator
///////////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeDispose(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm == NULL)
		return;
	tm->unref();
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeCreateManipulator(JNIEnv *env, jclass)
{
	osgGA::TerrainManipulator* tm = new osgGA::TerrainManipulator();
	tm->ref();
	return reinterpret_cast<jlong>(tm);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeSetByMatrix(JNIEnv *env, jclass, jlong cptr, jlong mptr) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(mptr);
	if((tm==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	tm->setByMatrix(mat);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeSetNode(JNIEnv *env, jclass, jlong cptr, jlong nptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	osg::Node* node = reinterpret_cast<osg::Node*>(nptr);
	if((tm==NULL) || (node==NULL))
		return;
	tm->setNode(node);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeSetTransformation(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong center_ptr, jlong up_ptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
    RefVec3 *center = reinterpret_cast<RefVec3 *>(center_ptr);
    RefVec3 *up = reinterpret_cast<RefVec3 *>(up_ptr);
    if(tm != NULL && eye !=NULL && center != NULL && up != NULL)
    {
    	tm->setTransformation(*eye, *center, *up);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Camera Manipulator
///////////////////////////////////////////////////////////////////////////////

/*
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeCreateManipulator(JNIEnv *env, jclass)
{
	osgGA::CameraManipulator* cm = new osgGA::CameraManipulator();
	cm->ref();
	return reinterpret_cast<jlong>(cm);
}
*/

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeDispose(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm == NULL)
		return;
	cm->unref();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetHomePosition(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong center_ptr, jlong up_ptr)
{
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
    RefVec3 *center = reinterpret_cast<RefVec3 *>(center_ptr);
    RefVec3 *up = reinterpret_cast<RefVec3 *>(up_ptr);
    if(cm != NULL && eye !=NULL && center != NULL && up != NULL)
    {
    	osg::Vec3d eyeD, centerD, upD;
        cm->getHomePosition(eyeD, centerD, upD);
        eye->set(eyeD.x(), eyeD.y(), eyeD.z());
        center->set(centerD.x(), centerD.y(), centerD.z());
        up->set(upD.x(), upD.y(), upD.z());
    }
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeSetHomePosition(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong center_ptr, jlong up_ptr, jboolean autoComputeHomePosition)
{
	bool _autoComputeHomePosition = ((autoComputeHomePosition==JNI_TRUE)?true:false);
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
    RefVec3 *center = reinterpret_cast<RefVec3 *>(center_ptr);
    RefVec3 *up = reinterpret_cast<RefVec3 *>(up_ptr);
    if(cm != NULL && eye !=NULL && center != NULL && up != NULL)
    {
        cm->setHomePosition(*eye,*center,*up, _autoComputeHomePosition);
        cm->home(0);
    }
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeComputeHomePosition(JNIEnv* env, jclass, jlong cptr, jlong camPtr, jboolean useBoundingBox)
{
	bool _useBoundingBox = ((useBoundingBox==JNI_TRUE)?true:false);
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	osg::Camera* c = reinterpret_cast<osg::Camera*>(camPtr);
	if((cm==NULL) || (c==NULL))
		return;
	cm->computeHomePosition(c, _useBoundingBox);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetSideVector(JNIEnv *env, jclass, jlong cptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return 0l;
	osg::Vec3d eyeD, centerD, upD;
    cm->getHomePosition(eyeD, centerD, upD);
    osg::CoordinateFrame cf = cm->getCoordinateFrame(eyeD);
	osg::Vec3 v = cm->getSideVector(cf);
	RefVec3 *r = new RefVec3();
	r->set(v);
	r->ref();
	return reinterpret_cast<jlong>(r);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetFrontVector(JNIEnv *env, jclass, jlong cptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return 0l;
	osg::Vec3d eyeD, centerD, upD;
    cm->getHomePosition(eyeD, centerD, upD);
    osg::CoordinateFrame cf = cm->getCoordinateFrame(eyeD);
	osg::Vec3 v = cm->getFrontVector(cf);
	RefVec3 *r = new RefVec3();
	r->set(v);
	r->ref();
	return reinterpret_cast<jlong>(r);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetUpVector(JNIEnv *env, jclass, jlong cptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return 0l;
	osg::Vec3d eyeD, centerD, upD;
    cm->getHomePosition(eyeD, centerD, upD);
    osg::CoordinateFrame cf = cm->getCoordinateFrame(eyeD);
	osg::Vec3 v = cm->getUpVector(cf);
	RefVec3 *r = new RefVec3();
	r->set(v);
	r->ref();
	return reinterpret_cast<jlong>(r);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeSetByMatrix(JNIEnv *env, jclass, jlong cptr, jlong mptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(mptr);
	if((cm==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	cm->setByMatrix(mat);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeSetByInverseMatrix(JNIEnv *env, jclass, jlong cptr, jlong mptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(mptr);
	if((cm==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	cm->setByInverseMatrix(mat);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return 0l;

	osg::Matrixd mat = cm->getMatrix();
	osg::RefMatrixf* result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetInverseMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return 0l;

	osg::RefMatrixf *result = NULL;
	osg::Matrixd mat = cm->getInverseMatrix();
	result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT jboolean JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeGetAutoComputeHomePosition(JNIEnv *env, jclass, jlong cptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return 0l;
	bool flag = cm->getAutoComputeHomePosition();
	return ((flag==true)?JNI_TRUE:JNI_FALSE);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeSetAutoComputeHomePosition(JNIEnv *env, jclass, jlong cptr, jboolean autoComputeHomePosition) {
	bool _autoComputeHomePosition = ((autoComputeHomePosition==JNI_TRUE)?true:false);
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm!=NULL)
		cm->setAutoComputeHomePosition(_autoComputeHomePosition);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeHome(JNIEnv *env, jclass, jlong cptr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm!=NULL)
		cm->home(0.0);
}

///////////////////////////////////////////////////////////////////////////////
//Touch Events
///////////////////////////////////////////////////////////////////////////////
JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_ViewerEventAdapter_nativeTouchBegan(JNIEnv * /*env*/, jobject /*obj*/, jlong viewer_cptr, jint index, jint state, jfloat x, jfloat y)
{
	osgViewer::Viewer *v = reinterpret_cast<osgViewer::Viewer*> (viewer_cptr);
	if (v == NULL)
		return 0;
	osgGA::GUIEventAdapter* me = v->getEventQueue()->touchBegan(index,(osgGA::GUIEventAdapter::TouchPhase)state,x,y);
	me->ref();
	return reinterpret_cast<jlong>(me);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_ViewerEventAdapter_nativeTouchMoved(JNIEnv * /*env*/, jobject /*obj*/, jlong viewer_cptr, jint index, jint state, jfloat x, jfloat y)
{
	osgViewer::Viewer *v = reinterpret_cast<osgViewer::Viewer*> (viewer_cptr);
	if (v == NULL)
		return 0;
	osgGA::GUIEventAdapter* me = v->getEventQueue()->touchMoved(index,(osgGA::GUIEventAdapter::TouchPhase)state,x,y);
	me->ref();
	return reinterpret_cast<jlong>(me);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_ViewerEventAdapter_nativeTouchEnded(JNIEnv * /*env*/, jobject /*obj*/, jlong viewer_cptr, jint index, jint state, jfloat x, jfloat y, jint nTaps)
{
	osgViewer::Viewer *v = reinterpret_cast<osgViewer::Viewer*> (viewer_cptr);
	if (v == NULL)
		return 0;
	osgGA::GUIEventAdapter* me = v->getEventQueue()->touchEnded(index,(osgGA::GUIEventAdapter::TouchPhase)state,x,y,nTaps);
	me->ref();
	return reinterpret_cast<jlong>(me);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_ViewerEventAdapter_nativeAddTouchPoint(JNIEnv * /*env*/, jobject /*obj*/, jlong viewer_cptr, jlong eaCptr, jint index, jint state, jfloat x, jfloat y)
{
	osgViewer::Viewer *v = reinterpret_cast<osgViewer::Viewer*> (viewer_cptr);
	if (v == NULL)
		return;
	osgGA::GUIEventAdapter* me = reinterpret_cast<osgGA::GUIEventAdapter*> (eaCptr);
	if (me == NULL)
		return;
	me->addTouchPoint(index,(osgGA::GUIEventAdapter::TouchPhase)state,x,y);
}

}
