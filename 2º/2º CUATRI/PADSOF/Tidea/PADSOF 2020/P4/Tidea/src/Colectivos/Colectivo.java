package Colectivos;

import java.io.IOException;
import java.io.Serializable;
import java.util.*;
import Usuarios.*;
import es.uam.eps.sadp.grants.InvalidIDException;
import Proyectos.*;
import Sistemas.Sistema;

/**
 * Los Usuarios se agrupan en colectivos, de tal forma que si el representante
 * de un colectivo, que es el que crea el colectivo, vota un proyecto todos los
 * integrantes del colectivo apoyaran automa- ticamente el proyecto. Ademas se
 * pueden crear subcolectivos, pero los usuarios de un colectivo no tienen
 * porque pertenecer al nuevo subcolectivo.
 * 
 * @author Diego Cano, Juan Moreno, Julio Carreras
 * @version 1.1
 * @since 1.1
 */
public class Colectivo implements Serializable {

	/**
	 * variable serialVersionUID
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Nombre del colectivo.
	 */
	private String nombre;

	/**
	 * Usuario representante del colectivo.
	 */
	private Usuario representante;

	/**
	 * Lista de usuarios del colectivo.
	 */
	private ArrayList<Usuario> integrantesColectivo;

	/**
	 * Lista de subcolectivos de cada colectivo (profundidad n-1)
	 */
	private ArrayList<Colectivo> subcolectivos;

	/**
	 * Colectivo padre del colectivo, el primero esta inicializado a null.
	 */
	private Colectivo colectivopadre;

	/**
	 * Constructor de la clase colectivo.
	 * 
	 * @param nombre        Nombre del colectivo.
	 * @param representante Representante del colectivo.
	 */
	public Colectivo(String nombre, Usuario representante) {
		this.setNombre(nombre);
		this.setRepresentante(representante);
		this.integrantesColectivo = new ArrayList<Usuario>();
		this.subcolectivos = new ArrayList<Colectivo>();
		this.setColectivoPadre(null);
	}

	/**
	 * Getter de representante del colectivo.
	 * 
	 * @return Representante del colectivo.
	 */
	public Usuario getRepresentante() {
		return representante;
	}

	/**
	 * Setter de representante del colectivo.
	 * 
	 * @param u Usuario representante del colectivo.
	 */
	public void setRepresentante(Usuario u) {
		this.representante = u;
	}

	/**
	 * Getter de Nombre del colectivo
	 * 
	 * @return nombre del colectivo.
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Setter del nombre del colectivo.
	 * 
	 * @param nombre Nombre del colectivo.
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Getter de los integrantes del colectivo.
	 * 
	 * @return integrantes del del colectivo.
	 */
	public ArrayList<Usuario> getIntegrantesColectivo() {
		return integrantesColectivo;
	}

	/**
	 * Anade un integrante al colectivo.
	 * @param integranteNuevo Integrante nuevo.
	 */
	public void addIntegrantesColectivo(Usuario integranteNuevo) {
		this.getIntegrantesColectivo().add(integranteNuevo);
	}

	/**
	 * Getter de los subcolectivos que pertenecen a un colectivo
	 * 
	 * @return subcolectivos del colectivo.
	 */
	public ArrayList<Colectivo> getSubcolectivos() {
		return subcolectivos;
	}

	/**
	 * Anade un subcolectivo al colectivo.
	 * @param sC Subcolectivo  a anadir.
	 */
	public void addSubcolectivo(Colectivo sC) {
		this.getSubcolectivos().add(sC);
	}

	/**
	 * Getter de todos los subcolectivos del colectivo.
	 * @return subcolectivos del colectivo.
	 */
	public ArrayList<Colectivo> getAllSubcolectivos() {
		ArrayList<Colectivo> list = new ArrayList<Colectivo>();

		for (Colectivo s : this.getSubcolectivos()) {
			list.add(s);
			subc(s, list);
		}
		return list;
	}

	/**
	 * Comprueba si un subcolectivo pertenece al colectivo y si no lo anade.
	 * @param s Subcolectivo a comprobar.
	 * @param list Lista de colectivos.
	 */
	private void subc(Colectivo s, ArrayList<Colectivo> list) {
		for (Colectivo su : s.getSubcolectivos()) {
			subc(su, list);
		}
		if (!list.contains(s)) {
			list.add(s);
		}
		return;
	}

	/**
	 * Setter de una lista de subcolectivos de cada colectivo.
	 * 
	 * @param subcolectivos Lista de subcolectivos.
	 */
	public void setSubcolectivos(ArrayList<Colectivo> subcolectivos) {
		this.subcolectivos = subcolectivos;
	}

	/**
	 * Getter del colectivo padre del colectivo.
	 * @return Colectivo padre.
	 */
	public Colectivo getColectivoPadre() {
		return colectivopadre;
	}

	/**
	 * Setter del colectivo padre del colectivo.
	 * @param colectivopadre COlectivo padre.
	 */
	public void setColectivoPadre(Colectivo colectivopadre) {
		this.colectivopadre = colectivopadre;
	}

	/**
	 * Calcula la afinidad entre dos colectivos basandose en los proyectos que apoya
	 * cada colectivo.
	 * 
	 * @param c colectivo con el que se quiere comparar el colectivo.
	 * @return la afinidad entre los dos colectivos.
	 * @throws IOException            excepcion.
	 * @throws ClassNotFoundException expecion.
	 * @throws InvalidIDException 
	 */
	public double afinidadColectivos(Colectivo c) throws ClassNotFoundException, IOException, InvalidIDException {
		int n1 = 0;
		int n2 = 0;
		double afinidad;

		if (c == null || this.getRepresentante().getProyectosdeRepresentante().size() == 0 ||c.getRepresentante().getProyectosdeRepresentante().size() == 0) {
			return 0.0;
		}
		/**
		 * Proyectos comunes al colectivo 1.
		 */
		for (Proyecto p1 : this.getRepresentante().getProyectosdeRepresentante()) {
			if (c.getRepresentante().getProyectosdeRepresentante().contains(p1)) {
				n1++;
			}
		}

		/**
		 * Proyectos comunes al colectivo 2.
		 */
		for (Proyecto p2 : c.getRepresentante().getProyectosdeRepresentante()) {
			if (this.getRepresentante().getProyectosdeRepresentante().contains(p2)) {
				n2++;
			}
		}

		afinidad = (n1 + n2) / (this.getRepresentante().getProyectosdeRepresentante().size()
				+ c.getRepresentante().getProyectosdeRepresentante().size());


		return afinidad;
	}

	/**
	 * Metodo con el que un usuario se une a un colectivo. 
	 * @throws ClassNotFoundException excepcion. 
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public boolean unirseColectivo() throws ClassNotFoundException, IOException, InvalidIDException {
		Usuario u = Sistema.getInstancia().usuarioLogin();
		if (this.getIntegrantesColectivo().contains(u) == false) {
			for (Colectivo sc : this.getAllSubcolectivos()) {
				if (sc.getIntegrantesColectivo().contains(u)) {
					return false;
				}
			}
			if (this.getColectivoPadre() != null) {
				for (Colectivo p : this.getPadres()) {
					if (p.getIntegrantesColectivo().contains(u)) {
						return false; 
					}
				}
			}
			this.getIntegrantesColectivo().add(u);
			u.getColectivosdeUsuario().add(this);
			return true; 
		}
		return false; 
	}

	/**
	 * Getter del array de colectivos padres del colectivo.
	 * @return Array de colectivos padres.
	 */
	public ArrayList<Colectivo> getPadres() {
		ArrayList<Colectivo> padres = new ArrayList<Colectivo>();
		padres.add(colectivopadre);
		subPadres(colectivopadre, padres);
		return padres;
	}

	/**
	 * Comprueba si el colectivo pertenece a alguno de sus colectivos padres.
	 * @param c Colectivo a comprobar.
	 * @param list Lista de colectivos.
	 */
	private void subPadres(Colectivo c, ArrayList<Colectivo> list) {

		if (c.getColectivoPadre() != null) {
			subPadres(c.getColectivoPadre(), list);
		}

		if (!list.contains(c)) {
			list.add(c);
		}
		return;
	}

	/**
	 * Metodo con el que un usuario abandona un colectivo.
	 * 
	 * @param c colectivo que deja.
	 * 
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException            excepcion.
	 * @throws InvalidIDException 
	 */
	public void abandonarColectivo() throws ClassNotFoundException, IOException, InvalidIDException {

		Usuario u = Sistema.getInstancia().usuarioLogin();

		if (this.getIntegrantesColectivo().contains(u) == true) {

			this.getIntegrantesColectivo().remove(u);
			u.getColectivosdeUsuario().remove(this);

			for (Proyecto proyecto : Sistema.getInstancia().getProyectos()) {

				if (proyecto.getVotantes().contains(u) && proyecto.getColectivosProyecto().contains(this)) {

					proyecto.getVotantes().remove(u);
					proyecto.actualizarProyecto();
				}
			}
		}
	}

	/**
	 * Metodo con la que un usuario crea un subcolectivo.
	 * 
	 * @param c      colectivo padre.
	 * @param nombre nombre del subcolectivo.
	 * @return subcolectivo del colectivo.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException            excepcion.
	 * @throws InvalidIDException 
	 */
	public Colectivo crearSubColectivo(String nombre) throws ClassNotFoundException, IOException, InvalidIDException {

		Usuario u = Sistema.getInstancia().usuarioLogin();

		if (nombre.length() > 25) {
			return null;
		}

		for (Colectivo colectivos1 : Sistema.getInstancia().getColectivos()) {
			if (nombre == colectivos1.getNombre()) {
				return null;
			}
		}

		if (Sistema.getInstancia().getColectivos().contains(this)) {
			if (this.getSubcolectivos().isEmpty()) {
				Colectivo primero = new Colectivo(nombre, u);
				primero.getIntegrantesColectivo().add(u);
				this.getSubcolectivos().add(primero);
				Sistema.getInstancia().aniadirColectivo(primero);
				primero.setColectivoPadre(this);
				return primero;
			}
			Colectivo sc = new Colectivo(nombre, u);
			for (Colectivo colectivos2 : this.getSubcolectivos()) {
				if (sc.getNombre().equals(colectivos2.getNombre())) {
					return null;
				} else {
					this.addSubcolectivo(sc);
					sc.addIntegrantesColectivo(u);
					Sistema.getInstancia().aniadirColectivo(sc);
					sc.setColectivoPadre(this);
					return sc;
				}
			}
		}
		return null;
	}

	/**
	 * Devuelve una cadena con los atributos de Colectivo que queramos meter
	 * 
	 * @return String con caracteristicas de un Colectivo
	 */
	public String toString() {
		return "" + this.getNombre() + ",  Integrantes:  "+ this.getIntegrantesColectivo();
	}

}
