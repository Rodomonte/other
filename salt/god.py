# salt god

from time import sleep

while True:
  try:
    with open('salt.py') as salt:
      exec(salt.read())
  except Exception as e:
    print('Exception:', e)
  sleep(30)
