package com.mesai0.blogspot.ZeptoLabTest;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView.Renderer;
/**
A wrapper of the game engine native renderer. 
*/	

public class RendererWrapper implements Renderer {

	private int width;
	private int height;
	
	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		width = 0;
		height = 0;
		Native.onSurfaceCreated();	
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// To ignore the redundant calls of onSurfaceChanged !!
		if(this.width != width && this.height != height){
			this.width = width;
			this.height = height;
			Native.onSurfaceChanged(width, height);
		}
		
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		Native.onDrawFrame();
	}
   
	public void onTouchEventDown()
	{
		Native.onTouchEventDown();
	}
	
	public void onTouchEventUp()
	{
		Native.onTouchEventUp();
	}
	
	
	
}