# saltystats

# TODO
# store bet,payout,chars in hist
# graph win rate diff 5-10% buckets vs upset rate (+ variance),
#   expected % gain favor/upset
# collect everyone's salt/bets, report max single salt/odds/rate win/loss,
#   max gain/loss over time + # of bets
# add 150k to main 10/3/16
# group analysis: if same couple guys beat the same couple guys, pattern exists
#   such that a typing can be assumed. This type beats that type.

from selenium.webdriver import Chrome
from plotly.offline import plot
from plotly.graph_objs import Scatter

from util import *
from bots import *

br = Chrome()
login(br, bots[0])
salt = int(prefix(br.find_element_by_id('balance').text, '<') \
           .translate({ord(c): None for c in ','}))

bets = []
page = 1
while True:
  br.get(url_mystats + str(page))
  t = br.page_source
  if search(t, 'No data available in table') != '':
    break
  t = search(t, 'aria-live')
  while True:
    t = search(t, 'td class')
    if t == '':
      break
    b = Bet()
    if t[14] == 'E':
      b.mode = 'e'
      t = search(t, 'Classic')[8:]
    elif t[14] == 'T':
      b.mode = 't'
      t = search(t, 'Classic')[8:]
    else:
      b.mode = 'm'
      t = search(t, 'Casino')[7:]
    b.mnum = int(prefix(t, '<'))
    t = search(t, 'text')[6:]
    b.rname = prefix(t, '<')
    t = search(t, 'text')[6:]
    b.bname = prefix(t, '<')
    t = search(t, 'td class')[13:]
    b.wager = int(prefix(t, ' '))
    t = search(t, 'text')[6:]
    n = prefix(t, '<')
    b.color = 'r' if n == b.rname else 'b'
    t = search(t, 'td class')[8:]
    t = search(t, 'td class')[13:]
    p = prefix(t, '<')
    b.payout = 0 if p == '' else int(p)
    t = search(t, 'td class')[13:]
    b.date = prefix(t, '<')
    bets += [b]
  page += 1

br.quit()

r = []
s = salt
i = len(bets)
x = [i]
y = [s]
m = 'm'

for j in range(len(bets)+1):
  if j != len(bets):
    b = bets[j]
  if j == len(bets) or (b.mode != m and (m == 'm' or m == 'e')):
    x.reverse()
    y.reverse()
    if m == 'm':
      r += [[x, y, 'm', dict(color='rgb(22,96,167)')]]
    else:
      r += [[x, y, 'e', dict(color='rgb(40,200,40)')]]
    x = [x[0]]
    y = [y[0]]

  elif j == len(bets) or (m == 't' and b.mode != m):
    x.reverse()
    y.reverse()
    t = 0
    for k in range(len(y)):
      y[k] += t
      if y[k] < y[0]:
        t += y[0] - y[k]
        y[k] = y[0]
    if bets[j-1].mnum in twins:
      t += 250000
    s -= t
    for k in range(len(y)):
      y[k] -= t
    r += [[x, y, 't', dict(color='rgb(205,12,24)',dash='dot')]]
    x = [x[0]]
    y = [y[0]]

  if j == len(bets):
    break
  i -= 1
  s -= b.payout
  if s < 0:
    s = 0
  x += [i]
  y += [s]
  m = b.mode

r.reverse()
t = 0
for ro in r:
  for i in range(len(ro[1])):
    ro[1][i] += t
    if ro[1][i] < r[0][1][0]:
      t += r[0][1][0] - ro[1][i]
      ro[1][i] = r[0][1][0]
for ro in r:
  for i in range(len(ro[1])):
    ro[1][i] -= t

rf = [Scatter(x=ro[0], y=ro[1], name=ro[2], line=ro[3]) for ro in r]
while True:
  try:
    plot(rf)
    break
  except Error:
    print('Can\'t write plot, trying again')
