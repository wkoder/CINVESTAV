package main

import ("fmt"; "os"; "bufio"; "container/vector"; "strings")

type Node struct { // Trie node (http://en.wikipedia.org/wiki/Trie)
	next [10] *Node // Node children
	matchings *vector.StringVector // Node matchings (len > 0 says it's a terminal node)
}

func (node *Node) init() { // Initializes the node
	node.matchings = new(vector.StringVector)
}

type Encoder struct {
	root *Node
}

func (encoder *Encoder) init() { // Initializes the encoder
	encoder.root = new(Node)
	encoder.root.init()
}

func (encoder *Encoder) buildTrie(reader *bufio.Reader) { // Builds the Trie from the dictionary
	var encoding = [26]int {5, 7, 6, 3, 0, 4, 9, 9, 6, 1, 7, 8, 5, 1, 8, 8, 1, 2, 3, 4, 7, 6, 2, 2, 3, 9}
	for {
		str, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		encoder.addToDictionary(str[0 : len(str)-1], encoding)
	}
}

func (encoder *Encoder) addToDictionary(str string, encoding [26]int) { // Adds a word to the Trie
	low := strings.ToLower(str)
	var currnode = encoder.root
	for i := 0; i < len(low); i++ {
		if low[i] >= 'a' && low[i] <= 'z' { // Skip non-letters
			n := encoding[low[i] - 'a']
			if currnode.next[n] == nil { // Build the Trie
				currnode.next[n] = new(Node)
				currnode.next[n].init()
				currnode.next[n].matchings = new(vector.StringVector)
			}
			currnode = currnode.next[n]
		}
	}
	
	currnode.matchings.Push(str) // Adds the word to the final node
}

func (encoder *Encoder) findEncodings(reader *bufio.Reader) { // Finds all the encondings of a list of phone numbers
	for {
		str, err := reader.ReadString('\n')
		if err != nil {
			break
		}
		encoder.findWordEncodings(0, str[0 : len(str)-1], encoder.root, true, "")
	}
}

// Finds the encodings of a phone number given the position and the current node
func (encoder *Encoder) findWordEncodings(pos int, phone string, node *Node, canBeDigit bool, encoding string) {
	if pos == len(phone) { // Finished
		if node != encoder.root {
			return
		}

		fmt.Println(phone + ": " + encoding) // Got a encoding
		return
	}

	if phone[pos] < '0' || phone[pos] > '9' { // Skip non-digits
		encoder.findWordEncodings(pos+1, phone, node, canBeDigit, encoding)
		return
	}

	n := phone[pos] - '0'
	if node.next[n] != nil {
		encoder.findWordEncodings(pos+1, phone, node.next[n], false, encoding) // Keep encoding
		for i := 0; i < node.next[n].matchings.Len(); i++ { // Try each possibility
			e := encoding
			if len(e) > 0 {
				e += " "
			}
			// Start again from the root
			encoder.findWordEncodings(pos+1, phone, encoder.root, true, e + node.next[n].matchings.At(i))
		}
	}

	if canBeDigit && !encoder.wordStarts(pos, phone) { // Can we put a digit here?
		e := encoding
		if len(e) > 0 {
			e += " "
		}
		encoder.findWordEncodings(pos+1, phone, encoder.root, false, e + string(phone[pos])) // Start encoding again
	}
}

// Checks if a word starts from the given position in the phone number
func (encoder *Encoder) wordStarts(pos int, phone string) bool {
	var node = encoder.root
	for ; pos < len(phone); pos++ {
		if phone[pos] >= '0' && phone[pos] <= '9' { // Just digits
			if node.matchings.Len() > 0 { // There is such word
				return true
			}
			n := phone[pos] - '0'
			if node.next[n] == nil { // No word starts from the position
				return false
			}
			node = node.next[n]
		}
	}

	return node.matchings.Len() > 0 // Is there a word?
}

// Args: dictionary.in phone-numbers.in
func main() {
	dict, error := os.Open(os.Args[1], os.O_RDONLY, 0666)
	if error != nil {
		return
	}
	
	phones, error := os.Open(os.Args[2], os.O_RDONLY, 0666)
	if error != nil {
		return
	}

	var encoder Encoder
	encoder.init()
	encoder.buildTrie(bufio.NewReader(dict))
	encoder.findEncodings(bufio.NewReader(phones))
}

