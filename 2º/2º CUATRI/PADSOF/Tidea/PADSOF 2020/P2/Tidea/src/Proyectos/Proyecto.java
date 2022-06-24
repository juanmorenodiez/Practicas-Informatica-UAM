package Proyectos;
import java.util.ArrayList;
import java.util.Date;

import Usuarios.Usuario;

public class Proyecto {
	private String titulo;
	private String descripcion;
	private double importeSolicitado;
	private double importeConcedido;
	private Usuario usuarioProponente;
	private TipoEstadoProyecto estadoProyecto;
	private Integer id;
	private Integer apoyosRecibidos;
	private Integer apoyosFinanciacion;
	private ArrayList<Usuario> integrantes;
	private Date fechaCreacion;
	private Date fechaUltimoVoto;
	
	public Proyecto (String titulo, String descr, Date fecha, double importeSolicitado) {
		this.titulo = titulo;
		this.descripcion = descr;
		this.apoyosRecibidos = 0;
		this.setImporteSolicitado(importeSolicitado);
		this.setEstadoProyecto(TipoEstadoProyecto.PENDIENTEVALIDACION);
	}
	
	
	public String getTitulo() {
		return titulo;
	}
	
	public void setTitulo(String titulo) {
		this.titulo = titulo;
	}
	
	public String getDescripcion() {
		return descripcion;
	}
	
	public void setDescripcion(String descripcion) {
		this.descripcion = descripcion;
	}
	
	public Integer getApoyosRecibidos() {
		return apoyosRecibidos;
	}
	
	public void setApoyosRecibidos(Integer apoyosRecibidos) {
		this.apoyosRecibidos = apoyosRecibidos;
	}
	
	public Integer getApoyosFinanciacion() {
		return apoyosFinanciacion;
	}
	
	public void setApoyosFinanciacion(Integer apoyosFinanciacion) {
		this.apoyosFinanciacion = apoyosFinanciacion;
	}
	
	public Date getFechaCreacion() {
		return fechaCreacion;
	}
	
	public void setFechaCreacion(Date fecha) {
		this.fechaCreacion = fecha;
	}

	public TipoEstadoProyecto getEstadoProyecto() {
		return estadoProyecto;
	}

	public void setEstadoProyecto(TipoEstadoProyecto estadoProyecto) {
		this.estadoProyecto = estadoProyecto;
	}
	
	


	public double getImporteSolicitado() {
		return importeSolicitado;
	}


	public void setImporteSolicitado(double importeSolicitado) {
		this.importeSolicitado = importeSolicitado;
	}


	public double getImporteConcedido() {
		return importeConcedido;
	}


	public void setImporteConcedido(double importeConcedido) {
		this.importeConcedido = importeConcedido;
	}


	public Usuario getUsuarioProponente() {
		return usuarioProponente;
	}


	public void setUsuarioProponente(Usuario usuarioProponente) {
		this.usuarioProponente = usuarioProponente;
	}


	public Integer getId() {
		return id;
	}


	public void setId(Integer id) {
		this.id = id;
	}


	public ArrayList<Usuario> getIntegrantes() {
		return integrantes;
	}


	public Date getFechaUltimoVoto() {
		return fechaUltimoVoto;
	}


	public void setFechaUltimoVoto(Date fechaUltimoVoto) {
		this.fechaUltimoVoto = fechaUltimoVoto;
	}
	
	public String toString() {
		return this.getTitulo() + "\n" + this.getDescripcion();
	}

}
