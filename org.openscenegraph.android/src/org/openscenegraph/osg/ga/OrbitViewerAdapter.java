package org.openscenegraph.osg.ga;

import org.openscenegraph.osg.viewer.Viewer;

import android.view.MotionEvent;
import android.view.View;

public class OrbitViewerAdapter extends ViewerEventAdapter {
	//public abstract boolean onTouch(View v, MotionEvent event);

	public OrbitViewerAdapter(Viewer renderView)
	{
		super(renderView);
	}

	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
        int numPoints = event.getPointerCount();
        GUIEventAdapter ea = null;
        float factor = (numPoints > 1)?1.0f/500.0f:1.0f;
        for(int i = 0; i<numPoints; i++)
        {
        	int action        = event.getActionMasked();
        	//int point         = event.getActionIndex();
        	float x = (numPoints > 1)?(v.getWidth() - event.getX(i)):event.getX(i);
        	x*=factor;
        	float y = event.getY(i)*factor;
        	switch(action)
        	{
        	case MotionEvent.ACTION_DOWN:
        	case MotionEvent.ACTION_POINTER_DOWN:
        		if(ea == null)
        			ea = touchBegan(event.getPointerId(i), 1, x, y );
        		else
        			addTouchPoint( ea.getNativePtr(),  event.getPointerId(i), 1, x, y );
        		break;
        	case MotionEvent.ACTION_UP:
        		v.performClick();
        	case MotionEvent.ACTION_POINTER_UP:
        		if(ea == null)
        			ea = touchEnded(event.getPointerId(i), 4, x, y ,1);
        		else
        			addTouchPoint( ea.getNativePtr(),  event.getPointerId(i), 4, x, y );
        		break;
        	case MotionEvent.ACTION_MOVE:
        		if(ea == null)
        			ea = touchMoved(event.getPointerId(i), 2, x, y );
        		else
        			addTouchPoint( ea.getNativePtr(),  event.getPointerId(i), 2, x, y );
        		break;
        	}
        }
        return true;
	}

	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
        int numPoints = event.getPointerCount();
        GUIEventAdapter ea = null;
        float factor = (numPoints > 1)?1.0f/500.0f:1.0f;
        for(int i = 0; i<numPoints; i++)
        {
        	int action        = event.getActionMasked();
        	//int point         = event.getActionIndex();
        	float x = (numPoints > 1)?(v.getWidth() - event.getX(i)):event.getX(i);
        	x*=factor;
        	float y = event.getY(i)*factor;
        	switch(action)
        	{
        	case MotionEvent.ACTION_DOWN:
        	case MotionEvent.ACTION_POINTER_DOWN:
        		if(ea == null)
        			ea = touchBegan(event.getPointerId(i), 1, x, y );
        		else
        			addTouchPoint( ea.getNativePtr(),  event.getPointerId(i), 1, x, y );
        		break;
        	case MotionEvent.ACTION_UP:
        		v.performClick();
        	case MotionEvent.ACTION_POINTER_UP:
        		if(ea == null)
        			ea = touchEnded(event.getPointerId(i), 4, x, y ,1);
        		else
        			addTouchPoint( ea.getNativePtr(),  event.getPointerId(i), 4, x, y );
        		break;
        	case MotionEvent.ACTION_MOVE:
        		if(ea == null)
        			ea = touchMoved(event.getPointerId(i), 2, x, y );
        		else
        			addTouchPoint( ea.getNativePtr(),  event.getPointerId(i), 2, x, y );
        		break;
        	}
        }
        return true;
	}
}
