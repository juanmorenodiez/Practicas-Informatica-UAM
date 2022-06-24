import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

/**
 * Clase RuleSet almacena un conjunto de reglas que debe cumplir un objeto.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.5
 * @since 1.1
 */
public class RuleSet<T> {
	
	/**
	 * Conjutno de reglas.
	 */
	Set<Rule<T>> rules = new HashSet<Rule<T>>();
	
	/**
	 * Objetos.
	 */
	Collection<T> objs;
	
	/**
	 * Comprueba si los objetos cumplen las reglas.
	 */
	public void process() {
		int flag = 0;
		for (T object : objs) {
			for (Rule<T> regla : this.rules) {
				if(regla.process(object)) {
					flag = 1;
				}
				if (flag == 1) {
					break;
				}
			}
		}
	}
	
	/**
	 * Setter de la colecccion de objetos
	 * @param str Objeto a insertar.
	 */
	public void setExecContext(Collection<T> str) {
		this.objs = str;
	}
	
	/**
	 * Getter de la coleccion de objetos.
	 * @return Objeto.
	 */
	public Collection<T> getExecContext() {
		return objs;
	}
	
	/**
	 * Getter de las reglas.
	 * @return Conjunto de reglas.
	 */
	public Set<Rule<T>> getRules() {
		return rules;
	}
	
	/**
	 * Anade una regla al conjunto de reglas.
	 * @param regla Regla a anadir.
	 * @return Conjunto de reglas modificado.
	 */
	public RuleSet<T> add(Rule<T> regla) {
		this.rules.add(regla);
		return this;
	} 

}
