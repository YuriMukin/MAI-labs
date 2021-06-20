import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt
from scipy.optimize import fmin_tnc
from itertools import combinations


def Get_ready(data):
    #удалим строки с колличеством путей не 2 и с неизвестным исходом 
    data = data.drop(pd.isnull(data)[(data.twoways!=1) | (pd.isnull(data).exit==True)].index)
    #из иформации о временим происшествия оставим только месяц
    data['date'] = pd.DatetimeIndex(data['date']).month
    #заполним пропуски средним значением столбца
    data = data.fillna(data.mean())
    #data.to_csv('res.csv', sep = ',')
    return data

#вычисляем вероятность вхождения в группу вагонов перекрывших соседний путь 
def Probability(thet, x):
    theta = thet[1:]
    tmp = np.exp(-x.mul(theta, axis = 1).sum(axis=1)-thet[0])
    #tmp = np.exp(-x.mul(thet, axis = 1).sum(axis=1))
    return 1/(1+tmp)

#тут вводим функцию стоимости ошибки, котороую будем минимизировать, тем самым обучая модель
def Error_cost(theta, x, y):
    #функция которая при вероятности стремящейся к 1 при целевой 0 стремится к бесконечности и наоборот 
    #аналогичное поведениме при стремлении к 0 и целивой 1
    cost = -np.sum(y * np.log(Probability(theta, x)) + (1 - y) * np.log(
        1 - Probability(theta, x)))
    return cost

#функция градиента в точке тетта
def Grad(theta, x, y):
    t = np.exp(theta[0])
    return np.append(t/(t+1), np.dot(x.T, Probability(theta,   x) - y))
    #return np.dot(x.T, Probability(theta,   x) - y)

#поскольку, задача минимизации функции довольно сложна и комплексна, использую готовое решение
def Get_weight(x, y, theta):
    opt_weights = fmin_tnc(func=Error_cost, x0=theta, fprime=Grad,args=(x, y))
    return opt_weights[0]

    
def accuracy(x, actual_classes, theta):
        predicted_classes = (Probability(theta,x) >= 0.5).astype(int)
        accuracy = np.mean(predicted_classes == actual_classes)
        return accuracy

#ROC анализ
def Sen_Spe(data):
    data['exitp']=0
    t_max = max(data.my_predict)
    t =  min(data.my_predict)
    X=[]
    Y=[]
    while t<=t_max:
        data.exitp[data.my_predict>=t] = 1
        data.exitp[data.my_predict<t] = 0
        TP = ((data.exit == 1) & (data.exitp == 1)).sum()
        TN = ((data.exit == 0) & (data.exitp == 0)).sum()
        FP = ((data.exit == 0) & (data.exitp == 1)).sum()
        FN = ((data.exit == 1) & (data.exitp == 0)).sum()
        Y.append(TP/(TP+FN))
        X.append(TN/(TN+FP))
        t = t+0.01
    return X,Y

#считаем площад под графиком
def AUC(data):
    AUC = 0
    X,Y = Sen_Spe(data)
    for i in range(len(X)-1):
        AUC = AUC + ((X[i]+X[i+1])/2)*(Y[i]-Y[i+1])
    return(AUC)

def AIC(data, k):
    L = np.prod((data.my_predict**data.exit)*(1-data.my_predict)**(1-data.exit))
    return 2*k-2*np.log(L)


data = Get_ready(pd.read_excel('WI.xlsx'))
aim = data.exit
print('use matched AUC baset set: 1\nuse matched AIC baset set: 2\nselect valueы using AUC: 3\nselect valueы using AIC: 4')
a = int(input())
if a == 3:
    d = ['date', 'length','commonlength','maxder','dcar','speed','weight','load'
     ,'curve','profile','type']
    count0 = 0 
    for j in range(1,len(d)):
        for i in combinations(d, j):
            count0 = count0 +1
    best = 0
    count1 = 0
    bs=[]
    for j in range(1,len(d)):
        for i in combinations(d, j):
            count1 = count1 + 1
            lst = list(i)
            fit = data[lst].copy()
            tht = np.zeros((fit.shape[1]+1, 1))
            weights = Get_weight(fit,aim,tht)
            data['my_predict'] = Probability(weights,fit)
            res = AUC(data)
            print('iter', count1, ' left ', count0-count1)
            if res>best:
                best = res
                bs = lst
    fit = data[bs].copy()
    tht = np.zeros((fit.shape[1]+1, 1))
    weights = Get_weight(fit,aim,tht)
    data['my_predict'] = Probability(weights,fit)
    print('AIC: ',AIC(data, len(bs)))
    print('AUC: ',best,'\n',bs)
    data = data.drop(['exitp'], axis = 1)
    data.to_csv('res.csv', sep = ',')
elif a == 4:
    d = ['date', 'length','commonlength','maxder','dcar','speed','weight','load'
     ,'curve','profile','type']
    count0 = 0 
    for j in range(1,len(d)):
        for i in combinations(d, j):
            count0 = count0 +1
    best = np.inf
    count1 = 0
    bs=[]
    for j in range(1,len(d)):
        for i in combinations(d, j):
            count1 = count1 + 1
            lst = list(i)
            fit = data[lst].copy()
            tht = np.zeros((fit.shape[1]+1, 1))
            weights = Get_weight(fit,aim,tht)
            data['my_predict'] = Probability(weights,fit)
            res = AIC(data, len(lst))
            print('iter', count1, ' left ', count0-count1)
            if res<best:
                best = res
                bs = lst
    fit = data[bs].copy()
    tht = np.zeros((fit.shape[1]+1, 1))
    weights = Get_weight(fit,aim,tht)
    data['my_predict'] = Probability(weights,fit)
    print('AUC: ',AUC(data))
    print('AIC: ',best,'\n',bs)
    data = data.drop(['exitp'], axis = 1)
    data.to_csv('res.csv', sep = ',')
elif a == 1:
    fit = data[['length', 'commonlength', 'maxder', 'dcar', 'weight', 'load', 'curve', 'profile', 'type']].copy()
    tht = np.zeros((fit.shape[1]+1, 1))
    weights = Get_weight(fit,aim,tht)
    data['my_predict'] = Probability(weights,fit)
    print('AUC: ',AUC(data))
    print('AIC: ',AIC(data, 9))
    print(accuracy(fit, aim, weights))
    data = data.drop(['exitp'], axis = 1)
    data.to_csv('res.csv', sep = ',')
else:
    fit = data[['dcar']].copy()
    tht = np.zeros((fit.shape[1]+1, 1))
    weights = Get_weight(fit,aim,tht)
    data['my_predict'] = Probability(weights,fit)
    print('AUC: ',AUC(data))
    print('AIC: ',AIC(data, 1))
    print(accuracy(fit, aim, weights))
    data = data.drop(['exitp'], axis = 1)
    data.to_csv('res.csv', sep = ',')
print(np.array(data.my_predict))