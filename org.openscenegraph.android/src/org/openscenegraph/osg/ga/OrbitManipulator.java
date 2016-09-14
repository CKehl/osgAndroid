package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Quat;
import org.openscenegraph.osg.core.Vec3;

public class OrbitManipulator extends CameraManipulator {
	private static native long nativeCreateManipulator();
	private static native void nativeDispose(long cptr);
	private static native void nativeSetByMatrix(long cptr, long matptr);
	private static native void nativeSetByInverseMatrix(long cptr, long matptr);
	private static native long nativeGetMatrix(long cptr);
	private static native long nativeGetInverseMatrix(long cptr);
	private static native void nativeSetHeading(long cptr, double azimuth);
	private static native double nativeGetHeading(long cptr);
	private static native void nativeSetElevation(long cptr, double elevation);
	private static native double nativeGetElevation(long cptr);
	private static native void nativeSetCenter(long cptr, long center_ptr);
	private static native long nativeGetCenter(long cptr);
	private static native void nativeSetRotation(long cptr, long rotation_ptr);
	private static native long nativeGetRotation(long cptr);
	private static native void nativeSetDistance(long cptr, double distance);
	private static native double nativeGetDistance(long cptr);
	
	protected long _cptr;

	
	public OrbitManipulator()
	{
		super();
		_cptr = nativeCreateManipulator();
	}
	
	public OrbitManipulator(long cptr) {
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
	
	public void setByMatrix(Matrix matrix)
	{
		nativeSetByMatrix(_cptr, matrix.getNativePtr());
	}
	
	public void setByInverseMatrix(Matrix matrix)
	{
		nativeSetByInverseMatrix(_cptr, matrix.getNativePtr());
	}
	
	public Matrix getMatrix()
	{
		return new Matrix(nativeGetMatrix(_cptr));
	}
	
	public Matrix getInverseMatrix()
	{
		return new Matrix(nativeGetInverseMatrix(_cptr));
	}
	
	public void setHeading(double azimuth)
	{
		nativeSetHeading(_cptr, azimuth);
	}
	
	public double getHeading()
	{
		return nativeGetHeading(_cptr);
	}
	
	public void setElevation(double elevation)
	{
		nativeSetElevation(_cptr, elevation);
	}
	
	public double getElevation()
	{
		return nativeGetElevation(_cptr);
	}
	
	public void setCenter(Vec3 center)
	{
		nativeSetCenter(_cptr, center.getNativePtr());
	}
	
	public Vec3 getCenter()
	{
		return new Vec3(nativeGetCenter(_cptr));
	}
	
	public void setRotation(Quat quat)
	{
		nativeSetRotation(_cptr, quat.getNativePtr());
	}
	
	public Quat getRotation()
	{
		return new Quat(nativeGetRotation(_cptr));
	}
	
	public void setDistance(double distance)
	{
		nativeSetDistance(_cptr, distance);
	}
	
	public double getDistance()
	{
		return nativeGetDistance(_cptr);
	}
}
