a = json_parse("null")
json_print(a)

b = json_parse("{\"name\":\"Awesome 4K\",\"resolutions\":[{\"width\":1280,\"height\":720},{\"width\":1920,\"height\":1080},{\"width\":3840,\"height\":2160}]}")
json_print(b)
n = json_get(b, "name")
print(n)

w = json_get(json_get(json_get(b, "resolutions"), 1), "width")
print(w)

mytable = {}
mytable["table"]={}
mytable["test"]="test"
mytable["num"]=1
mytable["table"]["xx"]="Lua"
mytable["table"]["num"]=2
printtable(mytable)