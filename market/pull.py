# stock pull

from os import remove
from os.path import isfile
from time import sleep
from selenium.webdriver import Chrome
from selenium.webdriver.chrome.options import Options

url_syms_pre = 'http://www.nasdaq.com/screening/companies-by-name.aspx?letter='
url_syms_suf = '&render=download'
url_vals_pre = \
  'https://www.google.com/finance/getprices?i=60&p=5d&f=d,o,h,l,c,v&df=cpct&q='
dir_home = 'C:\\Home\\Code\\market'
file_syms = 'companylist.csv'

opts = Options()
prefs = {'download.default_directory' : dir_home}
opts.add_experimental_option('prefs', prefs)
br = Chrome(chrome_options=opts)

syms = []
for i in range(26):
  c = chr(i + ord('A'))
  br.get(url_syms_pre + c + url_syms_suf)
  path = dir_home + '\\' + file_syms
  while not isfile(path):
    sleep(0.2)
  csv = open(path)
  for line in csv:
    toks = line.split(',')
    if toks[0] == '"Symbol"':
      continue
    syms += [toks[0].split('"')[1]]
  csv.close()
  remove(path)
  while isfile(path):
    sleep(0.2)

for sym in syms[:2]:
  url = url_vals_pre + sym
  br.get(url)
  src = br.page_source
  print(src)

br.quit()
