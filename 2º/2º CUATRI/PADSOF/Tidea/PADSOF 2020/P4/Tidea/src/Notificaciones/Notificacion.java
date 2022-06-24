package Notificaciones;

import java.io.Serializable;

import Enumeraciones.*;
import Proyectos.Proyecto;


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
	 * serial version UID
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Texto de la notificacion.
	 */
	private String texto;

	/**
	 * Tipo de la notificacion.
	 */
	private Proyecto proyectoNotif;
	
	/**
	 * Muestra si se ha leida la notifiacion o no.
	 */
	private TipoNotificacion tipo;

	/**
	 * Constructor de la clase notificacion.
	 * 
	 * @param texto Texto de la notificacion.
	 * @param tipo  Tipo de la notificacion.
	 */
	public Notificacion(String texto, TipoNotificacion tipo, Proyecto proyecto) {
		this.texto = texto;
		this.tipo = tipo;
		this.setProyectoNotif(proyecto);
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
	 * Getter de las notificaciones del proyecto.
	 * @return Notificaciones del proyecto.
	 */
	public Proyecto getProyectoNotif() {
		return proyectoNotif;
	}

	/**
	 * Setter de las notificaciones del proyecto.
	 * @param proyectoNotif Nueva notificacion del proyecto.
	 */
	public void setProyectoNotif(Proyecto proyectoNotif) {
		this.proyectoNotif = proyectoNotif;
	}


}
