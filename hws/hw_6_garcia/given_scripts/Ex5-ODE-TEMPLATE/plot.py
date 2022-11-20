import numpy as np
import matplotlib.pyplot as plt

t=[]
x=[]
y=[]
f=open('test.rk4', 'r')
i=0
for line in f:
   if (i >0):
        t.append(float(line.split()[0]))
        x.append(float(line.split()[1]))
        y.append(float(line.split()[2]))
   i=i+1

t1=[]
x1=[]
y1=[]
plt.plot(t,x,'g.-',label='rk4')

f=open('test.lf', 'r')
i=0
for line in f:
   if (i >0):
        t1.append(float(line.split()[0]))
        x1.append(float(line.split()[1]))
        y1.append(float(line.split()[2]))
   i=i+1

plt.plot(t1,x1,'b.-',label='lf')

t2=[]
x2=[]
y2=[]
f=open('test.eu', 'r')
i=0
for line in f:
   if (i >0):
        t2.append(float(line.split()[0]))
        x2.append(float(line.split()[1]))
        y2.append(float(line.split()[2]))
   i=i+1

plt.plot(t2,x2,'r.-',label='eu')
plt.legend()

plt.show()
