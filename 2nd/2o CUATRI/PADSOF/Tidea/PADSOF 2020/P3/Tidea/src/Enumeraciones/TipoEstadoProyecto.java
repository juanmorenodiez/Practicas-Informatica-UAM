package Enumeraciones;

/**
 * Enumeracion del estado en el que se encuentra el proyecto, puede estar
 * validado por el administrador, financiado, puede haber solicitado la
 * financiacion y estar esperandola y puede estar esperando a ser validado por
 * el administrador.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras
 * @version 1.3
 * @since 1.1
 */
public enum TipoEstadoProyecto {

	VALIDADO(0), RECHAZADO(1), VOTOSALCANZADOS(2), PENDIENTEVALIDACION(3), CADUCADO(4);

	/**
	 * Constructor de la enumeracion TipoEstadoProyecto.
	 * 
	 * @param v valor del estado del proyecto
	 */
	private TipoEstadoProyecto(int v) {
		this.setValor(v);
	}

	/**
	 * Getter de valor del estado del proyecto.
	 * 
	 * @return valor del estado del proyecto.
	 */
	public int getValor() {
		return valor;
	}

	/**
	 * Setter del valor del estado del proyecto.
	 * 
	 * @param valor Valor del estado del proyecto.
	 */
	public void setValor(int valor) {
		this.valor = valor;
	}

	/**
	 * Valor que adquiere el estado del proyecto.
	 */
	private int valor;
}
