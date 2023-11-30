#ifndef _BLACKWHITELIST_H_
#define _BLACKWHITELIST_H_

#include <stdio.h>
#include <string.h>
//#include "ff.h"
#include "hw_config.h"
#include "sd_card.h"

bool filterContent(const char *inputPath, const char *whitelistPath, const char *blacklistPath);

#endif
