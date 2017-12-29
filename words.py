# WORDS

d,p = [],[]
f = open('dict.txt', 'r')
for line in f:
  d += [line[:-2]]

while True:
  print
  print 'Enter: pre/suf/con/set/pool <token> <len=2+>'
  tok = raw_input().split(' ')
  k = int(tok[2]) if (len(tok) > 2 and tok[2] != '*' and tok[2] != '^') else -1

  a,r = [],[]
  if tok[0] == 'pool':
    i = 0
    while i < len(tok[1]):
      if tok[1][i] == '\'':
        a += [tok[1][i+1:i+3]]
        i += 4
      else:
        a += [tok[1][i]]
        i += 1

  for w in (p if len(tok) > 2 and tok[2] == '^' else d):
    if k != -1 and len(w) != k: continue

    if tok[0] == 'pool':
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

    elif tok[0] == 'set':
      if len(tok[1]) != len(w): continue
      f = True
      for i in range(len(tok[1])):
        if tok[1][i] != '*' and len(w) > i and w[i] != tok[1][i]:
          f = False
          break
      if f: r += [w]

    elif tok[0] == 'pre':
      if w[:len(tok[1])] == tok[1]: r += [w]

    elif tok[0] == 'suf':
      if w[len(w)-len(tok[1]):] == tok[1]: r += [w]

    elif tok[0] == 'con':
      for i in range(len(w)-len(tok[1])+1):
        if w[i:i+len(tok[1])] == tok[1]: r += [w]

    if len(tok) < 3 or (tok[2] != '*' and tok[2] != '^'):
      if len(r) > 1 and len(r[-1]) > len(r[0]): r = [r[-1]]
      elif len(r) > 1 and len(r[-1]) < len(r[0]): r = r[:len(r)-1]
  p = r
  print r
  print '('+str(len(r))+')'
