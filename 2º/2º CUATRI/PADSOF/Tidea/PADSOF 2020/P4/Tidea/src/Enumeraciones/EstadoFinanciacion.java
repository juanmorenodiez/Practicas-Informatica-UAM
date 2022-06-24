package Enumeraciones;

/**
 * Enumeracion del estado en el que se encuentra la financiacion del proyecto, puede estar
 * No financiable,financiable o puede haber solicitado la
 * financiacion y estar esperandola.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras
 * @version 1.3
 * @since 1.1
 */
public enum EstadoFinanciacion {
	NO_FINANCIABLE(0), FINANCIABLE(1), FINANCIADO(2), FINANCIACIONSOLICITADA(3);

	/**
	 * Constructor de la enumeracion EstadoFinanciacion.
	 * 
	 * @param v valor del estado de financiaci�n de un proyecto
	 */
	private EstadoFinanciacion(int v) {
		this.setValor(v);
	}

	/**
	 * Getter de valor del estado financiaci�n de un proyecto.
	 * 
	 * @return valor del estado de financiaci�n de un proyecto.
	 */
	public int getValor() {
		return valor;
	}

	/**
	 * Setter del valor del estado del proyecto.
	 * 
	 * @param valor Valor del estado de financiaci�n de un proyecto.
	 */
	public void setValor(int valor) {
		this.valor = valor;
	}

	/**
	 * Valor que adquiere el estado de financiaci�n de un proyecto.
	 */
	private int valor;

}
