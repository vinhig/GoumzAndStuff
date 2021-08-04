package be.wholesome.goumzandstuff

import android.app.Activity
import android.content.Context
import android.content.pm.ActivityInfo
import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.ScaleGestureDetector
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

    private var lastX: Float = 0.0f
    private var lastY: Float = 0.0f

    external fun onTouch(state: Int, x: Float, y: Float)

    external fun onDragStart()
    external fun onDrag(x: Float, y: Float)
    external fun onDragStop(x: Float, y: Float)

    external fun onZoomStart()
    external fun onZoom(delta: Float)
    external fun onZoomStop(delta: Float)

    private val scrollListener: GestureDetector;

    private val scaleListener: ScaleGestureDetector;

    init {
        debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR or GLSurfaceView.DEBUG_LOG_GL_CALLS

        // Create an OpenGL ES 3.0 context
        setEGLContextClientVersion(3)

        renderer = MyGLRenderer()

        scrollListener = object : GestureDetector(this.context, object :
            GestureDetector.SimpleOnGestureListener() {
            override fun onScroll(
                e1: MotionEvent?,
                e2: MotionEvent?,
                distanceX: Float,
                distanceY: Float
            ): Boolean {
                onDrag(-distanceX / width, distanceY / height)
                return true
            }
        }) {}

        scaleListener =
            object : ScaleGestureDetector(this.context, object : OnScaleGestureListener {
                override fun onScaleBegin(p0: ScaleGestureDetector?): Boolean {
                    onZoomStart()
                    return true
                }

                override fun onScale(p0: ScaleGestureDetector): Boolean {
                    onZoom(1.0f / p0.scaleFactor)
                    return true
                }

                override fun onScaleEnd(p0: ScaleGestureDetector) {
                    onZoomStop(1.0f / p0.scaleFactor)
                }
            }) {}

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(renderer)
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        scaleListener.onTouchEvent(event)
        scrollListener.onTouchEvent(event)
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