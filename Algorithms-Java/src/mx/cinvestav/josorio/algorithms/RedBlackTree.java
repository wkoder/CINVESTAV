package mx.cinvestav.josorio.algorithms;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Red black tree implementation.
 * @author Moises Osorio
 */
public class RedBlackTree<T extends Comparable<T>> {
	
	private Node root;

	public RedBlackTree() {

	}
	
	/**
	 * InsercionArborea algorithm.
	 * @param z Node to insert
	 */
	private void treeInsertion(Node z) {
		Node node = root;
		Node p = null;
		while (node != null) {
			p = node;
			p.size++;
			if (z.value.compareTo(node.value) < 0)
				node = node.left;
			else
				node = node.right;
		}
		
		z.parent = p;
		if (p == null)
			root = z;
		else if (z.value.compareTo(p.value) < 0)
			p.left = z;
		else
			p.right = z;
	}

	/**
	 * Checks if a is a left node.
	 * @param a Node to check.
	 * @return If a is a left node.
	 */
	private boolean isLeft(Node a) {
		return a.parent != null && a.parent.left == a;
	}

	/**
	 * Checks if a is a right node.
	 * @param a Node to check.
	 * @return If a is a right node.
	 */
	private boolean isRight(Node a) {
		return a.parent != null && a.parent.right == a;
	}
	
	/**
	 * Gets the size of the node.
	 * @param x
	 * @return
	 */
	private int size(Node x) {
		return x == null? 0 : x.size;
	}

	/**
	 * Rotates the tree from x to the left
	 * @param x
	 */
	private void rotateLeft(Node x) {
		Node y = x.right;
		x.right = y.left;
		if (y.left != null)
			y.left.parent = x;
		y.parent = x.parent;
		if (x.parent == null)
			root = y;
		else {
			if (x == x.parent.left)
				x.parent.left = y;
			else
				x.parent.right = y;
		}
		
		y.left = x;
		x.parent = y;
		
		y.size = size(x);
		x.size = size(x.left) + size(x.right) + 1;
	}
	
	/**
	 * Rotates the tree from y to the right.
	 * @param y
	 */
	private void rotateRight(Node y) {
		Node x = y.left;
		y.left = x.right;
		if (x.right != null)
			x.right.parent = y;
		x.parent = y.parent;
		if (y.parent == null)
			root = x;
		else {
			if (y == y.parent.right)
				y.parent.right = x;
			else
				y.parent.left = x;
		}
		
		x.right = y;
		y.parent = x;
		
		x.size = size(y);
		y.size = size(y.left) + size(y.right) + 1;
	}
	
	/**
	 * InsercionRN algorithm.
	 * @param value Value to add.
	 */
	public void add(T value) {
		Node x = new Node(value);
		treeInsertion(x);
		x.color = 1; // Red
		Node parent = x.parent;
		
		while (x != root && parent.color == 1) { // Parent is red
			boolean isLeft = isLeft(parent);
			Node uncle;
			if (isLeft)
				uncle = parent.parent.right;
			else
				uncle = parent.parent.left;
			
			if (uncle != null && uncle.color == 1) { // Uncle is red
				parent.color = 0; // Black
				uncle.color = 0; // Black
				x = parent.parent;
				x.color = 1; // Red
				parent = x.parent;
			} else { // Uncle is black
				if (isLeft) {
					if (x == parent.right) {
						x = parent;
						rotateLeft(parent);
					}
				} else {
					if (x == parent.left) {
						x = parent;
						rotateRight(parent);
					}
				}
				
				parent.color = 0; // Black
				parent.parent.color = 1; // Red
				if (isLeft)
					rotateRight(parent.parent);
				else
					rotateLeft(parent.parent);
			}
		}
		
		root.color = 0; // Black
	}
	
	/**
	 * Finds the node with the given value.
	 * @param value Value to find.
	 * @param node Root of the current subtree.
	 * @return The node found.
	 */
	private Node find(T value, Node node) {
		if (node == null)
			return null;
		
		int cmp = node.value.compareTo(value);
		if (cmp == 0) // This is it!
			return node;
		else if (cmp < 0) // Right subtree
			return find(value, node.right);
		else // Left subtree
			return find(value, node.left);
	}
	
	/**
	 * MinimoArboreo algorithm.
	 * @param x
	 * @return
	 */
	private Node minimum(Node x) {
		Node max = x;
		while (max.left != null)
			max = max.left;
		
		return max;
	}
	
	/**
	 * SucesorArboreo Algorithm.
	 * @param x
	 * @return
	 */
	private Node treeSuccessor(Node x) {
		Node node = x;
		Node p;
		if (node.right != null)
			p = minimum(node.right);
		else {
			p = node.parent;
			while (p != null && node == p.left) {
				node = p;
				p = node.parent;
			}
		}
		
		return p;
	}
	
	/**
	 * SupresionRN algorithm.
	 * @param value Value to remove.
	 */
	public void remove(T value) {
		Node z = find(value, root);
		if (z == null)
			return;
		
		Node overlap;
		if (z.left == null || z.right == null)
			overlap = z;
		else
			overlap = treeSuccessor(z);
		
		Node son;
		if (overlap.left != null)
			son = overlap.left;
		else
			son = overlap.right;
		
		son.parent = overlap.parent;
		if (overlap.parent == null)
			root = son;
		else {
			if (overlap == overlap.parent.left)
				overlap.parent.left = son;
			else
				overlap.parent.right = son;
		}
		
		if (overlap != z)
			z.value = overlap.value;
		
		if (overlap.color == 0) // Black
			adjustRemove(son);
	}
	
	/**
	 * AjustarSupresionRN algorithm.
	 * @param node
	 */
	private void adjustRemove(Node x) {
		while (x != root && x.color == 0) { // Black
			Node parent = x.parent;
			boolean isLeft = isLeft(x);
			
			Node brother;
			if (isLeft)
				brother = x.parent.right;
			else
				brother = x.parent.left;
			if (brother.color == 1) { // Red
				brother.color = 0; // Black
				if (isLeft) {
					rotateLeft(parent);
					brother = parent.right;
				} else {
					rotateRight(parent);
					brother = parent.left;
				}
			}
			
			if (brother.left != null && brother.left.color == 0 && 
					brother.right != null && brother.right.color == 0) { // Both are black
				brother.color = 1; // Red
				x = parent;
			} else {
				if (isLeft) {
					if (brother.right.color == 0) { // Black
						brother.color = 1; // Red
						rotateLeft(brother);
						brother = parent.right;
					}
				} else {
					if (brother.left.color == 0) { // Black
						brother.color = 1; // Red
						rotateRight(brother);
						brother = parent.left;
					}
				}
				
				brother.color = parent.color;
				parent.color = 0; // Black
				if (isLeft) {
					brother.right.color = 0; // Black
					rotateLeft(parent);
				} else {
					brother.left.color = 0; // Black
					rotateRight(parent);
				}
				
				x = root;
			}
		}
	}
	
	/**
	 * Adjusts the size of the subtree at x.
	 * @param x
	 * @return
	 */
	private int adjustSize(Node x) {
		if (x == null)
			return 0;
		
		return x.size = adjustSize(x.left) + adjustSize(x.right) + 1;
	}
	
	/**
	 * Gets the inorder list of the tree.
	 * @return
	 */
	public List<T> getInorder() {
		List<T> order = new ArrayList<T>();
		inorder(root, order);
		return order;
	}
	
	/**
	 * Inorder traversal.
	 * @param node
	 * @param order
	 */
	private void inorder(Node node, List<T> order) {
		if (node == null)
			return;
		
		inorder(node.left, order);
		order.add(node.value);
		inorder(node.right, order);
	}
	
	/**
	 * Selects the element with order i.
	 * @param i
	 * @return
	 */
	public T getSelection(int i) {
		return select(root, i);
	}
	
	/**
	 * Gets the rank of the given value.
	 * @param value
	 * @return
	 */
	public int getRank(T value) {
		Node x = find(value, root);
		if (x == null)
			return -1;
		
		return rank(x);
	}
	
	/**
	 * SeleccionOM algorithm.
	 * @param x
	 * @param i
	 * @return
	 */
	private T select(Node x, int i) {
		if (x == null)
			return null;
		
		int j = size(x.left) + 1;
		if (i == j)
			return x.value;
		
		if (i < j)
			return select(x.left, i);
		
		return select(x.right, i - j);
	}
	
	/**
	 * RangoOM algorithm.
	 * @param x
	 * @return
	 */
	private int rank(Node x) {
		int r = size(x.left) + 1;
		Node y = x;
		while (y != root) {
			if (isRight(y))
				r += size(y.parent.left) + 1;
			
			y = y.parent;
		}
		
		return r;
	}
	
	/**
	 * Internal node of the tree.
	 */
	private class Node {
		private T value;
		private Node parent;
		private Node left;
		private Node right;
		private int color;
		private int size;
		
		public Node(T value) {
			this.value = value;
			size = 1;
		}
		
		@Override
		public String toString() {
			return value.toString();
		}
	}
	
	/**
	 * Receives a list of integers to sort them using a red black tree.
	 * @param args
	 */
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		RedBlackTree<Integer> tree = new RedBlackTree<Integer>();
		int n = scan.nextInt();
		for (int i = 0; i < n; i++) {
			int k = scan.nextInt();
			tree.add(k);
		}
		
		for (int i = 0; i < n; i++)
			System.out.print(tree.getSelection(i+1) + " ");
		System.out.println();
		
		for (int i = 0; i < n; i++) {
			Integer value = tree.getSelection(i+1);
			System.out.print(tree.getRank(value) + " ");
		}
		System.out.println();
	}
	
}
