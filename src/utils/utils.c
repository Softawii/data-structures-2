//
// Created by yancf on 05/07/2022.
//

#include <stdbool.h>
#include "../../include/utils/utils.h"

bool starts_with(const char *pre, const char *str)
{
    size_t  lenpre = strlen(pre),
            lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}
