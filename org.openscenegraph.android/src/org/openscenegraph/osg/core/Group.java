/* @License 
 -------------------------------------------------------------------------------
 | osgAndroid - Copyright (C) 2012 Rafael Gait�n, Mirage Technologies S.L.     |
 |                                                                             |
 | This library is free software; you can redistribute it and/or modify        |
 | it under the terms of the GNU Lesser General Public License as published    |
 | by the Free Software Foundation; either version 3 of the License, or        |
 | (at your option) any later version.                                         |
 |                                                                             |
 | This library is distributed in the hope that it will be useful, but         |
 | WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  |
 | or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public     |
 | License for more details.                                                   |
 |                                                                             |
 | You should have received a copy of the GNU Lesser General Public License    |
 | along with this software; if not, write to the Free Software Foundation,    |
 | Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.               |
 ---------------------------------------------------------------------------- */
package org.openscenegraph.osg.core;


public class Group extends Node {

	private static native long nativeCreateGroup();
	private static native void nativeDispose(long cptr);
	private static native boolean nativeAddChild(long cptr, long node);
	private static native boolean nativeRemoveChild(long cptr, long node);
	private static native int nativeGetNumChildren(long cptr);
	private static native long nativeGetChild(long cptr, int i);
	private static native void nativeSetActiveLight(long cptr, long pos_ptr);
	
	public Group(long cptr) {
		super(cptr);	
	}
	
	@Override
	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}
	
	public Group() {
		_cptr = nativeCreateGroup();
	}

	public boolean addChild(Node node) {
		return nativeAddChild(_cptr, node.getNativePtr());
	}
	
	public boolean removeChild(Node node) {
		return nativeRemoveChild(_cptr, node.getNativePtr());
	}
	
	public int getNumChildren() {
		return nativeGetNumChildren(_cptr);
	}
	
	public Node getChild(int index)
	{
		return new Node(nativeGetChild(_cptr, index));
	}
	
	public Node getLastChild()
	{
		return new Node(nativeGetChild(_cptr, getNumChildren()-1));
	}

	public void setActiveLight(Vec4 position) {
		nativeSetActiveLight(_cptr, position.getNativePtr());
	}
	
}
