package org.openscenegraph.osg.ga;

public class FirstPersonManipulator extends CameraManipulator {
	private static native long nativeCreateManipulator();

	public FirstPersonManipulator(long cptr) {
		super(cptr);
	}

	public FirstPersonManipulator() {
		_cptr = nativeCreateManipulator();
	}
}
