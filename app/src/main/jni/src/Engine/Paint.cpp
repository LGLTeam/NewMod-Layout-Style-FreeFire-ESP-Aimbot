
#include "Paint.h"
#include "Canvas.h"
#include <wchar.h>

jstring wcstojstr2(JNIEnv *env, const wchar_t *input)
{
    jobject bb = env->NewDirectByteBuffer((void *) input, wcslen(input) * sizeof(wchar_t));
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

void Paint::Cleanup() {
    env->DeleteLocalRef(Style_FILL);
    env->DeleteLocalRef(Style_STROKE);
    env->DeleteLocalRef(Style_FILL_AND_STROKE);
    env->DeleteLocalRef(Align_LEFT);
    env->DeleteLocalRef(Align_RIGHT);
    env->DeleteLocalRef(Align_CENTER);
    env->DeleteLocalRef(m_Paint);
    delete[] this;
}

void Paint::setTextSize(float size) {
    env->CallVoidMethod(this->m_Paint, this->setTextSizeId, size);
}

void Paint::setARGB(int a, int r, int g, int b) {
    env->CallVoidMethod(this->m_Paint, this->setARGBId, a, r, g, b);
}

void Paint::setStyle(Style style) {
    if(style == Style::FILL)
        env->CallVoidMethod(this->m_Paint, this->setStyleId, this->Style_FILL);
    if(style == Style::STROKE)
        env->CallVoidMethod(this->m_Paint, this->setStyleId, this->Style_STROKE);
    if(style == Style::FILL_AND_STROKE)
        env->CallVoidMethod(this->m_Paint, this->setStyleId, this->Style_FILL_AND_STROKE);
}

void Paint::getTextBounds(const char *text, int start, int end, jobject bounds) {
    jstring str = env->NewStringUTF(text);
    env->CallVoidMethod(this->m_Paint, this->getTextBoundsId, str, 0, end, bounds);
    env->DeleteLocalRef(str);
}

void Paint::getTextBounds(const wchar_t *text, int start, int end, jobject bounds) {
    jstring str = wcstojstr2(this->env, text);
    env->CallVoidMethod(this->m_Paint, this->getTextBoundsId, str, 0, end, bounds);
    env->DeleteLocalRef(str);
}

void Paint::setStrokeWidth(float size) {
    env->CallVoidMethod(this->m_Paint, this->setStrokeWidthId, size);
}

void Paint::setTextAlign(Align align) {
    if(align == Align::LEFT)
        env->CallVoidMethod(this->m_Paint, this->setTextAlignId, this->Align_LEFT);
    if(align == Align::RIGHT)
        env->CallVoidMethod(this->m_Paint, this->setTextAlignId, this->Align_RIGHT);
    if(align == Align::CENTER)
        env->CallVoidMethod(this->m_Paint, this->setTextAlignId, this->Align_CENTER);
}

float Paint::ascent() {
    return env->CallFloatMethod(this->m_Paint, this->ascentId);
}
float Paint::descent() {
    return env->CallFloatMethod(this->m_Paint, this->descentId);
}

void Paint::setShadowLayer(float radius, float dx, float dy, int shadowColor) {
    return env->CallVoidMethod(this->m_Paint, this->setShadowLayerId, radius, dx, dy, shadowColor);
}

void Paint::setTypeface(jobject typeface)
{
    auto result = env->CallObjectMethod(this->m_Paint, this->setTypefaceId, typeface);
    env->DeleteLocalRef(result);
}

void Paint::setAntiAlias(bool b) {
    return env->CallVoidMethod(this->m_Paint, this->setAntiAliasId, b);
}