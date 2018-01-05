# WORDS

d,p = [],[]
f = open('dict.txt', 'r')
for line in f:
  d += [line[:-2]]
lc = ''

while True:
  print
  print 'Enter: pre/suf/con/set/pool/" <token> <len=2+>'
  tok = raw_input().split(' ')
  if (tok[0] == '"' or tok[1] == '"' or (len(tok) > 2 and tok[2] == '"')) \
    and lc == '': continue
  c = lc[0] if tok[0] == '"' else tok[0]
  t = lc[1] if tok[1] == '"' else tok[1]
  k = lc[2] if (len(tok) > 2 and tok[2] == '"') else \
    (int(tok[2]) if (len(tok) > 2 and tok[2] != '*' and tok[2] != '^') else -1)
  lc = (c, t, k)

  a,r = [],[]
  if c == 'pool':
    i = 0
    while i < len(t):
      if t[i] == '\'':
        a += [t[i+1:i+3]]
        i += 4
      else:
        a += [t[i]]
        i += 1

  for w in (p if len(tok) > 2 and tok[2] == '^' else d):
    if k != -1 and len(w) != k: continue

    if c == 'pool':
      x = w
      b = len(x)
      for ch in a:
        if len(ch) < 2: continue
        if ch in x:
          x = x.replace(ch, '%%', 1)
          b -= 2
      for ch in a:
        if len(ch) > 1: continue
        if ch in x or ch == '*':
          x = x.replace(ch, '%', 1)
          b -= 1
      if b == 0: r += [w]

    elif c == 'set':
      if len(t) != len(w): continue
      f = True
      for i in range(len(t)):
        if t[i] != '*' and len(w) > i and w[i] != t[i]:
          f = False
          break
      if f: r += [w]

    elif c == 'pre':
      if w[:len(t)] == t: r += [w]

    elif c == 'suf':
      if w[len(w)-len(t):] == t: r += [w]

    elif c == 'con':
      for i in range(len(w)-len(t)+1):
        if w[i:i+len(t)] == t: r += [w]

    if len(tok) < 3 or (tok[2] != '*' and tok[2] != '^'):
      if len(r) > 1 and len(r[-1]) > len(r[0]): r = [r[-1]]
      elif len(r) > 1 and len(r[-1]) < len(r[0]): r = r[:len(r)-1]
  p = r
  print r
  print '('+str(len(r))+')'
