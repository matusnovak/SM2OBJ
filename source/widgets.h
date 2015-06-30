/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SM2OBJ_WIDGETS
#define SM2OBJ_WIDGETS

#include <tchar.h>
#include <windows.h>
#include <string>

namespace sm2obj {
    HWND createButton(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createCheckbox(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createRadio(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createTextInput(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createCombo(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createList(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createProgressbar(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createLabel(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);
    HWND createGroup(HWND Handle, const std::string& Label, int PosX, int PosY, int Width, int Height, int ID);

    bool getCheckboxValue(HWND& Checkbox);
    bool getRadioValue(HWND& Radio);
    std::string getTextInputValue(HWND& TextInput);
    int getComboValue(HWND& Combo);
    int getListValue(HWND& List);

    void setCheckboxValue(HWND& Checkbox, bool Value);
    void setRadioValue(HWND& Radio, bool Value);
    void setTextInputValue(HWND& TextInput, const std::string& Value);
    void setComboValue(HWND& Combo, int Value);
    void addComboValue(HWND& Combo, const std::string& Value);
    void setListValue(HWND& List, int Value);
    void addListValue(HWND& List, const std::string& Value);
    void setProgressbarValue(HWND& Progressbar, int Value);
    void setLabelValue(HWND& Label, const std::string& Value);

    void setWidgetFont(HWND& Widget, HFONT& Font);

    HFONT createFont(const std::string& Name, int Size, int Weight);

    void showModalInfo(HWND Handle, const std::string& Title, const std::string& Message);
    void showModalError(HWND Handle, const std::string& Title, const std::string& Message);
    void showModalWarning(HWND Handle, const std::string& Title, const std::string& Message);
};

#endif
