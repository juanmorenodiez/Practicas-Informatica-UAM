package Usuarios;
import java.util.ArrayList;
import java.util.Date;

import Proyectos.Proyecto;
import Sistemas.*;


public class Usuario {
	private String NIF;
	private String password;
	private TipoUsuario tipo;
	private boolean loggedIn;
	private TipoEstadoUsuario estadoUsuario;
	private ArrayList<Proyecto> proyectosdeUsuario;

	
	public Usuario(String NIF, String password, TipoUsuario tipo) {
		this.setNIF(NIF);
		this.setPassword(password);
		this.setTipo(tipo);
		this.setLoggedIn(false);
		this.setEstadoUsuario(TipoEstadoUsuario.PENDIENTEVALIDAR);
	}

	public String getNIF() {
		return NIF;
	}

	public void setNIF(String NIF) {
		this.NIF = NIF;
	}

	public String getPassword() {
		return password;
	}

	public void setPassword(String password) {
		this.password = password;
	}

	public TipoUsuario getTipo() {
		return tipo;
	}

	public void setTipo(TipoUsuario tipo) {
		this.tipo = tipo;
	}

	public TipoEstadoUsuario getEstadoUsuario() {
		return estadoUsuario;
	}

	public void setEstadoUsuario(TipoEstadoUsuario estadoUsuario) {
		this.estadoUsuario = estadoUsuario;
	}
	
	public ArrayList<Proyecto> getProyectosdeUsuario() {
		return proyectosdeUsuario;
	}
	
	public void rechazarUsuario(Usuario u) {
		if(this.tipo.getValor() == 0) {
			Sistema.getInstancia().rechazarUsuario(u);
		}
	}
	
	public void validarUsuario(Usuario u) {
		if( this.getTipo() == TipoUsuario.ADMINISTRADOR) {
			if(this.tipo.getValor() == 0) {
				Sistema.getInstancia().validarUsuario(u);
			}
		}
		return;
		
	}
	
	public Proyecto crearProyecto(String titulo, String descr, Date fecha, double importeSolicitado) {
		
		if(this.getEstadoUsuario() == TipoEstadoUsuario.VALIDADO && this.getTipo() == TipoUsuario.USUARIOREGISTRADO && this.isLoggedIn() == true) {
			Proyecto p = new Proyecto(titulo, descr, fecha, importeSolicitado);
			p.setUsuarioProponente(this);
			Sistema.getInstancia().getProyectos().add(p);
			return p;
		}
		return null;		
	}

	public boolean isLoggedIn() {
		return loggedIn;
	}

	public void setLoggedIn(boolean loggedIn) {
		this.loggedIn = loggedIn;
	}

	public String toString() {
		return "NIF: " + this.getNIF() + "\n Pass: " + this.getPassword() + "\n Estado: " + this.getEstadoUsuario() + "\n Tipo: " + this.getTipo() + "\n Logged: " + this.isLoggedIn() + "\n\n";
 	}
	
}
