'''
Hamming Code Implement

Desc :
    0. The Hamming Code is coded from the LSB -> MSB
                    MSB ----------------------------- LSB
        Location:       n, n - 1, ........... 3, 2, 1

    1. Find the proper num of checking bits
        Assume we have (n) bits data, and (x) bits check bits
        They satisfied the following unequation
            2^x - 1 >= n + x

        the x is the smallest one

    2. Find the proper location of checking bits
        Assume the num of checking bits is x
        then the (i)th checking bits would be put up at (2^(i - 1)) bit

            checking bits : [1st, 2nd, 3rd, 4th, 5th ... nth]
            place : [1,2,4,8,16,32 ... 2^(n - 1)]

    3. Group those checking bits
        An important principle : one data bit need more checking bits to ensure
            its correct

        so, we use the following method to determine that A checking checks
            which bits.

            1st checking bit -- 0001, checks the bits whose location xor 0001 is 1
                                example : 011(3), 101(5), 111(7) (Exclude itself)
            2nd -- 0010, checks the loc 'and' 0010 is 0010
            3rd -- 0100, checks the loc 'and' 0100 is 0100
            ...
            nth -- 1...00, checks the loc 'and' 2^n is 1...0

    4. Set the value of checking bits(0 or 1)
        In the step3, we group them by our checking bits
            1st checking bit group -- {Loc3, Loc5, Loc7 ... }
            2nd -- {Loc3, Loc6, Loc7 ...}
            3rd -- {Loc5, Loc6, Loc7 ...}
            ...

        now, in a group, we add(xor) them all to get the specified checking bit
            1st checking = Loc3 ^ Loc5 ^ Loc7 ^ ...
            2nd = Loc3 ^ Loc6 ^ Loc7 ^ ...
            ...

Algorithm:
    Generate described in Desc Part, skip
    check : 
        recver recvs A data with hamming codes, whose length is (y)

        we know y < 2^m - 1, so we can find the smallest (m)
        so the (y)-bits data contains (m) bits checking bits

        needs group them and xor them all in the same group
            G1 = Loc3 ^ Loc5 ^ Loc7 ^ ... ^ Check1
            G2 = Loc3 ^ Loc6 ^ Loc7 ^ ... ^ Check2
            ...

        Expect all 0, others means error happended, we can construct a new
        consequence to reveal the error bits:
            MSB ---------------------- LSB
        Loc:   Gn, Gn-1, ... , G2, G1
        GnGn-1...G2G1 is the location of the error bit
            example : G1 = 1, G2 = 1, G3 = 0, G4 = 1
                     error in 1011 (11) 
'''

# suppose string only
def genHammingCode(data):
    # special process -- reverse
    data = data[::-1]

    r = findRofData(data)
    m = len(data)
    power_seq = gen2power(r)

    # prepare a list to store result
    result = ['d'] * (m + r)

    # remain space for checking bits
    for i in range(r):
        loc_index = power_seq[i] - 1
        result[loc_index] = 'x'

    # put data bits
    data_index = 0
    for i in range(m + r):
        if result[i] == 'd':
            result[i] = data[data_index]
            data_index += 1
    print("temp result {}".format(result))

    # group data
    groups = groupData(result, r)
    for key in groups:
        groups[key] = xorAll(groups[key])
    print(groups)

    # put checking bits to the proper locs
    for i in range(r):
        value = groups[i]
        loc_index = power_seq[i] - 1
        result[loc_index] = value


    # reverse the whole sequence
    result.reverse()
    return ''.join(result)


def findRofData(data):
    m = len(data)
    for i in range(m):
        if(2**i >= m + i + 1):
            return i
    print("Nothing Satisfied")
    exit(0)


# gen 1,2,4,8...
def gen2power(r):
    result = []
    for i in range(r):
        result.append(2**i)

    return result

def groupData(data, r):
    power_seq = gen2power(r)
    result = {}
    for key in range(r):
        result[key] = []

    # in normal count format(1,2,3,...)
    for i in range(1, len(data) + 1):
        if (data[i - 1] == 'x'):
            continue
        for j in range(r):
            bin_vector = power_seq[j]
            if (i & bin_vector == bin_vector and i != bin_vector):
                print('add {} to group {}'.format(i, j))
                result[j].append(data[i - 1])

    print(result)
    return result


def xorAll(group):
    tmp = int(group[0])
    for i in range(1, len(group)):
        tmp = tmp ^ int(group[i])
    return str(tmp)

def checkHammingCode(data):
    data = data[::-1]

    r = findRofRecv(data)
    m = len(data) - r
    power_seq = gen2power(r)

    # prepare a lis to store result
    result = ['d'] * (r + m)

    # remain space for checking bits
    for i in range(r):
        loc_index = power_seq[i] - 1
        result[loc_index] = 'x'

    # put data bits
    data_index = 0
    for i in range(m + r):
        result[i] = data[i]
    print("temp result {}".format(result))

    

    # group data
    groups = groupData(result, r)

    # add checking bit into counts
    for i in range(r):
        loc_index = power_seq[i] - 1
        groups[i].append(result[loc_index])

    # calc xor 
    for key in groups:
        groups[key] = xorAll(groups[key])
    print(groups)

    # get the result of check
    check_res = []
    for i in range(r):
        check_res.append(groups[i])

    check_res = ''.join(check_res[::-1])

    if check_res == '0' * r:
        print("Hamming Correct !")
    else:
        index = -int(check_res,2)
        result.reverse()
        result[index] = str((~int(result[index])) & 1)
        print("Error Detected in 0b{}, it should be {}"\
                .format(check_res, ''.join(result)))


def findRofRecv(data):
    l = len(data)
    for i in range(l):
        if 2**i - 1 >= l:
            return i
    print("Nothing Satisfied")
    exit(-1)


def main():
    data = '1010'
    code = genHammingCode(data)
    print(code)
    print("======= Test Correct ==========")
    result = checkHammingCode(code)
    print("======= Test Error ============")
    code = '1010110'
    result = checkHammingCode(code)

if __name__ == '__main__':
    main()













