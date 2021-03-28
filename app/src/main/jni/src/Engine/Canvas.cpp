

#include "Canvas.h"
#include "Paint.h"
#include "Rect.h"
#include <wchar.h>
#include <string.h>

jstring wcstojstr(JNIEnv *env, const wchar_t *input) {
    jobject bb = env->NewDirectByteBuffer((void *)input, wcslen(input) * sizeof(wchar_t));
    jstring UTF32LE = env->NewStringUTF("UTF-32LE");

    jclass charsetClass = env->FindClass("java/nio/charset/Charset");
    jmethodID forNameMethod = env->GetStaticMethodID(charsetClass, "forName", "(Ljava/lang/String;)Ljava/nio/charset/Charset;");
    jobject charset = env->CallStaticObjectMethod(charsetClass, forNameMethod, UTF32LE);

    jmethodID decodeMethod = env->GetMethodID(charsetClass, "decode", "(Ljava/nio/ByteBuffer;)Ljava/nio/CharBuffer;");
    jobject cb = env->CallObjectMethod(charset, decodeMethod, bb);

    jclass charBufferClass = env->FindClass("java/nio/CharBuffer");
    jmethodID toStringMethod = env->GetMethodID(charBufferClass, "toString", "()Ljava/lang/String;");
    jstring ret = (jstring)env->CallObjectMethod(cb, toStringMethod);

    env->DeleteLocalRef(bb);
    env->DeleteLocalRef(UTF32LE);
    env->DeleteLocalRef(charsetClass);
    env->DeleteLocalRef(charset);
    env->DeleteLocalRef(cb);
    env->DeleteLocalRef(charBufferClass);

    return ret;
}

void Canvas::Cleanup() {
    env->DeleteLocalRef(this->m_CanvasObj);
    env->DeleteGlobalRef(this->m_CurrentTypeface);

    m_Rect->Cleanup();
    m_Typeface->Cleanup();

    delete[] this;
}

float Canvas::scaleSize(float size) {
    return (size * density);
}

void Canvas::UpdateCanvas(jobject canvas) {
    this->m_CanvasObj = canvas;
}

void Canvas::HighEndMode(bool bHigh) {
    this->lowend = !bHigh;
}

void Canvas::drawText(const char *text, float X, float Y, float size, Align align, long textColor, long outlineColor) {
    if (!text)
        return;

    Paint *paint = new Paint(this->env);
    if(!lowend) {
        paint->setTypeface(this->m_CurrentTypeface);
        paint->setAntiAlias(true);
    }

    paint->setTextSize(this->scaleSize(size));
    paint->setTextAlign(align);

    paint->getTextBounds(text, 0, strlen(text), m_Rect->m_Rect);

    jstring str = env->NewStringUTF(text);

    if (outlineColor) {
        if (!lowend) {
            paint->setStyle(Style::FILL);
            int a = (outlineColor >> 24) & 255;
            int r = (outlineColor >> 16) & 255;
            int g = (outlineColor >> 8) & 255;
            int b = outlineColor & 255;
            paint->setARGB(a, r, g, b);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, str, X - 1, Y - 1, paint->m_Paint);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, str, X + 1, Y + 1, paint->m_Paint);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, str, X - 1, Y + 1, paint->m_Paint);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, str, X + 1, Y - 1, paint->m_Paint);
        }
    }

    int a = (textColor >> 24) & 255;
    int r = (textColor >> 16) & 255;
    int g = (textColor >> 8) & 255;
    int b = textColor & 255;

    paint->setStyle(Style::FILL);
    paint->setARGB(a, r, g, b);
    env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, str, X, Y, paint->m_Paint);

    env->DeleteLocalRef(str);

    paint->Cleanup();
}

void Canvas::drawTextW(const wchar_t *text, int len, float X, float Y, float size, Align align, long textColor, long outlineColor) {
    if (!text)
        return;

    Paint *paint = new Paint(this->env);
    if (!lowend) {
        paint->setTypeface(this->m_CurrentTypeface);
        paint->setAntiAlias(true);
    }

    paint->setTextSize(this->scaleSize(size));
    paint->setTextAlign(align);

    paint->getTextBounds(text, 0, len, m_Rect->m_Rect);

    jstring convertedStr = wcstojstr(env, text);

    if (outlineColor) {
        if (!lowend) {
            paint->setStyle(Style::FILL);
            int a = (outlineColor >> 24) & 255;
            int r = (outlineColor >> 16) & 255;
            int g = (outlineColor >> 8) & 255;
            int b = outlineColor & 255;
            paint->setARGB(a, r, g, b);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, convertedStr, X - 1, Y - 1, paint->m_Paint);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, convertedStr, X + 1, Y + 1, paint->m_Paint);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, convertedStr, X - 1, Y + 1, paint->m_Paint);
            env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, convertedStr, X + 1, Y - 1, paint->m_Paint);
        }
    }

    int a = (textColor >> 24) & 255;
    int r = (textColor >> 16) & 255;
    int g = (textColor >> 8) & 255;
    int b = textColor & 255;

    paint->setStyle(Style::FILL);
    paint->setARGB(a, r, g, b);
    env->CallVoidMethod(this->m_CanvasObj, this->drawTextId, convertedStr, X, Y, paint->m_Paint);


    env->DeleteLocalRef(convertedStr);

    paint->Cleanup();
}

void Canvas::drawBox(float X, float Y, float width, float height, long color) {


    Paint *paint = new Paint(this->env);

    if(!lowend) paint->setAntiAlias(true);

    int a = (color >> 24) & 255;
    int r = (color >> 16) & 255;
    int g = (color >> 8) & 255;
    int b = color & 255;

    paint->setStyle(Style::FILL);
    paint->setARGB(a, r, g, b);

    env->CallVoidMethod(this->m_CanvasObj, this->drawRectId, X, Y, X + width, Y + height, paint->m_Paint);

    paint->Cleanup();
}

void Canvas::drawBorder(float X, float Y, float width, float height, float thicc, long color) {

    Paint *paint = new Paint(this->env);

    if(!lowend) paint->setAntiAlias(true);

    int a = (color >> 24) & 255;
    int r = (color >> 16) & 255;
    int g = (color >> 8) & 255;
    int b = color & 255;

    paint->setStyle(Style::STROKE);
    paint->setARGB(a, r, g, b);
    paint->setStrokeWidth(thicc);

    env->CallVoidMethod(this->m_CanvasObj, this->drawRectId, X, Y, X + width, Y + height, paint->m_Paint);

    paint->Cleanup();
}

void Canvas::drawBorderRect(float left, float top, float right, float bottom, float thicc, long color) {

    Paint *paint = new Paint(this->env);

    if(!lowend) paint->setAntiAlias(true);

    int a = (color >> 24) & 255;
    int r = (color >> 16) & 255;
    int g = (color >> 8) & 255;
    int b = color & 255;

    paint->setStyle(Style::STROKE);
    paint->setARGB(a, r, g, b);
    paint->setStrokeWidth(thicc);

    env->CallVoidMethod(this->m_CanvasObj, this->drawRectId, left, top, right, bottom, paint->m_Paint);

    paint->Cleanup();
}

void Canvas::drawLine(float startX, float startY, float stopX, float stopY, float thicc, long color) {

    Paint *paint = new Paint(this->env);

    if(!lowend) paint->setAntiAlias(true);

    int a = (color >> 24) & 255;
    int r = (color >> 16) & 255;
    int g = (color >> 8) & 255;
    int b = color & 255;

    paint->setStyle(Style::FILL_AND_STROKE);
    paint->setARGB(a, r, g, b);
    paint->setStrokeWidth(thicc);

    env->CallVoidMethod(this->m_CanvasObj, this->drawLineId, startX, startY, stopX, stopY, paint->m_Paint);

    paint->Cleanup();
}

void Canvas::drawCircle(float x, float y, float radius, float thicc, bool fill, long color) {
    Paint *paint = new Paint(this->env);

    if(!lowend) paint->setAntiAlias(true);

    int a = (color >> 24) & 255;
    int r = (color >> 16) & 255;
    int g = (color >> 8) & 255;
    int b = color & 255;

    if (!fill)
        paint->setStyle(Style::STROKE);
    else
        paint->setStyle(Style::FILL);
    paint->setARGB(a, r, g, b);
    paint->setStrokeWidth(thicc);

    env->CallVoidMethod(this->m_CanvasObj, this->drawCircleId, x, y, radius, paint->m_Paint);

    paint->Cleanup();
}
