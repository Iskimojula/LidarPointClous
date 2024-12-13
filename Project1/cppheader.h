#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <stack>
#include <stdio.h>
#include <stdint.h>
#include <thread>
#include <filesystem>

#define absoluteunsignedlonglong(a)  ((a > 0)?(a):(-a))
#ifdef _MSC_VER
#ifndef STRTOK
#define STRTOK(aptr,delm,savP) strtok_s(aptr,delm,&savP)
#endif
#define TDEBUG(...)            qDebug(__VA_ARGS__)

#else
#ifndef STRTOK
#define STRTOK(aptr,delm,savP) strtok_r(aptr,delm,&savP);
#endif
#define TDEBUG(...)            LOGD(__VA_ARGS__)
#endif