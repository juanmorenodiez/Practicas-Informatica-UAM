import java.util.*;

/**
 * Clase Graph que define el objeto Grafo. En este caso
 * tendremos un conjunto de enlaces y un conjunto
 * de nodos.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.5
 * @since 1.1
 */
public class Graph<T, E> implements Collection<Node<T>>{
	/**
	 * Conjunto de nodos.
	 */
	private Set<Node<T>> nodos;
	/**
	 * Conjunto de enlaces.
	 */
	private Set<Edge<T>> enlaces;
	
	/**
	 * Constructor de la clase Graph
	 */
	public Graph() {
		this.nodos = new TreeSet<Node<T>>();
		this.enlaces = new TreeSet<Edge<T>>();
	}
	
	/**
	 * Metodo que añade un nodo
	 * al conjunto de nodos del
	 * grafo.
	 * 
	 * @param e Nodo a añadir.
	 * @return true si se añade, false si no.
	 */
	@Override
	public boolean add(Node<T> e) {
		return nodos.add(e);
	}

	/**
	 * Metodo que añade una coleccion
	 * entera al conjunto de nodos del
	 * grafo.
	 * 
	 * @param c Coleccion de nodos a añadir.
	 * @return true si se añaden, false si no.
	 */
	@Override
	public boolean addAll(Collection<? extends Node<T>> c) {
		return nodos.addAll(c);
	}
	
	/**
	 * Metodo que permite la iteracion en 
	 * la clase grafo sobre su conjunto
	 * de nodos.
	 * 
	 * @return Iterador de nodos.
	 */
	@Override
	public Iterator<Node<T>> iterator() {
		return nodos.iterator();
	}

	/**
	 * Metodo que convierte en Array
	 * un cojunto de nodos.
	 * 
	 * @return Array con los nodos.
	 */
	@Override
	public Object[] toArray() {
		return nodos.toArray();
	}

	@Override
	public void clear() {
		// TODO Auto-generated method stub
	}

	@Override
	public boolean contains(Object arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean containsAll(Collection<?> arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isEmpty() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean remove(Object arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean removeAll(Collection<?> arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean retainAll(Collection<?> arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return 0;
	}

	/**
	 * Metodo que conecta dos nodos
	 * creando un enlace
	 * 
	 * @param n1 Nodo origen
	 * @param i valor del enlace
	 * @param n2 Nodo destino
	 */
	public void connect(Node<T> n1, int i, Node<T> n2) {
		Edge<T> enlace = new Edge<T>(n1, i, n2);
		this.getEnlaces().add(enlace);
		n1.getEnlaces().add(enlace);
		n2.getEnlaces().add(enlace);
		
	}

	/**
	 * Getter del conjunto de nodos
	 * del grafo.
	 * 
	 * @return num_criterias
	 */
	public Set<Node<T>> getNodos() {
		return nodos;
	}

	/**
	 * Setter del conjunto de nodos
	 * del grafo.
	 * 
	 * @param nodos Conjunto de nodos a setear
	 */
	public void setNodos(Set<Node<T>> nodos) {
		this.nodos = nodos;
	}
	
	/**
	 * Getter del conjunto de enlaces
	 * del grafo.
	 * 
	 * @return enlaces
	 */
	public Set<Edge<T>> getEnlaces() {
		return enlaces;
	}

	/**
	 * Setter del conjunto de enlaces
	 * del grafo.
	 * 
	 * @param enlaces Conjunto de enlaces a setear
	 */
	public void setEnlaces(Set<Edge<T>> enlaces) {
		this.enlaces = enlaces;
	}
	
	
	@SuppressWarnings("hiding")
	@Override
	public <T> T[] toArray(T[] a) {
		// TODO Auto-generated method stub
		return null;
	}
	
	/**
	 * Metodo toString de la clase
	 * Graph.
	 * 
	 * @return String con la informacion
	 * de un grafo.
	 */
	public String toString() {
		String ret = null;
		
		ret = "Nodes:\n";
		for (Node<T> n : this.nodos) {
			ret += n.getId() + "[" + n.getValue() + "]\n";
		}
		
		ret += "Edges:\n";
		
		for (Edge<T> e : this.enlaces) {
			ret += "( " + e.getOrigen().getId() + " --" + e.getValue() + "--> " + e.getDestino().getId() + " )\n";
		}
		
		return ret;
		
	}
}
