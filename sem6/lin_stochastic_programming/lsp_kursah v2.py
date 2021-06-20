import numpy as np
from scipy import stats
import itertools
import random
import time

pa = []

class Flight:

    def __init__(self, start, cont, prob_p=[0.99, 0.95], prob_d=0.99):
        self.start = start
        self.cont = cont
        self.prob_p = prob_p
        self.prob_d = prob_d


    def __str__(self):
        return "flight({}, {}, {}, {})\n".format(self.start, self.cont, self.prob_p, self.prob_d)

    def __repr__(self):
        return "\n[{}, {}, {}, {}]".format(self.start, self.cont, self.prob_p, self.prob_d)



def is_in(m, J, I1, I2, K, Kr, z, l, flights):
    I1 = np.array(list(I1 & J))
    I2 = np.array(list(I2 & J))
    J_ = list(J)
    mi = J_[0]
    if len(J_)<l:
        l=len(J_)
    for i in I1:
        if not((np.sum(m[i-mi,:]*z)) >= (flights[i].prob_p[0])):
            #pa.append(1)
            return False
        if not((np.sum(m[i-mi,:]*z)) >= (flights[i].prob_p[1])):
            #pa.append(2)
            return False
    for i in I2:
        if np.sum(m[i-mi, Kr[str(i)]]) != 0:
            #pa.append(3)
            return False
    for i in J_:
        for j in J_[J_.index(i):]:#range(i, J_)[l-1]+1):
            for k in range(K):
                if (j <= i):
                    tmp = (m[i-mi,k] + m[j-mi,k] - 1)*(flights[i].start + flights[i].cont + (flights[i].prob_d)) - m[j-mi,k]*(flights[j].start+168)
                else:
                    tmp = (m[i-mi,k] + m[j-mi,k] - 1)*(flights[i].start + flights[i].cont + (flights[i].prob_d)) - m[j-mi,k]*flights[j].start
                if tmp>0:
                    #pa.append(4)
                    return False
    return True


def calk_coef(z, p, t, c1, c2, c3, c4, L, K):
    res = np.zeros((L, K))
    for i in range(1000):
        X1 = (np.repeat(np.array(np.int32(stats.norm(450, 100).rvs(size=L))), K, axis=0)).reshape(L,K)
        X2 = (np.repeat(np.array(np.int32(stats.norm(450, 100).rvs(size=L))), K, axis=0)).reshape(L,K)
        Cd = p*(np.minimum(z, X1)+np.minimum(z, X2))
        V = (np.repeat(np.array(np.int32(stats.bernoulli(0.01).rvs(size=K))), L, axis=0)).reshape(L,K)
        Cc = c1 + t*(c2+c3) + V*c4
        res+=Cd-Cc
    return (res/(1000))



def get_U(J, I1, I2, K, Kr, z, l, flights):
    #yul = int(input())
    #print(pa)
    lines = np.eye(K, dtype=int)
    res = {}
    if len(J)<l:
        l=len(J)
    count = 0
    for sempl in itertools.product(lines, repeat=l):
        tmp = np.array(sempl)
        if is_in(tmp, J, I1, I2, K, Kr, z, l, flights):
            count+=1
            res[str(count)] = tmp
    return res


def find_max(U, u, Ci, C0, count, l, K, I1, I2, Kr, z, flights):
    mx = -np.inf
    old_l = l
    tmp = 0
    U_ = U.copy()
    flag = True
    if len(list(u.keys())) != 0: 
           if u[list(u.keys())[0]].shape[0] < l:
               flag = False
               l =  u[list(u.keys())[0]].shape[0] 
    for key in u.keys():
        if count == 0:
            U_[count*l: (count+1)*l,:] = u[key]
            tmp = np.sum(u[key]*Ci[count*l: (count+1)*l,:])
        elif flag:
            U_[count*(l-1): (count+1)*(l-1)+1,:] = u[key]
            tmp = np.sum(u[key]*Ci[count*(l-1): (count+1)*(l-1)+1,:])
        else:
            U_[-l:,:] = u[key]
            tmp = np.sum(u[key]*Ci[-l:,:])
        if mx<tmp and is_in(U_, set(list(range(U.shape[0]))), I1, I2, K, Kr, z, l, flights):
            mx = tmp
            U = U_.copy()
            #print(u[key])
    if mx == -np.inf:
        mx = 0
    return U, mx
        

def main():
    start_time = time.time()
    L = 21#кол-во рейсов
    K = 4#кол-во самолетов  
    l = int(input())
    z = np.array([525, 700, 590, 510], dtype = int)#вместимость самолетов 
    p = np.array([3500, 4000, 4200, 4300, 3500, 4000, 3200, 5000, 4500, 4300, 3500, 3200,
                  3000, 2800, 3500, 4200, 4300, 4500, 4700, 3500, 3000])[:, np.newaxis]#стоимость билета на рейс 
    t = np.array([5, 6, 4, 7, 5, 6, 4, 8, 9, 7, 5, 4, 3, 2, 5, 6, 7, 8, 9, 5, 3])[:, np.newaxis]#время на рейс 
    arrive = [12, 16, 20, 36, 40, 44, 60, 64, 68, 84, 88, 92, 108, 112, 116, 132, 136, 140, 156, 160, 164]
    c1 = np.array([[150000, 200000, 250000,  200000, 250000]]*L)#затраты на обслуживание 
    c2 = np.array([[140900, 151400, 141540, 143000, 123180]]*L)#затраты на расходники 
    c3 = np.array([10000, 11000, 12000, 11000, 12000])#стоимость ремонта за час полета 
    c4 = np.array([7000000, 7000000, 7000000, 7000000, 7000000])#стоимость замены самолета 
    U = np.zeros((L,K))
    I1 = set([0, 2, 5])
    I2 = set([3])
    Kr = {'3':[0,1,2]}
    Ci = np.array([[20898,  20772,  20439,  20421],
                   [23560,  23408,  23150,  23207],
                   [28775,  28916,  28486,  28081],
                   [24578,  24413,  24213,  24362],
                   [20907,  20871,  20560,  20571],
                   [23832,  23645,  23432,  23469],
                   [19707,  19564,  19209,  19105],
                   [29563,  29499,  29351,  29432],
                   [23717,  23316,  23376,  23869],
                   [24953,  24704,  24569,  24749],
                   [20999,  20857,  20523,  20527],
                   [20066,  19964,  19581,  19451],
                   [19847,  19874,  19374,  19018],
                   [19419,  19381,  18870,  18530],
                   [20855,  20707,  20384,  20377],
                   [25526,  25471,  25219,  25142],
                   [25076,  24930,  24735,  24292],
                   [24786,  24561,  24449,  24699],
                   [24586,  24151,  24170,  24663],
                   [20257,  19993,  19725,  19797],
                   [19241,  19188,  18747,  18483]])#calk_coef(z, p, t, c1, c2,c3,c4, L, K)
    #print(Ci)
    C0 = np.array([[7432, 6226, 4165, 6447]*L]).reshape(L,K)#np.random.random((L,K))*10000
    flights = [Flight(12,	 5,	 [699, 699],	 5.4), 
               Flight(16,	 6,	 [564, 571],	 2.6),
               Flight(20,	 4,	 [505, 490],	 4.0),
               Flight(36,	 7,	 [575, 597],	 2.7),
               Flight(40,	 5,	 [539, 547],	 6.3),
               Flight(44,	 6,	 [607, 626],	 4.5),
               Flight(60,	 4,	 [700, 700],	 2.9),
               Flight(64,	 8,	 [557, 659],	 2.6),
               Flight(68,	 9,	 [681, 642],     3.1),
               Flight(84,	 7,	 [556, 642],	 3.5),
               Flight(88,	 5,	 [539, 602],	 3.0),
               Flight(92,	 4,	 [555, 672],	 3.9),
               Flight(108,	 3,	 [581, 665],	 9.3),
               Flight(112,	 2,	 [608, 548],	 3.0),
               Flight(116,	 5,	 [595, 683],	 3.1),
               Flight(132,	 6,	 [641, 684],	 4.5),
               Flight(136,	 7,	 [580, 629],	 3.4),
               Flight(140,	 8,	 [620, 556],	 3.3),
               Flight(156,	 9,	 [535, 561],	 2.8),
               Flight(160,	 7,	 [633, 562],	 4.7),
               Flight(164,	 3,	 [628, 614],	 3.7)]
    #for i in range(L):
        #flights.append(Flight(arrive[i], t[i], [stats.norm(450, 100).ppf(random.uniform(0.8,1)),stats.norm(450, 100).ppf(random.uniform(0.8,1))], stats.expon(1).ppf(random.uniform(0.8,1))))
    print(flights)
    J=[]
    count = 0
    income = list()
    for i in range(L):
        J.append(i)
        #print(J)
        if len(J)==l:
           u = get_U(set(J),I1, I2, K, Kr, z, l, flights)
           U, tmp = find_max(U, u, Ci, C0, count, l, K, I1, I2, Kr, z, flights)
           #print(U)
           income.append(tmp)
           J=[i]
           count+=1
    #print(J)
    u = get_U(set(J), I1, I2, K, Kr, z, l, flights)
    U, tmp = find_max(U, u, Ci, C0, count, l, K, I1, I2, Kr, z, flights)
    income.append(tmp)
    print(U)
    print(is_in(U, set(list(range(U.shape[0]))), I1, I2, K, Kr, z, 21, flights))
    #print(sum(income))
    print(sum(sum(U*Ci)))
    print("--- %s seconds ---" % (time.time() - start_time))

if __name__=="__main__":
    main()