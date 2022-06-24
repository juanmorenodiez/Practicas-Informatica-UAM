import java.util.*;
import java.util.Comparator;
import java.util.function.Predicate;


/**
 * Clase BlackBoxComparator que implementa Comparator. Principalmente
 * implementara el metodo compare para poder comparar grafos segun el 
 * numero de criterias que siguen.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.5
 * @since 1.1
 */

public class BlackBoxComparator<T, E> implements Comparator<ConstrainedGraph<T, E>>{
	/**
	 * Lista donde se almacenarán las criterias unitarias.
	 */
	private List<Criteria> unitarias;
	/**
	 * Lista donde se almacenarán las criterias existenciales.
	 */
	private List<Criteria> existenciales;
	/**
	 * Lista donde se almacenarán las criterias universales.
	 */
	private List<Criteria> universales;
	/**
	 * Lista de predicados asociados a una critera unitaria.
	 */
	private List<Predicate<Node<T>>> unitaryPredicates;
	/**
	 * Lista de predicados asociados a una critera existenciale.
	 */
	private List<Predicate<Node<T>>> existentialPredicates;
	/**
	 * Lista de predicados asociados a una critera universale.
	 */
	private List<Predicate<Node<T>>> universalPredicates;
	
	/**
	 * Constructor de la clase BlackBoxComparator.
	 */
	public BlackBoxComparator() {
		this.unitarias = new ArrayList<Criteria>();
		this.existenciales = new ArrayList<Criteria>();
		this.universales = new ArrayList<Criteria>();
		this.unitaryPredicates = new ArrayList<Predicate<Node<T>>>();
		this.existentialPredicates = new ArrayList<Predicate<Node<T>>>();
		this.universalPredicates = new ArrayList<Predicate<Node<T>>>();
	}
	
	
	/**
	 * Devuelve una magnitud sumada a otra
	 * por argumento.
	 * 
	 * @param g1 Primer grafo a comparar.
	 * @param g2 Segundo grafo a comparar.
	 * @return Comaparacion entre grafos (numero
	 * de criterias).
	 */
	@Override
	public int compare(ConstrainedGraph<T, E> g1, ConstrainedGraph<T, E> g2) {
		/* bucle para recorrer un predicado y ver si cumple un criteria de tipo "one" */
		for (@SuppressWarnings("unused") Criteria un : this.unitarias) {
			for (Predicate<Node<T>> p : this.unitaryPredicates) {
				if (g1.one(p)) {
					g1.addNumCriterias();
				}
				
				if (g2.one(p)) {
					g2.addNumCriterias();
				}
			}
		}
		
		/* bucle para recorrer un predicado y ver si cumple un criteria de tipo "forAll" */
		for (@SuppressWarnings("unused") Criteria uv : this.universales) {
			for (Predicate<Node<T>> p : this.universalPredicates) {
				if (g1.forAll(p)) {
					g1.addNumCriterias();
				}
				
				if (g2.forAll(p)) {
					g2.addNumCriterias();
				}
			}
		}
		
		/* bucle para recorrer un predicado y ver si cumple un criteria de tipo "exists" */
		for (@SuppressWarnings("unused") Criteria ex : this.existenciales) {
			for (Predicate<Node<T>> p : this.existentialPredicates) {
				if (g1.exists(p)) {
					g1.addNumCriterias();
				}
				
				if (g2.exists(p)) {
					g2.addNumCriterias();
				}
			}
		}
		
		int criteriasDiff = g1.getNumCriterias() - g2.getNumCriterias();
		
		if (criteriasDiff != 0) return criteriasDiff;
		
		return 0;
		
	}

	/**
	 * Añade al BlackBoxComparator la criteria que 
	 * se le pasa por argumento y el predicado correspondiente
	 * a esa criteria.
	 * 
	 * @param criteria Criteria a añadir.
	 * @param predicado Predicado a añadir.
	 * @return BlackBoxComparator con las listas de 
	 * criterias y predicados asociados.
	 */
	public BlackBoxComparator<T, E> addCriteria(Criteria criteria, Predicate<Node<T>> predicado) {
		if (criteria.equals(Criteria.UNITARY)) {
			this.unitarias.add(criteria);
			this.unitaryPredicates.add(predicado);
		}
		
		if (criteria.equals(Criteria.EXISTENTIAL)) {
			this.existenciales.add(criteria);
			this.existentialPredicates.add(predicado);
			
		}
		
		if (criteria.equals(Criteria.UNIVERSAL)) {
			this.universales.add(criteria);
			this.universalPredicates.add(predicado);
		}
		
		return this;
	}
	


}
