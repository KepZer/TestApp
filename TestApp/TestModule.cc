#include <napi.h>
#pragma comment(lib, "netapi32.lib")

#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include "wstring.h"


Napi::Boolean ContainsUser(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::wstring needUser;
    std::wstring user;
    needUser = info[0].As<WString>().WValue();

    DWORD dwlevel = 0;
    DWORD dwfilter = 0;
    USER_INFO_0* theEntries = new USER_INFO_0[20];
    DWORD dwprefmaxlen = 512;
    DWORD dwentriesread;
    DWORD dwtotalentries;
    NET_API_STATUS result;
    result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&theEntries, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);

    for (int i = 0; i < dwentriesread; i++)
    {
        user = theEntries[i].usri0_name;
        if (user == needUser) {
            return Napi::Boolean::New(env, true);
        }
    }

    return Napi::Boolean::New(env,false);
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "ContainsUser"), Napi::Function::New(env, ContainsUser));
    return exports;
};

NODE_API_MODULE(TestModule, init);