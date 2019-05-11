# salt util

from selenium.webdriver.chrome.options import Options
from selenium.webdriver import Chrome

twins = [6858, 7172]
url_login = 'http://www.saltybet.com/authenticate?signin=1'
url_logout = 'http://www.saltybet.com/logout'
url_main = 'http://www.saltybet.com'
url_stats = 'http://www.saltybet.com/stats'
url_mystats = 'http://www.saltybet.com/stats?mystats=1&page='
url_bracket = 'http://www.saltybet.com/shaker?bracket=1'

class Bet:
  def __init__(s):
    s.mnum, s.wager, s.payout = 0, 0, 0
    s.mode, s.rname, s.bname, s.color, s.date = '', '', '', '', ''
  def __str__(s):
    return s.mode + str(s.mnum) + ': ' + str(s.wager) + ' on ' + s.color + \
           ' -> ' + str(s.payout) + '  (' + s.rname + ' vs ' + s.bname + ')'

class Char:
  def __init__(s, n, mn, wr, t, l, m, p, a):
    s.mnum, s.wr, s.life, s.meter, s.pal = mn, wr, l, m, p
    s.name, s.tier, s.author = n, t, a
  def __str__(s):
    return s.name + ' ' + str(s.pal) + 'p'

def search(t, s):
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
        return t[i:]
  return ''

def prefix(t, d):
  t2 = search(t, d)
  s = len(t) - len(t2)
  return t[:s]

def get_browser():
  opts = Options()
  opts.add_argument('--disable-bundled-ppapi-flash')
  opts.add_extension('../../sw/Adblock-Plus_v1.12.4.crx')
  br = Chrome(executable_path='../../sw/chromedriver', chrome_options=opts)
  br.set_window_size(1536, 1024)
  return br

def login(br, bot):
  br.get(url_login)
  br.find_element_by_id('email').send_keys(bot.email)
  br.find_element_by_id('pword').send_keys(bot.pword)
  br.find_element_by_class_name('graybutton').click()
