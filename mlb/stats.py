# MLB SCAN

from os import listdir

def read():
  teams = {}
  for team in listdir('data'):
    years = {}
    for fname in listdir('data/'+team):
      f = open('data/'+team+'/'+fname)
      players = {}
      for line in f:
        player = {}
        for s in line.split(','):
          k, v = s.split(':')[0], s.split(':')[1].strip()
          player[k] = int(v) if v.isdigit() else v
        name = player['name']
        if name in players:
          for k in player:
            v = player[k]
            if k in players[name] and players[name][k] != v:
              print('ERR: '+player['pos']+' '+name+' key='+k+' v0='+ \
                    players[name][k]+' vn='+v)
            players[name][k] = v
        else: players[name] = player
      years[int(fname.split('.')[0])] = players
    teams[team] = years
  return teams

def stats(teams):
  stats = ('doubles', 'triples', 'home_runs', 'hits', 'runs')
  season = [(0, None) for i in range(5)]
  career = [(0, None) for i in range(5)]

  players = {}
  for team in teams:
    for year in teams[team]:
      for name in teams[team][year]:
        player = teams[team][year][name]
        for i in range(len(stats)):
          if player[stats[i]] > season[i][0]:
            season[i] = (player[stats[i]], name, team, year)
          if name in players:
            players[name] = \
              [players[name][i]+player[stats[i]] for i in range(len(stats))]
          else: players[name] = [player[stats[i]] for i in range(len(stats))]

  for name in players:
    for i in range(len(stats)):
      if players[name][i] > career[i][0]:
        career[i] = [players[name][i], name]

  for team in teams:
    for year in teams[team]:
      for name in teams[team][year]:
        for i in range(len(stats)):
          if name == career[i][1]:
            if len(career[i]) == 2: career[i] += [[team]]
            elif team not in career[i][2]: career[i][2] += [team]

  for team in teams:
    for year in teams[team]:
      for name in teams[team][year]:
        for i in range(len(stats)):
          if name == career[i][1]:
            if len(career[i]) == 3: career[i] += [[year]]
            elif year not in career[i][3]: career[i][3] += [year]
  for i in range(len(stats)):
    mn, mx = float('inf'), 0
    for year in career[i][3]:
      if year < mn: mn = year
      elif year > mx: mx = year
    career[i][3] = (mn, mx)

  print('2B/season', season[0])
  print('3B/season', season[1])
  print('HR/season', season[2])
  print('H/season ', season[3])
  print('R/season ', season[4])
  print()
  print('2B/career', career[0])
  print('3B/career', career[1])
  print('HR/career', career[2])
  print('H/career ', career[3])
  print('R/career ', career[4])

stats(read())
