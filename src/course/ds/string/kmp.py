'''
Implement KMP
'''

def get_next(template, next_list):
    i,j = 1, 0
    temp_len = len(template)

    template = list(template)
    template.insert(0, 0)
    next_list[1] = 0

    while(i < temp_len):
        if j == 0 or template[i] == template[j] :
            i += 1
            j += 1
            next_list[i] = j 
        else:
            j = next_list[j]

def gen_next_table(template):

    next_list_len = len(template)
    next_list = [0] * (next_list_len + 1)

    get_next(template, next_list)
    return next_list

def kmp(src, temp):
    next_list = gen_next_table(temp)
    temp_len = len(temp)
    
    temp = list(temp)
    temp.insert(0,'x')

    i,j = 1,1
    while(i <= len(src) and j <= temp_len):
        if j == 0 or src[i] == temp[j]:
            i += 1
            j += 1
        else:
            j = next_list[j]

    if j > temp_len:
        return i - temp_len
    else:
        return 0


if __name__ == '__main__':
    tb = gen_next_table(list("abaabcaba"))
    print(tb)

    temp = "abcac"
    src = "ababcabcacbab"
    print(kmp(src, temp))
