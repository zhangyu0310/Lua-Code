//
// Created by poppinzhang on 2021/12/16.
//

#include <stdlib.h>
#include <stdio.h>

#include "lauxlib.h"
#include "lualib.h"
#include "ldo.h"

#include <cJSON.h>

static int json_parse(lua_State* L)
{
  char* str = lua_tostring(L, 1);
  cJSON* json = cJSON_Parse(str);
  lua_pushuserdata(L, json);
  return 1;
}

static int json_print(lua_State* L)
{
  void* u = lua_touserdata(L, 1);
  if (u != NULL)
  {
    cJSON* json = (cJSON*)u;
    if (json == NULL) return;
    printf("%s\n", cJSON_Print(json));
  }
  return 0;
}

static int json_get(lua_State* L)
{
  // Get param 1 --- json
  void* u = lua_touserdata(L, 1);
  // Get param 2 --- id
  char* id_str = lua_tostring(L, 2);
  if (u != NULL)
  {
    cJSON* json = (cJSON*)u;
    if (json == NULL) return 0;
    cJSON* find = NULL;
    if (cJSON_IsObject(json))
    {
      if (id_str == NULL) return 0;
      find = cJSON_GetObjectItem(json, id_str);
    }
    else if (cJSON_IsArray(json))
    {
      find = cJSON_GetArrayItem(json, atoi(id_str));
    }
    if (find == NULL) return 0;
    switch (find->type & 0xFF)
    {
    case cJSON_NULL:
    case cJSON_False:
      lua_pushnil(L);
      break;
    case cJSON_True:
      lua_pushnumber(L, 1);
      break;
    case cJSON_Number:
      lua_pushnumber(L, cJSON_GetNumberValue(find));
      break;
    case cJSON_String:
      lua_pushstring(L, cJSON_GetStringValue(find));
      break;
    case cJSON_Array:
    case cJSON_Object:
    case cJSON_Raw:
      lua_pushuserdata(L, find);
      break;
    case cJSON_Invalid:
    default:
      return 0;
    }
  }
  return 1;
}

static struct luaL_reg jsonlib[] = {
{"json_parse", json_parse},
{"json_print", json_print},
{"json_get",   json_get},
};

LUALIB_API void lua_jsonlibopen(lua_State* L)
{
  luaL_openlib(L, jsonlib, (sizeof(jsonlib)/sizeof(jsonlib[0])));
}