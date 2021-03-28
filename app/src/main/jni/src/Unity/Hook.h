#ifndef ANDROID_MOD_MENU_HOOK_H
#define ANDROID_MOD_MENU_HOOK_H
#include <dlfcn.h>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Global.h"
using namespace std;
long AfindLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    long address = 0;

    sprintf( filename, "/proc/self/maps");

    fp = fopen( filename, "rt" );
    if( fp == NULL ){
        perror("fopen");
        goto done;
    }

    while( fgets( buffer, sizeof(buffer), fp ) ) {
        if(strstr( buffer, library ) ){
            address = (long)strtoul( buffer, NULL, 16 );
            goto done;
        }
    }

    done:

    if(fp){
        fclose(fp);
    }

    return address;
}

long ClibBase;

long AgetAbsoluteAddress(const char* libraryName, long relativeAddr) {
    if (ClibBase == 0) {
        ClibBase = AfindLibrary(libraryName);
        if (ClibBase == 0) {
            ClibBase = 0;
        }
    }
    return ClibBase + relativeAddr;
}


# define getRealOffset(offset) AgetAbsoluteAddress("libil2cpp.so",offset)


class Vvector3 {
public:
    float X;
    float Y;
    float Z;
    Vvector3() : X(0), Y(0), Z(0) {}
    Vvector3(float x1, float y1, float z1) : X(x1), Y(y1), Z(z1) {}
    Vvector3(const Vvector3 &v);
    ~Vvector3();
};
Vvector3::Vvector3(const Vvector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
Vvector3::~Vvector3() {}

bool (*IsSameTeam)(void *_this, void* p1, void* p2) = (bool(*)(void *, void*, void*))getRealOffset(Global.IsSameTeam);
bool (*AttackableEntity_GetIsDead)(void *attackableEntity) = (bool (*)(void *))getRealOffset(Global.AttackableEntity_GetIsDead);
bool (*AttackableEntity_IsVisible)(void *attackableEntity) = (bool (*)(void *))getRealOffset(Global.AttackableEntity_IsVisible);

static void *get_MyFollowCamera(void *players) {
    void *(*_get_MyFollowCamera) (void *player) = (void *(*)(void *))getRealOffset(Global.get_MyFollowCamera);
    return _get_MyFollowCamera(players);
}

static bool IsFiring(void *player) {
    bool (*_IsFiring)(void *players) = (bool (*)(void *))getRealOffset(Global.IsFiring);
    return _IsFiring(player);
}

static void *SpectatorRequestQuitMatch(void *CurMatch) {
	void *(*_getQuit)(void *_CurMatch) = (void *(*)(void *))getRealOffset(0x1EC2BE0);
	_getQuit(CurMatch);
}

 void* (*_get_NickName)(void *players) = (void * (*)(void *))getRealOffset(Global.get_NickName);
    


static void *get_imo(void *player) {
    void *(*_get_imo)(void *players) = (void *(*)(void *))getRealOffset(Global.get_imo);
    return _get_imo(player);
}

static void set_esp(void *imo, Vector3 x, Vector3 y) {
    void (*_set_esp)(void *imo, Vector3 X, Vector3 Y) = (void (*)(void *, Vector3, Vector3))getRealOffset(Global.set_esp);
    _set_esp(imo, x, y);
}

/*static void set_esp2(Vector3 x, Vector3 y) {
    void (*_set_esp2)(Vector3 X, Vector3 Y) = (void (*)(Vector3, Vector3))getRealOffset(0x2699C98);
    _set_esp2(x, y);
}

*/


static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))getRealOffset(Global.get_IsSighting);
    return _get_IsSighting(player);
}

static Vector3 Transform_INTERNAL_GetPosition(void *player) {
    Vector3 out = Vector3::Zero();
    void (*_Transform_INTERNAL_GetPosition)(void *transform, Vector3 * out) = (void (*)(void *, Vector3 *))getRealOffset(Global.Transform_INTERNAL_GetPosition);
    _Transform_INTERNAL_GetPosition(player, &out);
    return out;
}

static void *Current_Local_Player() {
    void *(*_Local_Player)(void *players) = (void *(*)(void *))getRealOffset(Global.Current_Local_Player);
    return _Local_Player(NULL);
}

static void *CurrentLocalSpectator() {
    void *(*_LocalSpectator)(void *players) = (void *(*)(void *))getRealOffset(0x2092A3C);//1.56
    return _LocalSpectator(NULL);
}

static void *GetLocalPlayerOrObServer() {
    void *(*_GetLocalPlayerOrObServer)(void *players) = (void *(*)(void *))getRealOffset(Global.GetLocalPlayerOrObServer);
    return _GetLocalPlayerOrObServer(NULL);
}

static void *Component_GetTransform(void *player) {
    void *(*_Component_GetTransform)(void *component) = (void *(*)(void *))getRealOffset(Global.Component_GetTransform);
    return _Component_GetTransform(player);
}

static bool get_isAlive(void *player) {
    bool (*_get_isAlive)(void *players) = (bool (*)(void *))getRealOffset(Global.get_isAlive);
    return _get_isAlive(player);
}


static bool IsDieing(void *player) {
    bool (*_get_die)(void *players) = (bool (*)(void *))getRealOffset(0xB61D88);//1.56
    return _get_die(player);
}


static bool get_isLocalTeam(void *player) {
    bool (*get_isLocalTeam)(void *players) = (bool (*)(void *))getRealOffset(Global.get_isLocalTeam);
    return get_isLocalTeam(player);
}


static bool get_isVisible(void *player) {
    bool (*_get_isVisible)(void *players) = (bool (*)(void *))getRealOffset(Global.get_isVisible);
    return _get_isVisible(player);
}

static Vector3 GetAttackableCenterWS(void *player) {
    Vector3 (*_GetAttackableCenterWS)(void *players) = (Vector3 (*)(void *))getRealOffset(Global.GetAttackableCenterWS);
    return _GetAttackableCenterWS(player);
}

static Vector3 WorldToScreenPoint(void *PlayerCam, Vector3 PlayerPos) {
Vector3 (*_WorldToScreenPoint)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getRealOffset(0x27A27D8);//1.56
return _WorldToScreenPoint(PlayerCam,PlayerPos);
}


static int GetPhysXPose(void *player) {
    int (*_GetPhysXPose)(void *players) = (int (*)(void *))getRealOffset(Global.GetPhysXPose);
    return _GetPhysXPose(player);
}

static Vector3 GetForward(void *player) {
    Vector3 (*_GetForward)(void *players) = (Vector3 (*)(void *))getRealOffset(Global.GetForward);
    return _GetForward(player);
}

static void set_aim(void *player, Quaternion look) {
    void (*_set_aim)(void *players, Quaternion lock) = (void (*)(void *, Quaternion))getRealOffset(Global.set_aim);
    _set_aim(player, look);
}

static void Transform_INTERNAL_SetPosition(void *player, Vvector3 inn) {
    void (*_Transform_INTERNAL_SetPosition)(void *transform, Vvector3 in) = (void (*)(void *, Vvector3))getRealOffset(Global.Transform_INTERNAL_SetPosition);
    _Transform_INTERNAL_SetPosition(player, inn);
}

static void *Camera_main() {
    void *(*_Camera_main)(void *nuls) = (void *(*)(void *))getRealOffset(Global.Camera_main);
    return _Camera_main(NULL);
}

static void *CurCamera() {
    void *(*_CurCam)(void *nuls) = (void *(*)(void *))getRealOffset(0x2092268);//1.56
    return _CurCam(NULL);
}

static Vector3 ScreenPointToWorld(void *PlayerCam, Vector3 ScreenPos) {
Vector3 (*_ScreenPointToWorld)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) getRealOffset(0x2684604);
return _ScreenPointToWorld(PlayerCam,ScreenPos);
}


#endif
