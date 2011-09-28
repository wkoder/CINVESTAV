import java.io.*;
import java.util.*;

public class Main {
	
	private static int MAX = 200;
	private static int[] ENCODING = new int[]{5, 7, 6, 3, 0, 4, 9, 9, 6, 1, 7, 8, 5, 1, 8, 8, 1, 2, 3, 4, 7, 6, 2, 2, 3, 9};
	
	private Node root;
	private char[] buffer;
	private PrintWriter out;
	
	public Main() {
		root = new Node();
		buffer = new char[MAX];
	}
	
	public void sort() {
		root.sort(new Comparator<char[]>() {
			public int compare(char[] a, char[] b) {
				for (int i = 0; i < a.length && i < b.length; i++)
					if (a[i] < b[i])
						return -1;
					else if (a[i] > b[i])
						return 1;
				return a.length - b.length;
			}
		});
	}
	
	public void addWordToDictionary(String word) {
		Node current = root; // Root of the trie (suffix tree)
		for (int i = 0; i < word.length(); i++) {
			char ch = word.charAt(i);
			if (!Character.isLetter(ch)) // We skip non-letters
				continue;
			
			int n = ENCODING[Character.toLowerCase(ch) - 'a'];
			if (current.next[n] == null) // Select next branch
				current.next[n] = new Node();
			
			current = current.next[n];
		}
		
		current.matchings.add(word.toCharArray()); // Adds current matching to the end of the trie branch.
	}
	
	public void findEncodings(String phone) {
		if (!findEncodingsAt(0, phone.toCharArray(), 0, root, true))
			out.println(phone + " cannot be encoded.");
	}
	
	private boolean findEncodingsAt(int position, char[] phone, int bufferPosition, Node node, boolean canBeDigit) {
		System.out.println("Pos " + position + " : " + new String(phone));
		if (position == phone.length) {
			if (node != root) // Non-terminal node
				return false;
			
			out.print(phone);
			out.print(": ");
			for (int i = 0; i < bufferPosition; i++)
				out.print(buffer[i]);
			out.println();
			
			return true;
		}
		
		if (!Character.isDigit(phone[position])) // Skip non-digits
			return findEncodingsAt(position+1, phone, bufferPosition, node, canBeDigit);
		
		int n = phone[position] - '0';
		boolean ok = false;
		if (node.next[n] != null) { // A word still matches
			ok |= findEncodingsAt(position+1, phone, bufferPosition, node.next[n], false);

			for (char[] match : node.next[n].matchings) {
				int bufPos = bufferPosition;
				if (bufPos > 0)
					buffer[bufPos++] = ' ';
				for (int i = 0; i < match.length; i++, bufPos++)
					buffer[bufPos] = match[i];
				
				ok |= findEncodingsAt(position+1, phone, bufPos, root, true); // Deep in the branch
			}
		}
		
		return ok;
	}
	
	private class Node {
		private List<char[]> matchings;
		private Node[] next;
		
		public Node() {
			matchings = new ArrayList<char[]>();
			next = new Node[10];
		}
		
		public void sort(Comparator<char[]> comp) {
			Collections.sort(matchings, comp);
			for (Node n : next)
				if (n != null)
					n.sort(comp);
		}
	}
	
	public static void main(String[] args) throws NumberFormatException, IOException {
		long s = System.currentTimeMillis();
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
		int cases = Integer.parseInt(in.readLine());
		for (int c = 1; c <= cases; c++) {
			out.println("Scenario #" + c + ":");
			Main encoder = new Main();
			encoder.out = out;
			int d = Integer.parseInt(in.readLine());
			while (d-- > 0)
				encoder.addWordToDictionary(in.readLine());
			System.out.println("Add: " + (System.currentTimeMillis()-s));
			encoder.sort();
			System.out.println("Sort: " + (System.currentTimeMillis()-s));
			int w = Integer.parseInt(in.readLine());
			while (w-- > 0)
				encoder.findEncodings(in.readLine());
			System.out.println("find: " + (System.currentTimeMillis()-s));
			out.println();
		}
		out.flush();
		System.out.println(System.currentTimeMillis()-s);
	}
}
