package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Node;
import org.openscenegraph.osg.core.Vec3;

public class TerrainManipulator extends CameraManipulator {
	private static native void nativeDispose(long cptr);
	private static native long nativeCreateManipulator();
	private static native void nativeSetByMatrix(long cptr, long mptr);
	private static native long nativeGetNode(long cptr);
	private static native void nativeSetNode(long cptr, long nptr);
	private static native void nativeSetTransformation(long cptr, long eye_ptr, long center_ptr, long up_ptr);
	private static native boolean nativeGetVerticalAxisFixed(long cptr);
	private static native void nativeSetVerticalAxisFixed(long cptr, boolean value);
	private static native boolean nativeGetAllowThrow(long cptr);
	private static native void nativeSetAllowThrow(long cptr, boolean allowThrow);
	private static native void nativeHome(long cptr, double delay);
	
	public TerrainManipulator()
	{
		super();
		_cptr = nativeCreateManipulator();
	}
	
	public TerrainManipulator(long cptr) {
		super();
		_cptr = cptr;
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
	
	public Node getNode() {
		return new Node(nativeGetNode(_cptr));
	}
	
	public void setNode(Node node)
	{
		nativeSetNode(_cptr, node.getNativePtr());
	}
	
	public void setTransformation(Vec3 eye, Vec3 center, Vec3 up)
	{
		nativeSetTransformation(_cptr, eye.getNativePtr(), center.getNativePtr(), up.getNativePtr());
	}
	
	public boolean getVerticalAxisFixed() {
		return nativeGetVerticalAxisFixed(_cptr);
	}
	
	public void setVerticalAxisFixed(boolean value) {
		nativeSetVerticalAxisFixed(_cptr, value);
	}
	
	public boolean getAllowThrow() {
		return nativeGetAllowThrow(_cptr);
	}
	
	public void setAllowThrow(boolean allowThrow) {
		nativeSetAllowThrow(_cptr, allowThrow);
	}
	
	@Override
	public void home() {
		nativeHome(_cptr, 0);
	}
}
