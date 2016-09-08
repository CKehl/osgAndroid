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
#include <osgGA/CameraManipulator>

#include "GLES2ShaderGenVisitor.h"

#define  LOG_TAG    "org.openscenegraph.osg.ga"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern "C"
{

JNIEXPORT void JNICALL Java_org_openscenegraph_osg_ga_GUIEventAdapter_nativeDispose(JNIEnv *env, jclass, jlong cptr)
{
	osgGA::GUIEventAdapter* ea = reinterpret_cast<osgGA::GUIEventAdapter*>(cptr);
	if(ea == NULL)
		return;
	ea->unref();
}

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


}
