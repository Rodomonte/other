# salt

# TODO
# my stats
# crash protection on browser stall
# t mode betfns
# exhib stats w/ palletes, team win rate handling

from os.path import isfile
from time import sleep
from datetime import datetime
from pickle import load, dump
from selenium.common.exceptions import WebDriverException

from util import *
from bots import *

# User history
if isfile('salt.dat'):
  dbots = load(open('salt.dat', 'rb'))
  for dbot in dbots:
    for bot in bots:
      if bot.user == dbot.user:
        bot.hist = dbot.hist
        break

# Login
br = get_browser()
login(br, bots[0])

# Mute and pause
def wait():
  sleep(0.5)
  br.switch_to.frame(br.find_element_by_id('iframeplayer'))
  div = br.find_element_by_id('video-playback')
  try:
    if div.get_attribute('data-muted') == 'false':
      br.find_element_by_class_name('player-button--volume').click()
    if div.get_attribute('data-paused') == 'false':
      br.find_element_by_class_name('player-button--playpause').click()
  except WebDriverException: pass
  br.switch_to_default_content()

# Wait until bet opens
while True:
  try:
    while search(br.page_source, 'Bets are OPEN!') == '':
      wait()

    # Determine game mode
    br.get(url_bracket)
    t = br.page_source
    if search(t, 'exhibition matches left!') != '' or \
       search(t, 'after the next exhibition match!') != '': mode = 'e'
    elif search(t, 'are left in the bracket!') != '' or \
         search(t, 'exhibitions after the tournament!') != '': mode = 't'
    else: mode = 'm'

    # Fetch fighter stats
    br.get(url_stats)
    td = []
    for team in range(0, 2):
      while br.find_element_by_id('p1winrate').text == '':
        continue
      t = [br.find_element_by_id('p' + str(team+1) + f).text for f in \
           ['namestats', 'totalmatches', 'winrate', 'tier', 'life', 'meter', \
            'palette', 'author']]
      t[2] = t[2][:-1]
      if '/' in t[1]:
        t2 = []
        for i in range(len(t)):
          parts = t[i].split(' / ')
          t[i] = parts[0]
          t2 += [parts[1]]
        td += [[t, t2]]
      else:
        td += [[t]]

    # Create character objects
    chars = []
    for team in td:
      chars += [[]]
      for t in team:
        chars[-1] += [Char(t[0], int(t[1]), int(t[2])/100.0, t[3], int(t[4]), \
                           int(t[5]), int(t[6]), t[7])]

    # Login
    br.get(url_main)
    for bot in bots[:2]:
      if bot != bots[0]:
        login(br, bot)

      # Fetch bankroll
      salt = int(prefix(br.find_element_by_id('balance').text, '<') \
                 .translate({ord(c): None for c in ','}))
      bot.hist += [(salt, datetime.now())]

      # Place bet
      bet = bot.betfn(mode, salt, chars)
      while True:
        try:
          br.find_element_by_id('wager').send_keys(str(bet[1]))
          break
        except Exception as e:
          pass

      while search(br.page_source, 'redtext">\u2190') == '' and \
            search(br.page_source, 'bluetext">\u2192') == '':
        bname = 'player1' if bet[0] == 'r' else 'player2'
        br.find_element_by_id(bname).click()
        sleep(0.5)
      while search(br.page_source, 'greentext">\u2713') == '':
        sleep(0.5)
      print(bot.user + ' bet $' + str(bet[1]) + ' on ' + bet[0] + ' at ' + \
            str(datetime.now()))

      # Logout
      br.get(url_logout)

    # Write bet data
    dump(bots, open('salt.dat', 'wb'))

    # Wait until bets close
    login(br, bots[0])
    while search(br.page_source, 'Bets are OPEN!') != '':
      wait()

  # Terminate and reopen browser
  except Exception as e:
    br.quit()
    print('Exception:', e)
    br = get_browser()
    login(br, bots[0])

# Unreached
br.quit()
