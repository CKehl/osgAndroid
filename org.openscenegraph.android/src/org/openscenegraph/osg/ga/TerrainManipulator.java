package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Node;
import org.openscenegraph.osg.core.Vec3;

public class TerrainManipulator extends CameraManipulator {
	private static native void nativeDispose(long cptr);
	private static native long nativeCreateManipulator();
	private static native void nativeSetByMatrix(long cptr, long mptr);
	private static native void nativeSetNode(long cptr, long nptr);
	private static native void nativeSetTransformation(long cptr, long eye_ptr, long center_ptr, long up_ptr);
	
	public TerrainManipulator()
	{
		super();
		_cptr = nativeCreateManipulator();
	}
	
	public TerrainManipulator(long cptr) {
		super(cptr);
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
	
	public void setNode(Node node)
	{
		nativeSetNode(_cptr, node.getNativePtr());
	}
	
	public void setTransformation(Vec3 eye, Vec3 center, Vec3 up)
	{
		nativeSetTransformation(_cptr, eye.getNativePtr(), center.getNativePtr(), up.getNativePtr());
	}
}
