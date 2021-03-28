
#ifndef ML_CANVAS_H
#define ML_CANVAS_H

#include <jni.h>
#include "Typeface.h"
#include "Rect.h"

#define ARGB(a,r,g,b) 0 | a << 24 | r << 16 | g << 8 | b

enum Style
{
    FILL = 0,
    STROKE = 1,
    FILL_AND_STROKE = 2
};

enum Align
{
    LEFT = 0,
    RIGHT = 1,
    CENTER
};

class Canvas
{
private:
    jobject m_CanvasObj, m_CurrentTypeface;
    jmethodID drawTextId;
    jmethodID drawRectId;
    jmethodID drawLineId;
    jmethodID drawCircleId;

    int width, height; float density; bool lowend;

    Rect *m_Rect;
    Typeface *m_Typeface;
public:
    JNIEnv *env;
    Canvas(JNIEnv *env, int width, int height, float density)
    {
        this->env = env;

        this->lowend = false;

        this->width = width;
        this->height = height;
        this->density = density;

        jclass canvasClass = env->FindClass("android/graphics/Canvas");
        drawTextId = env->GetMethodID(canvasClass, "drawText", "(Ljava/lang/String;FFLandroid/graphics/Paint;)V");
        drawRectId = env->GetMethodID(canvasClass, "drawRect", "(FFFFLandroid/graphics/Paint;)V");
        drawLineId = env->GetMethodID(canvasClass, "drawLine", "(FFFFLandroid/graphics/Paint;)V");
        drawCircleId = env->GetMethodID(canvasClass, "drawCircle", "(FFFLandroid/graphics/Paint;)V");
        env->DeleteLocalRef(canvasClass);

        m_Rect = new Rect(this->env);
        m_Typeface = new Typeface(this->env);
        m_CurrentTypeface = env->NewGlobalRef(m_Typeface->create("Arial Rounded MT", (int)FontStyle::BOLD));
    }

    void Cleanup();
    void UpdateCanvas(jobject canvas);
    void HighEndMode(bool bHigh);

    float scaleSize(float size);
    void drawText(const char *text, float X, float Y, float size = 5, Align align = Align::LEFT, long textColor = 0xFFFFFFFF, long outlineColor = 0x0);
    void drawTextW(const wchar_t *text, int len, float X, float Y, float size = 5, Align align = Align::LEFT, long textColor = 0xFFFFFFFF, long outlineColor = 0x0);
    void drawBox(float X, float Y, float width, float height, long color = 0xFFFFFFFF);
    void drawBorder(float X, float Y, float width, float height, float thicc, long color = 0xFFFFFFFF);
    void drawBorderRect(float left, float top, float right, float bottom, float thicc, long color = 0xFFFFFFFF);
    void drawLine(float startX, float startY, float stopX, float stopY, float thicc, long color = 0xFFFFFFFF);
    void drawCircle(float x, float y, float radius, float thicc, bool fill = false, long color = 0xFFFFFFFF);
};


#endif //ML_CANVAS_H
