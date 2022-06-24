import java.util.function.Consumer;
import java.util.function.Predicate;

/**
 * Clase rule.java que implementa la reglas que se le aplican a un grafo con
 * sus correspondientes predicados.
 * 
 * @author Diego cano y Juan Moreno
 * @version 1.6
 * @since 1.1
 */
public class Rule<T> {
	
	/**
	 * Id de la regla.
	 */
	private String id;
	
	/**
	 * Tipo de la regla.
	 */
	private String tipo;
	
	/**
	 * Predicado de la regla.
	 */
	private Predicate<T> condicion;
	
	/**
	 * Resultado de la regla.
	 */
	private Consumer<T> resultado;

	/**
	 * Constructor de la regla.
	 * @param id Id de la regla.
	 * @param tipo Tipo de la regla.
	 */
	public Rule(String id, String tipo) {
		this.id = id;
		this.tipo = tipo;
	}
	
	/**
	 * Segundo Constructor de la regla.
	 * @param <T> Regla a ser almacenada.
	 * @param id Id de la regla.
	 * @param tipo Tipo de la regla.
	 * @return Regla nueva.
	 */
	public static <T> Rule<T> rule(String id, String tipo) {
		Rule<T> regla = new Rule<T>(id, tipo);
		return regla;
	}

	/**
	 * Getter del Id de la regla.
	 * @return Id de la regla.
	 */
	public String getId() {
		return id;
	}

	/**
	 * Setter del Id de la regla.
	 * @param id Id de la regla.
	 */
	public void setId(String id) {
		this.id = id;
	}

	/**
	 * Getter del tipo de la regla.
	 * @return Tipo de la regla.
	 */
	public String getTipo() {
		return tipo;
	}

	/**
	 * Setter del tipo de la regla.
	 * @param tipo Tipo de la regla.
	 */
	public void setTipo(String tipo) {
		this.tipo = tipo;
	}

	/**
	 * Getter de la condicion de la regla.
	 * @return COndicion de la regla.
	 */
	public Predicate<T> getPredicado() {
		return condicion;
	}

	/**
	 * Getter del resultado de la regla.
	 * @return Resultado de la regla.
	 */
	public Consumer<T> getResultado() {
		return resultado;
	}
		
	/**
	 * Obtiene una condicion para establecer la regla.
	 * @param predicado Condicion de la regla.
	 * @return Regla.
	 */
	public Rule<T> when(Predicate<T> predicado) {
		this.condicion = predicado;
		return this;
	}

	/**
	 * Obtiene un resultado para establecer en la regla.
	 * @param consumer Resultado de la regla.
	 * @return Regla.
	 */
	public Rule<T> exec(Consumer<T> consumer) {
		this.resultado = consumer;
		return this;
	}

	/**
	 * Comprueba si el objeto cumple la regla.
	 * @param object Objeto evaluado.
	 * @return true si la cumple, flase si no.
	 */
	public boolean process(T object) {
		if (condicion.test(object) == true) {
			resultado.accept(object);
			return true;
		}
		return false;
	}
}
