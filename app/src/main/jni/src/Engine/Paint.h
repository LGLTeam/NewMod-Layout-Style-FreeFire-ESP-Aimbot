//
//
//

#ifndef ML_PAINT_H
#define ML_PAINT_H

#include <jni.h>
#include "Canvas.h"
#include "Typeface.h"
class Paint
{
public:
    jobject m_Paint;
    JNIEnv *env;
public:
    jmethodID setStyleId;
    jmethodID setTextSizeId;
    jmethodID setARGBId;
    jmethodID getTextBoundsId;
    jmethodID setStrokeWidthId;
    jmethodID setTextAlignId;
    jmethodID ascentId;
    jmethodID descentId;
    jmethodID setShadowLayerId;
    jmethodID setTypefaceId;
    jmethodID setAntiAliasId;

    jobject Style_FILL, Style_STROKE, Style_FILL_AND_STROKE;
    jobject Align_LEFT, Align_RIGHT, Align_CENTER;

    Paint(JNIEnv *env)
    {
        this->env = env;

        jclass paintClass = env->FindClass("android/graphics/Paint");
        jmethodID init = env->GetMethodID(paintClass, "<init>", "()V");
        this->m_Paint = env->NewObject(paintClass, init);

        setStyleId = env->GetMethodID(paintClass, "setStyle", "(Landroid/graphics/Paint$Style;)V");
        setTextSizeId = env->GetMethodID(paintClass, "setTextSize", "(F)V");
        setARGBId = env->GetMethodID(paintClass, "setARGB", "(IIII)V");
        getTextBoundsId = env->GetMethodID(paintClass, "getTextBounds", "(Ljava/lang/String;IILandroid/graphics/Rect;)V");
        setStrokeWidthId = env->GetMethodID(paintClass, "setStrokeWidth", "(F)V");
        setTextAlignId = env->GetMethodID(paintClass, "setTextAlign", "(Landroid/graphics/Paint$Align;)V");
        ascentId = env->GetMethodID(paintClass, "ascent", "()F");
        descentId = env->GetMethodID(paintClass, "descent", "()F");
        setShadowLayerId = env->GetMethodID(paintClass, "setShadowLayer", "(FFFI)V");
        setTypefaceId = env->GetMethodID(paintClass, "setTypeface", "(Landroid/graphics/Typeface;)Landroid/graphics/Typeface;");
        setAntiAliasId = env->GetMethodID(paintClass, "setAntiAlias", "(Z)V");
        env->DeleteLocalRef(paintClass);

        jclass styleClass = env->FindClass("android/graphics/Paint$Style");
        jfieldID id = env->GetStaticFieldID(styleClass, "FILL", "Landroid/graphics/Paint$Style;");
        Style_FILL = env->GetStaticObjectField(styleClass, id);
        id = env->GetStaticFieldID(styleClass, "STROKE", "Landroid/graphics/Paint$Style;");
        Style_STROKE = env->GetStaticObjectField(styleClass, id);
        id = env->GetStaticFieldID(styleClass, "FILL_AND_STROKE", "Landroid/graphics/Paint$Style;");
        Style_FILL_AND_STROKE = env->GetStaticObjectField(styleClass, id);
        env->DeleteLocalRef(styleClass);

        jclass alignClass = env->FindClass("android/graphics/Paint$Align");
        id = env->GetStaticFieldID(alignClass, "LEFT", "Landroid/graphics/Paint$Align;");
        Align_LEFT = env->GetStaticObjectField(alignClass, id);
        id = env->GetStaticFieldID(alignClass, "RIGHT", "Landroid/graphics/Paint$Align;");
        Align_RIGHT = env->GetStaticObjectField(alignClass, id);
        id = env->GetStaticFieldID(alignClass, "CENTER", "Landroid/graphics/Paint$Align;");
        Align_CENTER = env->GetStaticObjectField(alignClass, id);
        env->DeleteLocalRef(alignClass);
    }

    virtual void Cleanup();

    virtual void setStyle(Style style);
    virtual void setTextSize(float size);
    virtual void setARGB(int a, int r, int g, int b);
    virtual void getTextBounds(const char *text, int start, int end, jobject bounds);
    virtual void getTextBounds(const wchar_t *text, int start, int end, jobject bounds);
    virtual void setStrokeWidth(float size=1.0f);
    virtual void setShadowLayer(float radius, float dx, float dy, int shadowColor);
    virtual void setTextAlign(Align align);
    virtual void setTypeface(jobject typeface);
    virtual void setAntiAlias(bool b);

    virtual float ascent();
    virtual float descent();
};


#endif //ML_PAINT_H
