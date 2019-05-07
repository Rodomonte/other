# PLANET ALIGNMENTS

from math import sqrt
from os import chdir   \
             , listdir


def find(txt, i0, tok):
  for i in range(i0, len(txt)):
    j, k = i, 0
    while j < len(txt) and k < len(tok) and txt[j] == tok[k]:
      j += 1
      k += 1
    if k == len(tok):
      return i
  return -1

def vsub(a, b):
  return (a[0]-b[0], a[1]-b[1], a[2]-b[2])

def vlen(a):
  return sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2])

def cross(a, b):
  return (a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2], a[0]*b[1] - a[1]*b[0])

def pldist(a, b, c): # distance from a to line(b, c)
  return vlen(cross(vsub(a, b), vsub(a, c))) / vlen(vsub(b, c))

def side(a, b):
  return vlen(a) + vlen(b) > 1.05 * vlen(vsub(a, b))

months = {'Jan':1, 'Feb':2, 'Mar':3, 'Apr':4, 'May':5, 'Jun':6, 'Jul':7, \
          'Aug':8, 'Sep':9, 'Oct':10, 'Nov':11, 'Dec':12}
def datelt(a, b):
  toka, tokb = a.split('-'), b.split('-')
  if int(toka[0]) < int(tokb[0]): return True
  if int(toka[0]) > int(tokb[0]): return False
  if months[toka[1]] < months[tokb[1]]: return True
  if months[toka[1]] > months[tokb[1]]: return False
  if int(toka[2]) < int(tokb[2]): return True
  if int(toka[2]) > int(tokb[2]): return False
  if int(toka[3]) < int(tokb[3]): return True
  if int(toka[3]) > int(tokb[3]): return False
  return False


# PARSE

mb = []
chdir('data/future')
files = listdir('.')
n = 0
for fname in files:
  if not fname.endswith('.txt'): continue

  fp = open(fname)
  txt = fp.read()
  i = find(txt, 0, '$$SOE')
  hdr = txt[:i]
  i += 6
  m = {}

  while True:
    j = find(txt, i, 'X')
    if txt[j+2] != '=': break
    ds = txt[i:j-2]
    i = find(txt, j, 'RR')+26
    cs = txt[j:i]

    tok = ds.split(' ')
    date = tok[3] + '-' + tok[4][:2]
    j = find(cs, 0, 'Y')
    x = float(cs[3:j-1])
    cs = cs[j:]
    j = find(cs, 0, 'Z')
    y = float(cs[3:j-1])
    cs = cs[j:]
    j = find(cs, 0, 'VX')
    z = float(cs[3:j-2])
    m[date] = (x, y, z)

  mb += [(fname.split('.')[0], hdr, m)]
  fp.close()
  n += 1
  print(n, 'of', len(files), 'parsed.')


# COLINEARITY

ERR = 0.05
ERRM = 0.01
TOP = 2000

N = len(mb)
u = {}
p4, m4 = {}, 100.0
p5, m5 = {}, 100.0

for i in range(N):
  for k, v in mb[i][2].items():
    if k in u: continue
    u[k] = 1

for date in u.keys():
  a = []
  for i in range(N):
    if date in mb[i][2]:
      a += [(mb[i][2][date], mb[i][0])]

  for i in range(len(a)-2):
    for j in range(i+1, len(a)-1):
      sun = pldist((0,0,0), a[i][0], a[j][0])
      for k in range(len(a)):
        if k == i or k == j: continue
        d = pldist(a[k][0], a[i][0], a[j][0])
        if (a[k][1] == 'luna' and d + sun < ERRM) or \
           (a[k][1] != 'luna' and d + sun < ERR):
          print('3', date, ':', a[i][1], '---', a[j][1], '---', a[k][1], \
                ':', d+sun, '********' if side(a[i][0], a[j][0]) and \
                            side(a[i][0], a[k][0]) else '')

        for ii in range(k+1, len(a)):
          if ii == i or ii == j: continue
          d2 = pldist(a[ii][0], a[i][0], a[j][0])
          if ((a[k][1] == 'luna' and d + sun < ERRM) or \
              (a[k][1] != 'luna' and d + sun < ERR)) and \
             ((a[ii][1] == 'luna' and d2 + sun < ERRM) or \
              (a[ii][1] != 'luna' and d2 + sun < ERR)):
            print('4', date, ':', a[i][1], '---', a[j][1], '---', a[k][1], \
                  '---', a[ii][1], ':', d, d2, \
                  '********' if side(a[i][0], a[j][0]) and \
                  side(a[i][0], a[k][0]) and side(a[i][0], a[ii][0]) else '')

          s = d + d2 + sun
          if len(p4) < TOP or s < m4:
            p4[s] = (date, a[i][1], a[j][1], a[k][1], a[ii][1], \
                     '********' if side(a[i][0], a[j][0]) and \
                     side(a[i][0], a[k][0]) else '')
            if len(p4) == TOP+1:
              skeys = sorted(p4.keys())
              del p4[skeys[-1]]
              m4 = skeys[TOP-1]

          # for jj in range(ii+1, len(a)):
          #   if jj == i or jj == j: continue
          #   d3 = pldist(a[jj][0], a[i][0], a[j][0])
          #   s = d + d2 + d3 + sun
          #   if len(p5) < TOP+1 or s < m5:
          #     p5[s] = (date, a[i][1], a[j][1], a[k][1], a[ii][1], a[jj][1])
          #     if len(p5) == TOP+1:
          #       skeys = sorted(p5.keys())
          #       del p5[skeys[-1]]
          #       m5 = skeys[TOP-1]

print()
for key in sorted(p4.keys()):
  print(key, p4[key])

# print()
# for key in sorted(p5.keys()):
#   print(key, p5[key])
