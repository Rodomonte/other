# MLB PULL

from time import sleep, time
from os import mkdir
from os.path import exists
from selenium.webdriver import Chrome

url = 'https://www.baseball-reference.com/teams'
aliases = {'LAA' : 'ANA' \
         , 'MIA' : 'FLA' \
         , 'TBR' : 'TBD'}
start_year = 1970

def gethtml(u):
  while True:
    br = Chrome(executable_path='../sw/chromedriver.exe')
    br.set_page_load_timeout(10)
    html = ''
    try: br.get(u)
    except:
      br.quit()
      continue
    clock = time()
    while True:
      try:
        html = br.page_source
        br.quit()
        return html
      except: pass
      if time() - clock > 10:
        br.quit()
        break

def find(t, s):
  for i in range(len(t)):
    if t[i] == s[0]:
      found = True
      j = i+1
      for k in range(1,len(s)):
        if t[j] != s[k]:
          found = False
          break
        j += 1
      if found:
        return (i, t[i:])
  return (-1, '')

def find_digit(t):
  for i in range(len(t)):
    if t[i] >= '0' and t[i] <= '9': return (i, t[i:])
  return (-1, '')

def pr(s):
  r = ''
  for i in range(len(s)):
    r += s[i]
    if s[i] == '\n':
      r += '\n'
  print(r)

def write(team, year, players):
  s = ''
  for player in players:
    for stat in player:
      s += stat+':'+player[stat]+','
    s = s[:-1]+'\n'
  path = 'data/'+team+'/'+str(year)+'.csv'
  f = open(path, 'w+')
  f.write(s)
  f.close()
  if exists(path): print('Wrote', path)

def pull_teams():
  teams = []
  html = gethtml(url)
  html = find(html, 'href="/teams')[1][11:]
  html = find(html, 'teams')[1][5:]

  while find(html, 'leagues')[0] > find(html, 'teams')[0]:
    teams += [html[1:4]]
    if not exists('data/'+teams[-1]): mkdir('data/'+teams[-1])
    html = find(html, 'teams')[1][5:]
    html = find(html, 'teams')[1][5:]
  html = find(html, 'year_min')[1][8:]

  r = []
  for i in range(len(teams)):
    html = find(html, 'tr data-row')[1]
    m = len(html)
    team = ''
    for t in teams:
      n = find(html[:1000], aliases[t] if t in aliases else t)[0]
      if n != -1 and n < m:
        m = n
        team = t

    html = find(html, 'year_min')[1][8:]
    start = int(find_digit(html)[1][:4])
    html = find(html, 'year_max')[1][8:]
    end = int(find_digit(html)[1][:4])
    r += [(team, start, end)]
  return r

def pull_stats(team, start, end):
  for year in range(max(start_year, start), end+1):
    if exists('data/'+team+'/'+str(year)+'.csv'): continue

    players = []
    names = {}
    html = gethtml(url+'/'+team+'/'+str(year)+'.shtml')
    html = find(html, '<caption>Team Batting')[1]

    while True:
      player = {}
      html = find(html, 'data-row')[1]
      if html == '': break

      html = find(html, 'csk')[1][3:]
      html = find(html, 'csk')[1]
      html = find(html, '>')[1]
      if html[1] == '<': html = find(html[1:], '>')[1]
      player['pos'] = html[1:find(html, '<')[0]]
      if player['pos'] == 'Rank': continue

      html = find(html, 'href')[1]
      html = find(html, '>')[1]
      player['name'] = html[1:find(html, '<')[0]]
      if player['name'] in names: break
      else: names[player['name']] = True

      html = find(html, 'age')[1]
      player['age'] = html[5:find(html, '<')[0]]
      try: n = int(player['age'])
      except: break

      html = find(html, 'G')[1]
      player['games'] = html[3:find(html, '<')[0]]
      html = find(html, 'PA')[1]
      player['plate_appearances'] = html[4:find(html, '<')[0]]
      html = find(html, 'AB')[1]
      player['at_bats'] = html[4:find(html, '<')[0]]
      html = find(html, 'R')[1]
      player['runs'] = html[3:find(html, '<')[0]]
      html = find(html, 'H')[1]
      player['hits'] = html[3:find(html, '<')[0]]
      html = find(html, '2B')[1]
      player['doubles'] = html[4:find(html, '<')[0]]
      html = find(html, '3B')[1]
      player['triples'] = html[4:find(html, '<')[0]]
      html = find(html, 'HR')[1]
      player['home_runs'] = html[4:find(html, '<')[0]]
      html = find(html, 'RBI')[1]
      player['runs_batted_in'] = html[5:find(html, '<')[0]]
      html = find(html, 'SB')[1]
      player['stolen_bases'] = html[4:find(html, '<')[0]]
      html = find(html, 'CS')[1]
      player['caught_stealing'] = html[4:find(html, '<')[0]]
      html = find(html, 'BB')[1]
      player['walks'] = html[4:find(html, '<')[0]]
      html = find(html, 'SO')[1]
      player['strikeouts'] = html[4:find(html, '<')[0]]
      html = find(html, 'avg')[1]
      player['batting_avg'] = html[5:find(html, '<')[0]]
      html = find(html, 'onbase_perc')[1]
      player['onbase'] = html[13:find(html, '<')[0]]
      html = find(html, 'slugging_perc')[1]
      player['slugging'] = html[15:find(html, '<')[0]]
      html = find(html, 'slugging')[1]
      player['ops'] = html[10:find(html, '<')[0]]
      html = find(html, 'plus')[1]
      player['ops+'] = html[6:find(html, '<')[0]]
      html = find(html, 'TB')[1]
      player['bases'] = html[4:find(html, '<')[0]]
      html = find(html, 'GIDP')[1]
      player['double_plays'] = html[6:find(html, '<')[0]]
      html = find(html, 'HBP')[1]
      player['hit_by_pitch'] = html[5:find(html, '<')[0]]
      html = find(html, 'SH')[1]
      player['sac_hits'] = html[4:find(html, '<')[0]]
      html = find(html, 'SF')[1]
      player['sac_flies'] = html[4:find(html, '<')[0]]
      html = find(html, 'IBB')[1]
      player['intentional_walks'] = html[5:find(html, '<')[0]]

      players += [player]
    if len(players) > 0: write(team, year, players)

teams = pull_teams()
for team in teams:
  pull_stats(team[0], team[1], team[2])
br.quit()
