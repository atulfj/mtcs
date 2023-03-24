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
	alexa.sendline("4")
	alexa.expect('.*')
	alexa.sendline("go")
	alexa.expect('.*')
	alexa.sendline("jump")
	alexa.expect('.*')
	alexa.sendline("jump")
	alexa.expect('.*')
	alexa.sendline("back")
	alexa.expect('.*')
	alexa.sendline("pull")
	alexa.expect('.*')
	alexa.sendline("back")
	alexa.expect('.*')
	alexa.sendline("back")
	alexa.expect('.*')
	alexa.sendline("enter")
	alexa.expect('.*')
	alexa.sendline("wave")
	alexa.expect('.*')
	alexa.sendline("back")
	alexa.expect('.*')
	alexa.sendline("back")
	alexa.expect('.*')
	alexa.sendline("thrnxxtzy")
	alexa.expect('.*')
	alexa.sendline("read")
	alexa.expect('.*')
	alexa.sendline("the_magic_of_wand")
	alexa.expect('.*')
	alexa.sendline("c")
	alexa.expect('.*')
	alexa.sendline("read")
	alexa.expect('.*')
	alexa.sendline("password")
	alexa.expect('.*')
	alexa.sendline("c")
	alexa.expect('The text in the screen vanishes!')

crawl()

fp = open("p1.txt", 'r')
fc = open("c1.txt",'w')

counter = 0

for line in fp.readlines():
	counter += 1
	alexa.sendline(line)
	alexa.expect("Slowly, a new text starts.*")
	print(f"sent: {line}, received: {str(alexa.after)[73:89]}")
	fc.writelines(str(alexa.after)[73:89]+"\n")
	alexa.sendline("c")
	alexa.expect('The text in the screen vanishes!')
	if counter == 10000:
		alexa.close()
		break
	if counter%1000 == 0:
		alexa.close()
		alexa = pexpect.spawn('ssh student@172.27.26.188')
		crawl()
	
fp.close()
fc.close()

fp = open("p2.txt", 'r')
fc = open("c2.txt",'w')

alexa = pexpect.spawn('ssh student@172.27.26.188')
crawl()

counter = 0
for line in fp.readlines():
	counter += 1
	alexa.sendline(line)
	alexa.expect("Slowly, a new text starts.*")
	print(f"sent: {line}, received: {str(alexa.after)[73:89]}")
	fc.writelines(str(alexa.after)[73:89]+"\n")
	alexa.sendline("c")
	alexa.expect('The text in the screen vanishes!')
	if counter == 10000:
		alexa.close()
		break
	if counter%1000 == 0:
		alexa.close()
		alexa = pexpect.spawn('ssh student@172.27.26.188')
		crawl()

fp.close()
fc.close()
