# PULL

from json               import dumps
from selenium.webdriver import Chrome


url_pre = 'https://magiccards.info/query?q=c%21'
url_suf = '+f%3Acommander&s=cname&v=card&p='
url2 = 'https://magiccards.info/query?q=%28c%3Ac+or+c%3Al%29' + \
       '+f%3Acommander&s=cname&v=card&p='

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

    # s = s[s.find('jpg" alt=')+10:]
    # c['name'] = s[:s.find('"')]
    # s = s[s.find('<p>')+3:]
    # t = s[:s.find('</p>')].replace('\n', ' ').replace('\x97', '-')
    # while '  ' in t:
    #   t = t.replace('  ', ' ')

    # tok = t.split(',')
    # u, v = tok[0], tok[1]
    # tok = u.split(' ')
    # k = 0
    # c['types'] = []
    # while k < len(tok) and tok[k] in types:
    #   c['types'] += [tok[k]]
    #   k += 1
    # k += 1

    # c['subtypes'] = []
    # while k < len(tok):
    #   if k == len(tok)-1 and CRE in c['types']:
    #     tok = tok[-1].split('/')
    #     c['power'] = int(tok[0])
    #     c['toughness'] = int(tok[1])
    #   else:
    #     c['subtypes'] += [tok[k]]
    #   k += 1

    # t = v.split(' ')[1].lower()
    # it = iter(range(len(t)))
    # for k in it:
    #   if t[k].isdigit():
    #     c['cost_n'] = int(t[k])
    #     continue
    #   key = 'cost_'
    #   if t[k] == '{':
    #     key += t[k+1] + t[k+3]
    #     for i in range(4):
    #       next(it, None)
    #   else:
    #     key += t[k]
    #   if key in c.keys():
    #     c[key] += 1
    #   else:
    #     c[key] = 1

    # s = s[s.find('<b>')+3:]

    page += 1
br.quit()
