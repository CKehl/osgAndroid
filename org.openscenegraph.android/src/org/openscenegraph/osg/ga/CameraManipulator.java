package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Camera;
import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Object;
import org.openscenegraph.osg.core.Vec3;

public class CameraManipulator extends Object {

	private static native void nativeDispose(long cptr);
	private static native void nativeGetHomePosition(long cptr, long eye_ptr, long center_ptr, long up_ptr);
	private static native void nativeSetHomePosition(long cptr, long eye_ptr, long center_ptr, long up_ptr, boolean autoComputeHomePosition);
	private static native void nativeComputeHomePosition(long cptr, long camPtr, boolean useBoundingBox);
	private static native long nativeGetSideVector(long cptr);
	private static native long nativeGetFrontVector(long cptr);
	private static native long nativeGetUpVector(long cptr);
	private static native void nativeSetByMatrix(long cptr, long mptr);
	private static native void nativeSetByInverseMatrix(long cptr, long mptr);
	private static native long nativeGetMatrix(long cptr);
	private static native long nativeGetInverseMatrix(long cptr);
	private static native boolean nativeGetAutoComputeHomePosition(long cptr);
	private static native void nativeSetAutoComputeHomePosition(long cptr, boolean autoComputeHomePosition);
	private static native void nativeHome(long cptr);
	
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
	
	public void computeHomePosition(Camera camera, boolean useBoundingBox) {
		nativeComputeHomePosition(_cptr, camera.getNativePtr(), useBoundingBox);
	}
	
	public Vec3 getSideVector() {
		return new Vec3(nativeGetSideVector(_cptr));
	}
	
	public Vec3 getFrontVector() {
		return new Vec3(nativeGetFrontVector(_cptr));
	}
	
	public Vec3 getUpVector() {
		return new Vec3(nativeGetUpVector(_cptr));
	}
	
	public void setByMatrix(Matrix matrix) {
		nativeSetByMatrix(_cptr, matrix.getNativePtr());
	}
	
	public void setByInverseMatrix(Matrix matrix) {
		nativeSetByInverseMatrix(_cptr, matrix.getNativePtr());
	}
	
	public Matrix getMatrix() {
		return new Matrix(nativeGetMatrix(_cptr));
	}
	
	public Matrix getInverseMatrix() {
		return new Matrix(nativeGetInverseMatrix(_cptr));
	}
	
	public boolean getAutoComputeHomePosition() {
		return nativeGetAutoComputeHomePosition(_cptr);
	}
	
	public void setAutoComputeHomePosition(boolean flag) {
		nativeSetAutoComputeHomePosition(_cptr, flag);
	}
	
	public void home() {
		nativeHome(_cptr);
	}
}
