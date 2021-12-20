//
// Created by poppinzhang on 2021/12/16.
//

#include <stdlib.h>
#include <stdio.h>

#include "lauxlib.h"
#include "lualib.h"
#include "ldo.h"

#include <cJSON.h>

static void json_parse (void)
{
  char* str = luaL_check_string(1);
  cJSON* json = cJSON_Parse(str);
  lua_pushuserdata(json);
}

static void json_print (void)
{
  lua_Object obj = lua_getparam(1);
  void* u = lua_getuserdata(obj);
  if (u != NULL)
  {
    cJSON* json = (cJSON*)u;
    if (json == NULL) return;
    printf("%s\n", cJSON_Print(json));
  }
}

static void json_get(void)
{
  // Get param 1 --- json
  lua_Object j = lua_getparam(1);
  void* u = lua_getuserdata(j);
  // Get param 2 --- id
  lua_Object id = lua_getparam(2);
  double id_num = -1;
  char* id_str = NULL;
  if (lua_isnumber(id))
  {
    id_num = lua_getnumber(id);
  }
  else if (lua_isstring(id))
  {
    id_str = lua_getstring(id);
  }

  if (u != NULL)
  {
    cJSON* json = (cJSON*)u;
    if (json == NULL) return;
    cJSON* find = NULL;
    if (cJSON_IsObject(json))
    {
      if (id_str == NULL) return;
      find = cJSON_GetObjectItem(json, id_str);
    }
    else if (cJSON_IsArray(json))
    {
      find = cJSON_GetArrayItem(json, id_num);
    }
    if (find == NULL) return;
    switch (find->type & 0xFF)
    {
    case cJSON_NULL:
    case cJSON_False:
      lua_pushnil();
      break;
    case cJSON_True:
      lua_pushnumber(1);
      break;
    case cJSON_Number:
      lua_pushnumber(cJSON_GetNumberValue(find));
      break;
    case cJSON_String:
      lua_pushstring(cJSON_GetStringValue(find));
      break;
    case cJSON_Array:
    case cJSON_Object:
    case cJSON_Raw:
      lua_pushuserdata(find);
      break;
    case cJSON_Invalid:
    default:
      return;
    }
  }
}

static struct luaL_reg jsonlib[] = {
{"json_parse", json_parse},
{"json_print", json_print},
{"json_get",   json_get},
};

void lua_jsonlibopen (void)
{
  luaL_openlib(jsonlib, (sizeof(jsonlib)/sizeof(jsonlib[0])));
}