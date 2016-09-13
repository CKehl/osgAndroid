package org.openscenegraph.osg.ga;

import java.util.ArrayList;
import java.util.List;

import org.openscenegraph.osg.core.Matrix;
import org.openscenegraph.osg.core.Quat;
import org.openscenegraph.osg.core.Vec3;
import org.openscenegraph.osg.viewer.Viewer;

import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class OrbitAroundCenterAdapter extends OrbitViewerAdapter {
	List<Float> _mx = null, _my = null;
	Vec3 _center;
	OrbitManipulator _om;
	float _verticalAngle = 0f;
	float _horizontalAngle = 0f;
	boolean _trackPointerMotion = false;
	List<Integer> _trackedPointer = null;

	public OrbitAroundCenterAdapter(Viewer renderView) {
		super(renderView);
		// TODO Auto-generated constructor stub
		_trackedPointer = new ArrayList<Integer>();
		_mx = new ArrayList<Float>();
		_my = new ArrayList<Float>();
	}
	
	public OrbitAroundCenterAdapter(Viewer renderView, CameraManipulator cm) {
		super(renderView);
		// TODO Auto-generated constructor stub
		_om = new OrbitManipulator(cm.getNativePtr());
		_trackedPointer = new ArrayList<Integer>();
		_mx = new ArrayList<Float>();
		_my = new ArrayList<Float>();
	}
	
	public void setCenter(Vec3 center) {
		_center = center;
	}
	
	@Override
	public boolean onTouch(View v, MotionEvent event) {
		// TODO Auto-generated method stub
        int numPoints = event.getPointerCount();
        //float factor = (numPoints > 1)?1.0f/500.0f:1.0f;
        float factor = 0.5f;
        for(int i = 0; i<numPoints; i++)
        {
        	int action        = event.getActionMasked();
        	//int point         = event.getActionIndex();
        	//float x = (numPoints > 1)?(v.getWidth() - event.getX(i)):event.getX(i);
        	float x = event.getY(i);
        	float y = event.getY(i);
        	switch(action)
        	{
        	case MotionEvent.ACTION_DOWN:
        	case MotionEvent.ACTION_POINTER_DOWN:
        		_trackedPointer.add(event.getPointerId(i));
        		_trackPointerMotion = true;
        		_mx.add(x);
        		_my.add(y);
        		break;
        	case MotionEvent.ACTION_UP:
        	case MotionEvent.ACTION_POINTER_UP:
        		_trackedPointer.remove(i);
        		_mx.remove(i);
        		_my.remove(i);
        		if(_trackedPointer.isEmpty()==false)
        			_trackPointerMotion=false;
        		break;
        	case MotionEvent.ACTION_MOVE:
        		_horizontalAngle += (x-_mx.get(i))*factor;
        		_verticalAngle += (y-_my.get(i))*factor;
        		_mx.set(i, x);
        		_my.set(i, y);
        		break;
        	}
        }
        
        Vec3 eye = new Vec3(), center = new Vec3(), up = new Vec3();
		_om.getHomePosition(eye, center, up);
		Log.d("OrbitAroundCenterAdapter", "Eye: "+eye.toString());
		Log.d("OrbitAroundCenterAdapter", "Center: "+center.toString());
		Log.d("OrbitAroundCenterAdapter", "Up: "+up.toString());
		if(_center==null)
			return false;
		Vec3 viewPoint = _center.sub(eye);
		Matrix r = new Matrix();
		r.makeRotate(new Quat(_verticalAngle, 0, _horizontalAngle, 0));
		Vec3 newViewPoint = viewPoint.mult(r);
		Vec3 newUpVector = up.mult(r);
		newViewPoint = newViewPoint.sum(_center);
		//_om.setCenter(newViewPoint);
		_om.setHomePosition(newViewPoint, center, newUpVector, false);
		Log.d("OrbitAroundCenterAdapter", "Eye (new): "+newViewPoint.toString());
		Log.d("OrbitAroundCenterAdapter", "Center (new): "+center.toString());
		Log.d("OrbitAroundCenterAdapter", "Up (new): "+newUpVector.toString());
		return true;
	}

}
