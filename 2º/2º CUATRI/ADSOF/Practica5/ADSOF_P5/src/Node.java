import java.util.*;

/**
 * Clase Node que implementa Comparable. Almacena la informacion de un nodo
 * que posteriormente se introduciran en los grafos.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.4
 * @since 1.1
 */
public class Node<T> implements Comparable<Node<T>>{
	
	/**
	 * Valor del nodo.
	 */
	private T value;
	
	/**
	 * Id del nodo.
	 */
	private Integer id;
	
	/**
	 * Enlaces del nodo.
	 */
	private Set<Edge<T>> enlaces;
	
	/**
	 * Numero del Id del nodo.
	 */
	public static int num_id;
	
	/**
	 * Constructor del nodo.
	 * @param value valor del nodo.
	 */
	public Node(T value) {
		this.value = value;
		if (id == null) {
			this.id = Node.num_id;
		}
		
		this.enlaces = new TreeSet<Edge<T>>();
		Node.num_id += 1;
	}
	
	/**
	 * Getter del valor del nodo.
	 * @return valor del nodo.
	 */
	public T getValue() {
		return value;
	}

	/**
	 * Setter del valor del nodo.
	 * @param value Valor del nodo.
	 */
	public void setValue(T value) {
		this.value = value;
	}
	
	/**
	 * Getter del id del nodo.
	 * @return Id del nodo.
	 */
	public Integer getId() {
		return id;
	}

	/**
	 * Setter del Id del nodo.
	 * @param id Id del nodo.
	 */
	public void setId(Integer id) {
		this.id = id;
	}
	
	/**
	 * Getter de los enlaces del nodo.
	 * @return Enlaces del nodo.
	 */
	public Set<Edge<T>> getEnlaces() {
		return enlaces;
	}

	/**
	 * Setter de los enlaces del nodo.
	 * @param enlaces Enlaces del nodo.
	 */
	public void setEnlaces(Set<Edge<T>> enlaces) {
		this.enlaces = enlaces;
	}
	
	/**
	 * COmprueba si dos nodos estan conectados
	 * @param node Uno de los nodos a revisar su conectividad.
	 * @return true si estan conectados flase si no lo estan.
	 */
	public boolean isConnectedTo(Node<T> node) {
		for (Edge<T> edge : this.getEnlaces()) {
			if((edge.getOrigen().equals(this) && edge.getDestino().equals(node))) {
				return true;
			}
		}
		return false;
	}

	/**
	 * COmprueba si dos elementos estan conectados
	 * @param node Uno de los elementos a revisar su conectividad.
	 * @return true si estan conectados flase si no lo estan.
	 */
	public boolean isConnectedTo(T element) {
		for (Edge<T> edge : this.getEnlaces()) {
			if((edge.getOrigen().getValue().equals(this.getValue()) && edge.getDestino().getValue().equals(element))) {
				return true;
			}
		}
		return false;
	}


	/**
	 * Obtiene los vecinos del nodo.
	 * @return Vecinos de los nodos.
	 */
	public Set<Node<T>> neighbours() {
		Set<Node<T>> vecinos = new TreeSet<>();
		for(Edge<T> enlaces : this.getEnlaces()) {
			if (this.isConnectedTo(enlaces.getDestino())) {
				vecinos.add(enlaces.getDestino());
			}
		}
		
		return vecinos;
	}

	/**
	 * Getter de los valores de los enlaces del nodo.
	 * @param n2 Nodo a revisar.
	 * @return Enlaces del nodo.
	 */
	public Set<Integer> getEdgeValues(Node<T> n2) {
		Set<Integer> valores = new HashSet<>();
		for(Edge<T> enlaces : this.getEnlaces()) {
			if (this.isConnectedTo(n2) == true) {
				valores.add(enlaces.getValue());
			}
		}
		return valores;
	}
	
	/**
	 * Compara un nodo con otro nodo.
	 * @param node Uno de los nodos a comparar.
	 * @return la diferencia entre los ids de los nodos.
	 */
	@Override
	public int compareTo(Node<T> node) {
		int idDiff = this.id - node.getId();
		if (idDiff != 0) return idDiff;
		
		return 0;
	}
	
	/**
	 * Segundo tostring del nodo.
	 * @return
	 */
	public String get() {
		return this.getId() + " [" + this.getValue() + "]"; 
	}
	
	/**
	 * Metodo toString del nodo.
	 * @return
	 */
	public String toString() {
		return this.getId() + "[" + this.getValue() + "]";
	}

}
