package Proyectos;

import java.io.IOException;
import java.io.Serializable;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDate;
import java.util.ArrayList;
import static java.time.temporal.ChronoUnit.DAYS;

import Colectivos.Colectivo;
import Enumeraciones.*;
import Notificaciones.Notificacion;
import Sistemas.Sistema;
import Usuarios.*;
import es.uam.eps.sadp.grants.CCGG;
import es.uam.eps.sadp.grants.GrantRequest;
import es.uam.eps.sadp.grants.InvalidIDException;
import es.uam.eps.sadp.grants.InvalidRequestException;

/**
 * Los Usuarios pueden crear proyectos, que seran validos si el administrador lo
 * considera oportuno, tambien pueden votarlos si les parecen interesantes a
 * realizar y asi el proyecto pueda llegar a recibir financiacion.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.6
 * @since 1.1
 */
public abstract class Proyecto implements GrantRequest, Serializable {

	/**
	 * serialVersionUID que implementa Serializable
	 */
	private static final long serialVersionUID = 1L;
	
	/**
	 * Colectivos que apoyan el proyecto.
	 */
	private ArrayList<Usuario> suscriptores;

	/**
	 * Id del proyecto.
	 */
	private int Id;

	/**
	 * Titulo del proyecto.
	 */
	private String titulo;

	/**
	 * Descripcion del proyecto.
	 */
	private String descripcion;
	
	/**
	 * Clave de financiacion del proyecto.
	 */
	private String clave;

	/**
	 * Importe que el usuario quiere conseguir para el proyecto.
	 */
	private double importeSolicitado;

	/**
	 * Importe que concede el sistema de financiacion cuando el usuario lo manda a
	 * financiar.
	 */
	private double importeConcedido;

	/**
	 * Usuario que crea el proyecto.
	 */
	private Usuario usuarioProponente;

	/**
	 * Estado en el que se encuentra el proyecto.
	 */
	private TipoEstadoProyecto estadoProyecto;	
	
	/**
	 * Estado en el que se encuentra el proyecto.
	 */
	private EstadoFinanciacion estadoFinanciacion;
	
	/**
	 * Apoyos recibidos del proyecto.
	 */
	private Integer apoyosRecibidos;

	/**
	 * Fecha de validacion del proyecto.
	 */
	private LocalDate fechaValidacion;

	/**
	 * Fecha ultimo voto recibido del proyecto.
	 */
	private LocalDate fechaUltimoVoto;

	/**
	 * Votantes del proyecto.
	 */
	private ArrayList<Usuario> votantes;
	
	/**
	 * Colectivos que apoyan el proyecto.
	 */
	private ArrayList<Colectivo> colectivosProyecto;

	/**
	 * Constructor de la clase proyecto
	 * 
	 * @param titulo            Titulo del proyecto.
	 * @param descr             Descripcion del proyecto.
	 * @param importeSolicitado Importe solicitado del proyecto.
	 */
	public Proyecto(String titulo, String descr, double importeSolicitado) {
		this.titulo = titulo;
		this.descripcion = descr;
		this.importeSolicitado = importeSolicitado;
		this.importeConcedido = 0;
		this.estadoProyecto = TipoEstadoProyecto.PENDIENTEVALIDACION;
		this.apoyosRecibidos = 0;
		this.votantes = new ArrayList<Usuario>();
		this.colectivosProyecto = new ArrayList<>();
		this.estadoFinanciacion = EstadoFinanciacion.NO_FINANCIABLE;
		this.suscriptores = new ArrayList<>();
	}

	/**
	 * Getter del Id del proyecto.
	 * 
	 * @return Id del proyecto.
	 */
	public int getId() {
		return Id;
	}

	/**
	 * Setter del Id del proyecto.
	 * 
	 * @param id Id del proyecto.
	 */
	public void setId(int id) {
		Id = id;
	}

	/**
	 * Getter del titulo del proyecto.
	 * 
	 * @return Titulo del proyecto.
	 */
	public String getTitulo() {
		return titulo;
	}

	/**
	 * Setter del titulo del proyecto.
	 * 
	 * @param titulo Titulo del proyecto.
	 */
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}

	/**
	 * Getter de la descripcion del proyecto.
	 * 
	 * @return Descripcion del proyecto.
	 */
	public String getDescripcion() {
		return descripcion;
	}

	/**
	 * Setter de la descripcion del proyecto.
	 * 
	 * @param descripcion Descripcion del proyecto.
	 */
	public void setDescripcion(String descripcion) {
		this.descripcion = descripcion;
	}

	/**
	 * Getter de los apoyos recibidos del proyecto.
	 * 
	 * @return Apoyos recibidos del proyecto.
	 */
	public Integer getApoyosRecibidos() {
		return apoyosRecibidos;
	}

	/**
	 * Setter de los apoyosrecibidos del proyecto.
	 * 
	 * @param apoyosRecibidos Apoyos recibidos del proyecto.
	 */
	public void setApoyosRecibidos(int apoyosRecibidos) {
		this.apoyosRecibidos = apoyosRecibidos;
	}
	
	/**
	 * Getter del tipo de estado del proyecto.
	 * 
	 * @return Tipo de estado del proyecto.
	 */
	public TipoEstadoProyecto getEstadoProyecto() {
		return estadoProyecto;
	}

	/**
	 * Setter del estado del proyecto.
	 * 
	 * @param estadoProyecto Estado del proyecto.
	 */
	public void setEstadoProyecto(TipoEstadoProyecto estadoProyecto) {
		this.estadoProyecto = estadoProyecto;
	}

	/**
	 * Getter del importe Solicitado del proyecto.
	 * 
	 * @return Importe solicitado del proyecto.
	 */
	public double getImporteSolicitado() {
		return importeSolicitado;
	}

	/**
	 * Setter del importe solicitado para el proyecto.
	 * 
	 * @param importeSolicitado Importe solicitado para el proyecto.
	 */
	public void setImporteSolicitado(double importeSolicitado) {
		this.importeSolicitado = importeSolicitado;
	}

	/**
	 * Getter del importe concedido del proyecto.
	 * 
	 * @return Importe concedido del proyecto.
	 */
	public double getImporteConcedido() {
		return importeConcedido;
	}

	/**
	 * Setter del importe concedido para el proyecto.
	 * 
	 * @param importeConcedido Importe concedido para el proyecto.
	 */
	public void setImporteConcedido(double importeConcedido) {
		this.importeConcedido = importeConcedido;
	}

	/**
	 * Getter del usuario proponente del proyecto.
	 * 
	 * @return Usuario proponente del proyecto.
	 */
	public Usuario getUsuarioProponente() {
		return usuarioProponente;
	}

	/**
	 * Setter del usuario proponente del proyecto.
	 * 
	 * @param u usuario proponente del proyecto.
	 */
	public void setUsuarioProponente(Usuario u) {
		this.usuarioProponente = u;
	}

	/**
	 * Getter de la Fecha del ultimo voto del proyecto.
	 * 
	 * @return Fecha del ultimo voto del proyecto.
	 */
	public LocalDate getFechaUltimoVoto() {
		return fechaUltimoVoto;
	}

	/**
	 * Setter de la fecha del ultimo voto del proyecto.
	 * 
	 * @param localDate del ultimo voto del proyecto.
	 */
	public void setFechaUltimoVoto(LocalDate localDate) {
		this.fechaUltimoVoto = localDate;
	}

	/**
	 * Getter de los integrantes del proyecto.
	 * 
	 * @return Integrantes del proyecto.
	 */
	public ArrayList<Usuario> getVotantes() {
		return votantes;
	}

	/**
	 * Setter de los integrantes del proyecto.
	 * 
	 * @param integrantes Integrantes del proyecto.
	 */
	public void addVotantes(Usuario votante) {
		this.votantes.add(votante);
	}

	/**
	 * Getter de la fecha de validacion del proyecto.
	 * 
	 * @return Fecha de validacion del proyecto.
	 */
	public LocalDate getFechaValidacion() {
		return fechaValidacion;
	}

	/**
	 * Setter de la fecha de validacion del proyecto.
	 * 
	 * @param fechaValidacion Fecha de validacion del proyecto.
	 */
	public void setFechaValidacion(LocalDate fechaValidacion) {
		this.fechaValidacion = fechaValidacion;
	}
	
	/**
	 * Getter de los colectivos del proyecto.
	 * @return COlectivos del proyecto.
	 */
	public ArrayList<Colectivo> getColectivosProyecto() {
		return colectivosProyecto;
	}

	/**
	 * Anade un colectivo a los colectivos del proyecto.
	 * @param c COlectivo a anadir.
	 */
	public void addColectivosProyecto(Colectivo c) {
		this.colectivosProyecto.add(c);
	}

	/**
	 * Getter del estado de financiacion del proyecto.
	 * @return Estado de financiacion del proyecto.
	 */
	public EstadoFinanciacion getEstadoFinanciacion() {
		return estadoFinanciacion;
	}

	/**
	 * Setter del estado de financiacion del proyecto.
	 * @param estadoFinanciacion Estado de financiacion del proyecto.
	 */
	public void setEstadoFinanciacion(EstadoFinanciacion estadoFinanciacion) {
		this.estadoFinanciacion = estadoFinanciacion;
	}

	/**
	 * Getter de la clave del proyecto para saber su estado de financiacion.
	 * @return CLave del proyecto.
	 */
	public String getClave() {
		return clave;
	}

	/**
	 * Setter de la clave del proyecto.
	 * @param clave Clave del proyecto.
	 */
	public void setClave(String clave) {
		this.clave = clave;
	}
	
	/**
	 * Getter de los suscriptores del proyecto.
	 * @return Suscriptores del proyecto.
	 */
	public ArrayList<Usuario> getSuscriptores() {
		return suscriptores;
	}

	/**
	 * Anade un suscritos a los suscriptores del proyecto.
	 * @param suscriptor Suscriptores del proyecto.
	 */
	public void addSuscriptores(Usuario suscriptor) {
		this.suscriptores.add(suscriptor);
	}

	/**
	 * Metodo que comprueba el estado de financiacion de 
	 * un proyecto.
	 * 
	 * @param key Clave que habra que meter para identificar el estado que queremos devolver
	 * @return estado de la financiacion de un proyecto.
	 * @throws IOException excepcion
	 * @throws InvalidIDException excepcion
	 */
	public EstadoFinanciacion estadoFinanciacion(String key) throws IOException, InvalidIDException {
		/**CAMBIAR*/
		double clave;
		EstadoFinanciacion estadoF = null;
		clave = CCGG.getGateway().getAmountGranted(key);
		if (clave == 0) {
			estadoF = EstadoFinanciacion.FINANCIABLE;
		}

		else if (clave > 0) {
			estadoF = EstadoFinanciacion.FINANCIADO;
		}

		return estadoF;
	}
	
	/**
	 * Metodo que aprueba un proyecto pendiente de aprobacion/validacion.
	 * 
	 * @throws IOException excepcion.
	 * @throws ClassNotFoundException excepcion. 
	 * @throws InvalidIDException 
	 */
	public void aprobarProyecto() throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		if (u.getEstado().equals(TipoEstadoUsuario.ADMINISTRADOR)) {
			this.setEstadoProyecto(TipoEstadoProyecto.VALIDADO);
		}
	}

	/**
	 * Metodo que rechaza y elimina un proyecto pendiente de aprobacion/validacion.
	 * 
	 * @param razon Motivo por el que se rechaza el proyecto.
	 * @throws IOException            excepcion.
	 * @throws ClassNotFoundException excepcion.
	 * @throws InvalidIDException 
	 */
	public void rechazarProyecto(String razon) throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		if(!(u.getEstado().equals(TipoEstadoUsuario.ADMINISTRADOR))) {
			return;
		}

		if (this.getProjectKind().equals(ProjectKind.Infrastructure)) {
			/* eliminar imagen */
			Path imagesPath = Paths.get(((ProyectoInfraestructura) this).getImagen());

			try {
				Files.delete(imagesPath);
				System.out.println("File " + imagesPath.toAbsolutePath().toString() + " successfully removed");
			} catch (IOException e) {
				System.err.println("Unable to delete " + imagesPath.toAbsolutePath().toString() + " due to...");
				e.printStackTrace();
			}
		}

		/* Sistema.getInstancia().eliminarProyecto(p); */
		Notificacion n = new Notificacion("Tu proyecto ha sido rechazado porque: " + razon, TipoNotificacion.RECHAZO, this);
		if (this.getUsuarioProponente().contieneNotificacion(n) == false) {
			this.getUsuarioProponente().addNotificaciones(n);
		}
		this.setEstadoProyecto(TipoEstadoProyecto.RECHAZADO);
		return;
	}
	
	/**
	 * Metodo con la que un usuario apoya un proyecto.
	 * 
	 * @throws IOException
	 * @throws ClassNotFoundException
	 * @throws InvalidIDException 
	 * 
	 */
	public boolean apoyarProyecto() throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		this.actualizarProyecto();
		if(this.getEstadoProyecto() == TipoEstadoProyecto.CADUCADO) {
			return false;
		}
		
		if (this.getVotantes().contains(u) == false) {
			this.addVotantes(u);
			this.setFechaUltimoVoto(LocalDate.now());
			u.addProyectosdeUsuario(this);
			this.actualizarProyecto();
			return true;
		}
		return false;		
	}
	
	/**
	 * Metodo con el que un usuario apoya un proyecto como representante.
	 * 
	 * @param p Proyecto que va a apoyar.
	 * 
	 * @throws IOException            excepcion.
	 * @throws ClassNotFoundException excepcion.
	 * @throws InvalidIDException 
	 */
	public boolean apoyarProyectoRepresentante(Colectivo c) throws ClassNotFoundException, IOException, InvalidIDException {
		Usuario usuario = Sistema.getInstancia().usuarioLogin();
		this.actualizarProyecto();
		if (c.getRepresentante().equals(usuario)) {
			for (Colectivo s : c.getSubcolectivos()) {
				apoyarSubc(this, s);
			}
			for (Usuario u : c.getIntegrantesColectivo()) {
				if (this.getVotantes().contains(u) == false && u.getEstado() != TipoEstadoUsuario.BLOQUEADO) {
					this.addVotantes(u);
					this.setFechaUltimoVoto(LocalDate.now());
					return true;
				}
			}
			if (!usuario.getProyectosdeRepresentante().contains(this)) {
				usuario.addProyectosdeRepresentante(this);
			}
			if (this.getColectivosProyecto().contains(c) == true) {
				return false;
			}
			this.addColectivosProyecto(c);
			this.actualizarProyecto();
		}
		return false;		
	}

	/**
	 * Metodo con el que el proyecto apoya un subcolectivo.
	 * @param p Proyecto que va a apoyar.
	 * @param c COlectivo que se va a apoyar.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 */
	public void apoyarSubc(Proyecto p, Colectivo c) throws ClassNotFoundException, IOException {
		
		for (Colectivo s : c.getSubcolectivos()) {
			apoyarSubc(p, s);
		}
		
		for (Usuario u : c.getIntegrantesColectivo()) {
			
			if (p.getVotantes().contains(u) == false && u.getEstado() != TipoEstadoUsuario.BLOQUEADO) {
				p.addVotantes(u);
				p.setFechaUltimoVoto(LocalDate.now());
			}
		}
		
		c.getRepresentante().addProyectosdeRepresentante(this);
		
		if (p.getColectivosProyecto().contains(c) == true) {
			return;
		}
		
		p.addColectivosProyecto(c);
	}

	/**
	 * Metodo para suscribirse a un proyecto.
	 * @return true si se ha suscrito, false si no
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public boolean suscriberseProyecto () throws ClassNotFoundException, IOException, InvalidIDException {
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		if (this.getSuscriptores().contains(u)) {
			return false;
		}
		
		u.addProyectosSuscrito(this);
		this.addSuscriptores(u);
		
		return true;
	}
	
	/**
	 * Metodo para desuscribirse del proyecto.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void desSuscriberseProyecto () throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		u.getProyectosSuscrito().remove(this);
		this.getVotantes().remove(u);
		
	}
	
	/**
	 * Metodo para actualizar todos los estados del proyecto.
	 * @throws ClassNotFoundException excepcion.
	 * @throws IOException excepcion.
	 * @throws InvalidIDException excepcion.
	 */
	public void actualizarProyecto () throws ClassNotFoundException, IOException, InvalidIDException {
		int apoyos = 0;
				
		for (Usuario votante: this.getVotantes()) {
			if(votante.getEstado().equals(TipoEstadoUsuario.VALIDADO)) {
				apoyos++;
			}
		}
		this.setApoyosRecibidos(apoyos);
		
		if (this.getEstadoFinanciacion().equals(EstadoFinanciacion.FINANCIACIONSOLICITADA)) {
			Double importeConcebido = null;
			String followUp = this.getClave();
			
			try {
				importeConcebido = CCGG.getGateway().getAmountGranted(followUp);
			} catch (IOException e) {
				e.printStackTrace();
				return;
			} catch (InvalidIDException e) {
				e.printStackTrace();
				return;
			}
			
			
			
			if (importeConcebido == null) {
				this.setEstadoFinanciacion(EstadoFinanciacion.FINANCIACIONSOLICITADA);
				return;
			}
			
			else if (importeConcebido > 0) {
				this.setEstadoFinanciacion(EstadoFinanciacion.FINANCIADO);
				this.setImporteConcedido(importeConcebido);
				Notificacion notificacion = new Notificacion("Tu proyecto ha sido financiado!", TipoNotificacion.FINANCIACION_OK, this);
				if (this.getUsuarioProponente().contieneNotificacion(notificacion) == false) {
					this.getUsuarioProponente().addNotificaciones(notificacion);
				}
				
				for (Usuario u1 : this.getSuscriptores()) {
					if (u1.contieneNotificacion(notificacion) == false) {
						u1.addNotificaciones(notificacion);
					}
				}
			}
		}
		
		/* Si el proyecto ha sido validado, se notifica al usuario proponente */
		if (this.getEstadoProyecto().equals(TipoEstadoProyecto.VALIDADO)) {
			Notificacion notificacion = new Notificacion("Tu proyecto: " + this.getTitulo() + "ha sido validado.",
					TipoNotificacion.VALIDACION, this);
			if (this.getUsuarioProponente().contieneNotificacion(notificacion) == false) {
				this.getUsuarioProponente().addNotificaciones(notificacion);
			}
		}

		/* Cambio del estado en caducidad, se notifica a suscriptores y al proponente */
		if (DAYS.between(getFechaUltimoVoto(), getFechaValidacion()) >= 30) {
			this.setEstadoProyecto(TipoEstadoProyecto.CADUCADO);
			Notificacion notificacion = new Notificacion("El proyecto "+ this.getTitulo() +" esta caducado porque no ha recibido ningun voto en 30 dias.", TipoNotificacion.CADUCIDAD, this);
			if (this.getUsuarioProponente().contieneNotificacion(notificacion) == false) {
				this.getUsuarioProponente().addNotificaciones(notificacion);
			}
			
			for (Usuario u1 : this.getSuscriptores()) {
				if (u1.contieneNotificacion(notificacion) == false) {
					u1.addNotificaciones(notificacion);
				}
			}
		}
		
		if(this.getApoyosRecibidos() >= Sistema.getInstancia().apoyosFinanciacion) {
			this.setEstadoProyecto(TipoEstadoProyecto.VOTOSALCANZADOS);
			this.setEstadoFinanciacion(EstadoFinanciacion.FINANCIABLE);
			Notificacion notificacion = new Notificacion("El proyecto "+ this.getTitulo() +" esta en estado financiable porque ha alcanzado los votos necesario", TipoNotificacion.FINANCIABLE, this);
			if (this.getUsuarioProponente().contieneNotificacion(notificacion) == false) {
				this.getUsuarioProponente().addNotificaciones(notificacion);
			}
			
			for (Usuario usuario : this.getSuscriptores()) {
				if (usuario.contieneNotificacion(notificacion) == false) {
					usuario.addNotificaciones(notificacion);
				}
			}
		}
		
		if(this.getEstadoFinanciacion().equals(EstadoFinanciacion.FINANCIADO)) {
			
			Notificacion notificacion = new Notificacion("El proyecto "+ this.getTitulo() +" ha sido financiado, enhorabuena!.", TipoNotificacion.FINANCIACION_OK, this);
			if (this.getUsuarioProponente().contieneNotificacion(notificacion) == false) {
				this.getUsuarioProponente().addNotificaciones(notificacion);
			}
			
			for (Usuario usuario : this.getSuscriptores()) {
				if (usuario.contieneNotificacion(notificacion) == false) {
					usuario.addNotificaciones(notificacion);
				}
			}
		}
	}
	
	/**
	 * Metodo para solicitar la financiacion del proyecto.
	 * @return clave
	 * @throws IOException excepcion.
	 * @throws InvalidRequestException excepcion.
	 */
	public String solicitarFinanciacion() throws IOException, InvalidRequestException {
		String followUp;
		CCGG contacto = CCGG.getGateway();
		
		
		if (this.getEstadoFinanciacion().equals(EstadoFinanciacion.FINANCIACIONSOLICITADA)) {
			return null;
		}
		
		else {
			followUp = contacto.submitRequest(this);
			this.setEstadoFinanciacion(EstadoFinanciacion.FINANCIACIONSOLICITADA);
			Notificacion notificacion = new Notificacion("Financiaci�n solicitada correctamente!", TipoNotificacion.FINANCIACION_OK, this);
			
			if (this.getUsuarioProponente().contieneNotificacion(notificacion) == false) {
				this.getUsuarioProponente().addNotificaciones(notificacion);
			}
			
			for (Usuario u1 : this.getSuscriptores()) {
				if (u1.contieneNotificacion(notificacion) == false) {
					u1.addNotificaciones(notificacion);
				}
			}
			this.setClave(followUp);
			return followUp;
		}
	}

	/**
	 * Metodo String toString para imprimir datos del proyecto.
	 */
	public String toString() {
		return "Titulo: " + this.getTitulo() + "  " + this.getEstadoProyecto() + "  " + this.getEstadoFinanciacion(); 
	}
}
