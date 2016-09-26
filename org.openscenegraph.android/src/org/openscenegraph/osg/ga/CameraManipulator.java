package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Object;
import org.openscenegraph.osg.core.Vec3;

public class CameraManipulator extends Object {

	private static native void nativeDispose(long cptr);
	private static native void nativeGetHomePosition(long cptr, long eye_ptr, long center_ptr, long up_ptr);
	private static native void nativeSetHomePosition(long cptr, long eye_ptr, long center_ptr, long up_ptr, boolean autoComputeHomePosition);
	
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
	
	public void getHomePosition(Vec3 eye, Vec3 center, Vec3 up) {
		nativeGetHomePosition(_cptr, eye.getNativePtr(), center.getNativePtr(), up.getNativePtr());
	}
	
	public void setHomePosition(Vec3 eye, Vec3 center, Vec3 up, boolean autoComputeHomePosition) {
		nativeSetHomePosition(_cptr, eye.getNativePtr(), center.getNativePtr(), up.getNativePtr(), autoComputeHomePosition);
	}
	
	public Vec3 getSideVector() {
		return null;
	}
	
	public Vec3 getFrontVector() {
		return null;
	}
	
	public Vec3 getUpVector() {
		return null;
	}
	
	public void setByMatrix() {
		
	}
	
	public void setByInverseMatrix() {
		
	}
	
	public Matrix getMatrix() {
		return null;
	}
	
	public Matrix getInverseMatrix() {
		return null;
	}
	
	public boolean getAutoComputeHomePosition() {
		return false;
	}
	
	public void setAutoComputeHomePosition(boolean flag) {
		
	}
	
	public void home() {
		
	}
}
