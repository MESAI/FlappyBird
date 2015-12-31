package com.mesai0.blogspot.ZeptoLabTest;

import java.util.Formatter;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.pm.ConfigurationInfo;
import android.graphics.Typeface;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;
	private RendererWrapper rendererWrapper;
	private TextView score;
	private TextView start;
	private static Handler handler;
	private static final String MY_PREFS_NAME = "ZeptoLabTest";
	private Animation animation;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.main_layout);
	    score = (TextView) findViewById(R.id.scoreView);
	    score.setText("0");
	    start = (TextView) findViewById(R.id.startGame);
	    Typeface face = Typeface.createFromAsset(getAssets(), "square-deal.ttf");
	    score.setTypeface(face);
	    start.setTypeface(face);
	    
	    animation = AnimationUtils.loadAnimation(this,R.anim.fadein_fadeout);
	    start.setAnimation(animation);
	    start.setText(R.string.start);
	    
	    ActivityManager activityManager
	        = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
	    ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
	 
	    final boolean supportsEs2 =
	        configurationInfo.reqGlEsVersion >= 0x20000;
	 
	    if (supportsEs2) {
	        glSurfaceView = (GLSurfaceView) findViewById(R.id.glSurfaceView); 
	        glSurfaceView.setEGLContextClientVersion(2);
	        rendererWrapper = new RendererWrapper();
	        glSurfaceView.setRenderer(rendererWrapper);
	        rendererSet = true;
	   
	    } else {
	        // Should never be seen in production, since the manifest filters
	        // unsupported devices.
	        Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
	                Toast.LENGTH_LONG).show();
	        return;
	    }
	    
	    // this handler is used to receive the events coming 
	    // from the engine and excite them on the UI thread
	    handler = new Handler(){
	    	@Override
	    	public void handleMessage(Message msg) {
	    		switch(msg.what){
	    		case 0:{ // update the score
	    	 		if(msg.arg1 > 0){
	    	 			start.setVisibility(View.GONE);
	    			}
	    			Formatter f = new Formatter();
	    			score.setText(msg.arg1+"");
	    			f.flush();
	    			f.close();
	    		};break;
	    		case 1:{ // game over show a dialog
	    			AlertDialog alertDialog = new AlertDialog.Builder(MainActivity.this).create();
	    			alertDialog.setTitle("Game Over !!");
	    			int scoreValue  = Integer.parseInt(score.getText().toString());
	    			if(getHighScore()< scoreValue) // in case of normal game ending
	    			{
	    				TextView myMsg = new TextView(MainActivity.this);
	    				myMsg.setText("New High Score !!!\n"+scoreValue);
	    				myMsg.setGravity(Gravity.CENTER_HORIZONTAL);
		    			alertDialog.setView(myMsg);
		    			updateHighScore(scoreValue);
	    			}
	    			else{ // in case of a new hight score
	    				TextView myMsg = new TextView(MainActivity.this);
	    				myMsg.setText("Your score is "+ scoreValue +"\nYour Highest Score is "+getHighScore());
	    				myMsg.setGravity(Gravity.CENTER_HORIZONTAL);
		    			alertDialog.setView(myMsg);
	    			}
	    			alertDialog.setCancelable(false);
	    			alertDialog.setButton(AlertDialog.BUTTON_NEUTRAL, "OK",
	    			    new DialogInterface.OnClickListener() {
	    			        public void onClick(DialogInterface dialog, int which) {
	    			        	Native.resetGame();
	    			        	start.setText(R.string.start);
	    			        	start.setAnimation(animation);
	    			        	start.setVisibility(View.VISIBLE);
	    			            dialog.dismiss();
	    			        }
	    			    });
	    			alertDialog.show();
	    		}
	    		}
	    	}
	    };
	    
	}
	
	/**
	  Touch event listener used to send the user interactions to the game engine.
	  @param the event.
	  @return boolean indicating the propagation of the event. 
	*/	
	public boolean onTouchEvent(MotionEvent event) {
	    switch (event.getAction()) 
	    {
        	case MotionEvent.ACTION_DOWN:
        		rendererWrapper.onTouchEventDown();
            break;
        	case MotionEvent.ACTION_UP:{
        		start.setText(R.string.keep);
				start.setAnimation(null);
        		rendererWrapper.onTouchEventUp();
        	}
            break;
	    }
	    return false;
	}
	
	/**
	  Save the highest score in the shared preference
	  @param score
	*/	
	private void updateHighScore(int score)
	{
		SharedPreferences.Editor editor = getSharedPreferences(MY_PREFS_NAME, MODE_PRIVATE).edit();
		editor.putInt("highscore", score);
		editor.commit();
	}
	
	/**
	  Returns the highest score stored in the shared preference
	  @return hightest score
	*/	
	private int getHighScore()
	{
		SharedPreferences prefs = getSharedPreferences(MY_PREFS_NAME, MODE_PRIVATE); 
		int score = prefs.getInt("highscore", -1);
		return score;
	}
	
	@Override
	protected void onPause() {
	    super.onPause();
	 
	    if (rendererSet) {
	        glSurfaceView.onPause();
	    }
	}
	 
	@Override
	protected void onResume() {
	    super.onResume();
	 
	    if (rendererSet) {
	        glSurfaceView.onResume();
	    }
	}
	
	/**
	  A Callback Function to update the score on the UI
	  @param updated score
	*/	
	static void updateScore(int score) {
		Message msg = new Message();
		msg.what = 0;
		msg.arg1 = score;
		handler.sendMessage(msg);
	}
	
	/**
	  A Callback Function to announce the end of game
	*/	
	static void gameOver() {
		Message msg = new Message();
		msg.what = 1;
		handler.sendMessage(msg);
	}
	
}
