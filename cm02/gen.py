username = input('username:').encode()
username_len = len(username)

var_4h = 8
var_8h = bytearray(8)

for i in range(8):
    var_8h[i] = 0x52 + i

# 这里的未知函数通过调试器可以看出，把入参复制到了 var_8h 里
var_8h[:username_len] = username

for i in range(8):
    var_8h[i] ^= 0x25

# 最后的那个循环中，函数判断为 sprintf 或其他啥，格式化明确是2位小写16进制数
# 前面的计算看作是算偏移，一个
print(var_8h.hex())