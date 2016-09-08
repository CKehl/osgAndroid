package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Object;

public class CameraManipulator extends Object {

	private static native void nativeDispose(long cptr);
	
	public CameraManipulator()
	{
		super();
	}
	
	public CameraManipulator(long cptr) {
		super(cptr);
	}
	
	public void dispose() {
		super.dispose();
	}
	
	@Override
	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}
	
}
