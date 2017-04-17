/* @License 
 -------------------------------------------------------------------------------
 | osgAndroid - Copyright (C) 2012 Rafael Gait�n, Mirage Technologies S.L.     |
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
package org.openscenegraph.osg;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import android.content.Context;
import android.util.Log;

public class Library {
	private static boolean initialized = false;
	private static String TAG = "OpenSceneGraph-Android Library";

	public static void initLibrary(String glesVersion) {
		try {
			if (!initialized) {
				System.loadLibrary("gnustl_shared");
				System.loadLibrary("jniosg-"+ glesVersion);
				Log.i(TAG, "Successfully initialized");
				initialized = true;
			}
		} catch (Exception e) {
			Log.e(TAG, e.getMessage());
		}
	}
	
	public static boolean checkGL20Support( Context context )
	{
	    EGL10 egl = (EGL10) EGLContext.getEGL();       
	    EGLDisplay display = egl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);

	    int[] version = new int[2];
	    egl.eglInitialize(display, version);

	    int EGL_OPENGL_ES2_BIT = 4;
	    int[] configAttribs =
	    {
	        EGL10.EGL_RED_SIZE, 4,
	        EGL10.EGL_GREEN_SIZE, 4,
	        EGL10.EGL_BLUE_SIZE, 4,
	        EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	        EGL10.EGL_NONE
	    };

	    EGLConfig[] configs = new EGLConfig[10];
	    int[] num_config = new int[1];
	    egl.eglChooseConfig(display, configAttribs, configs, 10, num_config);     
	    egl.eglTerminate(display);
	    return num_config[0] > 0;
	} 
}
