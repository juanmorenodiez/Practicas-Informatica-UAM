package Enumeraciones;

/**
 * Enumeracion del tipo de notificaciones que recibe un usuario registrado en la
 * aplicacion, pueden ser del tipo proyecto, por ejemplo si ha enviado un
 * proyecto para que el administrador lo valide, de colectivo, si su colectivo
 * ha votado un proyecto nuevo o de financiacion, si ha recibido o no
 * financiacion.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.4
 * @since 1.1
 */
public enum TipoNotificacion {
	RECHAZO(0), CADUCIDAD(1), VALIDACION(2), FINANCIABLE(3), FINANCIACION_OK(4);

	/**
	 * Constructor del tipo de notificacion.
	 * 
	 * @param v Valor del tipo de notificacion.
	 */
	private TipoNotificacion(int v) {
		this.setValor(v);
	}

	/**
	 * Getter del valor del tipo de notificacion.
	 * 
	 * @return Valor del tipo de notificacion.
	 */
	public int getValor() {
		return valor;
	}

	/**
	 * Setter del valor del tipo de notificacion.
	 * 
	 * @param valor Valor del tipo de notificacion.
	 */
	public void setValor(int valor) {
		this.valor = valor;
	}

	/**
	 * Valor del tipo de notificacion.
	 */
	private int valor;

}
