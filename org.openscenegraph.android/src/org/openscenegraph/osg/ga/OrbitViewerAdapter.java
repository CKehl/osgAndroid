package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.viewer.Viewer;

import android.view.MotionEvent;
import android.view.View;

public abstract class OrbitViewerAdapter extends ViewerEventAdapter {
	
	public abstract boolean onTouch(View v, MotionEvent event);
	
	public OrbitViewerAdapter(Viewer renderView)
	{
		super(renderView);
	}

}
