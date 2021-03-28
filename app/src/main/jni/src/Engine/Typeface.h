//
//
//

#ifndef PUBG_TYPEFACE_H
#define PUBG_TYPEFACE_H

#include <jni.h>

enum FontStyle
{
    NORMAL = 0,
    BOLD = 0,
    ITALIC = 1,
    BOLD_ITALIC = 1
};

class Typeface {
private:
    jmethodID createMethod;
public:
    JNIEnv *env;
    jclass m_Typeface;

    Typeface(JNIEnv *env)
    {
        this->env = env;

        m_Typeface = env->FindClass("android/graphics/Typeface");
        createMethod = env->GetStaticMethodID(m_Typeface, "create", "(Ljava/lang/String;I)Landroid/graphics/Typeface;");
    }

    jobject create(const char *family, int style);
    void Cleanup();
};


#endif //PUBG_TYPEFACE_H
