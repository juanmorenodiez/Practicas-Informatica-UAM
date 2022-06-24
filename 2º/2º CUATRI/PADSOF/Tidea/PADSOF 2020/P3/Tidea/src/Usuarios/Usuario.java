package Usuarios;

import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import Colectivos.Colectivo;
import Enumeraciones.*;
import Notificaciones.Notificacion;
import Proyectos.*;
import Sistemas.*;
import es.uam.eps.sadp.grants.InvalidIDException;

/**
 * La aplicacion esta usada por usuario que para registrarse tiene que
 * introducir su NIF y su contraseña
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.9
 * @since 1.1
 */
public class Usuario implements Serializable {
	/**
	 * serialVersionUID que implementa Serializable
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * NIF del Usuario.
	 */
	private String NIF;

	/**
	 * Nombre del Usuario.
	 */
	private String nombre;

	/**
	 * Contrasena del Usuario.
	 */
	private String password;
	/**
	 * Estado en el que se encuentra el usuario
	 */
	private TipoEstadoUsuario estado;

	/**
	 * Lista de proyectos creados por el Usuario.
	 */
	private ArrayList<Proyecto> proyectosCreados;

	/**
	 * Lista de proyectos que apoya el Usuario.
	 */
	private ArrayList<Proyecto> proyectosdeUsuario;
	
	/**
	 * Lista de proyectos a los que esta suscrito.
	 */
	private ArrayList<Proyecto> proyectosSuscrito;

	/**
	 * Lista de proyectos que apoya el Usuario como representante.
	 */
	private ArrayList<Proyecto> proyectosdeRepresentante;

	/**
	 * Colectivos en los que esta el Usuario.
	 */
	private ArrayList<Colectivo> colectivosdeUsuario;
	
	private ArrayList<Notificacion> notificaciones;
	
	/**
	 * Si el usuario esta logIn o no.
	 */
	private boolean Login;

	/**
	 * Constructor de Usuario.
	 * 
	 * @param nombre   nombre del Usuario.
	 * @param NIF      NIF del Usuario.
	 * @param password contrasena del Usuario.
	 */
	public Usuario(String nombre, String NIF, String password) {
		this.setNombre(nombre);
		this.setNIF(NIF);
		this.setPassword(password);
		this.setEstado(TipoEstadoUsuario.PENDIENTEVALIDAR);
		this.proyectosdeUsuario = new ArrayList<Proyecto>();
		this.colectivosdeUsuario = new ArrayList<Colectivo>();
		this.proyectosdeRepresentante = new ArrayList<Proyecto>();
		this.proyectosCreados = new ArrayList<Proyecto>();
		this.notificaciones = new ArrayList<Notificacion>();
		this.setLogin(false);
	}

	/**
	 * Constructor de Usuario.
	 * 
	 * @param NIF      NIF del Usuario.
	 * @param nombre   nombre del Usuario.
	 * @param password contrasena del Usuario.
	 * @param estado   estado en el que se encuentra el usuario
	 */
	public Usuario(String nombre, String NIF, String password, TipoEstadoUsuario estado) {
		this.setNombre(nombre);
		this.setNIF(NIF);
		this.setPassword(password);
		this.setEstado(estado);
	}

	/**
	 * Getter del NIF del Usuario.
	 * 
	 * @return NIF del Usuario.
	 */
	public String getNIF() {
		return NIF;
	}

	/**
	 * Setter del NIF del Usuario.
	 * 
	 * @param NIF NIF del Usuario.
	 */
	public void setNIF(String NIF) {
		this.NIF = NIF;
	}

	/**
	 * Getter de la contrasena del Usuario.
	 * 
	 * @return contrasena del Usuario.
	 */
	public String getPassword() {
		return password;
	}

	/**
	 * Setter de la contrasena del Usuario.
	 * 
	 * @param password Contrasena del Usuario.
	 */
	public void setPassword(String password) {
		this.password = password;
	}

	/**
	 * Getter de la lista de proyectos que apoya el Usuario.
	 * 
	 * @return la lista de proyectos que apoya el Usuario.
	 */
	public ArrayList<Proyecto> getProyectosdeUsuario() {
		return proyectosdeUsuario;
	}
	
	public void addProyectosdeUsuario(Proyecto p) {
		this.getProyectosdeUsuario().add(p);
	}

	/**
	 * Getter de la lista de colectivos del Usuario.
	 * 
	 * @return Lista de colectivos del Usuario.
	 */
	public ArrayList<Colectivo> getColectivosdeUsuario() {
		return colectivosdeUsuario;
	}


	/**
	 * Getter del estado en el que se encuentra el usuario.
	 * 
	 * @return estado Estado del usuario.
	 */
	public TipoEstadoUsuario getEstado() {
		return estado;
	}

	/**
	 * Setter del estado en el que se encuentra el usuario.
	 * 
	 * @param estado Estado del usuario a asignar.
	 */
	public void setEstado(TipoEstadoUsuario estado) {
		this.estado = estado;
	}

	/**
	 * Getter del nombre del usuario.
	 * 
	 * @return nombre Nombre del usuario.
	 */
	public String getNombre() {
		return nombre;
	}

	/**
	 * Setter del nombre del usuario.
	 * 
	 * @param nombre Nombre del usuario a asignar.
	 */
	public void setNombre(String nombre) {
		this.nombre = nombre;
	}

	/**
	 * Getter de los proyectos de usuario como representante.
	 * @return proyectosdeRepresentante Proyectos de usuario como representante.
	 */
	public ArrayList<Proyecto> getProyectosdeRepresentante() {
		return proyectosdeRepresentante;
	}
	
	public void addProyectosdeRepresentante(Proyecto p) {
		this.getProyectosdeRepresentante().add(p);
	}
	
	/**
	 * Getter de los proyectos creados por el usuario.
	 * @return proyectosCreados Proyectos creados por el usuario.
	 */
	public ArrayList<Proyecto> getProyectosCreados() {
		return proyectosCreados;
	}

	/**
	 * Anade un proyecto a la lista de proyectos creados por el usuario.
	 * @param pC lista de proyectos creados por el usuario.
	 */
	public void addProyectosCreados(Proyecto pC) {
		this.proyectosCreados.add(pC);
	}

	public ArrayList<Proyecto> getProyectosSuscrito() {
		return proyectosSuscrito;
	}

	public void addProyectosSuscrito(Proyecto pS) {
		this.proyectosSuscrito.add(pS);
	}
	
	/**
	 * Devuelve si el usuario esta LogIn o no.
	 * @return Si esta LogIn o no.
	 */
	public boolean isLogin() {
		return Login;
	}

	/**
	 * Setter de si el usuario esta LogIn.
	 * @param login LogIn nuevo.
	 */
	public void setLogin(boolean login) {
		Login = login;
	}

	/**
	 * Getter de la notificaciones del usuario.
	 * @return Las notificaciones que tiene el usuario.
	 */
	public ArrayList<Notificacion> getNotificaciones() {
		return notificaciones;
	}

	/**
	 * Anade una notificacion a las notificaciones del usuario.
	 * @param notificaciones Notificaciones del usuario.
	 */
	public void addNotificaciones(Notificacion notificacion) {
		this.getNotificaciones().add(notificacion);
	}
	
	/**
	 * Metodo que servira para identificarse en el sistema y poder interactuar con
	 * el.
	 * 
	 * @param NIF      NIF del usuario que quiere iniciar sesion
	 * @param password contrasena del usuario que quiere iniciar sesion
	 * @throws ClassNotFoundException excepcion
	 * @throws IOException            excepcion
	 * @throws InvalidIDException 
	 */
	public void loginUsuario(String NIF, String password) throws ClassNotFoundException, IOException, InvalidIDException {
		
		if (NIF == null || password == null) {
			return;
		}

		Sistema.getInstancia().logIn(NIF, password);

		return;
	}

	/**
	 * Metodo que permite a un usuario crear un colectivo, se anadira a la lista de
	 * colectivos del sistema.
	 * 
	 * @param nombre Nombre del colectivo.
	 * @return Colectivo creado por el usuario.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException            excepcion.
	 * @throws InvalidIDException 
	 */
	public Colectivo crearColectivo(String nombre) throws ClassNotFoundException, IOException, InvalidIDException {
		
		if (nombre.length() > 25) {
			Notificacion n = new Notificacion("Titulo " + nombre +" del colectivo demasidado largo.", TipoNotificacion.COLECTIVO);
			this.addNotificaciones(n);
			return null;
		}
		if (this.isLogin() == true) {
			if (Sistema.getInstancia().getColectivos().isEmpty()) {
				Colectivo primero = new Colectivo(nombre, this);
				primero.addIntegrantesColectivo(this);
				Sistema.getInstancia().aniadirColectivo(primero);
				Notificacion n = new Notificacion("Tu colectivo " + nombre +" ha sido creado con exito.", TipoNotificacion.COLECTIVO);
				this.addNotificaciones(n);
				return primero;
			}
			Colectivo c = new Colectivo(nombre, this);
			for (Colectivo colectivo : Sistema.getInstancia().getColectivos()) {
				if (colectivo.getNombre().equals(c.getNombre())) {
					Notificacion n = new Notificacion("Ya existe un colectivo con el nombre " + nombre +".", TipoNotificacion.COLECTIVO);
					this.addNotificaciones(n);
					return null;
				} else {
					c.addIntegrantesColectivo(this);
					Sistema.getInstancia().aniadirColectivo(c);
					Notificacion n = new Notificacion("Tu colectivo " + nombre +" ha sido creado con exito.", TipoNotificacion.COLECTIVO);
					this.addNotificaciones(n);
					return c;
				}
			}
		}
		return null;
	}

	/**
	 * Metodo que cambiara el estado de un usuario del sistema y lo validara, solo
	 * accesible por el administrador.
	 * 
	 * @param u Usuario a validar.
	 * @throws IOException excepcion.
	 * @throws ClassNotFoundException excepcion.
	 * @throws InvalidIDException 
	 */
	public void validarUsuario(Usuario u) throws ClassNotFoundException, IOException, InvalidIDException {
		
		if (Sistema.getInstancia().getAdmin() != this) {
			return;
		}

		u.setEstado(TipoEstadoUsuario.VALIDADO);
	}

	/**
	 * Metodo que rechaza un usuario penbiente de validacion.
	 * 
	 * @param u Usuario a rechazar.
	 * @throws IOException excepcion.
	 * @throws ClassNotFoundException excepcion. 
	 * @throws InvalidIDException 
	 */
	public void rechazarUsuario(Usuario u) throws ClassNotFoundException, IOException, InvalidIDException {
		
		if (Sistema.getInstancia().getAdmin() != this) {
			return;
		}

		u.setEstado(TipoEstadoUsuario.RECHAZADO);
	}

	/**
	 * Metodo que bloquea un usuario existente en el sistema.
	 * 
	 * @param u usuario a bloquear.
	 * @throws IOException            excepcion
	 * @throws ClassNotFoundException excepcion
	 * @throws InvalidIDException 
	 */
	public void bloquearUsuario(Usuario u) throws ClassNotFoundException, IOException, InvalidIDException {
		
		if (Sistema.getInstancia().getAdmin() != this) {
			return;
		}

		/**
		 * En caso de que el usuario esta en la aplicacion, que no pueda seguir haciendo
		 * acciones de usuario validado
		 */
		for (Proyecto p : u.getProyectosdeUsuario()) {
			p.getVotantes().remove(u);
		}

		for (Proyecto p : u.getProyectosdeRepresentante()) {
			p.getVotantes().remove(u);
		}

		u.setEstado(TipoEstadoUsuario.BLOQUEADO);
	}

	/**
	 * Metodo que desbloquea un usuario bloqueado.
	 * 
	 * @param u usuario a desbloquear.
	 * @throws IOException            excepcion
	 * @throws ClassNotFoundException excepcion
	 */
	public void desbloquearUsuario(Usuario u) throws ClassNotFoundException, IOException {
		
		if (!this.getEstado().equals(TipoEstadoUsuario.ADMINISTRADOR)
				&& !u.getEstado().equals(TipoEstadoUsuario.BLOQUEADO)) {
			return;
		}

		for (Proyecto p : u.getProyectosdeUsuario()) {
			p.addVotantes(u);
		}

		for (Proyecto p : u.getProyectosdeRepresentante()) {
			p.addVotantes(u);
		}

		u.setEstado(TipoEstadoUsuario.VALIDADO);
	}

	/**
	 * Devuelve una cadena con los atributos de Usuario que queramos meter.
	 * 
	 * @return String Texto con caracterasticas de un Usuario
	 */
	public String toString() {
		return "" + this.getNombre();
	}

}
