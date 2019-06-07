from random import *

def gen():
  p=[i+1 for i in xrange(n)]
  shuffle(p)
  e=[]
  for i in xrange(1,n):
    e.append([p[randint(max(0,i-3),i-1)],p[i]])
  shuffle(e)
  for c in e:
    if randint(0,1):
      print c[0],c[1],randint(1,10**9)
    else:
      print c[1],c[0],randint(1,10**9)

n=100000
print n
gen()
gen()