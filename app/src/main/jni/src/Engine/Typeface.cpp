//
//
//

#include "Typeface.h"

jobject Typeface::create(const char *family, int style) {
    jstring fam = env->NewStringUTF(family);

    jobject result = env->CallStaticObjectMethod(this->m_Typeface, this->createMethod, fam, style);

    env->DeleteLocalRef(fam);

    return result;
}

void Typeface::Cleanup() {
    env->DeleteLocalRef(this->m_Typeface);
    delete[] this;
}