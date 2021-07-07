package Sistemas;

import java.util.*;

import Usuarios.*;
import Proyectos.*;

public class Sistema {
	private static Sistema instancia = null;
	private final Usuario admin;
	private ArrayList<Usuario> usuarios;
	private ArrayList<Proyecto> proyectos;
	
	public synchronized static Sistema getInstancia() {
		if(instancia == null) {
			instancia = new Sistema();
		}
		return instancia;
	}
	
	private Sistema () {
		this.usuarios = new ArrayList<Usuario>();
		this.proyectos = new ArrayList<Proyecto>();
		this.admin = new Usuario("admin", "admin", TipoUsuario.ADMINISTRADOR);
	}
	
	public Usuario getAdmin() {
		return admin;
	}
	
	public ArrayList<Proyecto> getProyectos() {
		return proyectos;
	}

	public ArrayList<Usuario> getUsuarios() {
		return usuarios;
	}
	
	
	public void validarUsuario(Usuario u) {
		if (u == null || !this.usuarios.contains(u)) {
			return;
		}
		
		u.setEstadoUsuario(TipoEstadoUsuario.VALIDADO);
	}
	
	
	public void rechazarUsuario(Usuario u) {
		if (u == null || !this.usuarios.contains(u)) {
			return;
		}
		
		this.usuarios.remove(u);
	}
	
	
	public void aprobarProyecto(Proyecto p) {
		if (p == null || !this.proyectos.contains(p)) {
			return;
		}
		
		p.setEstadoProyecto(TipoEstadoProyecto.VALIDADO);
	}
	
	
	public void rechazarProyecto(Proyecto p) {
		if (p == null || !this.proyectos.contains(p)) {
			return;
		}
		
		this.proyectos.remove(p);
	}
	

	public Usuario registrarse(String NIF, String password) {
		if (NIF == null || password == null) {
			return null;
		}
		
		for (Usuario u : usuarios) {
			if (u.getNIF() == NIF){
				return null;
			}
		}
		
		Usuario u = new Usuario(NIF, password, TipoUsuario.USUARIOREGISTRADO);
		this.usuarios.add(u);
		
		return u;
	}
	
	public Usuario LogIn(String NIF, String password) {
		if (NIF == null || password  == null) {
			return null;
		}
		
		for (Usuario u : usuarios) {
			if (u.getNIF() == NIF && u.getPassword() == password && u.getEstadoUsuario() == TipoEstadoUsuario.VALIDADO) {
				u.setLoggedIn(true);
				return u;
			}
		}
		return null;
	}
	
	public void logOut(Usuario u) {
		if (u == null || !this.usuarios.contains(u)) {
			return;
		}
		
		u.setLoggedIn(false);
	}
	
}
