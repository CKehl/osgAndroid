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
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
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

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_GUIEventAdapter_nativeCreateEventAdapter(JNIEnv* env, jclass) {
	osgGA::GUIEventAdapter* ea = new osgGA::GUIEventAdapter();
	if(ea==NULL)
		return 0l;
	ea->ref();
	return reinterpret_cast<jlong>(ea);
}


///////////////////////////////////////////////////////////////////////////////
// GUIActionAdapter
///////////////////////////////////////////////////////////////////////////////
//JNIEXPORT long JNICALL Java_org_openscenegraph_osg_ga_GUIActionAdapter_nativeCreateActionAdapter(JNIEnv* env, jclass) {
//	osgGA::GUIActionAdapter* us = new osgGA::GUIActionAdapter();
//	if(us==NULL)
//		return 0l;
//	us->ref();
//	return reinterpret_cast<jlong>(us);
//}
//
//JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_GUIActionAdapter_nativeDispose(JNIEnv* env, jclass, jlong cptr) {
//	osgGA::GUIActionAdapter* us = reinterpret_cast<osgGA::GUIActionAdapter*>(cptr);
//	if(us == NULL)
//		return;
//	us->unref();
//}
//=============================================================================

///////////////////////////////////////////////////////////////////////////////
// GUIEventHandler
///////////////////////////////////////////////////////////////////////////////


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

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeDispose(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm == NULL)
		return;
	fpm->unref();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetByMatrix(JNIEnv *env, jclass, jlong cptr, jlong mptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(mptr);
	if((fpm==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	fpm->setByMatrix(mat);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetByInverseMatrix(JNIEnv *env, jclass, jlong cptr, jlong mptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(mptr);
	if((fpm==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	fpm->setByInverseMatrix(mat);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return 0l;

	osg::Matrixd mat = fpm->getMatrix();
	osg::RefMatrixf* result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetInverseMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return 0l;

	osg::Matrixd mat = fpm->getInverseMatrix();
	osg::RefMatrixf* result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetTransformationByRotation(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong rotation_ptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
	RefQuat *q = reinterpret_cast<RefQuat *>(rotation_ptr);
    if(fpm != NULL && eye !=NULL && q!=NULL)
    {
    	fpm->setTransformation(*eye, *q);
    }
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetTransformationByViewParameters(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong center_ptr, jlong up_ptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
    RefVec3 *center = reinterpret_cast<RefVec3 *>(center_ptr);
    RefVec3 *up = reinterpret_cast<RefVec3 *>(up_ptr);
    if(fpm != NULL && eye !=NULL && center != NULL && up != NULL)
    {
    	fpm->setTransformation(*eye, *center, *up);
    }
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetTransformationByRotation(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong rotation_ptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
	RefQuat *q = reinterpret_cast<RefQuat *>(rotation_ptr);
    if(fpm != NULL && eye !=NULL && q!=NULL)
    {
    	osg::Vec3d eyeD;
    	osg::Quat rotationD;
    	fpm->getTransformation(eyeD, rotationD);
        eye->set(eyeD.x(), eyeD.y(), eyeD.z());
        q->set(rotationD.x(), rotationD.y(), rotationD.z(), rotationD.w());
    }
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetTransformationByViewParameters(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong center_ptr, jlong up_ptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
    RefVec3 *center = reinterpret_cast<RefVec3 *>(center_ptr);
    RefVec3 *up = reinterpret_cast<RefVec3 *>(up_ptr);
    if(fpm != NULL && eye !=NULL && center != NULL && up != NULL)
    {
    	osg::Vec3d eyeD, centerD, upD;
    	fpm->getTransformation(eyeD, centerD, upD);
        eye->set(eyeD.x(), eyeD.y(), eyeD.z());
        center->set(centerD.x(), centerD.y(), centerD.z());
        up->set(upD.x(), upD.y(), upD.z());
    }
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetVelocity(JNIEnv *env, jclass, jlong cptr, jdouble velocity)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return;
	fpm->setVelocity((double)velocity);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetVelocity(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return 0;
	return fpm->getVelocity();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetAcceleration(JNIEnv *env, jclass, jlong cptr, jdouble acceleration, jboolean relativeToModelSize)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return;
	fpm->setAcceleration((double)acceleration, relativeToModelSize);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetAcceleration(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return 0;
	return fpm->getAcceleration();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetMaxVelocity(JNIEnv *env, jclass, jlong cptr, jdouble maxVelocity, jboolean relativeToModelSize)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return;
	fpm->setMaxVelocity((double)maxVelocity, relativeToModelSize);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetMaxVelocity(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return 0;
	return fpm->getMaxVelocity();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeSetWheelMovement(JNIEnv *env, jclass, jlong cptr, jdouble wheelMovement, jboolean relativeToModelSize)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return;
	fpm->setWheelMovement((double)wheelMovement, relativeToModelSize);
}

JNIEXPORT jdouble JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeGetWheelMovement(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return 0;
	return fpm->getWheelMovement();
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_FirstPersonManipulator_nativeHome(JNIEnv *env, jclass, jlong cptr, jdouble delay)
{
	osgGA::FirstPersonManipulator* fpm = reinterpret_cast<osgGA::FirstPersonManipulator*>(cptr);
	if(fpm==NULL)
		return;
	fpm->home((double)delay);
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
	osgGA::TerrainManipulator* tm = new osgGA::TerrainManipulator(osgGA::TerrainManipulator::DEFAULT_SETTINGS);
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

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeSetByInverseMatrix(JNIEnv *env, jclass, jlong cptr, jlong mptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	osg::RefMatrixf *m = reinterpret_cast<osg::RefMatrixf *>(mptr);
	if((tm==NULL) || (m==NULL))
		return;
	osg::Matrixd mat = osg::Matrixd(*m);
	tm->setByInverseMatrix(mat);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeGetMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return 0l;

	osg::Matrixd mat = tm->getMatrix();
	osg::RefMatrixf* result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeGetInverseMatrix(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return 0l;

	osg::Matrixd mat = tm->getInverseMatrix();
	osg::RefMatrixf* result = new osg::RefMatrixf(mat);
	result->ref();
	return reinterpret_cast<jlong>(result);
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

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeGetTransformation(JNIEnv *env, jclass, jlong cptr, jlong eye_ptr, jlong center_ptr, jlong up_ptr)
{
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
    RefVec3 *eye = reinterpret_cast<RefVec3 *>(eye_ptr);
    RefVec3 *center = reinterpret_cast<RefVec3 *>(center_ptr);
    RefVec3 *up = reinterpret_cast<RefVec3 *>(up_ptr);
    if(tm != NULL && eye !=NULL && center != NULL && up != NULL)
    {
    	osg::Vec3d eyeD, centerD, upD;
    	tm->getTransformation(eyeD, centerD, upD);
        eye->set(eyeD.x(), eyeD.y(), eyeD.z());
        center->set(centerD.x(), centerD.y(), centerD.z());
        up->set(upD.x(), upD.y(), upD.z());
    }
}

JNIEXPORT jlong JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeGetNode(JNIEnv *env, jclass, jlong cptr) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return 0l;
	osg::Node* node = tm->getNode();
	node->ref();
	return reinterpret_cast<jlong>(node);
}

//JNIEXPORT jboolean JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeIntersect(JNIEnv* env, jclass, jlong cptr, jlong startPtr, jlong endPtr, jlong intersectionPtr) {
//	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(tm);
//	if(tm==NULL)
//		return JNI_FALSE;
//	RefVec3* startRef = reinterpret_cast<RefVec3*>(startPtr);
//	if(startRef==NULL)
//		return JNI_FALSE;
//	RefVec3* endRef = reinterpret_cast<RefVec3*>(endPtr);
//	if(endRef==NULL)
//		return JNI_FALSE;
//	RefVec3* intersectionRef = reinterpret_cast<RefVec3*>(intersectionPtr);
//	if(intersectionRef==NULL)
//		return JNI_FALSE;
//	osg::Vec3d start(startRef->x(), startRef->y(), startRef->z());
//	osg::Vec3d end(endRef->x(), endRef->y(), endRef->z());
//	osg::Vec3d intersection;
//	bool result = tm->intersect(start, end, intersection);
//	jboolean ret = JNI_FALSE;
//	if(result) {
//		intersectionRef->set(intersection.x(), intersection.y(), intersection.z());
//		ret = JNI_TRUE;
//	}
//	return ret;
//}

JNIEXPORT jboolean JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeGetVerticalAxisFixed(JNIEnv *env, jclass, jlong cptr) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return JNI_FALSE;
	bool value = tm->getVerticalAxisFixed();
	return ((value==true)?JNI_TRUE:JNI_FALSE);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeSetVerticalAxisFixed(JNIEnv *env, jclass, jlong cptr, jboolean value) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return;
	tm->setVerticalAxisFixed(value);
}

JNIEXPORT jboolean JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeGetAllowThrow(JNIEnv *env, jclass, jlong cptr) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return JNI_FALSE;
	bool allowThrow = tm->getAllowThrow();
	return ((allowThrow==true)?JNI_TRUE:JNI_FALSE);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeSetAllowThrow(JNIEnv *env, jclass, jlong cptr, jboolean allowThrow) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return;
	tm->setAllowThrow(allowThrow);
}

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_TerrainManipulator_nativeHome(JNIEnv *env, jclass, jlong cptr, jdouble delay) {
	osgGA::TerrainManipulator* tm = reinterpret_cast<osgGA::TerrainManipulator*>(cptr);
	if(tm==NULL)
		return;
	tm->home((double)delay);
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
		return JNI_FALSE;
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

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeInit(JNIEnv* env, jclass, jlong cptr, jlong eaPtr, jlong usPtr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return;
	osgGA::GUIEventAdapter* ea = reinterpret_cast<osgGA::GUIEventAdapter*>(eaPtr);
	if(ea==NULL)
		return;
	osgGA::GUIActionAdapter* us = reinterpret_cast<osgGA::GUIActionAdapter*>(usPtr);
	if(us==NULL)
		return;
	cm->init(*ea, *us);
}

JNIEXPORT jboolean JNICALL Java_org_openscenegraph_osg_ga_CameraManipulator_nativeHandle(JNIEnv* env, jclass, jlong cptr, jlong eaPtr, jlong usPtr) {
	osgGA::CameraManipulator* cm = reinterpret_cast<osgGA::CameraManipulator*>(cptr);
	if(cm==NULL)
		return JNI_FALSE;
	osgGA::GUIEventAdapter* ea = reinterpret_cast<osgGA::GUIEventAdapter*>(eaPtr);
	if(ea==NULL)
		return JNI_FALSE;
	osgGA::GUIActionAdapter* us = reinterpret_cast<osgGA::GUIActionAdapter*>(usPtr);
	if(us==NULL)
		return JNI_FALSE;
	bool result = cm->handle(*ea, *us);
	return ((result==true)?JNI_TRUE:JNI_FALSE);
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
