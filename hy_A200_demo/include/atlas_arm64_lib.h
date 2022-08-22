#pragma once
//#if defined(_MSC_VER)
//#define ATLASDLL_API __declspec(dllexport)
//#else
//#define ATLASDLL_API __attribute__((visibility("default")))
//#endif
#define ATLASDLL_API
ATLASDLL_API int Init_Atlas_Lib();
ATLASDLL_API void Uninit_Atlas_Lib();