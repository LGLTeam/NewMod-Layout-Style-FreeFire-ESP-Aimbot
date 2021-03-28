//
//
//

#include "Rect.h"

void Rect::Cleanup() {
    env->DeleteGlobalRef(m_Rect);
    delete[] this;
}

int Rect::getLeft() {
    return env->GetIntField(this->m_Rect, this->leftId);
}

int Rect::getRight(){
    return env->GetIntField(this->m_Rect, this->rightId);
}

int Rect::getTop(){
    return env->GetIntField(this->m_Rect, this->topId);
}

int Rect::getBottom(){
    return env->GetIntField(this->m_Rect, this->bottomId);
}

int Rect::getWidth() {
    return getRight() - getLeft();
}

int Rect::getHeight() {
    return getBottom() - getTop();
}

