package Usuarios;

import java.io.Serializable;

/**
 * Clase Distrito sirve para ver la lista de distritos para los proyectos de
 * tipo infraestructura
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.2
 * @since 1.1
 */
public class Distrito implements Serializable {

	/**
	 * serialVersionUID que implementa Serializable
	 */
	private static final long serialVersionUID = 1L;
	/**
	 * Nombre del distrito.
	 */
	private String nombre;

	/**
	 * Constructor del distrito.
	 * 
	 * @param nombre Nombre del distrito.
	 */
	public Distrito(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Getter del nombre del distrito.
	 * 
	 * @return nombre Nombre del distrito.
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Metodo toString de la clase distrito.
	 */
	public String toString() {
		return this.getNombre();
	}

}
