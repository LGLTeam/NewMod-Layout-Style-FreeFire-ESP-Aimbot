/*
 * Credit:
 *
 * Octowolve - Mod menu: https://github.com/z3r0Sec/Substrate-Template-With-Mod-Menu
 * And hooking: https://github.com/z3r0Sec/Substrate-Hooking-Example
 * VanHoevenTR A.K.A Nixi: https://github.com/LGLTeam/VanHoevenTR_Android_Mod_Menu
 * MrIkso - Mod menu: https://github.com/MrIkso/FloatingModMenu
 * Rprop - https://github.com/Rprop/And64InlineHook
 * MJx0 A.K.A Ruit - KittyMemory: https://github.com/MJx0/KittyMemory
 * */

package uk.lgl.modmenu;


import android.os.Process;
import android.graphics.Canvas;
import android.graphics.Color;
import android.content.res.Resources;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.os.Build.VERSION;
import android.view.WindowManager.LayoutParams;
import android.annotation.TargetApi;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.res.ColorStateList;
import android.app.AlertDialog;
import android.app.Service;
import android.os.Message;
import android.content.Context;
import android.content.Intent;
//import androidx.annotation.Nullable;
import android.content.res.ColorStateList;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.Typeface;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.graphics.drawable.GradientDrawable;
import android.text.Html;
import android.text.InputFilter;
import android.text.InputType;
import android.text.method.DigitsKeyListener;
import android.util.Base64;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import static android.view.ViewGroup.LayoutParams.WRAP_CONTENT;
import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;


import java.io.File;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

import static uk.lgl.modmenu.StaticActivity.cacheDir;



public class FloatingMod extends Service {
    private MediaPlayer FXPlayer;
    public View mFloatingView;
    private Button close;
    private Button kill;
    private LinearLayout mButtonPanel;
    public RelativeLayout mCollapsed;
    public LinearLayout mExpanded;
    private RelativeLayout mRootContainer;
    public WindowManager mWindowManager;
    public WindowManager.LayoutParams params;
    private LinearLayout patches;
    private static FloatingMod ErrorCod;
    private FrameLayout rootFrame;
    private ImageView startimage;
    private LinearLayout view1;
    private LinearLayout view2;
    int dpi;
    Handler handler;
    int screenHeight;
    int screenWidth;
    long sleepTime;
    int type;
    CanvasView canvasLayout;
    LayoutParams canvasLayoutParams;
    Thread mThread;
    Thread mUpdateScreen;
    private AlertDialog alert;
    private EditText edittextvalue;

    private static final String TAG = "Mod Menu";
	
	private LinearLayout.LayoutParams hr;
    float density;
    WindowManager windowManager;

    private Object paramString;

    private TextView textView;

   private class CanvasView extends View {
        public CanvasView(Context context) {
            super(context);
        }

        /* Access modifiers changed, original: protected */
        public void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            if (canvas != null) {
                FloatingMod.onDraw1(canvas, FloatingMod.this.screenWidth, FloatingMod.this.screenHeight, FloatingMod.this.density);
            }
        }
    }
    public static final int CACHE = 2002;

    public static final int INTERNET = 2003;

    //initialize methods from the native library
    

    public static native String Toast();

    private native String Title();

    private native String Heading();

    private native String Icon();

    private native String IconWebViewData();

    private native boolean EnableSounds();

    private native int IconSize();

    public native void Changes(int feature, int value);

    private native String[] getFeatureList();
	
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    //Override our Start Command so the Service doesnt try to recreate itself when the App is closed
    public int onStartCommand(Intent intent, int i, int i2) {
        return START_NOT_STICKY;
    }
private int getLayoutType()
    {
        if (Build.VERSION.SDK_INT >= 26)
        {
            return 2038;
        }
        if (Build.VERSION.SDK_INT >= 24)
        {
            return ErrorCod.CACHE;
        }
        if (Build.VERSION.SDK_INT >= 23)
        {
            return 2005;
        }
        return ErrorCod.INTERNET;
    }


    public FloatingMod() {
        this.sleepTime = 16;
        this.handler = new Handler() {
            public void handleMessage(Message message) {
                super.handleMessage(message);
                if (message.what == 0) {
                    try {
                        Point point = new Point();
                        FloatingMod.this.windowManager.getDefaultDisplay().getRealSize(point);
                        FloatingMod.this.screenWidth = point.x;
                        FloatingMod.this.screenHeight = point.y;
                        FloatingMod.this.canvasLayoutParams.width = WindowManager.LayoutParams.MATCH_PARENT;
                        FloatingMod.this.canvasLayoutParams.height = WindowManager.LayoutParams.MATCH_PARENT;
                        FloatingMod.this.windowManager.updateViewLayout(FloatingMod.this.canvasLayout, FloatingMod.this.canvasLayoutParams);
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        this.mThread = new Thread() {
            public void run() {
                Process.setThreadPriority(Process.THREAD_PRIORITY_BACKGROUND);
                while (isAlive() && !isInterrupted()) {
                    try {
                        long currentTimeMillis = System.currentTimeMillis();
                        FloatingMod.this.canvasLayout.postInvalidate();
                        Thread.sleep(Math.max(Math.min(0, FloatingMod.this.sleepTime - (System.currentTimeMillis() - currentTimeMillis)), FloatingMod.this.sleepTime));
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        this.mUpdateScreen = new Thread() {
            public void run() {
                    Process.setThreadPriority(Process.THREAD_PRIORITY_BACKGROUND);
                while (isAlive() && !isInterrupted()) {
                    try {
                        long currentTimeMillis = System.currentTimeMillis();
                        Point point = new Point();
                        FloatingMod.this.windowManager.getDefaultDisplay().getRealSize(point);
                        if (!(FloatingMod.this.screenWidth == point.x && FloatingMod.this.screenHeight == point.y)) {
                            FloatingMod.this.handler.sendEmptyMessage(0);
                        }
                        Thread.sleep(Math.max(Math.min(0, FloatingMod.this.sleepTime - (System.currentTimeMillis() - currentTimeMillis)), FloatingMod.this.sleepTime));
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        };
    }

    private static native void onDraw1(Canvas canvas, int i, int i2, float f);
	
	public void CreateCanvas() {
		 final int FLAGS = WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL |
		 WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN |
		 WindowManager.LayoutParams.FLAG_FULLSCREEN |
		 WindowManager.LayoutParams.FLAG_LAYOUT_INSET_DECOR |
		 WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE |
		 WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS |
		 WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
		
		LayoutParams layoutParams = new LayoutParams(WindowManager.LayoutParams.MATCH_PARENT,
													 WindowManager.LayoutParams.MATCH_PARENT,
													 getLayoutType(),
													 WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL |
													 WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE | WindowManager.LayoutParams.FLAG_FULLSCREEN,
													 PixelFormat.TRANSLUCENT);
		
		 
		this.canvasLayoutParams = layoutParams;
        this.canvasLayoutParams.gravity = Gravity.TOP | Gravity.START;
        this.canvasLayoutParams.x = 0;
        this.canvasLayoutParams.y = 100;
        CanvasView canvasView = new CanvasView(this);
        this.canvasLayout = canvasView;
        this.windowManager.addView(canvasView, this.canvasLayoutParams);
        this.sleepTime = 16;
    }
		 
		
													
	
    //When this Class is called the code in this function will be executed
    @Override
        
       public void onCreate() {
        super.onCreate();
        System.loadLibrary("VXTeam");
        this.windowManager = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        Point point = new Point();
        this.windowManager.getDefaultDisplay().getRealSize(point);
        this.screenWidth = point.x;
        this.screenHeight = point.y;
        this.dpi = Resources.getSystem().getDisplayMetrics().densityDpi;
        this.density = Resources.getSystem().getDisplayMetrics().density;
        this.type = getLayoutType();
        CreateCanvas();
        this.mThread.start();
        this.mUpdateScreen.start();
        initFloating();
        initAlertDiag();
    }
    //Here we write the code for our Menu
    private void initFloating() {
        this.rootFrame = new FrameLayout(this);
        this.mRootContainer = new RelativeLayout(this);
        this.mCollapsed = new RelativeLayout(this);
        this.mExpanded = new LinearLayout(this);
        this.view1 = new LinearLayout(this);
        this.patches = new LinearLayout(this);
        this.view2 = new LinearLayout(this);
        this.mButtonPanel = new LinearLayout(this);



        RelativeLayout relativeLayout = new RelativeLayout(this);
        relativeLayout.setLayoutParams(new RelativeLayout.LayoutParams(-2, -1));
        
        relativeLayout.setBackgroundColor(Color.TRANSPARENT);
		if(Build.VERSION.SDK_INT >= 21) { relativeLayout.setElevation(100f); }


		kill = new Button(this);
        kill.setVisibility(View.INVISIBLE);
		kill.setBackgroundColor(Color.parseColor("#000000"));
		kill.setText("Hide");

		kill.setTextColor(Color.parseColor("WHITE"));
		android.graphics.drawable.GradientDrawable FGIBJJI = new android.graphics.drawable.GradientDrawable();
        int FGIBJJIADD[] = new int[]{ Color.parseColor("#000000"), Color.parseColor("#FF002F") };
        FGIBJJI.setColors(FGIBJJIADD);
        FGIBJJI.setOrientation(android.graphics.drawable.GradientDrawable.Orientation.LEFT_RIGHT);
        FGIBJJI.setCornerRadii(new float[] { 15, 15, 15, 15, 15, 15, 15, 15 });
        FGIBJJI.setStroke(5, Color.parseColor("#000000"));
        kill.setBackground(FGIBJJI);
		RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(-2, -2);
		

        LinearLayout.LayoutParams ggg = new LinearLayout.LayoutParams(70, 50);
        this.close = new Button(this);
        this.close.setLayoutParams((ViewGroup.LayoutParams)ggg);
        this.close.setText("X");
        this.close.setTypeface((Typeface)null, Typeface.BOLD);
        this.close.setBackgroundColor(Color.BLACK);
        this.close.setGravity(17);
        this.close.setTextSize(11);
        this.close.setPadding(0, 3, 3, 0);
        this.close.setTextColor(Color.RED);
		
		relativeLayout.addView(close);



        rootFrame.setLayoutParams(new FrameLayout.LayoutParams(-1, -1));
        mRootContainer.setLayoutParams(new FrameLayout.LayoutParams(-2, -2));
        mCollapsed.setLayoutParams(new RelativeLayout.LayoutParams(-2, -2));
        mCollapsed.setVisibility(View.VISIBLE);
        startimage = new ImageView(getBaseContext());
        startimage.setLayoutParams(new RelativeLayout.LayoutParams(-2, -2));
        int applyDimension = (int) TypedValue.applyDimension(1, (float) IconSize(), getResources().getDisplayMetrics());
        startimage.getLayoutParams().height = applyDimension;
        startimage.getLayoutParams().width = applyDimension;
        startimage.requestLayout();
        startimage.setScaleType(ImageView.ScaleType.FIT_XY);
        byte[] decode = Base64.decode(Icon(), 0);
        startimage.setImageBitmap(BitmapFactory.decodeByteArray(decode, 0, decode.length));
        startimage.setImageAlpha(200);
        ((ViewGroup.MarginLayoutParams) startimage.getLayoutParams()).topMargin = convertDipToPixels(0);


		mExpanded.setVisibility(View.GONE);
		mExpanded.setAlpha(0.8F);
		mExpanded.setGravity(17);
	
		layoutParams.addRule(11);
		mExpanded.setOrientation(LinearLayout.VERTICAL);
		mExpanded.setPadding(0, 0, 0, 0);
        mExpanded.setBackgroundColor((Color.BLACK));
		if(Build.VERSION.SDK_INT >= 21) { mExpanded.setElevation(100f); }
		mExpanded.setLayoutParams(new LinearLayout.LayoutParams(dp(225), dp(430)));

        ScrollView scrollView = new ScrollView(this);
        scrollView.setBackgroundColor(Color.BLACK);
        scrollView.setAlpha(0.8F);
		scrollView.setLayoutParams(new LinearLayout.LayoutParams(MATCH_PARENT, dp(350)));
		if(Build.VERSION.SDK_INT >= 21) { scrollView.setElevation(100f); }
        scrollView.getBackground().setAlpha(200);


        this.patches.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        this.patches.setBackgroundColor(Color.BLACK);
        this.patches.setAlpha(0.8F);
        this.patches.setOrientation(1);


        this.hr = new LinearLayout.LayoutParams(-1, -1);
        this.hr.setMargins(0, 0, 0, 5);


        this.mButtonPanel.setLayoutParams(new LinearLayout.LayoutParams(-2, -2));


		/////PRIMEIRO TEXT VIEW/////

        LinearLayout.LayoutParams layoutParamstextView2 = new LinearLayout.LayoutParams(-1, -2);
        textView = new TextView(this);
        textView.setText("FreeFire");
        textView.setGravity(17);
        textView.setLayoutParams(layoutParamstextView2);
        textView.setShadowLayer((float)25, (float)0, (float)0, Color.CYAN);
        textView.setTypeface(Typeface.DEFAULT_BOLD);
        textView.setTextSize(20);
        textView.setPadding(10, 1, 10, 6);
        textView.setTextColor(Color.CYAN);

		/////SEGUNDO TEXT VIEW/////


        LinearLayout.LayoutParams layoutParamstextView = new LinearLayout.LayoutParams(-1, -2);
        TextView textView2 = new TextView(this);
        textView2.setText("ModByVxTeam");
        textView2.setGravity(17);
        textView2.setLayoutParams(layoutParamstextView);
        textView2.setShadowLayer((float)25, (float)0, (float)0, Color.CYAN);
        textView2.setTypeface(Typeface.DEFAULT_BOLD);
        textView2.setTextSize(14);
        textView2.setPadding(10, 1, 10, 6);
        textView2.setTextColor(Color.CYAN);

        new LinearLayout.LayoutParams(-1, dp(25)).topMargin = dp(2);
        rootFrame.addView(mRootContainer);
        mRootContainer.addView(mCollapsed);
        mRootContainer.addView(mExpanded);


        mCollapsed.addView(startimage);
        mExpanded.addView(textView);
        mExpanded.addView(textView2);
        mExpanded.addView(view1);
        mExpanded.addView(scrollView);
        scrollView.addView(patches);
        mExpanded.addView(view2);
        
        mFloatingView = rootFrame;
        if (Build.VERSION.SDK_INT >= 26) {
            params = new WindowManager.LayoutParams(-2, -2, 2038, 8, -3);
        } else {
            params = new WindowManager.LayoutParams(-2, -2, 2002, 8, -3);
        }
        WindowManager.LayoutParams layoutParams4 = params;
        layoutParams4.gravity = 51;
        layoutParams4.x = 0;
        layoutParams4.y = 100;
        mWindowManager = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        mWindowManager.addView(mFloatingView, params);
        RelativeLayout relativeLayout2 = mCollapsed;
        LinearLayout linearLayout = mExpanded;
        mFloatingView.setOnTouchListener(onTouchListener());
        startimage.setOnTouchListener(onTouchListener());

        initMenuButton(relativeLayout2, linearLayout);
        CreateMenuList();
    }

    private View.OnTouchListener onTouchListener() {
        return new View.OnTouchListener() {
            final View collapsedView = mCollapsed;
            final View expandedView = mExpanded;
            private float initialTouchX;
            private float initialTouchY;
            private int initialX;
            private int initialY;

            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch (motionEvent.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        initialX = params.x;
                        initialY = params.y;
                        initialTouchX = motionEvent.getRawX();
                        initialTouchY = motionEvent.getRawY();
                        return true;
                    case MotionEvent.ACTION_UP:
                        int rawX = (int) (motionEvent.getRawX() - initialTouchX);
                        int rawY = (int) (motionEvent.getRawY() - initialTouchY);

                        //The check for Xdiff <10 && YDiff< 10 because sometime elements moves a little while clicking.
                        //So that is click event.
                        if (rawX < 10 && rawY < 10 && isViewCollapsed()) {
                            //When user clicks on the image view of the collapsed layout,
                            //visibility of the collapsed layout will be changed to "View.GONE"
                            //and expanded view will become visible.
                            collapsedView.setVisibility(View.GONE);
                            expandedView.setVisibility(View.VISIBLE);

                            Toast.makeText(FloatingMod.this, Html.fromHtml(Toast()), Toast.LENGTH_SHORT).show();

                        }
                        return true;
                    case MotionEvent.ACTION_MOVE:
                        //Calculate the X and Y coordinates of the view.
                        params.x = initialX + ((int) (motionEvent.getRawX() - initialTouchX));
                        params.y = initialY + ((int) (motionEvent.getRawY() - initialTouchY));

                        //Update the layout with new X & Y coordinate
                        mWindowManager.updateViewLayout(mFloatingView, params);
                        return true;
                    default:
                        return false;
                }
            }
        };
    }

    //Initialize event handlers for Buttons, etc.
    private void initMenuButton(final View view2, final View view3) {
        startimage.setOnClickListener(new View.OnClickListener() {
                public void onClick(View view) {
                    view2.setVisibility(View.GONE);
                    view3.setVisibility(View.VISIBLE);

                }
            });
        textView.setOnClickListener(new View.OnClickListener() {
                public void onClick(View view) {
                    view2.setVisibility(View.VISIBLE);
                    view2.setAlpha(0.95f);
                    view3.setVisibility(View.GONE);

                    //Log.i("LGL", "Close");
                }
            });
    }

    private void CreateMenuList() {
        String[] listFT = getFeatureList();
        for (int i = 0; i < listFT.length; i++) {
            final int feature = i;
            String str = listFT[i];
            if (str.contains("Toggle_")) {

                addSwitch(str.replace("Toggle_", ""), new InterfaceBool() {
                        public void OnWrite(boolean z) {
                            Changes(feature, 0);
                        }
                    });
            } else if (str.contains("SeekBar_")) {
                String[] split = str.split("_");
                addSeekBar(split[1], Integer.parseInt(split[2]), Integer.parseInt(split[3]), new InterfaceInt() {
                        public void OnWrite(int i) {
                            Changes(feature, i);
                        }
                    });
            } else if (str.contains("Category_")) {
                addCategory(str.replace("Category_", ""));
            } else if (str.contains("Category2_")) {
                addCategory2(str.replace("Category2_", ""));
            
            } else if (str.contains("Button_OnOff")) {
                addButton(str.replace("Button_OnOff", ""), new InterfaceButton() {
                        public void OnWrite() {
                            Changes(feature, 0);
                        }
                    });
            } else if (str.contains("Spinner_")) {
                addSpinner(str.replace("Spinner_", ""), new InterfaceInt() {
                        @Override
                        public void OnWrite(int i) {
                            Changes(feature, i);
                        }
                    });
			} else if (str.contains("InputValue_")) {
                addTextField(str.replace("InputValue_", ""), feature, new InterfaceInt() {
                        @Override
                        public void OnWrite(int i) {
                            Changes(feature, 0);
                        }
                    });
            }
        }
    }


    private TextView textView2;
    private String featureNameExt;
    private int featureNum;
    private EditTextValue txtValue;

    public class EditTextValue {
        private int val;

        public void setValue(int i) {
            val = i;
        }

        public int getValue() {
            return val;
        }
    }

    private void addTextField(final String featureName, final int feature, final InterfaceInt interInt) {
        RelativeLayout relativeLayout2 = new RelativeLayout(this);
        relativeLayout2.setLayoutParams(new RelativeLayout.LayoutParams(-2, -1));
        relativeLayout2.setPadding(10, 5, 10, 5);
        relativeLayout2.setVerticalGravity(16);

        RelativeLayout.LayoutParams layoutParams = new RelativeLayout.LayoutParams(-2, -2);
        layoutParams.topMargin = 10;

        final TextView textView = new TextView(this);
        textView.setText(Html.fromHtml("<font face='roboto'>" + featureName + ": <font color='#fdd835'>Not set</font></font>"));
        textView.setTextColor(Color.parseColor("#DEEDF6"));
        textView.setLayoutParams(layoutParams);

        final TextView textViewRem = new TextView(this);
        textViewRem.setText("");

        final EditTextValue edittextval = new EditTextValue();

        RelativeLayout.LayoutParams layoutParams2 = new RelativeLayout.LayoutParams(-2, -2);
        layoutParams2.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);

        Button Button2 = new Button(this);
        Button2.setLayoutParams(layoutParams2);
        Button2.setBackgroundColor(Color.parseColor("#1C262D"));
        Button2.setText("SET");
        Button2.setTextColor(Color.parseColor("#D5E3EB"));
        Button2.setGravity(17);
        Button2.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    alert.show();
                    textView2 = textView;
                    featureNum = feature;
                    featureNameExt = featureName;
                    txtValue = edittextval;

                    edittextvalue.setText(String.valueOf(edittextval.getValue()));
                }
            });

        relativeLayout2.addView(textView);
        relativeLayout2.addView(Button2);
        patches.addView(relativeLayout2);
    }

    private void initAlertDiag() {
        LinearLayout linearLayout1 = new LinearLayout(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -1);
        linearLayout1.setPadding(10, 5, 0, 5);
        linearLayout1.setOrientation(LinearLayout.VERTICAL);
        linearLayout1.setGravity(17);
        linearLayout1.setLayoutParams(layoutParams);
        linearLayout1.setBackgroundColor(Color.parseColor("BLACK"));

        int i = Build.VERSION.SDK_INT >= 26 ? 2038 : 2002;
        LinearLayout linearLayout = new LinearLayout(this);
        linearLayout.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        linearLayout.setBackgroundColor(Color.parseColor("BLACK"));
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        FrameLayout frameLayout = new FrameLayout(this);
        frameLayout.setLayoutParams(new FrameLayout.LayoutParams(-2, -2));
        frameLayout.addView(linearLayout);

        final TextView textView = new TextView(this);
        textView.setText(Html.fromHtml("<font face='roboto'>Tap OK to apply changes. Tap outside to cancel</font>"));
        textView.setTextColor(Color.parseColor("#DEEDF6"));
        textView.setLayoutParams(layoutParams);

        edittextvalue = new EditText(this);
        edittextvalue.setLayoutParams(layoutParams);
        edittextvalue.setMaxLines(1);
        edittextvalue.setWidth(convertDipToPixels(300));
        edittextvalue.setTextColor(Color.parseColor("#93a6ae"));
        edittextvalue.setTextSize(13.0f);
        edittextvalue.setHintTextColor(Color.parseColor("#434d52"));
        edittextvalue.setInputType(InputType.TYPE_CLASS_NUMBER);
        edittextvalue.setKeyListener(DigitsKeyListener.getInstance("0123456789-"));

        InputFilter[] FilterArray = new InputFilter[1];
        FilterArray[0] = new InputFilter.LengthFilter(10);
        edittextvalue.setFilters(FilterArray);

        Button Button = new Button(this);
        Button.setBackgroundColor(Color.parseColor("BLACK"));
        Button.setTextColor(Color.parseColor("BLACK"));
        Button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Changes(featureNum, Integer.parseInt(edittextvalue.getText().toString()));
                    txtValue.setValue(Integer.parseInt(edittextvalue.getText().toString()));
                    textView2.setText(Html.fromHtml("<font face='roboto'>" + featureNameExt + ": <font color='#41c300'>" + edittextvalue.getText().toString() + "</font></font>"));
                    alert.dismiss();
                    playSound(Uri.fromFile(new File(cacheDir + "Select.ogg")));
                    //interStr.OnWrite(editText.getText().toString());
                }
            });

        alert = new AlertDialog.Builder(this, 2).create();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            Objects.requireNonNull(alert.getWindow()).setType(i);
        }
        linearLayout1.addView(textView);
        linearLayout1.addView(edittextvalue);
        linearLayout1.addView(Button);
        alert.setView(linearLayout1);
    }

    private void addSpinner(String feature, final InterfaceInt interInt) {
        List<String> list = new LinkedList<>(Arrays.asList(feature.split("_")));

        LinearLayout linearLayout = new LinearLayout(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -1);
        linearLayout.setPadding(10, 5, 10, 5);
        linearLayout.setOrientation(LinearLayout.VERTICAL);
        linearLayout.setGravity(17);
        linearLayout.setLayoutParams(layoutParams);
        linearLayout.setBackgroundColor(Color.parseColor("#00000000"));

        final TextView textView = new TextView(this);
        textView.setText(Html.fromHtml("<font face='roboto'>" + list.get(0) + ": <font color='#41c300'></font>"));
        textView.setTextColor(Color.parseColor("#DEEDF6"));

        // Create another LinearLayout as a workaround to use it as a background
        // and to keep the 'down' arrow symbol
        // If spinner had the setBackgroundColor set, there would be no arrow symbol
        LinearLayout linearLayout2 = new LinearLayout(this);
        LinearLayout.LayoutParams layoutParams2 = new LinearLayout.LayoutParams(-1, -1);
        layoutParams2.setMargins(10, 2, 10, 5);
        linearLayout2.setOrientation(LinearLayout.VERTICAL);
        linearLayout2.setGravity(17);
        linearLayout2.setBackgroundColor(Color.parseColor("#00000000"));
        linearLayout2.setLayoutParams(layoutParams2);

        Spinner spinner = new Spinner(this);
        spinner.setPadding(5, 10, 5, 8);
        spinner.setLayoutParams(layoutParams2);
        spinner.getBackground().setColorFilter(1, PorterDuff.Mode.SRC_ATOP); //trick to show white down arrow color
        //Creating the ArrayAdapter instance having the list
        list.remove(0);
        ArrayAdapter aa = new ArrayAdapter(this, android.R.layout.simple_spinner_item, list);
        aa.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        //Setting the ArrayAdapter data on the Spinner
        spinner.setAdapter(aa);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                @Override
                public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                    ((TextView) parentView.getChildAt(0)).setTextColor(Color.parseColor("YELLOW"));
                    interInt.OnWrite(position);
                    playSound(Uri.fromFile(new File(cacheDir + "Select.ogg")));
                }

                @Override
                public void onNothingSelected(AdapterView<?> parent) {
                    playSound(Uri.fromFile(new File(cacheDir + "Select.ogg")));
                }
            });
        linearLayout.addView(textView);
        linearLayout2.addView(spinner);
        patches.addView(linearLayout);
        patches.addView(linearLayout2);
    }

    private void addCategory(String text) {
        TextView textView = new TextView(this);
        textView.setBackgroundColor(Color.TRANSPARENT);
        textView.setText(text);
        textView.setGravity(17);
        textView.setTextSize(14.0f);
        textView.setTextColor(Color.parseColor("RED"));
        textView.setPadding(10, 5, 0, 5);
        patches.addView(textView);
    }
    
    private void addCategory2(String text) {
        TextView textView = new TextView(this);
        textView.setBackgroundColor(Color.TRANSPARENT);
        textView.setText(text);
        textView.setGravity(17);
        textView.setTextSize(14.0f);
        textView.setTextColor(Color.YELLOW);
        textView.setPadding(10, 5, 0, 5);
        patches.addView(textView);
    }

    public void addButton(String feature, final InterfaceButton interfaceButton) {
        final Button Button = new Button(this);
        Button.setLayoutParams((ViewGroup.LayoutParams)new LinearLayout.LayoutParams(555, 63));
        Button.setAllCaps(false);
        Button.setText((CharSequence)new StringBuffer().append(paramString).append(": Off").toString());
        Button.setTextColor(Color.WHITE);
        Button.setShadowLayer((float)15, (float)0, (float)0, Color.RED);
        Button.setBackgroundColor(Color.TRANSPARENT);
        Button.setPadding(0, 0, 0, 0);
        Button.setTextSize(13.0f);
        Button.setGravity(17);

        if (feature.contains("OnOff_")) {
            feature = feature.replace("OnOff_", "");
            Button.setText(feature + ": Off");
            Button.setBackgroundColor(Color.TRANSPARENT);
            Button.setShadowLayer(15, 0, 0, Color.RED);
            Button.setTextColor(Color.parseColor("#ffffff"));
			if(Build.VERSION.SDK_INT >= 21) { Button.setElevation(100f); }
			if(Build.VERSION.SDK_INT >= 21) { Button.setElevation(100f); }
            final String feature2 = feature;
            Button.setOnClickListener(new View.OnClickListener() {
                    private boolean isActive = true;

                    public void onClick(View v) {
                        interfaceButton.OnWrite();
                        if (isActive) {
                            Button.setText(feature2 + ": On");
                            Button.setBackgroundColor(Color.TRANSPARENT);
                            Button.setShadowLayer(15, 0, 0, Color.CYAN);
                            Button.setTextColor(Color.parseColor("#ffffff"));
							if(Build.VERSION.SDK_INT >= 21) { Button.setElevation(100f); }
							if(Build.VERSION.SDK_INT >= 21) { Button.setElevation(100f); }
                            isActive = false;
                            return;
                        }

                        Button.setText(feature2 + ": Off");
                        Button.setBackgroundColor(Color.TRANSPARENT);
                        Button.setShadowLayer(15, 0, 0, Color.RED);
                        Button.setTextColor(Color.parseColor("#ffffff"));
						if(Build.VERSION.SDK_INT >= 21) { Button.setElevation(100f); }
						if(Build.VERSION.SDK_INT >= 21) { Button.setElevation(100f); }
                        isActive = true;
                    }
                });
        } else {
            Button.setText(feature);
            Button.setBackgroundColor(Color.parseColor("WHITE"));
            final String feature2 = feature;
            Button.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        interfaceButton.OnWrite();
                        playSound(Uri.fromFile(new File(cacheDir + "Select.ogg")));
                    }
                });
        }
        patches.addView(Button);
    }

    private void addSwitch(String str, final InterfaceBool sw) {
        final Switch switchR = new Switch(this);
        switchR.setBackgroundColor(Color.TRANSPARENT);
        switchR.setText(Html.fromHtml("<font face='monospace'><b>" + str + "</b></font>"));
        switchR.setTextColor(-1);
        switchR.setShadowLayer(15, 0, 0, Color.RED);
        switchR.setTextSize(13.0f);
        

        switchR.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                public void onCheckedChanged(CompoundButton compoundButton, boolean z) {
                    if (z) {
                        switchR.setShadowLayer(15, 0, 0, Color.CYAN);
                        switchR.setTextColor(Color.parseColor("#ffffff"));
                        switchR.setBackgroundColor(Color.TRANSPARENT);
                    } else {
                        switchR.setShadowLayer(15, 0, 0, Color.RED);
                        switchR.setTextColor(Color.parseColor("#ffffff"));
                        switchR.setBackgroundColor(Color.TRANSPARENT);
                    }
                    sw.OnWrite(z);
                }
            });

        switchR.setLayoutParams(this.hr);
        this.patches.addView(switchR);
    }

    private void addSeekBar(String str,  int progress, int max, InterfaceInt sb) {
        LinearLayout linearLayout = new LinearLayout(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(-1, -1);
        linearLayout.setPadding(10, 5, 0, 5);
        linearLayout.setOrientation(1);
        linearLayout.setGravity(17);
        linearLayout.setLayoutParams(layoutParams);
        linearLayout.setBackgroundColor(Color.parseColor("#00000000"));
        TextView textView = new TextView(this);
        StringBuilder sb2 = new StringBuilder();
        sb2.append("<font face='monospace'><b>");
        sb2.append(str);
        sb2.append("<font face='monospace'><b>" + ": <font color='GREEN'>" + "</b></font>");
        sb2.append(progress);
        sb2.append("</b></font>");
        textView.setText(Html.fromHtml(sb2.toString()));
        textView.setTextSize(14);
        textView.setShadowLayer(15, 0, 0, Color.RED);
        textView.setTextColor(-1);
        textView.setTextColor(Color.WHITE);
        textView.setTypeface((Typeface) null, 1);
        SeekBar seekBar = new SeekBar(this);
        seekBar.setScaleY(1.0f);
        seekBar.getProgressDrawable().setColorFilter(Color.parseColor("#B200FFFF"), PorterDuff.Mode.MULTIPLY);
        seekBar.setPadding(25, 10, 35, 10);
        seekBar.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
		
        if (Build.VERSION.SDK_INT >= 21) {
            
        }
        seekBar.setMax(max);
        seekBar.setProgress(progress);
        final int i5 = progress;
        final SeekBar seekBar2 = seekBar;
        final InterfaceInt sb3 = sb;
        final TextView textView2 = textView;
        final String str3 = str;
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {


                private String itv;
                public void onStartTrackingTouch(SeekBar seekBar) {
                    
                }

                public void onStopTrackingTouch(SeekBar seekBar) {
                }

                public void onProgressChanged(SeekBar seekBar, int i, boolean z) {
                    int i2 = i5;
                    if (i < i2) {
                        seekBar2.setProgress(i2);
                        sb3.OnWrite(i5);
                        TextView textView = textView2;
                        textView.setText(Html.fromHtml("<font face='monospace'><b>" + str3 + ": <font color=BLACK'>" + i5 + "</b></font>"));
                        return;
                    }
                    sb3.OnWrite(i);
                    textView2.setText(Html.fromHtml("<font face='monospace'><b>" + str3 + ": <font color=BLACK'>" + i + "</b></font>"));

                }
            });

        linearLayout.addView(textView);
        linearLayout.addView(seekBar);
        linearLayout.setLayoutParams(this.hr);
        this.patches.addView(linearLayout);
    }

    boolean delayed;

    public void playSound(Uri uri) {
        if (EnableSounds()) {
            if (!delayed) {
                delayed = true;
                if (FXPlayer != null) {
                    FXPlayer.stop();
                    FXPlayer.release();
                }
                FXPlayer = MediaPlayer.create(this, uri);
                if (FXPlayer != null)
                //Volume reduced so sounds are not too loud
                    FXPlayer.setVolume(0.5f, 0.5f);
                FXPlayer.start();

                Handler handler = new Handler();
                handler.postDelayed(new Runnable() {
                        @Override
                        public void run() {
                            delayed = false;
                        }
                    }, 100);
            }
        }
    }

    public boolean isViewCollapsed() {
        return mFloatingView == null || mCollapsed.getVisibility() == View.VISIBLE;
    }

    //For our image a little converter
    private int convertDipToPixels(int i) {
        return (int) ((((float) i) * getResources().getDisplayMetrics().density) + 0.5f);
    }

    private int dp(int i) {
        return (int) TypedValue.applyDimension(1, (float) i, getResources().getDisplayMetrics());
    }

    //Destroy our View
    public void onDestroy() {
        super.onDestroy();
        View view = mFloatingView;
        if (view != null) {
            mWindowManager.removeView(view);
        }
    }

    //Check if we are still in the game. If now our Menu and Menu Button will dissapear
    private boolean isNotInGame() {
        RunningAppProcessInfo runningAppProcessInfo = new RunningAppProcessInfo();
        ActivityManager.getMyMemoryState(runningAppProcessInfo);
        return runningAppProcessInfo.importance != 100;
    }

    //Same as above so it wont crash in the background and therefore use alot of Battery life
    public void onTaskRemoved(Intent intent) {
        stopSelf();
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.onTaskRemoved(intent);
    }

    /* access modifiers changed from: private */
    public void Thread() {
        if (mFloatingView == null) {
            return;
        }
        if (isNotInGame()) {

        } else {
            mFloatingView.setVisibility(View.VISIBLE);
        }
    }

    private interface InterfaceButton {
        void OnWrite();
    }

    private interface InterfaceInt {
        void OnWrite(int i);
    }

    private interface InterfaceBool {
        void OnWrite(boolean z);
    }

    private interface InterfaceStr {
        void OnWrite(String s);
    }
}




