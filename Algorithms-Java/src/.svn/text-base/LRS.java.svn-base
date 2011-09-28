/*************************************************************************
 *  Compilation:  javac LRS.java
 *  Execution:    java LRS < file.txt
 *  Dependencies: StdIn.java SuffixArray.java
 *  Data files:   http://algs4.cs.princeton.edu/63suffix/tinyTale.txt
 *                http://algs4.cs.princeton.edu/63suffix/mobydick.txt
 *  
 *  Reads a text string from stdin, replaces all consecutive blocks of
 *  whitespace with a single space, and then computes the longest
 *  repeated substring in that text using a suffix array.
 * 
 *  % java LRS < tinyTale.txt 
 *  'st of times it was the '
 *
 *  % java LRS < mobydick.txt
 *  ',- Such a funny, sporty, gamy, jesty, joky, hoky-poky lad, is the Ocean, oh! Th'
 * 
 *  % java LRS 
 *  aaaaaaaaa
 *  'aaaaaaaa'
 *
 *  % java LRS
 *  abcdefg
 *  ''
 *
 *************************************************************************/


public class LRS {

    public static void main(String[] args) {
    	while (StdIn.hasNextLine()) {
	        String text = StdIn.readLine().replaceAll("\\s+", "");
	        SuffixArray sa = new SuffixArray(text);
	        int N = sa.length();
	        
	        if (N <= 1) {
	        	StdOut.println(text);
	        	continue;
	        }
//	        StdOut.println(sa.select(0));
//	        for (int i = 1; i < N; i++) {
//	        	StdOut.println(sa.select(i) + " - " + sa.lcp(i));
//	        }
	
	        String lrs = sa.select(N-1).substring(0, sa.lcp(N-1)+1);
	        for (int i = 1; i < N; i++) {
	            int length = sa.lcp(i);
	            if (length < sa.select(i-1).length()) {
	            	length = Math.max(length, i == 1 ? -1 : sa.lcp(i-1)) + 1;
	            	String lrs2 = sa.select(i-1).substring(0, length);
	            	if (length < lrs.length() || (length == lrs.length() && lrs2.compareTo(lrs) < 0)) {
		                lrs = lrs2;
//		                System.out.println("..." + lrs+ " - " + i);
	            	}
	            }
	        }
	        
	        StdOut.println(lrs);
	    }
    }
}
