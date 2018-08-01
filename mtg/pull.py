# PULL

from json               import dumps
from os                 import chdir
from selenium.webdriver import Chrome
from time               import sleep


url_pre = 'https://magiccards.info/query?q=c%21'
url_suf = '+f%3Acommander&s=cname&v=card&p='

ART = 'Artifact'
BAS = 'Basic'
CRE = 'Creature'
ENC = 'Enchantment'
INS = 'Instant'
LAN = 'Land'
LEG = 'Legendary'
PLA = 'Planeswalker'
SOR = 'Sorcery'
types = (ART, BAS, CRE, ENC, INS, LAN, LEG, PLA, SOR)
colors = 'wubrg'
color3 = ('whi', 'blu', 'blk', 'red', 'gre')

combs = []
lib = []


def gen_combs(s, pool, r):
  for color in pool:
    s2 = s + color
    r += [s2]
    gen_combs(s2, pool[pool.find(color)+1:], r)

gen_combs('', colors, combs)
for i in range(len(combs)):
  if(len(combs[i]) > 1):
    combs[i] += 'm'


br = Chrome()
for comb in combs:
  page = 1
  while True:
    br.get(url_pre + comb + url_suf + str(page))
    s = br.page_source
    c = {}

    i = s.find('jpg" alt=')
    s = s[i+10:]
    i = s.find('"')
    c['name'] = s[:i]

    i = s.find('<p>')
    s = s[i+3:]
    i = s.find('</p>')
    t = s[:i].replace('\n', ' ').replace('\x97', '-')
    while '  ' in t:
      t = t.replace('  ', ' ')

    tok = t.split(',')
    u, v = tok[0], tok[1]
    tok = u.split(' ')
    k = 0
    c['types'] = []
    while k < len(tok) and tok[k] in types:
      c['types'] += [tok[k]]
      k += 1
    k += 1

    c['subtypes'] = []
    while k < len(tok):
      if k == len(tok)-1 and CRE in c['types']:
        tok = tok[-1].split('/')
        c['power'] = int(tok[0])
        c['toughness'] = int(tok[1])
      else:
        c['subtypes'] += [tok[k]]
      k += 1

    t = v.split(' ')[1]
    for k in range(len(t)):
      if t[k].isdigit():
        c['cost_gen'] = int(t[k])
      elif t[k] == '{':
        #!
      else:
        i = colors.find(t[k].lower())
        key = 'cost_' + ('x' if t[k] == 'X' else color3[i])
        if key in c.keys():
          c[key] += 1
        else:
          c[key] = 1

    print(comb, c, t)
    print()
    #! if card on page already pulled, exit
    break

    page += 1
  #break

br.quit()
