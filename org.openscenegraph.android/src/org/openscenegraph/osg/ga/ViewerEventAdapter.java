package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.core.Object;
import org.openscenegraph.osg.viewer.Viewer;

public abstract class ViewerEventAdapter extends Object {
	private native long nativeTouchBegan   (long viewer_cptr, int index, int state,float x, float y);
	private native long nativeTouchEnded   (long viewer_cptr, int index, int state,float x, float y, int nTaps);
	private native long nativeTouchMoved   (long viewer_cptr, int index, int state,float x, float y);
	private native void nativeAddTouchPoint(long viewer_cptr, long eaCptr, int index, int state,float x, float y);
	
	Viewer _renderView = null;

	protected ViewerEventAdapter() {
		
	}
	
	protected ViewerEventAdapter(Viewer renderView) {
		_renderView = renderView;
	}
	
	protected GUIEventAdapter touchBegan(int index, int state, float x, float y)
	{
		return new GUIEventAdapter(nativeTouchBegan(_renderView.getNativePtr(), index, state, x, y));
	}
	
	protected GUIEventAdapter touchEnded(int index, int state, float x, float y, int nTaps){
		return new GUIEventAdapter(nativeTouchEnded(_renderView.getNativePtr(), index, state, x, y, nTaps));
	}
	
	protected GUIEventAdapter touchMoved(int index, int state,float x, float y)
	{
		return new GUIEventAdapter(nativeTouchMoved(_renderView.getNativePtr(), index, state, x, y));
	}
	
	protected void addTouchPoint(long eaCptr, int index, int state,float x, float y)
	{
		nativeAddTouchPoint(_renderView.getNativePtr(), eaCptr, index, state, x, y);
	}
}
