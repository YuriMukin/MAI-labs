import numpy as np 


class Polinom:
    
    body = np.array([])
    
    def __init__(self, pol):
        self.body = pol.copy()
        
    def findPolinom(self, x):
        result = self.body[0]
        for i in range(self.body.size-1):
            result = self.body[i+1] + result*x
        return result
    
    def diff_pol(self):
        polinom = self.body.copy()
        result = list()
        for i in range(polinom.size-1):
            result.append(polinom[i]*(polinom.size-i-1)) 
        return np.asarray(result)
    
    def divPolinom(self, x):
        polinom = self.body.copy()
        p = polinom[0]
        polinom = polinom[1:] 
        result = [p]
        for i in polinom:
            p = i + p*x
            result.append(p)
        return result
    
    def borders(self):
        answer = [1]
        polinom = Polinom(self.body)
        polinomC = Polinom(self.body)
        if polinom.body[0]<0:
            polinom.body = -polinom.body
            polinomC.body = -polinomC.body       
        for i in range(polinom.body.size):
            if ((i+1)%2 == 1):
                polinom.body[polinom.body.size-(i+1)] = -polinom.body[polinom.body.size-(i+1)]
        if ((polinom.body.size)%2==1):
            polinom.body = -polinom.body
        LBF = True
        while LBF:
            d = polinom.divPolinom(answer[0])
            allpos = True
            for i in d:
                if i<0:
                    allpos = False
            if allpos:
                answer[0] = -answer[0]
                LBF = False
            if LBF:
                answer[0] = answer[0]+1
        answer.append(answer[0])
        allpas = True
        while allpas:
            d = polinomC.divPolinom(answer[1])
            allpas = False
            for i in d:
                if i<0:
                    allpas = True
            if allpas:
               answer[1] = answer[1]+1
        return answer
    
    def nuton_method(self):
        xp = self.borders()[1]
        diff_pol = Polinom(self.diff_pol())
        result = xp - self.findPolinom(xp)/diff_pol.findPolinom(xp)
        while abs(xp-result)>0.001:
            xp=result
            result = xp - self.findPolinom(xp)/diff_pol.findPolinom(xp)
        return result
    
    def Chord(self):
        border = self.borders()
        a = border[0]-1
        b = border[1]+1
        while (abs(a-b)>0.001):
            a = b + (b - a) * self.findPolinom(b) / (self.findPolinom(b) - self.findPolinom(a))
            b = a - (a - b) * self.findPolinom(a) / (self.findPolinom(a) - self.findPolinom(b))
        return a
    
    def ring_of_roots(self):
        polinom = self.body.copy()
        if polinom[polinom.size-1] == 0:
            polinom = polinom[:-1]
        maxA = max(abs(polinom))
        an = abs(polinom[polinom.size-1])
        maxB = max(abs(polinom[: -1]))
        a0 = abs(polinom[0])
        return [1/(1+maxB/an), 1+maxA / a0]
    
    def top_border_Lagrange(self):
        polinom = self.body.copy()
        if polinom[0]<0:
            polinom = -polinom
        pos, = np.where(polinom<0)
        B = max(abs(polinom[pos]))
        a = polinom[0]
        return 1+pow(abs(B/a), 1/pos[0])
        
    def top_border_Newton(self):
        polinoms = {0: Polinom(self.body)}
        if polinoms[0].body[0]<0:
            polinoms[0].body = -polinoms[0].body
        for i in range(polinoms[0].body.size-1):
            polinoms[i+1] = Polinom(polinoms[i].diff_pol())
        C = 0
        temp = True 
        alld = True
        while temp:
            for i in range(polinoms[0].body.size-1):
                if(polinoms[i].findPolinom(C)<0):
                    alld = True
            if alld:
                C+=1
                alld = False
            else:
                temp = False
        return C
    
    def div_pol_into_pol (self, pold):
        if self.body.size < pold.size:
            return {'result':[],'remainder': self.body}
        dev = pold[0]
        pold = -pold[1:pold.size] 
        print(pold)
        res=np.empty(0)
        res = np.append(res,self.body[0]/dev)
        for i in range(1,self.body.size - pold.size):
            tmp = 0
            if i < pold.size:
                for j in range(i):
                    tmp = tmp + res[j]*pold[i-j-1]
            else:
                for j in range(pold.size):
                    tmp += res[res.size-j-1]*pold[j]
            res = np.append(res,[(self.body[i]+tmp)/dev])
        for i in range(pold.size):
            tmp = 0
            t = 1
            for j in range(i,pold.size):
                if self.body.size - pold.size-t >= 0:
                    tmp += res[self.body.size - pold.size-t]*pold[j]
                t+=1
            res = np.append(res,[self.body[self.body.size-pold.size+i]+tmp])
        return {'result':res[0:self.body.size - pold.size],'remainder': res[self.body.size - pold.size: res.size]}   