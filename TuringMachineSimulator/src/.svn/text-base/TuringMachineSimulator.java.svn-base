import java.io.*;
import java.util.*;

/**
 * Simulates a Turing Machine
 * @author Moises Osorio
 */
public class TuringMachineSimulator {
	
	private final static int EMPTY = 0;
	
	/**
	 * Map of tuples, indexed by state and then by tape value.
	 */
	private Map<Integer, Map<Integer, Tuple>> tuples;
	/**
	 * The tape.
	 */
	private List<Integer> tape;
	/**
	 * Reader head.
	 */
	private int head;
	
	public TuringMachineSimulator() {
		tuples = new HashMap<Integer, Map<Integer,Tuple>>();
	}
	
	/**
	 * Reads the tuples and tape from the stream.
	 * @param in Input stream.
	 */
	public void readTuplesAndTape(InputStream in) {
		Scanner scan = new Scanner(in);
		int M = scan.nextInt(); // The number of tuples
		while (M-- > 0) {
			Tuple tuple = new Tuple(scan.nextInt(), scan.nextInt(), scan.nextInt(), scan.nextInt(), scan.nextInt());
			Map<Integer, Tuple> state = tuples.get(tuple.q);
			if (state == null) { // Does not exist
				state = new HashMap<Integer, Tuple>();
				tuples.put(tuple.q, state);
			}
			
			if (state.containsKey(tuple.a)) { // Conflict!
				System.err.println("The tuple " + tuple + " conflicts with tuple " + state.get(tuple.a) + ".");
				System.exit(-1);
			}
			
			state.put(tuple.a, tuple); // Add the tuple
		}
		
		tape = new ArrayList<Integer>();
		while (scan.hasNextInt()) // Read all the tape, no need to read the length
			tape.add(scan.nextInt());
	}
	
	/**
	 * Executes the tuples with the given tape.
	 */
	public void execute() {
		Tuple tuple;
		head = 0;
		int state = 0;
		do {
			int value;
			if (head < 0 || head >= tape.size())
				value = EMPTY; // This is an empty position
			else
				value = tape.get(head); // Value of the reader head
			
			Map<Integer, Tuple> tuplesByState = tuples.get(state);
			if (tuplesByState == null) { // No tuple exist for this state
				System.err.println("There is no tuple for the state " + state + ".");
				System.exit(-1);
			}
			
			tuple = tuplesByState.get(value);
			if (tuple == null) { // No tuple exists for this value in this state
				System.err.println("There is no tuple that can handle the state " + state + " with value " + value + ".");
				System.exit(-1);
			}
			
			if (head < 0) { // The head is in the left of all the non-empty values of the tape
				head = 0; // Move the head, relatively is the same
				tape.add(0, tuple.b);
			} else if (head >= tape.size()) // The head is at the end
				tape.add(tuple.b);
			else
				tape.set(head, tuple.b); // Change the head value of the tape
			
			state = tuple.p; // New state
			head += tuple.m; // Move the head of the tape
		} while (tuple.m != 0); // Halt
		
		// Clean the tape removing empty values at the beginning and the end
		while (tape.size() > 0 && tape.get(tape.size()-1) == EMPTY)
			tape.remove(tape.size() - 1);
		while (tape.size() > 0 && tape.get(0) == EMPTY)
			tape.remove(0);
	}
	
	/**
	 * Prints the value read by the head.
	 * @param out Output stream.
	 */
	public void printHead(OutputStream out) {
		PrintWriter writer = new PrintWriter(out);
		int value;
		if (head < 0 || head >= tape.size())
			value = EMPTY; // Out of tape
		else
			value = tape.get(head); // Head value
		
		// Move to next line and flush the output
		writer.println(value);
		writer.flush();
	}
	
	/**
	 * Prints the tape.
	 * @param out Output stream.
	 */
	public void printTape(OutputStream out) {
		PrintWriter writer = new PrintWriter(out);
		for (int i = 0; i < tape.size(); i++) {
			if (i > 0)
				writer.print(" ");
			writer.print(tape.get(i));
		}
		
		// Move to next line and flush the output
		writer.println();
		writer.flush();
	}
	
	/**
	 * Entry point.
	 * @param args Optional: input-file output-file. If not given, standard I/O will be used.
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {
		InputStream in = System.in;
		OutputStream out = System.out;
		if (args.length > 0) {
			try { // Get the input file stream
				in = new FileInputStream(args[0]);
			} catch (FileNotFoundException e) {
				System.err.println("The input file '" + args[0] + "' was not found.");
				System.exit(-1);
			}
			
			if (args.length > 1) {
				try { // Get the output file stream
					out = new FileOutputStream(args[1]);
				} catch (FileNotFoundException e) {
					System.err.println("The output file '" + args[1] + "' was not found.");
					System.exit(-1);
				}
			}
		}
		
		TuringMachineSimulator simulator = new TuringMachineSimulator();
		simulator.readTuplesAndTape(in); // Read the tuples and tape
		simulator.execute(); // Simulate the Turing Machine
		simulator.printHead(out); // Print the head after simulation
		simulator.printTape(out); // Print the tape after simulation
		out.close(); // Close the output stream
	}
	
	/**
	 * Turing Machine tuple.
	 * @author Moises Osorio
	 */
	private class Tuple {
		
		private int a, b, q, p, m;
		
		public Tuple(int q, int a, int p, int b, int m) {
			this.q = q; // End state
			this.a = a; // Read value
			this.p = p; // Initial state
			this.b = b; // Substitute value
			this.m = m; // Direction
		}
		
		@Override
		public String toString() {
			return "(" + q + ", " + a + ", " + p + ", " + b + ", " + m + ")";
		}
	}
}
