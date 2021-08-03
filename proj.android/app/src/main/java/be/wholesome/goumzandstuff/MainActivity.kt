package be.wholesome.goumzandstuff

import android.app.Activity
import android.content.Context
import android.content.pm.ActivityInfo
import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.MotionEvent
import android.view.View
import androidx.core.view.MotionEventCompat
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlin.math.pow
import kotlin.math.sqrt


class MyGLRenderer : GLSurfaceView.Renderer {

    external fun onSurfaceCreated()

    external fun onDrawFrame()

    external fun onSurfaceChanged()

    override fun onSurfaceCreated(unused: GL10, config: EGLConfig) {
        onSurfaceCreated();
    }

    override fun onDrawFrame(unused: GL10) {
        onDrawFrame()
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {
        onSurfaceChanged()
    }
}


class MyGLSurfaceView(context: Context) : GLSurfaceView(context) {

    private val renderer: MyGLRenderer

    private var zooming: Boolean = false
    private var oldDistance: Float = 0.0f
    private var currentZoomRatio: Float = 0.0f

    private var lastAction: Int = 0

    external fun onZoomStart()
    external fun onZoom(delta: Float)
    external fun onZoomStop(delta: Float)

    external fun onTouch(x: Float, y: Float)

    external fun onDrag(x : Float, y: Float)

    init {
        debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR or GLSurfaceView.DEBUG_LOG_GL_CALLS

        // Create an OpenGL ES 3.0 context
        setEGLContextClientVersion(3)

        renderer = MyGLRenderer()

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(renderer)
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {

        if (event.pointerCount == 1) {
            if (zooming) {
                onZoomStop(currentZoomRatio)
                zooming = false
            }
            val action: Int = MotionEventCompat.getActionMasked(event)

            when(action) {
                MotionEvent.ACTION_DOWN -> {
                    lastAction = MotionEvent.ACTION_DOWN
                }
                MotionEvent.ACTION_MOVE -> {
                    lastAction = MotionEvent.ACTION_DOWN
                    onDrag(event.x, event.y)
                }
                MotionEvent.ACTION_UP -> {
                    if (lastAction == MotionEvent.ACTION_DOWN) {
                        onTouch(event.x, event.y)
                    }
                }

            }

            return true
            
        } else if (event.pointerCount == 2) {
            val action: Int = MotionEventCompat.getActionMasked(event)

            if (action == MotionEvent.ACTION_MOVE) {
                val dx: Float = event.getX(1) - event.getX(0)
                val dy: Float = event.getY(1) - event.getY(0)
                val distance: Float = sqrt(dx * dx + dy * dy)

                if (zooming) {
                    currentZoomRatio = oldDistance/distance
                    onZoom(currentZoomRatio)
                } else {
                    Log.d("yo", "first touch")
                    zooming = true
                    oldDistance = distance
                    onZoomStart()
                }
            }
        }

        return true
    }

}


class MainActivity : Activity() {

    private lateinit var glView: GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        window.decorView.systemUiVisibility =
            View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY or View.SYSTEM_UI_FLAG_FULLSCREEN

        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE;

        setAssetManager(assets);

        glView = MyGLSurfaceView(this)
        glView.debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR or GLSurfaceView.DEBUG_LOG_GL_CALLS
        setContentView(glView)

    }

    override fun onWindowFocusChanged(hasFocus: Boolean) {
        if (hasFocus) {
            hideVirtualButton()
        }
    }

    override fun onResume() {
        super.onResume()

        hideVirtualButton()
    }

    private fun hideVirtualButton() {
        window.decorView.systemUiVisibility =
            View.SYSTEM_UI_FLAG_HIDE_NAVIGATION or View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY or View.SYSTEM_UI_FLAG_FULLSCREEN
    }

    external fun setAssetManager(assetManager: AssetManager)

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("GoumzAndStuffGame")
        }
    }
}