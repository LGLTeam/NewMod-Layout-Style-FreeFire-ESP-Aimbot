#ifndef ANDROID_MOD_MENU_GLOBAL_H
#define ANDROID_MOD_MENU_GLOBAL_H

struct {

    uintptr_t MainCameraTransform = 0x50;
    uintptr_t HeadTF = 0x1B0; //0xAE5868 //esp
    uintptr_t HipTF = 0x1B4;
    uintptr_t IsClientBot = 0xC4;
    uintptr_t Component_GetTransform = 0x27A593C;
    uintptr_t GetCameraTrackableEntityTransfrom = 0xB473C0;
    uintptr_t Transform_INTERNAL_GetPosition = 0x2ABF900;
    uintptr_t Transform_INTERNAL_SetPosition = 0x2ABF9C0;
    uintptr_t GetForward = 0x2ABFFE4;
    uintptr_t get_isAlive = 0xB474D4;//0xA5C7D4
    uintptr_t GetPhysXPose = 0xB6C420;
    uintptr_t IsFiring = 0xB7F1AC;
    uintptr_t IsCrouching = 0xB6C454;
    uintptr_t get_IsSighting = 0xBB568C;//ths
    uintptr_t get_isLocalPlayer = 0xB62540;
    uintptr_t get_isLocalTeam = 0xB6AA08;
    uintptr_t get_isVisible = 0xB64180;
    uintptr_t set_aim = 0xB624F8;
    uintptr_t Camera_main_fov = 0x27A0E68;
    uintptr_t get_imo = 0xB4DB74;
    uintptr_t set_esp = 0xC84B4C;
    uintptr_t GetAttackableCenterWS = 0xB610BC;
    uintptr_t GetCharacterControllerTopPosition = 0xBA0084;//
    uintptr_t get_NickName = 0xB45728;
 //   uintptr_t WorldToScreenPoint = 0x2464B34;//esp
    uintptr_t get_height = 0x2AB461C;
    uintptr_t get_width = 0x2AB458C;
//    uintptr_t get_deltaTime = 0x2A4542C;
    uintptr_t CurrentUIScene = 0x207E01C;
    uintptr_t Curent_Match = 0x2092268;
    uintptr_t Current_Local_Player = 0x20925BC;
    uintptr_t GetLocalPlayerOrObServer = 0x2093860;//ths
    uintptr_t CurrentLocalSpectator = 0x2092A3C;
    uintptr_t Player_Index = 0x1A89FE0;
//    uintptr_t AddTeammateHud = 0x1195824;
    uintptr_t get_tele = 0xBF6AE4;
//    uintptr_t spof_uid = 0xB6F484;
// uintptr_t Yn = 0x8199A
//    uintptr_t spof_nick = 0xB6F57C;
   // uintptr_t ShowDynamicPopupMessage = 0x1183F08;
 //   uintptr_t ShowPopupMessage = 0x1184090;
    uintptr_t GetLocalPlayer = 0x1FDF980;
    uintptr_t GetCharacterHeight = 0xB735B0;
    uintptr_t set_height = 0x27A42E0;
    uintptr_t get_CharacterController = 0xB61928;
    uintptr_t IsUserControlChanged = 0xB6C338;
    uintptr_t set_invitee_nickname = 0x2C55DC4;
    uintptr_t Raycast = 0x2A57184;
    uintptr_t get_MyFollowCamera = 0xB61E7C;
    uintptr_t IsSameTeam = 0x1848054;
    uintptr_t AttackableEntity_GetIsDead = 0x2316ECC;
    uintptr_t AttackableEntity_IsVisible = 0x232AE04;
    uintptr_t Camera_WorldToScreenPoint =  0x27A27D8;
    uintptr_t Camera_main = 0x27A2DC8;


} Global;

#endif
