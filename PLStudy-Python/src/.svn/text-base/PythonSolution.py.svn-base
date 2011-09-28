#! /usr/bin/python

import sys
import string

# Number encoding
ENCODING = [5, 7, 6, 3, 0, 4, 9, 9, 6, 1, 7, 8, 5, 1, 8, 8, 1, 2, 3, 4, 7, 6, 2, 2, 3, 9]

# Trie node (http://en.wikipedia.org/wiki/Trie)
class Node:
	def __init__(self):
		self.matchings = []
		self.next = [None] * 10

#Encodes a phone number based on a dictionary (http://www.flownet.com/ron/papers/lisp-java)
class Encoder:
	def __init__(self):
		self.root = Node()
		
	# Process the dictionary
	def processDictionary(self, f):
		for line in f:
			self.addToDictionary(line[0:len(line)-1])

	# Finds all the encodings of a list of phone numbers
	def findEncodings(self, f):
		for line in f:
			self.findWordEncodings(0, line[0:len(line)-1], self.root, True, [])

	# Adds a single word to the dictionary
	def addToDictionary(self, word):
		node = self.root
		for ch in word:
			if ch in string.ascii_letters: # Skip non-letters
				n = ENCODING[ord(ch.lower()) - ord('a')] # Normalized value (0, 25)
				if node.next[n] == None:
					node.next[n] = Node()
				node = node.next[n] # Build the trie
		node.matchings.append(word)

	# Finds all the encodings of a phone number from the given position and node
	def findWordEncodings(self, position, phone, node, canBeDigit, encoding):
		if position == len(phone): # We finished
			if node != self.root:
				return
			print phone + ": " + " ".join(encoding) # We got a good encoding
			return

		if phone[position] not in string.digits: # Skip non-digits
			self.findWordEncodings(position+1, phone, node, canBeDigit, encoding)
			return
		
		n = int(phone[position]) # Value of digit
		if node.next[n] != None: # We have a valid path
			self.findWordEncodings(position+1, phone, node.next[n], False, encoding) # Continue matching inside the trie
			for match in node.next[n].matchings:
				encoding.append(match)
				self.findWordEncodings(position+1, phone, self.root, True, encoding) # Start encoding again
				encoding.pop()

		if canBeDigit and not self.wordStarts(position, phone): # We can put a digit
			encoding.append(phone[position])
			self.findWordEncodings(position+1, phone, node, False, encoding) # Start encoding again
			encoding.pop()

	# Checks if a word from the dictionary starts from the given position at the phone number
	def wordStarts(self, position, phone):
		node = self.root
		while position < len(phone):
			if node == None:
				return False
			if len(node.matchings) > 0: # There is at least one matching
				return True
			if phone[position] not in string.digits: # Skip non-digits
				position = position + 1
				continue
			n = int(phone[position])
			node = node.next[n] # Keep matching in the Trie
			position = position + 1

		return node != None and len(node.matchings) > 0 # Did we end matching?

# Args: dictionary.in phone-numbers.in
if __name__ == "__main__":
	encoder = Encoder()
	encoder.processDictionary(open(sys.argv[1]))
	encoder.findEncodings(open(sys.argv[2]))

