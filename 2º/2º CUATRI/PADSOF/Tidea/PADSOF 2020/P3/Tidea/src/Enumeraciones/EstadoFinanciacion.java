package Enumeraciones;

public enum EstadoFinanciacion {
	NO_FINANCIABLE(0), FINANCIABLE(1), FINANCIADO(2), FINANCIACIONSOLICITADA(3);

	/**
	 * Constructor de la enumeracion EstadoFinanciacion.
	 * 
	 * @param v valor del estado de financiación de un proyecto
	 */
	private EstadoFinanciacion(int v) {
		this.setValor(v);
	}

	/**
	 * Getter de valor del estado financiación de un proyecto.
	 * 
	 * @return valor del estado de financiación de un proyecto.
	 */
	public int getValor() {
		return valor;
	}

	/**
	 * Setter del valor del estado del proyecto.
	 * 
	 * @param valor Valor del estado de financiación de un proyecto.
	 */
	public void setValor(int valor) {
		this.valor = valor;
	}

	/**
	 * Valor que adquiere el estado de financiación de un proyecto.
	 */
	private int valor;

}
