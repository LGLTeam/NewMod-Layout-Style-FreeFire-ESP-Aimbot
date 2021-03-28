package uk.lgl.modmenu;

import android.app.Service;
import android.content.Intent;
import android.graphics.Canvas;
import android.os.Build;
import android.os.IBinder;
import android.view.WindowManager;

public class Loader extends Service {

    @Override
    public IBinder onBind(Intent p1) {
        return null;
    }

    /* access modifiers changed from: private */
    public ESPView overlayView;
    /* access modifiers changed from: private */
    public WindowManager windowManager;

    public static native void DrawOl(ESPView ESPView, Canvas canvas);


    @Override
    public void onCreate() {

        super.onCreate();


		this.windowManager = (WindowManager) getSystemService(WINDOW_SERVICE);

        this.overlayView = new ESPView(this);
        DrawCanvas();
    }

    public void Destroy() {
        if (this.overlayView != null) {
            this.windowManager.removeView(this.overlayView);
            this.overlayView = null;
        }
    }

    /* access modifiers changed from: private */
    public void DrawCanvas() {

        WindowManager.LayoutParams layoutParams = new WindowManager.LayoutParams(-1, -1, getLayoutType(), 56, -3);
        layoutParams.gravity = 8388659;
        layoutParams.x = 0;
        layoutParams.y = 100;
        this.windowManager.addView(this.overlayView, layoutParams);
    }

    /* access modifiers changed from: private */
    public int getLayoutType() {

        if (Build.VERSION.SDK_INT >= 26) {
            return 2038;
        }
        if (Build.VERSION.SDK_INT >= 24) {
            return 2002;
        }
        if (Build.VERSION.SDK_INT >= 23) {
            return 2005;
        }
        return 2003;
    }
}

