package be.wholesome.goumzandstuff

import android.app.Activity
import android.content.Context
import android.content.pm.ActivityInfo
import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.view.View
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


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

    init {
        debugFlags = GLSurfaceView.DEBUG_CHECK_GL_ERROR or GLSurfaceView.DEBUG_LOG_GL_CALLS

        // Create an OpenGL ES 3.0 context
        setEGLContextClientVersion(3)

        renderer = MyGLRenderer()

        // Set the Renderer for drawing on the GLSurfaceView
        setRenderer(renderer)
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