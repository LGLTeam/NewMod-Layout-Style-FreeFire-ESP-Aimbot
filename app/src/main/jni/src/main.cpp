#include <pthread.h>
#include <jni.h>
#include <src/Includes/Utils.h>
#include "src/Unity/Quaternion.hpp"
#include "src/Unity/Vector3.hpp"
#include "src/Engine/Rect.h"
#include "src/Engine/Canvas.h"
#include "src/Engine/Paint.h"
#include "src/Engine/Typeface.h"
#include "src/Unity/Color.hpp"
#include "src/Unity/Vector2.hpp"
#include "src/Unity/Unity.h"
#include <src/Substrate/SubstrateHook.h>
#include <src/Unity/Hook.h>
#include <src/Unity/Global.h>
#include <dlfcn.h>
//#include "esp/ESP.h"
//#include <assert.h>
//#include <malloc.h>
#include <string.h>
//#include <stdlib.h>
//#include "android/log.h"
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "KittyMemory/MemoryPatch.h"
#include "Includes/Logger.h"
using namespace std;

#define CR_XD "CMSR"
# define getRealOffset(offset) AgetAbsoluteAddress("libil2cpp.so",offset)
#define HOOK(offset, ptr, orig) MSHookFunction((void *)getRealOffset(offset), (void *)ptr, (void **)&orig)



extern "C" {
JNIEXPORT jboolean JNICALL
Java_uk_lgl_modmenu_FloatingMod_EnableSounds(
        JNIEnv *env,
        jobject activityObject) {
    return true;
}



JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingMod_Icon(
        JNIEnv *env,
        jobject activityObject) {

    //Use https://www.base64encode.org/ to encode your image to base64
return env->NewStringUTF(
            "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");
}
 
 
JNIEXPORT jint JNICALL
Java_uk_lgl_modmenu_FloatingMod_IconSize(
        JNIEnv *env,
        jobject activityObject) {
    return 70;
}

JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingMod_IconWebViewData(
        JNIEnv *env,
        jobject activityObject) {

    //Upload your image or gif on imgur.com or other sites
    //To disable it:
    //return NULL
    //It would load the base64 icon from above as usual

    //From internet: return env->NewStringUTF("https://i.imgur.com/SujJ85j.gif"); (Requires android.permission.INTERNET)
    //From assets folder: return env->NewStringUTF("file:///android_asset/example.gif"); (Requires android.permission.INTERNET)
    //Base64 html: return env->NewStringUTF("data:image/png;base64, <encoded base64 here>");
    //Nothing: return NULL
    return env->NewStringUTF("https://i.imgur.com/SujJ85j.gif");
}



JNIEXPORT jstring JNICALL
Java_uk_lgl_modmenu_FloatingMod_Toast(
        JNIEnv *env,
        jclass clazz) {
        return env->NewStringUTF("<b><font color=GREEN>By KazzyMods</font></b><font color=RED><b></b></font>");
}


//Singnature 
//gameassistem loadassi_gamepro 
//MapReset
//LibnameRestore


JNIEXPORT jobjectArray  JNICALL
Java_uk_lgl_modmenu_FloatingMod_getFeatureList(
        JNIEnv *env,
        jobject activityObject) {
    jobjectArray ret;


    const char *features[] = {
            "Category_----------AIMBOTs----------",

            "Toggle_ Aimbot",
            "Toggle_ Aim Por Tiro",
            "Toggle_Aim Por Mira",
            "Toggle_Visible Check",
            "SeekBar_Aim Fov_0_360",
            "SeekBar_Aim Smooth_0_180",
            "Category_---------ESP Types---------",

            "Toggle_Show Name Enemy",
            "Toggle_Show Box Enemy",
            "Toggle_Show Line Enemy",
            "Toggle_Show Line Enemy 2",
            "Toggle_Show Line Enemy 3",
            "Toggle_Show Box Red",
            "Toggle_Show Circle H"
            
           
    }; // 7

    int Total_Feature = (sizeof features /
                         sizeof features[0]);

    ret = (jobjectArray) env->NewObjectArray(Total_Feature, env->FindClass("java/lang/String"),
                                             env->NewStringUTF(""));
    int i;
    for (i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));
    return (ret);
}

struct My_Patches {
    MemoryPatch
            Bypass,Bypass1,Bypass2,Bypass3,Bypass4,Fix1,Fix2,Fix3,Fix4,Fix5,Fix6,Fix7,Fix8,Fix9,Fix10,Anti1,Anti2,Anti3,Anti4,Anti5,Anti6,Anti7,Anti8,Anti9,Anti10,Anti11,Anti12;
} XPatches;

bool feature1 = false, feature2 = false, feature3 = false, FixHs = false;
bool UseFiring = false, UseScope = false, EspF = false, UseVisible = false;
bool UseFOV = false;
bool Telekill = false;
bool EspBox = false;
float FovCount2 = 0.998f;
int FovCount1;
int speedHack = 0;
bool active = true;
bool launched = false;
bool Chams = false;
bool LineTeste = false;
bool linha = false;
int MxDis1;
float MxDis;
bool EspMoco = false;
bool espFire = false;
int var2 = -1;
int var1 = -1;
bool EspLine2 = false;
bool EspLine3 = false;
bool UseColors = false;
bool DrawText = false;
bool linecolor = false;
bool lineteste = false;
bool crosshair = false;
bool boxteste = false;
bool esplinhagrossa = false;
bool DrawCrossHair = false;
bool textotest = false;
bool DrawLineTeste = false;
bool EspBox2 = false;
bool EspBox3 = false;
bool EspBox4 = false;
bool EspBox5 = false;
bool EspLine4 = false;
bool EspLine5 = false;
bool espNames = false;
bool Esp = false;
bool value = false;
bool alvo = false;



int m_gSWidth;
int m_gSHeight;
bool EspLine = false;
bool UseMxD = false;
const char *libName = "libil2cpp.so";
Color CustomColors;
bool isEspReady = false;

JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_FloatingMod_Changes(
        JNIEnv *env,
        jobject activityObject,
        jint feature,
        jint Value) {
    switch (feature) {

        case 1: // Switch
            feature1 = !feature1;
            break;
        case 2:
            UseFiring = !UseFiring;
            break;
        case 3:
            UseScope = !UseScope;
            break;
        case 4:
            UseVisible = !UseVisible;
            break;
        case 5:
            FovCount1 = Value;
            if(FovCount1 > 1){
                UseFOV = true;
                FovCount2 = 1.0f - (0.0027f * (float)FovCount1);
            } else {
                UseFOV = false;
            }
            break;
        case 6:
            MxDis1 = Value;
            if(MxDis1 > 1){
                UseMxD = true;
                MxDis = (float)MxDis1;
            } else {
                UseMxD = false;
            }
            break;
        case 8: // Switch
            feature2 = !feature2;
            break;
        case 9: // Switch
            EspBox = !EspBox;
            break;
        case 10: // Switch
            EspLine = !EspLine;
            break;
        case 11:
            EspLine2 = !EspLine2;
            break;
        case 12:
            EspLine3 = !EspLine3;
            break;
         case 13:
            EspBox2 = !EspBox2;
            break;
         case 14:
             alvo = !alvo;
             break;
            
        
		
			
			
			
    }
}
}

struct EnemyData {
    float Health;
    float Distance;
    Vector3 Location;
    Vector2 HeadLocation;
};

struct Response {
    int PlayerCount;
    EnemyData Players[54];
};

struct {
    bool EspReady;
} CMSR;

static void *CurrentMatch() {
    void *(*_Curent_Match) (void *nuls) = (void *(*)(void *))getRealOffset(0x2092268);//1.56
    return _Curent_Match(NULL);
}
//void* (*get_main)() = (void*(*)())getRealOffset(0x2684900); // UnityEngine.Camera
int (*XsWidth)() = (int(*)())getRealOffset(Global.get_width);
int (*XsHeight)() = (int(*)())getRealOffset(Global.get_height);


//bool (*get_IsDieing)(void* player) = (bool(*)(void *))getRealOffset(0xA0E51C);

static bool get_IsSkyDiving(void *player) {
    bool (*_get_div)(void *players) = (bool (*)(void *))getRealOffset(0xB4D998);//1.56
    return _get_div(player);
}
static bool get_IsSkyDashing(void *player) {
    bool (*_get_sky)(void *players) = (bool (*)(void *))getRealOffset(0xB63910);//1.56
    return _get_sky(player);
}
static bool get_IsParachuting(void *player) {
    bool (*_get_paraq)(void *players) = (bool (*)(void *))getRealOffset(0xB4D9F0);//1.56
    return _get_paraq(player);
}

int FramePerS;


void* UIInGameScene = NULL;



Vector3 GetHeadPosition(void* player){
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + 0x1B0));//1.56
}

Vector3 GetHipPosition(void* player){
    return Transform_INTERNAL_GetPosition(*(void**) ((uint64_t) player + 0x1B0));//1.56
}

static void *CurrentUIScene() {
    void *(*_CurrentUIScene)(void *nuls) = (void *(*)(void *))getRealOffset(Global.CurrentUIScene);
    return _CurrentUIScene(NULL);
}

void* (*_String_Concat)(void *_null, void *_this,void* str1, void* str2) = (void*(*)(void*,void*,void*, void*))getRealOffset(0x2200BA0);//1.56

static monoString *U3DStr(const char *str)
{
    monoString *(*String_CreateString)(void *_this, const char *str) = (monoString * (*)(void *, const char *))getRealOffset(0x22107D0);//1.56
    return String_CreateString(NULL, str);
}
static monoString *U3DStrFormat(float distance) {
    char buffer[10];
    sprintf(buffer, " [%.f m]", distance);
    return U3DStr(buffer);
}

static monoString *U3DStrFpsCount(int FpS) {
    char dist[10];
    sprintf(dist, " [%d FPS %s]", FpS,"~0");
    return U3DStr(dist);
}

static void ShowPopupMessage2(monoString *nick) {
    void (*_ShowDynamicPopupMessage)(void *players, monoString * nicks, float duration) = (void (*)(void *, monoString *, float))getRealOffset(0x1141E54);//1.56
    void *ui = CurrentUIScene();
    if (ui != NULL) {
        _ShowDynamicPopupMessage(ui, nick, 3.5);
    }
}

static void SetColor(Color CurColor) {
    void (*_SetColor)(Color _Colors) = (void (*)(Color))getRealOffset(0x2021DF0);//1.56
    _SetColor(CurColor);
}

static Vector2 WorldLocToScreenPoint(void *WorldCam, Vector3 WorldPos) {
    Vector2 (*_WorldToScreenScene)(void* Camera, Vector3 position) = (Vector2 (*)(void*, Vector3)) getRealOffset(0x27A27D8);//1.56
    return _WorldToScreenScene(WorldCam,WorldPos);
}



/*static void *World_Camera() {
    void *(*_World_Camera)(void *nuls) = (void *(*)(void *))getRealOffset(0x2662C44);
    return _World_Camera(NULL);
}

*/

void (*ShowPopupMessage)(void *players, void * nicks, float duration) = (void (*)(void *, void *, float))getRealOffset(0x1141FDC);//1.56


static bool RealDead(void *player) {
    bool (*_RealDead)(void *players) = (bool (*)(void *)) getRealOffset(0x2316ECC);//1.56
    return _RealDead(player);
}


       

void (*LateUpdate)(void *componentPlayer);
void AimBot(void *local_player, void *enemy_player) {
    void* CurrentWP = get_imo(local_player);
    if(FixHs) {
        //int SxWidth = Screen_get_width();
        //int SxWidth = Screen_get_width();

    }
    Vector3 CurTF = GetHipPosition(local_player);
    Vector3 CurEnTF = GetHipPosition(enemy_player);

    if(feature2) {
        float KDist2 = Vector3::Distance(CurTF,CurEnTF);
        ShowPopupMessage(CurrentUIScene(),_String_Concat(NULL,NULL,_get_NickName(enemy_player),U3DStrFormat(KDist2)),1.0f);
    }
	
	
    int pose = GetPhysXPose(enemy_player);
    bool visible = get_isVisible(enemy_player);
    bool sameteam = get_isLocalTeam(enemy_player);
    Vector3 HeadTF = GetHeadPosition(enemy_player);
    Vector3 HipTF = GetHipPosition(enemy_player);
    void *Main_Camera = *(void **)((uintptr_t)local_player + Global.MainCameraTransform);
    bool SkyDiv = get_IsSkyDiving(local_player);
    bool SkyDash = get_IsSkyDashing(local_player);
    bool Parachut = get_IsParachuting(local_player);
	
    if (pose != 8 && visible && !sameteam && Main_Camera != NULL && !SkyDiv && !SkyDash && !Parachut){
        Vector3 CenterWS = GetAttackableCenterWS(local_player);
        bool scope = get_IsSighting(local_player);
        float distance = Vector3::Distance(CenterWS, HeadTF);

        Vector3 PlayerLocation = Transform_INTERNAL_GetPosition(Main_Camera);
        float Distance2 = Vector3::Distance(PlayerLocation,HipTF);
        Quaternion PlayerLook = GetRotationToLocation(HeadTF, 0.1f, PlayerLocation);
        //Quaternion PlayerLook2 = GetRotationToLocation(HipTF, 0.1f, PlayerLocation);
        Vector3 fwd = GetForward(Main_Camera);
        Vector3 nrml = Vector3::Normalized(HeadTF - PlayerLocation);
        float PlayerDot = Vector3::Dot(fwd, nrml);
        bool firing = IsFiring(local_player);
        bool EnemyVisible = AttackableEntity_IsVisible(enemy_player);

        if (Telekill) {
            for (int u = 0; u < 6; u++) {
                puts("CMSR");
            }
		

			
						//Linea Satelite De Enemigo//
void* CurrentWP = get_imo(local_player);
if(linha) {   
Vector3 From = Transform_INTERNAL_GetPosition(Component_GetTransform(Camera_main()));
Vector3 BodyZPos = GetHipPosition(local_player);
Vector3 From2 = From + Vector3(2.3,8,(BodyZPos.Z - From.Z));
Vector3 To = GetHeadPosition(enemy_player);
set_esp(CurrentWP,From2,To);    
}
				
            //set_aim(local_player, PlayerLook);
            void *_MountTF = Component_GetTransform(enemy_player);
            if (_MountTF != NULL) {
                Vector3 MountTF =
                        Transform_INTERNAL_GetPosition(_MountTF) - (GetForward(_MountTF) * 1.3f);
                Transform_INTERNAL_SetPosition(Component_GetTransform(local_player), Vvector3(MountTF.X, MountTF.Y, MountTF.Z));
            }
        }
		
		




        if(!UseFOV && ((!UseMxD) || (UseMxD && Distance2 < MxDis)) && ((!UseVisible) || (UseVisible && EnemyVisible))) {
            if(feature1) {
                set_aim(local_player, PlayerLook);
            } else if(scope && UseScope) {
                set_aim(local_player, PlayerLook);
            } else if (firing && UseFiring)  {
                set_aim(local_player, PlayerLook);
            }
        } else if(UseFOV && PlayerDot > FovCount2 && ((!UseMxD) || (UseMxD && Distance2 < MxDis)) && ((!UseVisible) || (UseVisible && EnemyVisible))){
            if(feature1) {
                set_aim(local_player, PlayerLook);
            } else if(scope && UseScope) {
                set_aim(local_player, PlayerLook);
            } else if (firing && UseFiring)  {
                set_aim(local_player, PlayerLook);
            }
        }

    }
}



Response response{};
void createDataList(void* Enemy, void* LocalPlayer) {
    void* MainCam = Camera_main();
    Vector3 CamPos = Transform_INTERNAL_GetPosition(Component_GetTransform(MainCam));
    Vector3 EnemyPos = GetHipPosition(Enemy);
    Vector2 BoxToScreen = WorldLocToScreenPoint(Camera_main(),EnemyPos);
    float DistanceBox = (Vector2::Distance(BoxToScreen,Vector2(CamPos.X,CamPos.Y)) / 100.0f);
    Vector2 HeadPos = WorldLocToScreenPoint(Camera_main(),GetHeadPosition(Enemy));

    EnemyData* data = &response.Players[response.PlayerCount];
    data->Distance = DistanceBox;
    data->Location = CamPos;
    data->HeadLocation = HeadPos;
    ++response.PlayerCount;

}


void *fakeEnemy;
void _LateUpdate(void *player){
    if (player != NULL) {
        void *local_player = Current_Local_Player();
        if (local_player == NULL){
            local_player = GetLocalPlayerOrObServer();
        }
        if (local_player != NULL){
            void *current_match = CurrentMatch();
            if (current_match != NULL) {

                if (EspF) {
                    int FpS = FramePerS;
                    ShowPopupMessage2(U3DStrFpsCount(FpS));
                }
	
				
                isEspReady = false;
                  if(UseColors){
                        SetColor(CustomColors);
                    }
                    
                void *fakeCamPlayer = get_MyFollowCamera(local_player);
                void *fakeCamEnemy = get_MyFollowCamera(player);
                if (fakeCamPlayer != NULL && fakeCamEnemy != NULL){
                    void *fakeCamPlayerTF = Component_GetTransform(fakeCamPlayer);
                    void *fakeCamEnemyTF = Component_GetTransform(player);
                    if (fakeCamPlayerTF != NULL && fakeCamEnemyTF != NULL){
                        Vector3 fakeCamPlayerPos = Transform_INTERNAL_GetPosition(fakeCamPlayerTF);
                        Vector3 fakeCamEnemyPos = Transform_INTERNAL_GetPosition(fakeCamEnemyTF);
                        float distance = Vector3::Distance(fakeCamPlayerPos, fakeCamEnemyPos);
                        //void *Main1Camera = *(void **)((uintptr_t)local_player + Global.MainCameraTransform);
                        //CMSREsp.Local = local_player;
                        if (player != local_player){
                            if (distance > 1.6f) {
                                bool sameteams = get_isLocalTeam(player);
                                int pose = GetPhysXPose(player);
                                //         bool alive = get_isAlive(player);
                                bool visible = get_isVisible(player);
                                bool Dead1 = AttackableEntity_GetIsDead(player);
                                bool Dieing1 = IsDieing(player);
                                bool Dead2 = RealDead(player);
                                if (!sameteams && pose != 8 && visible && !Dead1 && !Dieing1 && !Dead2){
                                    AimBot(local_player, player);

                                }
                            } else {
                                fakeEnemy = player;
                            }
                        }
                    }
                    if(!isEspReady) {
                        CMSR.EspReady = false;
                        response.PlayerCount = 1;
                        m_gSWidth = XsWidth();
                        m_gSHeight = XsHeight();
                        monoDictionary<uint8_t *, void **> *players = *(monoDictionary<uint8_t*, void **> **)((long)current_match + 0x44);
                        for(int u = 0; u < players->getNumValues(); u++)
                        {
                            void* closestEnemy = players->getValues()[u];
                            if (closestEnemy != local_player && closestEnemy != NULL && get_isVisible(closestEnemy) && !AttackableEntity_GetIsDead(closestEnemy)) {

                                createDataList(closestEnemy,local_player);
                            }
                        }
                        isEspReady = true;
                        CMSR.EspReady = true;
                    }

                }
            }
        }
    }
    LateUpdate(player);
}

//ESP espOverlay;

/*void DrawESP(ESP esp, int screenWidth, int screenHeight) {
    int count = response.PlayerCount;
    if (count >= 1) {
        for (int i = 1; i < count; i++) {
            EnemyData player = response.Players[i];
            Vector2 location = player.Localation;
            Vector2 screen(screenWidth, screenHeight);
            float mScale = screenHeight / (float) 1080;
            int borders = isOutsideSafezone(location, screen);
            char buffer360[10];
            float distance360 = Vector3::Distance(player.Enemy, player.Player);
            sprintf(buffer360, "%.f m", distance360);
            
            if(EspLine) {
                esp.DrawLineTeste(Color::Green(), 1, Vector2((screenWidth / 2), 0), player.HeadLocation);
            }
        }
    }*/


extern "C"
JNIEXPORT void JNICALL
Java_uk_lgl_modmenu_Loader_DrawOl(JNIEnv *env, jclass type, jobject espView, jobject canvas) {/*
    espOverlay = ESP(env, espView, canvas);
    if (espOverlay.isValid()){
        DrawLineTeste(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
    }*/






}
//}
//}
//void GetPlayerData(int PlayerIndex) {

Canvas *m_Canvas = 0;
void native_onDraw(JNIEnv *env, jclass clazz, jobject canvas, int screenWidth, int screenHeight, float screenDensity) {
    if (!m_Canvas) {
        m_Canvas = new Canvas(env, screenWidth, screenHeight, screenDensity);
    }

    if (!m_Canvas)
        return;

    float lineSize = m_Canvas->scaleSize(0.75f);
    m_Canvas->UpdateCanvas(canvas);
    m_Canvas->HighEndMode(true);
    int count = response.PlayerCount;

    if (count >= 1 && CMSR.EspReady) {
        //Aimbot(count,&response.Players);
        for (int i = 1; i < count; i++) {
            EnemyData player = response.Players[i];
            Vector2 HeadLoc = player.HeadLocation;
	
				
				
			
            if (EspLine) {
                Vector2 To = player.HeadLocation;
                Vector2 From = Vector2(m_gSWidth / 6, 1);
                m_Canvas->drawLine(From.X, From.Y, To.X, To.Y, lineSize, 0xFFFF00FF); //COLOR RED
                

        
            
            if (EspBox) {
                Vector2 End = player.HeadLocation;
                        float boxHeight = (screenWidth / player.Distance);
                        float boxWidth = (screenHeight / player.Distance);
                        m_Canvas->drawBox(End.X - (boxWidth / 2), End.Y, boxWidth, boxHeight,
                        0xFFFF00FF);
                        
             if (EspBox2) {
                Vector2 End = player.HeadLocation;
                float boxHeight = (m_gSWidth / player.Distance);
                float boxWidth = (m_gSHeight / player.Distance);
                m_Canvas->drawBox(End.X - (boxWidth / 2), End.Y, boxWidth, boxHeight,
                                  0xFFFF0000);
        
        //   set_esp2(From2,To);
    
                                  
             if (EspBox3) {
                Vector2 End = player.HeadLocation;
                float boxHeight = (m_gSWidth / player.Distance);
                float boxWidth = (m_gSHeight / player.Distance);
                m_Canvas->drawBox(End.X - (boxWidth / 2), End.Y, boxWidth, boxHeight,
                                  0xFFFFFFFF);
                                 
             if (EspBox4) {
                Vector2 End = player.HeadLocation;
                float boxHeight = (m_gSWidth / player.Distance);
                float boxWidth = (m_gSHeight / player.Distance);
                m_Canvas->drawBox(End.X - (boxWidth / 2), End.Y, boxWidth, boxHeight,
                                  0xFF000000);
                                 
            if (EspBox5) {
                Vector2 End = player.HeadLocation;
                float boxHeight = (m_gSWidth / player.Distance);
                float boxWidth = (m_gSHeight / player.Distance);
                m_Canvas->drawBox(End.X - (boxWidth / 2), End.Y, boxWidth, boxHeight,
                                  0xFFFF04FFF3);
             if (alvo) {
                 Vector2 From = Vector2(m_gSWidth / 7, 1);
                m_Canvas->drawCircle(From.X, From.Y, To.X, To.Y,  0xFFFF00FF);
                                  
			 
			 
			
			  if (EspLine3) {
                Vector2 To = player.HeadLocation;
                Vector2 From = Vector2(m_gSWidth / 4, 1);
                m_Canvas->drawLine(From.X, From.Y, To.X, To.Y, lineSize, 0xFFFFFFFFFF);
				
			if (EspLine2) {
                Vector2 To = player.HeadLocation;
                Vector2 From = Vector2(m_gSWidth / 4, 1);
                m_Canvas->drawLine(From.X, From.Y, To.X, To.Y, lineSize, 0xFFFFFF0000);
            
		   if (EspLine4) {
                Vector2 To = player.HeadLocation;
                Vector2 From = Vector2(m_gSWidth / 3, 1);
                m_Canvas->drawLine(From.X, From.Y, To.X, To.Y, lineSize, 0xFFFF000000);
            
	      if (EspLine5) {
                Vector2 To = player.HeadLocation;
                Vector2 From = Vector2(m_gSWidth / 3, 1);
                m_Canvas->drawLine(From.X, From.Y, To.X, To.Y, lineSize, 0xFFFFFF04FFF3);
}
}
}
}
}
}
}
}
}
}
}
}
}
}

bool FirstStart = false;
void (*DoState)(void * _Instance, int param);
void _DoState(void * _Instance, int param) {
    if(Telekill) {
        DoState(_Instance,-1);
        FirstStart = true;
    } else if(!Telekill && FirstStart) {
        DoState(_Instance,1);
        FirstStart = false;
    } else {
        DoState(_Instance, param);
    }
}

void (*DoUpdate)(void* Counter); // COW.FpsCounter
void _DoUpdate(void* Counter) {
    DoUpdate(Counter);
    if (Counter) {
        FramePerS =  *(int*)((uint64_t)Counter + 0x14);
    }
}

void *KLoad(void * arg){
    while(true)
    {
        if(getRealOffset(0) != 0)
        {
            if(active)
            {
                HOOK(0xB89958,_LateUpdate,LateUpdate);//1.56 Altualizado

                pthread_exit(0);
            }
        }
        sleep(1);
    }
    return NULL;
}



void *hack_thread(void *) {
    ProcMap il2cppMap;
    do {
        il2cppMap = KittyMemory::getLibraryMap(libName);
        sleep(1);
    } while (!il2cppMap.isValid());

	
	
	
    // MSHookFunction((void *) getRealOffset(0x121F504),
    //       (void *) _OnInit, (void **) &OnInit);


    return NULL;
}

static JNINativeMethod methods[] = {{"onDraw1",  "(Landroid/graphics/Canvas;IIF)V", (void *)native_onDraw},};

JNIEXPORT jint JNICALL

JNI_OnLoad(JavaVM *vm, void * /*reserved*/) {
    JNIEnv *env;
    vm->GetEnv((void **)&env, JNI_VERSION_1_6);
    jclass clazz = env->FindClass("uk/lgl/modmenu/FloatingMod");
    env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0]));

    if(!launched) {
        launched = true;
        pthread_t ptid;
        pthread_create(&ptid, NULL, hack_thread, NULL);

        pthread_t ptid2;
        pthread_create(&ptid2, NULL, KLoad, NULL);
    }
    return JNI_VERSION_1_6;

}


JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {}


