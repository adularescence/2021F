#!/usr/bin/python3
import os
import signal
import sys
import tempfile
import subprocess
import glob
import shutil
import re
import time
import csv
import threading

'''
This class takes the place of sys.stdout. It intercepts whatever is
being written to the console and writes it the console, a file, and
a local data structure.
In other words, whatever you print here or in your program also
prints to the file and to a list. The list can then be searched for 
proper output. 
'''
class Tee(object):
	def open(self, name, mode):
		sys.stdout.flush()
		self.file = open(name, mode)
		self.stdout = sys.stdout
		sys.stdout = self
		#self.data = []
	def close(self):
		sys.stdout = self.stdout
		self.file.close()
	def write(self, data):
		self.file.write(data)
		self.stdout.write(data)
		#if data != '\n':
			#self.data.append(data)
	def flush(self):
		self.file.flush()
		self.stdout.flush()
		
verbose = False

def kill_proc(proc, timeout):
	# you must have done something wrong
	# to end up here
	timeout["value"] = True
	proc.kill()

# a run with timeout function 
def run_with_timeout(cmd, timeout_sec, stdinput):
	#print("Running: ",cmd)
	proc = subprocess.Popen(cmd,stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	timeout = {"value": False}
	timer = threading.Timer(timeout_sec, kill_proc, [proc, timeout])
	timer.start()
	(out, err) = proc.communicate(input = stdinput.encode("utf-8"))
	out = out.decode("utf-8")
	err = err.decode("utf-8")
	if len(out) < 1000:
		print(out)
	else:
		#wow you printed a lot of stuff
		print(out[:1000] + "...")
	if verbose:
		print(err)
	timer.cancel()
	return proc.returncode, timeout["value"], out, err

	
def run(cmd, time, stdinput="", testlist = []):
	#print("Running: {}\n".format(cmd))
	print("Executing: {}".format(" ".join(cmd)))
	try:
		
		# just in case we will kill your process 
		# after <time> seconds
		res, timeout, out, err = run_with_timeout(cmd, time, stdinput)
	except:
		print("An exception occurred")
		print("{} test failed!".format(" ".join(cmd)))
		return 0
	if timeout:
		print("Taking too long, abort")
		print("Could be an infinite loop or segmentation fault")
		return 0
	if res == 0:
		# program ran and nothing crashed. Check the output
		if len(testlist)==0:
			print("Test passed")
			return 2
		score = 0
		#save the last thing written to cout
		for e in testlist:
			if (out.find(e) == -1 and err.find(e) == -1):
				print(e+" not found")
			else:
				print(e+" found, 2 marks")
				score+=2
		return score
	else: 
		print("Program exited with non-zero status, test failed")
	return 0

def unzip_and_test(dirname, zipfile, outof):

	# Unzip the zip file. If you pass a '-nozip' flag, skip
	# If we attempt to unzip and fail, exit with 0 marks
	if zipfile == "*.zip":
		print("{}\n* Unzipping {}\n{}".format("*"*75, zipfile, "*"*75))
		sys.stdout.flush()
		status = subprocess.call(["unzip", "-n", zipfile])
		if status != 0:
			print("unzip exited with non-zero status")
			print("\n\n{stars}\n* Mark: {mark}/{outof}\n".format(stars="*"*75, mark=0, outof=outof))
			return
		
		
	#unzipping successful
	#switch to directory dirname
	os.chdir(dirname)
	sys.stdout.flush()
	print("\n{stars}\n* Compilation\n{stars}".format(stars="*"*75))
	
	# run the 'make clean' and 'make all' commands
	cmds = ["clean","all"]
	for c in cmds:
		cmd = ["make",c]
		print("Executing: {}".format(" ".join(cmd)))
		res = subprocess.call(cmd)
		sys.stdout.flush()
		if res:
			# make command produced an error
			# return with 0 marks
			print("make: non-zero exit status {}".format(res))
			#print("\n\n{stars}\n* Mark: {mark}/{outof}\n".format(stars="*"*75, mark=0, outof=outof))
			#return
		
	score = 0
	
	#arguments are:
	#<command, timeout, input, find in output, score per string found>
		
	#args=['0','1','2']
	#out = ['Podcast class','Podcast destructor', 'Podcast deep copy']
	
		
	print("\nTesting Podcast class\n")
	score += run(["./test"], 5, '0', ["Dogs", "Episode Title: 3"])
	print("\nTesting Podcast destructor\n")
	score += run(["valgrind","./test"], 5, '1', ["All heap blocks were freed -- no leaks are possible"])
	print("\nTesting Podcast deep copy\n")
	score += run(["./test"], 5, '2', ["Cats", "Vestibulum sapien"])

	print("\n\n{stars}\n* Mark: {mark}/{outof}\n{stars}\n".format(stars="*"*75, mark=score, outof=outof))



	

def process_all():
	global verbose
	zipfile = '*.zip'
	if len(sys.argv)>1:
		for i in range(1, len(sys.argv)):
			if sys.argv[i].find("-nozip")!=-1:
				zipfile = "nozip"
			if sys.argv[i].find("-v")!=-1 or sys.argv[i].find("-verbose")!=-1:
				verbose = True 
			
	t = Tee()
	
	
	
	t.open('results.txt', 'w')
	
	dirname = 'tutorial5'
	#dirname = '.'
	unzip_and_test(dirname,zipfile, 10)
		
	t.close()




if __name__ == "__main__":
	
	sys.stdout.flush()
	process_all()
	sys.stdout.flush()
	
