package Notificaciones;

import java.io.Serializable;

import Enumeraciones.*;


/**
 * La clase notificacion sirve para informar a los usa¡uarios de las distintas
 * informaciones que pueden recibir.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.5
 * @since 1.1
 */
public class Notificacion implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Texto de la notificacion.
	 */
	private String texto;

	/**
	 * Tipo de la notificacion.
	 */
	private TipoNotificacion tipo;
	
	/**
	 * Muestra si se ha leida la notifiacion o no.
	 */
	private boolean leida;

	/**
	 * Constructor de la clase notificacion.
	 * 
	 * @param texto Texto de la notificacion.
	 * @param tipo  Tipo de la notificacion.
	 */
	public Notificacion(String texto, TipoNotificacion tipo) {
		this.texto = texto;
		this.tipo = tipo;
		this.setLeida(false);
	}

	/**
	 * Getter del texto de la notificacion.
	 * 
	 * @return Texto de la notificacion.
	 */
	public String getTexto() {
		return texto;
	}

	/**
	 * Setter del texto de la notificacion.
	 * 
	 * @param texto Texto de la notificacion.
	 */
	public void setTexto(String texto) {
		this.texto = texto;
	}

	/**
	 * Getter del tipo de notificacion.
	 * 
	 * @return Tipo de notificacion.
	 */
	public TipoNotificacion getTipo() {
		return tipo;
	}

	/**
	 * Setter del tipo de notificacion.
	 * 
	 * @param tipo Tipo de notificacion.
	 */
	public void setTipo(TipoNotificacion tipo) {
		this.tipo = tipo;
	}
	
	/**
	 * String toString para imprimir la notificacion.
	 */
	public String toString() {
		return "Tipo de notificacion: " + this.tipo + "\nNotificacion: " + this.texto + "\n";
	}

	/**
	 * Muestra si se ha leido la notificacion o no.
	 * @return true si se ha leido la notificacion o false si no se ha leido.
	 */
	public boolean isLeida() {
		return leida;
	}

	/**
	 * Setter de notificacion leida.
	 * @param leida Si se ha leido o no la notificacion.
	 */
	public void setLeida(boolean leida) {
		this.leida = leida;
	}

}
