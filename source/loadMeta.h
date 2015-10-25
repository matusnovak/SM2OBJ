/*
*   This file is part of SM2OBJ project.
*   Copyright (C) 2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef SMD2OBJ_LOAD_META
#define SMD2OBJ_LOAD_META

#include <ffw.h>
#include "config.h"

namespace sm2obj{
    bool loadMeta(entityInfoStruct* Output, const std::string& Path, const std::string& Name);
};
#endif
