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
being written to the console and also writes it to a file.
'''
class Tee(object):
	def open(self, name, mode):
		sys.stdout.flush()
		self.file = open(name, mode)
		self.stdout = sys.stdout
		sys.stdout = self
	def close(self):
		sys.stdout = self.stdout
		self.file.close()
	def write(self, data):
		self.file.write(data)
		self.stdout.write(data)
	def flush(self):
		self.file.flush()
		self.stdout.flush()

def kill_proc(proc, timeout):
	# you must have done something wrong
	# to end up here
    timeout["value"] = True
    proc.kill()

# a run with timeout function 
def run_with_timeout(cmd, timeout_sec, stdinput):
    proc = subprocess.Popen(cmd,stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    timeout = {"value": False}
    timer = threading.Timer(timeout_sec, kill_proc, [proc, timeout])
    timer.start()
    (out, err) = proc.communicate(input = stdinput.encode("utf-8"))
    if len(out) < 1000:
    	out = out.decode("utf-8")
    else:
    	#wow you printed a lot of stuff
    	out = out[:1000].decode("utf-8") + "..."
    print(out)
    timer.cancel()
    return proc.returncode, timeout["value"], out

	
def run(cmd, time, stdinput="", testlist = [], scores = [2]):
	print("Running: {}\n".format(cmd))
	try:
		
		# just in case we will kill your process 
		# after <time> seconds
		res, timeout, out = run_with_timeout(cmd, time, stdinput)
	except:
		print("An exception occurred")
		print("{} test failed!".format(cmd))
		return 0
	if timeout:
		print("Taking too long, abort")
		print("Infinite loop?")
		return 0
	if res == 0:
		# program ran and nothing crashed. Check the output
		if len(testlist)==0:
			print("Test passed")
			return scores[0]
		score = 0
		index = 0
		for e in testlist:
			if out.find(e) == -1:
				print(e+" not found")
			else:
				print(e+" found, ",scores[index]," marks")
				score+=scores[index]
			index = index + 1
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
			print("\n\n{stars}\n* Mark: {mark}/{outof}\n".format(stars="*"*75, mark=0, outof=outof))
			return
		
	#"make" should have made 3 executables, p1, p2, and p3
	#this code runs and test them
	score = 0
	
	#substitute with your name if you prefer
	#arguments are:
	#<command, timeout, input, find in output, score per string found>
	score += run("./p1", 5, "Darryl",["Darryl"],[2])
	score += run("./p2", 5, "5 10",["5","10","50"],[1,1,2])
	score += run("./p3", 5, "5 3",["5","3","125"],[1,1,2])
	
	'''
	f = open('p3.cc','r')
	p3 = f.read()
	
	The above is an example. I may read your file in and use a regex to search 
	for specific things that were asked for in the specification.
	'''

	print("\n\n{stars}\n* Mark: {mark}/{outof}\n{stars}\n".format(stars="*"*75, mark=score, outof=outof))



	

def process_all():
	 
	zipfile = '*.zip'
	if len(sys.argv)>1:
		if sys.argv[1].find("-nozip")!=-1:
			zipfile = "nozip"
			
	t = Tee()
	
	t.open('results.txt', 'w')
	dirname = 'tutorial1'
	#dirname = '.'
	unzip_and_test(dirname,zipfile, 10)
		
	t.close()



if __name__ == "__main__":
	
	sys.stdout.flush()
	process_all()
	sys.stdout.flush()
	
