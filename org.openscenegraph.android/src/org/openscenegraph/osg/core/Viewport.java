package org.openscenegraph.osg.core;

public class Viewport extends Object {
	private static native void nativeDispose(long cptr);
	private static native long nativeCreateViewport();
	private static native void nativeSetViewport(float x, float y, float width, float height);
	private static native float nativeX(long cptr);
	private static native float nativeY(long cptr);
	private static native double nativeAspectRatio(long cptr);
	private static native float nativeWidth(long cptr);
	private static native float nativeHeight(long cptr);
	private static native long nativeComputeWindowMatrix(long cptr);

	public Viewport() {
		super();
		_cptr = nativeCreateViewport();
	}
	
	public Viewport(long cptr) {
		super();
		_cptr = cptr;
	}
	
	@Override
	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}
	
	@Override
	public void dispose() {
		if(_cptr != 0)
			nativeDispose(_cptr);
		_cptr = 0;
	}
	
	public void setViewport(float x, float y, float width, float height) {
		nativeSetViewport(x, y, width, height);
	}
	
	public float x() {
		return nativeX(_cptr);
	}
	
	public float y() {
		return nativeY(_cptr);
	}
	
	public double aspectRatio() {
		return nativeAspectRatio(_cptr);
	}
	
	public float width() {
		return nativeWidth(_cptr);
	}
	
	public float height() {
		return nativeHeight(_cptr);
	}
	
	public Matrix computeWindowMatrix() {
		return new Matrix(nativeComputeWindowMatrix(_cptr));
	}
}
