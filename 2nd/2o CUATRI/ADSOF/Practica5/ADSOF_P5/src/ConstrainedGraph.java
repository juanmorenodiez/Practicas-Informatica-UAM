import java.util.function.Predicate;
import java.util.Optional;

/**
 * Clase ConstrainedGraph que extiende de grafo e implementa
 * las funcionalidades correspondientes a un ConstrainedGraph.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.5
 * @since 1.1
 */
public class ConstrainedGraph<T, E> extends Graph<T, E>{
	/**
	 * Witness del grafo
	 */
	private Optional<Node<T>> witness;
	
	/**
	 * Numero de criterias asociado al grafo.
	 */
	private Integer num_criterias = 0;
	
	/**
	 * Constructor de la clase ConstrainedGraph.
	 */
	public ConstrainedGraph() {
		super();
	}

	/**
	 * Metodo que comprueba que se cumple
	 * la condicion universal para un predicado
	 * que se introduce como argumento.
	 * 
	 * @param predicado Predicado a comprobar.
	 * @return true si se cumple, false si no.
	 */
	public boolean forAll(Predicate<Node<T>> predicado) {	
		for (Node<T> node : this.getNodos()) {
			if (predicado.test(node) == false) {
				return false;
			}
		}
		
		return true;
	}
	
	/**
	 * Metodo que comprueba que se cumple
	 * la condicion unitaria para un predicado
	 * que se introduce como argumento.
	 * 
	 * @param predicado Predicado a comprobar.
	 * @return true si se cumple, false si no.
	 */
	public boolean one(Predicate<Node<T>> predicado) {
		int flag = 0;
		
		for (Node<T> node : this.getNodos()) {
			if (predicado.test(node) == true) {
				flag += 1;
			}
		}
	
		if (flag == 1) {
			return true;
		}
			
		return false;
	}

	/**
	 * Metodo que comprueba que se cumple
	 * la condicion existencial para un predicado
	 * que se introduce como argumento.
	 * 
	 * @param predicado Predicado a comprobar.
	 * @return true si se cumple, false si no.
	 */
	public boolean exists(Predicate<Node<T>> predicado) {
		for (Node<T> node : this.getNodos()) {
			if (predicado.test(node) == true) {
				witness = Optional.of(node);
				return true;
			}
		}
		witness = Optional.empty();
		return false;
	}
	
	/**
	 * Getter del numero de criterias
	 * de un grafo.
	 * 
	 * @return num_criterias
	 */
	public Integer getNumCriterias() {
		return num_criterias;
	}
	
	/**
	 * Setter del numero de criterias
	 * de un grafo.
	 * 
	 * @param criterias numero de criterias setear
	 */
	public void setNumCriterias(Integer criterias) {
		this.num_criterias = criterias;
	}
	
	/**
	 * Metodo que suma uno al
	 * numero de criterias del grafo.
	 */
	public void addNumCriterias() {
		num_criterias += 1;
	}
	
	/**
	 * Getter que devuelve el witness de 
	 * un grafo.
	 * 
	 * @return Witness del grafo correspondiente.
	 */
	public Optional<Node<T>> getWitness() {
		return this.witness;
	}
	
}
