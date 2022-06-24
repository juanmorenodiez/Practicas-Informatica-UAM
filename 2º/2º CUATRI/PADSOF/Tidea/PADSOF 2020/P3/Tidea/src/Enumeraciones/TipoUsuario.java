package Enumeraciones;

/**
 * Enumeracion del estado en el que se encuentra el usuario, puede ser el administrador, puede estar bloqueado por el administrador, validado
 * (REGISTRADO) o pendiente de validar por el administrador.
 * @author Diego Cano, Juan Moreno y Julio Carreras
 * @version 1.2
 * @since 1.1
 */
public enum TipoUsuario {

	ADMINISTRADOR(0),
	REGISTRADO(1);
	
	/**
	 * Constructor del tipo de usuario.
	 * @param v valor del tipo de usuario.
	 */
	private TipoUsuario(int v) {
		this.setValor(v);
	}
	
	/**
	 * Getter del valor del tipo de usuario.
	 * @return valor del tipo de usuario.
	 */
	public int getValor() {
		return valor;
	}

	/**
	 * Setter del valor del tipo de usuario.
	 * @param valor Valor del tipo de usuario.
	 */
	public void setValor(int valor) {
		this.valor = valor;
	}

	/**
	 * Valor del tipo de usuario.
	 */
	private int valor;
	
		
}
