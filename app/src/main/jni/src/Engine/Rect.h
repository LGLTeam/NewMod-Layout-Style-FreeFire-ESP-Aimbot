//
//
//

#ifndef MENU_RECT_H
#define MENU_RECT_H

#include <jni.h>

class Rect {
private:
    jfieldID leftId, topId, rightId, bottomId;
public:
    JNIEnv *env;
    jobject m_Rect;

    Rect(JNIEnv *env)
    {
        this->env = env;

        jclass rectClass = env->FindClass("android/graphics/Rect");
        jmethodID init = env->GetMethodID(rectClass, "<init>", "()V");
        this->m_Rect = env->NewGlobalRef(env->NewObject(rectClass, init));

        leftId = env->GetFieldID(rectClass, "left", "I");
        topId = env->GetFieldID(rectClass, "top", "I");
        rightId = env->GetFieldID(rectClass, "right", "I");
        bottomId = env->GetFieldID(rectClass, "bottom", "I");

        env->DeleteLocalRef(rectClass);
    }

    void Cleanup();

    int getLeft();
    int getRight();
    int getTop();
    int getBottom();

    int getWidth();
    int getHeight();
};


#endif //MENU_RECT_H
