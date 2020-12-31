'''
Bank Alogorithm

Desc:
    Every Process should declare their max need of every kinds of resources 
    at the very first. Banker will check their requests according to it.

Algorithm:
    0. Assume Banker function has the following format to init:
        Bank(Max, Allocation)
       And has the following format for request
        Bank.check(process, request)


    1. Given Max and Allocation Matrix, calculate Need Matrix by:
         Need = Max - Allocation

    2. if Pi's Request[j] <= Need[i, j], continue to the step 3
        else report Debt Error

    3. if Pi's Request[j] <= Available[j], go to step 4
        else Pi should wait

    4. Pre-Calculate Available, Allocation and Need, call secure_check()
        if it's secure, then alloc resources in reality
        else drop the result of calculation, Pi should wait


Secure Check Algorithm

Desc:
    Check if we could find a proper sequence to exec process

Alogrithm:
    0. init the Secure Sequence []
       Work = Available

    1. Find A row from Need, which should satisfy 
        - Pi is not in the Secure Sequence
        - this row is smaller than Work

       if no process satisfy this, return Danger

    2. Work = Work + Allocation[i]
       (option) set Need[i] = [0..0]

    3. Put Pi into Secure Sequence

    4. if all Pi is in the Secure Sequence, it's safe
       else back to 1
'''

import numpy as np
import copy as cp

REPORT_OUTOFMAX = -1
REPORT_NOENOUGH = -2
REPORT_UNSECURE = -3
REPORT_OK = 0

class Process():
    def __init__(self, name, max_resrc):
        self.name = name
        self.max = max_resrc
        self.current = [0] * len(max_resrc)

    def request(self, request, bank):

        report = bank.recv_request(self, request)
        if report is REPORT_OK:
            print("Get Resource")
            return 0

        print("report {}".format(report))
        print("Not Success")
        return -1

    def get_name(self):
        return self.name

    def get_max(self):
        return self.max


class Banker():
    def __init__(self, available):
        self.available = available
        self.maxavailable = available
        self.max = []
        self.allocation = []
        self.need = []
        self.proc_table = {}
        self.proc_cnt = 0

    def _list_small_than(self, a, b):
        for i in range(len(a)):
            if a[i] > b[i]:
                return False
        
        return True
    def assign(self, proc):
        if self._list_small_than(proc.get_max(), self.maxavailable) is False:
            print("Cannot affoard")
            return -1

        self.proc_table[proc.get_name()] = self.proc_cnt
        self.proc_cnt += 1

        m = self.max
        a = self.allocation
        n = self.need

        # decalre process max resrc
        m.append(proc.get_max())

        # init allocation of this process
        a.append([0] * len(self.available))

        # init need as max
        n.append(proc.get_max())


    def _list_calc(self, a, symbol, b):
        result = []
        if symbol == '-':
            for i in range(len(a)):
               result.append(a[i] - b[i]) 

        elif symbol == '+':
            for i in range(len(a)):
                result.append(a[i] + b[i])

        return result


    def _virtual_allocation(self, pi, req):
        available = cp.deepcopy(self.available)
        need = cp.deepcopy(self.need)
        alloc = cp.deepcopy(self.allocation)

        available = self._list_calc(available, '-', req)
        for j in range(len(req)):
            alloc[pi][j] = alloc[pi][j] + req[j]
            need[pi][j] = need[pi][j] - req[j]

        return available, need, alloc


    def _check_sec(self, va, valloc, vneed):
        sec_seq = []
        
        work = va
        len_sec_seq = 0
        max_pi = len(vneed)

        while True:
            if len_sec_seq == max_pi:
                break

            for i in range(max_pi):
                if i in sec_seq:
                    continue
                if self._list_small_than(vneed[i], work):
                    work = self._list_calc(work, '+', valloc[i])
                    sec_seq.append(i)

            if len_sec_seq == len(sec_seq):
                return False
            else:
                len_sec_seq = len(sec_seq)

        return True


    def recv_request(self, proc, req):
        pi = self.proc_table[proc.get_name()]
        available = self.available
        need = self.need

        if self._list_small_than(req, need[pi]) is False:
            return REPORT_OUTOFMAX

        if self._list_small_than(req, available) is False:
            return REPORT_NOENOUGH

        va, vneed, valloc = self._virtual_allocation(pi, req)
        
        if self._check_sec(va, valloc, vneed):
            self.available = va
            self.allocation = valloc
            self.need = vneed
            return REPORT_OK

        # p should wait
        return REPORT_UNSECURE

    def get_current_resrc(self):
        print(self.available)

    def get_current_assign(self):
        print(self.proc_table)
        print("============")
        for i in self.max:
            print(i)
        print("============")






if __name__ == '__main__':
    banker = Banker([10, 5, 7])
    p1 = Process("p1", [7, 5, 3])
    p2 = Process("p2", [3, 2, 2])
    p3 = Process("p3", [9, 0, 2])
    p4 = Process("p4", [2,2,2])
    p5 = Process("p5", [4,3,3])

    banker.assign(p1)
    banker.assign(p2)
    banker.assign(p3)
    banker.assign(p4)
    banker.assign(p5)

    p1.request([0,1,0], banker)
    p2.request([2,0,0], banker)
    p3.request([3,0,2], banker)
    p4.request([2,1,1], banker)
    p5.request([0,0,2], banker)
    banker.get_current_assign()
    banker.get_current_resrc()






