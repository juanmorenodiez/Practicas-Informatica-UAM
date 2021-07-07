/**
 * Clase Edge la cual define la conexion entre dos
 * nodos del grafo.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.5
 * @since 1.1
 */
public class Edge<T> implements Comparable<Edge<T>>{
	/**
	 * Valor entero de la conexion.
	 */
	private int value;
	/**
	 * Nodo origen de la conexion.
	 */
	private Node<T> origen;
	/**
	 * Nodo destino de la conexion.
	 */
	private Node<T> destino;
	
	/**
	 * Constructor de la clase Edge.
	 * 
	 * @param origen Nodo origen
	 * @param numero Valor numerico del enlace
	 * @param destino Nodo destino
	 */
	public Edge(Node<T> origen, int numero, Node<T> destino) {
		this.origen = origen;
		this.value = numero;
		this.destino = destino;
	}

	/**
	 * Getter del valor numerico
	 * del enlace.
	 * 
	 * @return value
	 */
	public int getValue() {
		return value;
	}

	/**
	 * Setter del valor numerico
	 * del enlace.
	 * 
	 * @param value Valor a setear
	 */
	public void setValue(int value) {
		this.value = value;
	}

	/**
	 * Getter del nodo origen
	 * del enlace.
	 * 
	 * @return origen
	 */
	public Node<T> getOrigen() {
		return origen;
	}

	/**
	 * Setter del nodo origen
	 * del enlace.
	 * 
	 * @param origen Nodo a setear
	 */
	public void setOrigen(Node<T> origen) {
		this.origen = origen;
	}

	/**
	 * Getter del nodo destino
	 * del enlace.
	 * 
	 * @return destino
	 */
	public Node<T> getDestino() {
		return destino;
	}

	/**
	 * Setter del nodo destino
	 * del enlace.
	 * 
	 * @param destino Nodo a setear
	 */
	public void setDestino(Node<T> destino) {
		this.destino = destino;
	}
	
	/**
	 * Metodo compareTo ya que implementamos comparable.
	 * 
	 * @param edge Enlace con el que se va a
	 * comparar.
	 * @return entero con la comparacion
	 * entre enlaces.
	 */
	@Override
	public int compareTo(Edge<T> edge) {
		int origenDiff = this.getOrigen().getId();
		if (origenDiff != 0) return origenDiff;
		int destDeff = this.getDestino().getId();
		if (destDeff != 0) return destDeff;
		int valueDiff = this.value - edge.getValue();
		if (valueDiff != 0) return valueDiff;
		
		return 0;
	}
	

	/**
	 * Metodo toString de la clase
	 * edge.
	 * 
	 * @return String con la informacion
	 * de un enlace.
	 */
	public String toString() {
		return "( " + this.getOrigen().getId() + " --" + this.getValue() + "--> " + this.getDestino().getId() + " )";
	}
}
