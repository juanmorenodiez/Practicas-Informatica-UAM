package Enumeraciones;

/**
 * Enumeracion del estado en el que se encuentra el usuario.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras
 * @version 1.4
 * @since 1.1
 */
public enum TipoEstadoUsuario {

	BLOQUEADO(0), VALIDADO(1), RECHAZADO(2), PENDIENTEVALIDAR(3), ADMINISTRADOR(4);

	/**
	 * Constructor de la enumeracion TipoEstadoUsuario.
	 * 
	 * @param v valor del estado del usuario.
	 */
	private TipoEstadoUsuario(int v) {
		this.setValor(v);
	}

	/**
	 * Getter de valor del estado del usuario.
	 * 
	 * @return valor del estado del usuario.
	 */
	public int getValor() {
		return valor;
	}

	/**
	 * Setter del valor del estado del usuario.
	 * 
	 * @param valor Valor del estado del usuario.
	 */
	public void setValor(int valor) {
		this.valor = valor;
	}

	/**
	 * Valor que adquiere el estado del usuario.
	 */
	private int valor;
}