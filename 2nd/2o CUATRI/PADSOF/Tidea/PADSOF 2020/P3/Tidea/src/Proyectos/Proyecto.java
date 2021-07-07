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
	
	
	
	public ArrayList<Colectivo> getColectivosProyecto() {
		return colectivosProyecto;
	}

	public void addColectivosProyecto(Colectivo c) {
		this.colectivosProyecto.add(c);
	}

	public EstadoFinanciacion getEstadoFinanciacion() {
		return estadoFinanciacion;
	}

	public void setEstadoFinanciacion(EstadoFinanciacion estadoFinanciacion) {
		this.estadoFinanciacion = estadoFinanciacion;
	}

	public String getClave() {
		return clave;
	}

	public void setClave(String clave) {
		this.clave = clave;
	}
	

	public ArrayList<Usuario> getSuscriptores() {
		return suscriptores;
	}

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
	 * Solicita financiacion si el proyecto ha llegado al numero de apoyos fijados para que se 
	 * evalue su financiacion.
	 * 
	 * @throws IOException excepcion.
	 * @throws InvalidRequestException excepcion.
	 * @throws InvalidIDException excepcion.
	 * @throws ClassNotFoundException excepcion.
	 */
	public void solicitarFinanciacion() throws IOException, InvalidRequestException, InvalidIDException, ClassNotFoundException {
		/**CAMBIAR **/
		CCGG proxy = CCGG.getGateway();
		int i;
		
		this.actualizarProyecto();
		if(this.getEstadoProyecto() == TipoEstadoProyecto.CADUCADO) {
			return;
		}
		if (this.getEstadoFinanciacion() != EstadoFinanciacion.FINANCIABLE) {
			return;
		}
		
		Notificacion n1 = new Notificacion("Tu proyecto "+ this.getTitulo() +" ha sido enviado para la solicitud de financiacion, tendras el resulado en un tiempo", TipoNotificacion.PROYECTO);
		this.getUsuarioProponente().addNotificaciones(n1);
		
		for (i = 0; i < 10 && proxy == null; i++) {
			proxy = CCGG.getGateway();
		}

		this.setClave(proxy.submitRequest(this));

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
			Notificacion n = new Notificacion("Enhorabuena"+ this.getUsuarioProponente().getNombre() +" tu proyecto "+ this.getTitulo() +"ha sido aprobado.", TipoNotificacion.PROYECTO);
			this.getUsuarioProponente().addNotificaciones(n);
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
		Notificacion n = new Notificacion("Tu proyecto ha sido rechazado porque: "+razon, TipoNotificacion.PROYECTO);
		this.getUsuarioProponente().addNotificaciones(n);
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
	public void apoyarProyecto() throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		this.actualizarProyecto();
		if(this.getEstadoProyecto() == TipoEstadoProyecto.CADUCADO) {
			Notificacion n1 = new Notificacion("El proyecto "+this.getTitulo()+ "Se encuentra caducado por falta de votos.", TipoNotificacion.PROYECTO);
			this.getUsuarioProponente().addNotificaciones(n1);
			return;
		}
		
		if (this.getVotantes().contains(u) == false) {
			this.addVotantes(u);
			this.setFechaUltimoVoto(LocalDate.now());
			u.addProyectosdeUsuario(this);
			Notificacion n2= new Notificacion("Acabas de apoyar el proyecto "+this.getTitulo() +".", TipoNotificacion.PROYECTO);
			this.getUsuarioProponente().addNotificaciones(n2);
		}
		this.actualizarProyecto();
		
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
	public void apoyarProyectoRepresentante(Colectivo c) throws ClassNotFoundException, IOException, InvalidIDException {
		Usuario usuario = Sistema.getInstancia().usuarioLogin();
		this.actualizarProyecto();
		if (c.getRepresentante().equals(usuario)) {
			for (Colectivo s : c.getSubcolectivos()) {
				apoyarSubc(this, s);
			}
			for (Usuario u : c.getIntegrantesColectivo()) {
				if (this.getVotantes().contains(u) == false && u.getEstado() != TipoEstadoUsuario.BLOQUEADO) {
					this.addVotantes(u);
					Notificacion n2 = new Notificacion("El colectivo "+ c.getNombre() +" ahora apoya el proyecto "+this.getTitulo() +".", TipoNotificacion.PROYECTO);
					u.addNotificaciones(n2);
					this.setFechaUltimoVoto(LocalDate.now());
				}
			}
			if (!usuario.getProyectosdeRepresentante().contains(this)) {
				usuario.addProyectosdeRepresentante(this);
			}
			if (this.getColectivosProyecto().contains(c) == true) {
				Notificacion n4 = new Notificacion("No se ha anadido el proyecto"+ this.getTitulo() +" a la lista de los colectivos apoyados por tu colectivo"+ c.getNombre() +"porque ya estaba anadido", TipoNotificacion.PROYECTO);
				usuario.addNotificaciones(n4);
				return;
			}
			Notificacion n3 = new Notificacion("Se ha anadido el proyecto"+ this.getTitulo() +" a la lista de los colectivos apoyados por tu colectivo"+ c.getNombre(), TipoNotificacion.PROYECTO);
			usuario.addNotificaciones(n3);
			this.addColectivosProyecto(c);
			this.actualizarProyecto();
		}
		
	}

	public void apoyarSubc(Proyecto p, Colectivo c) throws ClassNotFoundException, IOException {
		
		for (Colectivo s : c.getSubcolectivos()) {
			apoyarSubc(p, s);
		}
		
		for (Usuario u : c.getIntegrantesColectivo()) {
			
			if (p.getVotantes().contains(u) == false && u.getEstado() != TipoEstadoUsuario.BLOQUEADO) {
				Notificacion n1 = new Notificacion("El colectivo "+ c.getNombre() +" ahora apoya el proyecto "+this.getTitulo() +".", TipoNotificacion.PROYECTO);
				u.addNotificaciones(n1);
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

	public void suscriberseProyecto () throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		u.addProyectosSuscrito(this);
		this.addSuscriptores(u);
		
	}
	
	public void desSuscriberseProyecto () throws ClassNotFoundException, IOException, InvalidIDException {
		
		Usuario u = Sistema.getInstancia().usuarioLogin();
		
		u.getProyectosSuscrito().remove(this);
		this.getVotantes().remove(u);
		
	}
	
	public void actualizarProyecto () throws ClassNotFoundException, IOException, InvalidIDException {
		
		int apoyos = 0;
				
		for (Usuario votante: this.getVotantes()) {
			if(votante.getEstado() == TipoEstadoUsuario.VALIDADO) {
				apoyos++;
			}
		}
		
		this.setApoyosRecibidos(apoyos);
		
		if (DAYS.between(getFechaUltimoVoto(), getFechaValidacion()) >= 30) {
			
			this.setEstadoProyecto(TipoEstadoProyecto.CADUCADO);
			Notificacion n1 = new Notificacion("El proyecto "+ this.getTitulo() +" esta caducado porque no ha recibido ningun voto en 30 dias.", TipoNotificacion.PROYECTO);
			this.getUsuarioProponente().addNotificaciones(n1);
			
			for (Usuario u1 : this.getSuscriptores()) {
				u1.addNotificaciones(n1);
			}
			
			for (Usuario u2 : this.getVotantes()) {
				u2.addNotificaciones(n1);
			}
			return;
		}
		
		if(this.getApoyosRecibidos() >= Sistema.getInstancia().apoyosFinanciacion) {
			
			this.setEstadoFinanciacion(EstadoFinanciacion.FINANCIABLE);
			Notificacion n2 = new Notificacion("El proyecto "+ this.getTitulo() +" esta en estado financiable porque ha alcanzado los votos necesario, puedes enviarlo a financiar.", TipoNotificacion.PROYECTO);
			this.getUsuarioProponente().addNotificaciones(n2);
		}
		
		/*
		double cantidad;
		CCGG proxy = CCGG.getGateway();
		System.out.println(proxy.getAmountGranted(this.clave));
		cantidad = proxy.getAmountGranted(this.clave);

		if (cantidad > 0) {
			this.setEstadoFinanciacion(EstadoFinanciacion.FINANCIADO);
			this.setImporteConcedido(cantidad);
		}
		*/
		
		if(this.getEstadoFinanciacion().equals(EstadoFinanciacion.FINANCIADO)) {
			
			Notificacion n3 = new Notificacion("El proyecto "+ this.getTitulo() +" ha sido financiado, enhorabuena!.", TipoNotificacion.PROYECTO);
			this.getUsuarioProponente().addNotificaciones(n3);
			
			for (Usuario u5 : this.getSuscriptores()) {
				u5.addNotificaciones(n3);
			}
			
			for (Usuario u6 : this.getVotantes()) {
				u6.addNotificaciones(n3);
			}
		}
	}

	/**
	 * Metodo String toString para imprimir datos del proyecto.
	 */
	public String toString() {
		return "Titulo: " + this.getTitulo();
	}
}
