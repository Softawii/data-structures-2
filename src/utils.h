//
// Created by yancf on 02/07/2022.
//

#ifndef REPLACEMENTSELECTION_UTILS_H
#define REPLACEMENTSELECTION_UTILS_H

#include <stdbool.h>
#include <string.h>

bool starts_with(const char *pre, const char *str)
{
    size_t  lenpre = strlen(pre),
            lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}


#endif //REPLACEMENTSELECTION_UTILS_H
