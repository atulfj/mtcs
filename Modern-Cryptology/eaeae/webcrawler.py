import pexpect

alexa = pexpect.spawn('ssh student@172.27.26.188')

def crawl():
	alexa.expect('student@172.27.26.188\'s password:')
	alexa.sendline('cs641')
	alexa.expect('Enter your group name: ') 
	alexa.sendline("team_2")
	alexa.expect('Enter password: ')
	alexa.sendline("twopoint1")
	alexa.expect('.*', timeout=50)
	alexa.sendline("5")
	alexa.expect('.*')
	alexa.sendline("go")
	alexa.expect('.*')
	alexa.sendline("wave")
	alexa.expect('.*')
	alexa.sendline("dive")
	alexa.expect('.*')
	alexa.sendline("go")
	alexa.expect('.*')
	alexa.sendline("read")
	alexa.expect('.*')

fp = open("p.txt", 'r')
fc = open("c.txt", 'w')

crawl()
for ptxt in fp.readlines():
	lines = ptxt.split()
	for line in lines:
		alexa.sendline(line)
		alexa.expect("Slowly, a new text starts.*")
		response = str(alexa.after)[73:89]
		print(f"sent: {line}, received: {response}")
		fc.writelines(response + " ")
		alexa.sendline("c")
		alexa.expect("The text in the screen vanishes!", timeout=50)
	fc.write("\n")

alexa.close()
fp.close()
fc.close()
