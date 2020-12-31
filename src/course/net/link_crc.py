'''
CRC of Link Layer

Desc:
    given a m bit packet data
    generate a r bit sequence called (FCS)
        The processed frame will be : m+r bits now

    Sender and Recver should set a common polymonium G(x) (presented by Bin-format)
        which satisfied the following requirements:
            1. 1st and last bit should be 1
            2. (m + r) bits frame can be divided by G(x) without remaining

Algorithm:
    0. suppose the level of G(x) is (r), we have a (m) bits frame
    
    1. add (r) zeros after LSB(the end), we get (m + r) bits data, called T

    2. divied T by G(x) in binary format(should mod 2),
        we will get r bits remaining called R

    3. Concat T and R, its our frame with CRC code

    4. Recver use the common G(x) to divide the (m + r) bits -- T concat R
        if remains 0 -- correct
        else -- error

Interface Design:
    GDict -- Dict to store G(x)
    
    string genFrameWithCRC(string frame_bits, string gx)

    string mod2divide(string data, string gx)

    string fixZero(string frame_bits, string gx)

    Bool checkFrameByCRC(string data, string gx)

'''

GDict = {
        'su': "1101"
        }

def genFrameWithCRC(frame_bits, gx):
    fixed_bits = fixZero(frame_bits, gx)
    crc = mod2divide(fixed_bits, gx)
    print("Frame Bits : {}\nCrc Code : {}".format(frame_bits, crc))
    return frame_bits + crc


# ======= For Mod ==========
def mod2divide(data, gx):
    data = clearZero(data)
    gx = clearZero(gx)

    r = len(gx) - 1
    start = data[:r]
    tmp = start

    for i in range(r, len(data)):
        tmp = tmp + data[i]
        if tmp[0] == '0':
            plus = '0' * (r + 1)
        else:
            plus = gx

        tmp = binXor(tmp, plus)[1:]

    return tmp


def binXor(str1, str2):
    result_len = max(len(str1), len(str2))
    result = [0] * result_len

    str1 = str1.zfill(result_len)
    str2 = str2.zfill(result_len)

    for i in range(result_len):
        result[i] = str(int(str1[i]) ^ int(str2[i]))

    return ''.join(result)

def clearZero(binnum):
    num = binnum.lstrip('0')
    return num

# Add Zeros after the frame_bits according to gx
def fixZero(frame_bits, gx):
    if(gx[0] == '1' and gx[-1] == '1'):
        r = len(gx) - 1
    else:
        print("Bad G(x) Format")
        exit(-1)

    result  = frame_bits + '0' * r
    return result

# ======= Check ==========
def checkFrameByCRC(data, gx):
    remain = mod2divide(data, gx)
    if int(remain) == 0:
        print("CRC Correct!")
        return True
    else:
        print("CRC Error!")
        return False


def main():
    data = '101001'
    gx = '1101'
    sent_data = genFrameWithCRC(data, gx)
    checkFrameByCRC(sent_data, gx)


if __name__ == '__main__':
    main()













