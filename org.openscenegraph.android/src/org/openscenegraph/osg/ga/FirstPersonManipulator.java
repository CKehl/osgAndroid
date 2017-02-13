package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Quat;
import org.openscenegraph.osg.core.Vec3;

public class FirstPersonManipulator extends CameraManipulator {
	private static native long nativeCreateManipulator();
	private static native void nativeDispose(long cptr);
	private static native void nativeSetByMatrix(long cptr, long mptr);
	private static native void nativeSetByInverseMatrix(long cptr, long mptr);
	private static native long nativeGetMatrix(long cptr);
	private static native long nativeGetInverseMatrix(long cptr);
	private static native void nativeSetTransformationByRotation(long cptr, long eye_ptr, long rotation_ptr);
	private static native void nativeGetTransformationByRotation(long cptr, long eye_ptr, long rotation_ptr);
	private static native void nativeSetTransformationByViewParameters(long cptr, long eye_ptr, long center_ptr, long up_ptr);
	private static native void nativeGetTransformationByViewParameters(long cptr, long eye_ptr, long center_ptr, long up_ptr);
	private static native double nativeGetVelocity(long cptr);
	private static native void nativeSetVelocity(long cptr, double velocity);
	private static native double nativeGetAcceleration(long cptr);
	private static native void nativeSetAcceleration(long cptr, double acceleration, boolean relativeToModelSize);
	private static native double nativeGetMaxVelocity(long cptr);
	private static native void nativeSetMaxVelocity(long cptr, double maxVelocity, boolean relativeToModelSize);
	private static native double nativeGetWheelMovement(long cptr);
	private static native void nativeSetWheelMovement(long cptr, double wheelMovement, boolean relativeToModelSize);
	private static native void nativeHome(long cptr, double delay);

	public FirstPersonManipulator(long cptr) {
		super(cptr);
	}

	public FirstPersonManipulator() {
		_cptr = nativeCreateManipulator();
	}
	
	public void dispose() {
		if(_cptr != 0)
			nativeDispose(_cptr);
		_cptr = 0;
	}
	
	@Override
	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}
	
	public void setByMatrix(Matrix matrix)
	{
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

	public void setTransformation(Vec3 eye, Quat rotation)
	{
		nativeSetTransformationByRotation(_cptr, eye.getNativePtr(), rotation.getNativePtr());
	}
	
	public void getTransformation(Vec3 eye, Quat rotation)
	{
		nativeGetTransformationByRotation(_cptr, eye.getNativePtr(), rotation.getNativePtr());
	}

	public void setTransformation(Vec3 eye, Vec3 center, Vec3 up)
	{
		nativeSetTransformationByViewParameters(_cptr, eye.getNativePtr(), center.getNativePtr(), up.getNativePtr());
	}
	
	public void getTransformation(Vec3 eye, Vec3 center, Vec3 up)
	{
		nativeGetTransformationByViewParameters(_cptr, eye.getNativePtr(), center.getNativePtr(), up.getNativePtr());
	}
	
	public void setVelocity(double velocity) {
		nativeSetVelocity(_cptr, velocity);
	}
	
	public double getVelocity() {
		return nativeGetVelocity(_cptr);
	}
	
	public void setAcceleration(double acceleration, boolean relativeToModelSize) {
		nativeSetAcceleration(_cptr, acceleration, relativeToModelSize);
	}
	
	public double getAcceleration() {
		return nativeGetAcceleration(_cptr);
	}
	
	public void setMaxVelocity(double maxVelocity, boolean relativeToModelSize) {
		nativeSetMaxVelocity(_cptr, maxVelocity, relativeToModelSize);
	}
	
	public double getMaxVelocity() {
		return nativeGetMaxVelocity(_cptr);
	}
	
	public void setWheelMovement(double wheelMovement, boolean relativeToModelSize) {
		nativeSetWheelMovement(_cptr, wheelMovement, relativeToModelSize);
	}
	
	public double getWheelMovement() {
		return nativeGetWheelMovement(_cptr);
	}
	
	@Override
	public void home() {
		nativeHome(_cptr, 0);
	}
}
