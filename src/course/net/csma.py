'''
CSMA protocol

    1. 1-persistent CSMA
        if it's busy, keep listening on it. Send Frame once the line is spare

    2. non-persistent CSMA
        if it's busy, wait a random time then listen on it, send frame once spare

    3. p-persistent CSMA
        if busy, keep listening until it's free
        if free, (p) possibility to send frame now, and (1-p) to send in the next
            time slot, should also keep listening until it's free
            and then have (p) possibility to send ...

Alg:
    1. gen random '0' '1' to estimate time slots and  conflicts
    2. use different ways to detect conflicts

'''

import numpy as np
import random

# gen (length) sequence of values according to distribution
# input : 
#       distr = [0.1, 0.0, 0.3, 0.6]
#       choice = [1,2,3,4]
#       length = 100
def genRandomSeq(distribution, values, length):
    p = np.array(distribution)
    result = [0] * length

    for i in range(length):
        value = np.random.choice(values, p = p.ravel())
        result[i] = value

    return result

# 10% to have conflicts
# 1 --- conflict 0 ---- free
def genConflictsSlots(slots_num):
    return genRandomSeq([0.9, 0.1], [0, 1], slots_num)

# return True or False, the possibility of persistent is (p)
# 1--yes, 0--no
def should_I_send(p):
    distr = np.array([1 - p, p])
    num = np.random.choice([0, 1], p = distr.ravel())
    
    if num == 1:
        return True
    else:
        return False

# base
class Entity:
    def __init__(self, time_seq, name):
        self.current_time = 0
        self.time_seq = time_seq
        self.name = name

    def __log(self, sth):
        print("{} report {} at time slot {}".format(self.name, sth, self.current_time))

    def check(self):
        state = self.time_seq[self.current_time]
        
        if state == 0:
            self.__log("Bus Free")
            return True
        else:
            self.__log("Bus Busy")
            return False

    def tiktok(self):
        self.current_time += 1

    def send(self):
        self.__log("<<<<<<<<<<Send Frame>>>>>>>>>")

# 1-pers
class OnePersEntity(Entity):
    def check_and_send(self):
        result = Entity.check(self)
        if result is True:
            Entity.send(self)
        Entity.tiktok(self)

# non-pers
class NonPersEntity(Entity):
    def __init__(self, time_seq, name):
        self.current_time = 0
        self.time_seq = time_seq
        self.name = name
        self.wait_time = 0

    def check_and_send(self):
        if self.wait_time != 0:
            Entity.tiktok(self)
            self.wait_time -= 1
            return

        result = Entity.check(self)
        if result == False:
            # busy
            Entity.tiktok(self)
            return

        random_wait = random.randint(0,2)
        if random_wait == 0 :
            Entity.send(self)

        self.wait_time += random_wait
        print("{} should wait {} slots to send".format(self.name, self.wait_time))
        Entity.tiktok(self)

# p-pers
class PPersEntity(Entity):
    def __init__(self, time_seq, name, p):
        self.current_time = 0
        self.time_seq = time_seq
        self.name = name
        self.p = p

    def check_and_send(self):
        result = Entity.check(self)
        if result is True:
            if should_I_send(self.p):
                Entity.send(self)
            else:
                print("p-pers not send now")
        
        Entity.tiktok(self)



if __name__ == '__main__':
    print("==== Test Gen Sequence =====")
    print(genRandomSeq([0.3, 0.7], ['0', '1'], 12))
    print("==== Test Entities =====")
    entity1 = OnePersEntity([0,1,1,1,0], "1-p")
    entity1.check_and_send()

    entity2 = NonPersEntity([0,1,1,1,0], "non-p")
    entity2.check_and_send()

    entity3 = PPersEntity([0,1,1,1,0], "p-pers", 0.1)
    entity3.check_and_send()

    print(">>>>>>>Test All<<<<<<<")
    seq = genConflictsSlots(16)
    entity_1 = OnePersEntity(seq, "1-p")
    entity_2 = NonPersEntity(seq, "non-p")
    entity_3 = PPersEntity(seq, "p-p", 0.1)
    for i in range(len(seq)):
        entity_1.check_and_send()
        entity_2.check_and_send()
        entity_3.check_and_send()

    












