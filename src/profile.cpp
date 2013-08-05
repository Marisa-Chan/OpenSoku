#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "profile.h"
#include "input.h"

kCode dx2sfml_lookup[256] =
{
    kC_Escape, //0
    kC_Escape, //1
    kC_Num1,
    kC_Num2,
    kC_Num3,
    kC_Num4,
    kC_Num5,
    kC_Num6,
    kC_Num7,
    kC_Num8,
    kC_Num9,   //10
    kC_Num0,
    kC_Dash,
    kC_Equal,
    kC_Back,
    kC_Tab,
    kC_Q,
    kC_W,
    kC_E,
    kC_R,
    kC_T,      //20
    kC_Y,
    kC_U,
    kC_I,
    kC_O,
    kC_P,
    kC_LBracket,
    kC_RBracket,
    kC_Return,
    kC_LControl,
    kC_A,      //30
    kC_S,
    kC_D,
    kC_F,
    kC_G,
    kC_H,
    kC_J,
    kC_K,
    kC_L,
    kC_SemiColon,
    kC_Quote,  //40
    kC_Tilde,
    kC_LShift,
    kC_BackSlash,
    kC_Z,
    kC_X,
    kC_C,
    kC_V,
    kC_B,
    kC_N,
    kC_M,      //50
    kC_Comma,
    kC_Period,
    kC_Slash,
    kC_RShift,
    kC_Multiply,
    kC_LAlt,
    kC_Space,
    kC_Escape, // CAPITAL
    kC_F1,
    kC_F2,     //60
    kC_F3,
    kC_F4,
    kC_F5,
    kC_F6,
    kC_F7,
    kC_F8,
    kC_F9,
    kC_F10,
    kC_Escape, //NUMLOCK
    kC_Escape, //SCROLL //70
    kC_Numpad7,
    kC_Numpad8,
    kC_Numpad9,
    kC_Subtract,
    kC_Numpad4,
    kC_Numpad5,
    kC_Numpad6,
    kC_Add,
    kC_Numpad1,
    kC_Numpad2, //80
    kC_Numpad3,
    kC_Numpad0,
    kC_Escape, //DECIMAL
    kC_Escape, kC_Escape, kC_Escape, //0x54-0x56
    kC_F11,
    kC_F12,
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x59-0x5C
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x5D-0x60
    kC_Escape, kC_Escape, kC_Escape, //0x61-0x63
    kC_F13,
    kC_F14,
    kC_F15,
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x67-0x6A
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x6B-0x6E
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x6F-0x72
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x73-0x76
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x77-0x7A
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x7B-0x7E
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x7F-0x82
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x83-0x86
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x87-0x8A
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x8B-0x8E
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x8F-0x92
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x93-0x96
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x97-0x9A
    kC_Escape, kC_Escape, //0x9B-0x9C
    kC_RControl,
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0x9E-0xA1
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xA2-0xA5
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xA6-0xA9
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xAA-0xAD
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xAE-0xB1
    kC_Escape, kC_Escape, kC_Escape, //0xB2-0xB4
    kC_Divide,
    kC_Escape, kC_Escape, //0xB6-0xB7
    kC_RAlt,
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xB9-0xBC
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xBD-0xC0
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xC1-0xC4
    kC_Escape, kC_Escape, //0xC5-0xC6
    kC_Home,
    kC_Up,
    kC_PageUp,
    kC_Escape,
    kC_Left,
    kC_Escape,
    kC_Right,
    kC_Escape,
    kC_End,
    kC_Down,
    kC_PageDown,
    kC_Insert,
    kC_Delete,
    kC_Escape, kC_Escape, kC_Escape, kC_Escape, //0xD4-0xD7
    kC_Escape, kC_Escape, kC_Escape, //0xD8-0xDA
    kC_LSystem,
    kC_RSystem,
    kC_Menu,
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xDE-0xE1
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xE2-0xE5
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xE6-0xE9
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xEA-0xED
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xEE-0xF1
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xF2-0xF5
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xF6-0xF9
    kC_Escape, kC_Escape, kC_Escape, kC_Escape,//0xFA-0xFD
    kC_Escape, kC_Escape //0xFE-0xFF
};

#define DX2SFML_CONV(x) x = dx2sfml_lookup[(x) & 0xFF]


void dx2sfml(s_keybind *keys)
{
    DX2SFML_CONV(keys->UP);
    DX2SFML_CONV(keys->DOWN);
    DX2SFML_CONV(keys->LEFT);
    DX2SFML_CONV(keys->RIGHT);
    DX2SFML_CONV(keys->A);
    DX2SFML_CONV(keys->B);
    DX2SFML_CONV(keys->C);
    DX2SFML_CONV(keys->D);
    DX2SFML_CONV(keys->AB);
    DX2SFML_CONV(keys->BC);
    DX2SFML_CONV(keys->START);
}

s_profile *profile_load_from_file(const char *file)
{
    filehandle *f = arc_get_file(file);

    if (!f)
        return NULL;

    s_profile *tmp = new s_profile();

    f->read(52, &tmp->kbd);
    dx2sfml(&tmp->kbd);

    f->read(52, &tmp->joy);
    f->read(1,  &tmp->unk1);
    f->read(1,  &tmp->unk2);
    for (int32_t chr=0; chr < 20; chr++)
        for (int32_t dk=0; dk < 4; dk++)
        {
            uint8_t crd_num = 20;
            f->read(1, &crd_num);
            for (int32_t crd=0; crd < crd_num; crd++)
                f->read(2, &tmp->decks[chr][dk][crd]);
        }


    return tmp;
}
