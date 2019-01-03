// PARSE

#ifndef parse_h
#define parse_h

/*

lib = 'lib.json'


nc = 0
def repl(m):
  global nc
  nc += 1
  return '"c' + str(nc) + '": {'

def strip(s):
  swaps = ', \n'
  for i in range(len(s)):
    if s[i] not in swaps: break
  s = s[i:]
  for i in range(len(s)-1, -1, -1):
    if s[i] not in swaps: break
  s = s[:i+1]
  return s

def split(s):
  r = {}
  mark, b = 0, 0
  for i in range(1, len(s)):
    if s[i] == '{':
      b += 1
    elif s[i] == '}':
      b -= 1
      if b == 0:
        card = strip(s[mark+1:i+1])
        j = card[1:].find('"')+1
        r[card[1:j]] = card[j+3:]
        mark = i
  return r

# String to tuple
def s2t(s):
  return loads(s, object_hook = \
                  lambda d: namedtuple('x', d.keys())(*d.values()))

# Tuple to dict
def t2d(t):
  stypes = (type(None), bool, int, float, str)
  d = dict(t._asdict())
  for k, v in d.items():
    if type(v) == list:
      for i in range(len(v)):
        if type(v[i]) not in stypes:
          d[k][i] = t2d(v[i])
      continue
    if type(v) not in stypes:
      d[k] = t2d(v)
  return d


f = open(lib, 'r')
s = f.read()
f.close()

c = split(sub(r'".*":\s{', repl, s))
d = {}
for k, v in c.items():
  if len(d) % 100 == 0:
    print(len(d))
  d[k] = t2d(s2t(v))

*/


int parse(vec<Card>& lib){

}
