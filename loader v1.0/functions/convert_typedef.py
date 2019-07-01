# coding=utf-8
# 需要手工修复一些数据
f = open("functions.txt", "r")

replaces_keyword = {
	"WINBASEAPI" : "",
	"WINADVAPI" : "",
	"FAR" : "",
	"__out": "",
	"_opt" : "",
	"\r": " ",
	"\t": " ",
	"\n": " "
}

target = f.read()

f.close()

for k in replaces_keyword:
	target = target.replace(k, replaces_keyword[k])

ret_type = ""
call_type = ""
func_name = ""
params = ""

current = 0

prev = ""

for c in target:
	if c == " ":
		if prev in ["", " "]:
			continue
		elif current != 3:
			current = current + 1
		elif current == 3:
			params = params + c
	elif c == '(' and current != 3:
		params = '('
		current = current + 1
	elif c == ';':
		print "typedef %s (%s *_%s)%s;" % (ret_type, call_type, func_name, params)
		ret_type = ""
		call_type = ""
		func_name = ""
		params = ""

		current = 0

		prev = ""
		continue
	else:
		if current == 0:
			ret_type = ret_type + c
		elif current == 1:
			call_type = call_type + c
		elif current == 2:
			func_name = func_name + c
		elif current == 3:
			params = params + c
	prev = c
