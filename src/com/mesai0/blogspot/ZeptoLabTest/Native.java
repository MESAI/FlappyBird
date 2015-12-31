package com.mesai0.blogspot.ZeptoLabTest;

/**
This class is responsible for the communication with java code and the native code.
*/	
public class Native {
	// The game engine library
    static {
        System.loadLibrary("game");
    }
 
    public static native void onSurfaceCreated();
 
    public static native void onSurfaceChanged(int width, int height);
 
    public static native void onDrawFrame();
    
    public static native void onTouchEventDown();
    
    public static native void onTouchEventUp();
    
    public static native void resetGame();
    
    public static native void clean();
}
