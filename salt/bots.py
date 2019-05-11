# salt bots

import random

from util import *

class Bot:
  def __init__(s, e, u, p, b):
    s.email = e
    s.user = u
    s.pword = p
    s.betfn = b
    s.hist = []

mcap = 100000
tcap = 200000

def bet_favor(mode, salt, chars):
  rwr, bwr = chars[0][0].wr, chars[1][0].wr
  if mode == 'm':
    if salt < mcap:          bet = salt
    elif abs(rwr-bwr) < 0.3: bet = salt * 0.01
    elif abs(rwr-bwr) < 0.4: bet = salt * 0.02
    elif abs(rwr-bwr) < 0.5: bet = salt * 0.1
    else:                    bet = salt * 0.2
  elif mode == 't':
    bet = salt if salt < tcap else salt * 0.1
  else:
    bet = salt if salt < mcap else salt * 0.01
    rwr += chars[0][1].wr if len(chars[0]) == 2 else 0.0
    bwr += chars[1][1].wr if len(chars[1]) == 2 else 0.0
  bet = int(round(bet))
  return ('r',bet) if rwr > bwr else ('b',bet)

def bet_upset(mode, salt, chars):
  rwr, bwr = chars[0][0].wr, chars[1][0].wr
  if mode == 'm':
    if salt < mcap:          bet = salt
    elif abs(rwr-bwr) < 0.2: bet = salt * 0.02
    else:                    bet = salt * 0.01
  elif mode == 't':
    bet = salt if salt < tcap else salt * 0.05
  else:
    bet = salt if salt < mcap else salt * 0.01
    rwr += chars[0][1].wr if len(chars[0]) == 2 else 0.0
    bwr += chars[1][1].wr if len(chars[1]) == 2 else 0.0
  bet = int(round(bet))
  return ('r',bet) if rwr < bwr else ('b',bet)

def bet_comb(mode, salt, chars):
  rwr, bwr = chars[0][0].wr, chars[1][0].wr
  if mode == 'm':
    if salt < mcap:          bet = salt
    elif abs(rwr-bwr) < 0.3: bet = salt * 0.02
    elif abs(rwr-bwr) < 0.4: bet = salt * 0.05
    elif abs(rwr-bwr) < 0.5: bet = salt * 0.2
    else:                    bet = salt * 0.5
  elif mode == 't':
    bet = salt if salt < tcap else salt * 0.1
  else:
    bet = salt if salt < mcap else salt * 0.02
    rwr += chars[0][1].wr if len(chars[0]) == 2 else 0.0
    bwr += chars[1][1].wr if len(chars[1]) == 2 else 0.0
  bet = int(round(bet))
  return ('r',bet) if (abs(rwr-bwr) < 0.2 and rwr < bwr) or \
                      (abs(rwr-bwr) >= 0.2 and rwr > bwr) else ('b',bet)

def bet_random(mode, salt, chars):
  bet = salt if salt < (tcap if mode == 't' else mcap) else salt * 0.02
  bet = int(round(bet))
  return ('r',bet) if random.randint(1,2) == 1 else ('b',bet)

def bet_main(mode, salt, chars):
  rwr, bwr = chars[0][0].wr, chars[1][0].wr
  if mode == 'm':
    if salt < mcap:          bet = salt
    elif abs(rwr-bwr) < 0.2: bet = salt * 0.003 # 24k at 8m
    elif abs(rwr-bwr) < 0.3: bet = salt * 0.005 # 40k
    elif abs(rwr-bwr) < 0.4: bet = salt * 0.01  # 80k
    elif abs(rwr-bwr) < 0.5: bet = salt * 0.02  # 160k
    else:                    bet = salt * 0.05  # 400k
    col = 'r' if (abs(rwr-bwr) < 0.1 and rwr < bwr) or \
                 (abs(rwr-bwr) >= 0.1 and rwr > bwr) else 'b'
  elif mode == 't':
    bet = salt if salt < tcap else salt * 0.1
    col = 'r' if (abs(rwr-bwr) < 0.1 and rwr < bwr) or \
                 (abs(rwr-bwr) >= 0.1 and rwr > bwr) else 'b'
  else:
    bet = salt if salt < mcap else salt * 0.001
    col = 'r' if random.randint(1,2) == 1 else 'b'
  bet = int(round(bet))
  return (col,bet)

bots = []
bots += [Bot('rcb0000@gmail.com', 'rodomonte', '', bet_main)]
bots += [Bot('chachebiku@throwam.com', 'spicysalmon', 'mg81o04pd7gh6', \
              bet_favor)]
bots += [Bot('rotibathel@throwam.com', 'ableanchovy', 'j48fvjxcms874', \
              bet_upset)]
bots += [Bot('nijostoses@throwam.com', 'tensiletuna', 'd84jf9jfj8923', \
              bet_comb)]
bots += [Bot('sojecesali@throwam.com', 'humanehalibut', 'zm1956nhewh2f', \
              bet_random)]
