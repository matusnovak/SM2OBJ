/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#include "widgets.h"
#include "CommCtrl.h"

HWND sm2obj::createButton(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(0, "Button", Label.c_str(), WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createCheckbox(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(0, "Button", Label.c_str(), BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createRadio(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(0, "Button", Label.c_str(), WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_RADIOBUTTON, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createTextInput(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", Label.c_str(), WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createCombo(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(WS_EX_STATICEDGE, "COMBOBOX", Label.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createList(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(0, "LISTBOX", Label.c_str(), WS_BORDER | WS_CHILD | WS_VISIBLE, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createProgressbar(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(0, PROGRESS_CLASS, NULL, WS_CHILD | WS_VISIBLE, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createLabel(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(WS_EX_TRANSPARENT, "STATIC", Label.c_str(), WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU , PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

HWND sm2obj::createGroup(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID){
    return CreateWindowEx(0, "BUTTON", Label.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_GROUPBOX, PosX, PosY, Width, Height, Handle, (HMENU)ID, NULL, NULL);
}

bool sm2obj::getCheckboxValue(HWND& Checkbox){
    return SendMessage(Checkbox, BM_GETCHECK, 0, 0);
}

bool sm2obj::getRadioValue(HWND& Radio){
    return SendMessage(Radio, BM_GETCHECK, 0, 0);
}

std::string sm2obj::getTextInputValue(HWND& TextInput){
    int len = SendMessage(TextInput, WM_GETTEXTLENGTH, 0, 0);
    std::string buffer;
    buffer.resize(len);
    SendMessage(TextInput, WM_GETTEXT, (WPARAM)len+1, (LPARAM)&buffer[0]);
    return buffer;
}

int sm2obj::getComboValue(HWND& Combo){
    return SendMessage(Combo, CB_GETCURSEL , 0, 0);
}

int sm2obj::getListValue(HWND& List){
    return SendMessage(List, LB_GETCURSEL, 0, 0);
}

void sm2obj::setCheckboxValue(HWND& Checkbox, bool Value){
    if(Value)SendMessage(Checkbox, BM_SETCHECK, BST_CHECKED, 0);
    else     SendMessage(Checkbox, BM_SETCHECK, BST_UNCHECKED, 0);
}

void sm2obj::setRadioValue(HWND& Radio, bool Value){
    if(Value)SendMessage(Radio, BM_SETCHECK, BST_CHECKED, 0);
    else     SendMessage(Radio, BM_SETCHECK, BST_UNCHECKED, 0);
}

void sm2obj::setTextInputValue(HWND& TextInput, const std::string& Value){
    SendMessage(TextInput, WM_SETTEXT, 0, (LPARAM)Value.c_str());
}

void sm2obj::setComboValue(HWND& Combo, int Value){
    SendMessage(Combo, CB_SETCURSEL, Value, 0);
}

void sm2obj::addComboValue(HWND& Combo, const std::string& Value){
    SendMessage(Combo, CB_ADDSTRING, 0, (LPARAM)Value.c_str());
}

void sm2obj::setListValue(HWND& List, int Value){
    SendMessage(List, LB_SETCURSEL, Value, 0);
}

void sm2obj::addListValue(HWND& List, const std::string& Value){
    SendMessage(List, LB_ADDSTRING, 0, (LPARAM)Value.c_str());
}

void sm2obj::setProgressbarValue(HWND& Progressbar, int Value){
    SendMessage(Progressbar, PBM_SETPOS, Value, 0);
}

void sm2obj::setLabelValue(HWND& Label, const std::string& Value){
    SendMessage(Label, WM_SETTEXT, 0, (LPARAM)Value.c_str());
}

void sm2obj::setWidgetFont(HWND& Widget, HFONT& Font){
    SendMessage(Widget, WM_SETFONT, (WPARAM)Font, TRUE);
}

HFONT sm2obj::createFont(const std::string& Name, int Size, int Weight){
    return CreateFont(Size,0,0,0,Weight,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEVICE_PRECIS,CLIP_MASK,ANTIALIASED_QUALITY, DEFAULT_PITCH,Name.c_str());
}

void sm2obj::showModalInfo(HWND Handle, const std::string& Title, const std::string& Message){
    MessageBox(Handle, Message.c_str(), Title.c_str(), MB_OK | MB_ICONINFORMATION);
}

void sm2obj::showModalError(HWND Handle, const std::string& Title, const std::string& Message){
    MessageBox(Handle, Message.c_str(), Title.c_str(), MB_OK | MB_ICONERROR);
}

void sm2obj::showModalWarning(HWND Handle, const std::string& Title, const std::string& Message){
    MessageBox(Handle, Message.c_str(), Title.c_str(), MB_OK | MB_ICONWARNING);
}
