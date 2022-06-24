package Testers;

import Usuarios.*;

import Colectivos.Colectivo;
import Proyectos.*;
import Sistemas.*;


public class Main1 {
	public static void main(String[] args) throws InterruptedException {
		final Sistema sistema;
		Usuario usuario1, usuario2, admin;
		Proyecto proyecto1, proyecto2;
		Colectivo c1;
		
		/* obtenemos una instancia del sistema */
		sistema = Sistema.getInstancia();
		
		/* Registramos dos usuarios */
		System.out.println("Registrando al usuario con NIF: 11111111");
		usuario1 = sistema.registrarse("11111111", "usuario1");
		System.out.println("Usuario con NIF :" + usuario1.getNIF() + " registrado!\nEstado: "+ usuario1.getTipo());
		System.out.println("Registrando al usuario con NIF: 22222222");
		usuario2 = sistema.registrarse("22222222", "usuario2");
		System.out.println("Usuario con NIF :" + usuario2.getNIF() + " registrado!\nEstado: "+ usuario2.getTipo());
		
		admin = sistema.getAdmin();
		
		/* hacemos logIn del administrador para que pueda realizar tareas */
		admin.loginUsuario("admin", "admin");
		
		/* El administrador valida a los usuarios 1 y 2, previamente registrados */
		admin.validarUsuario(usuario1);
		System.out.println("Estado del usuario tras ser validado " + usuario1.getNIF() + ": " + usuario1.getTipo());
		admin.validarUsuario(usuario2);
		System.out.println("Estado del usuario tras ser validado " + usuario2.getNIF() + ": " + usuario2.getTipo());
		
	
		/* los dos usuarios pueden hacer LogIn ya que el admin los ha validado */
		usuario1.loginUsuario("11111111", "usuario1");
		usuario2.loginUsuario("22222222", "usuario2");
		
		/* Hacemos que cada usuario cree un tipo de proyecto*/
		proyecto1 = usuario1.crearProyectoInfraestructura("Proyecto de infraestructura numero 1", "Descripcion del primer proyecto de infraestructura", 5000.00, "imagen");
		proyecto2 = usuario2.crearProyectoSocial("Proyecto social numero 1", "Descripcion del primer proyecto social", 2500.00, "Grupo social numero 1");
		
		System.out.println("Proponente del " + proyecto1.getTitulo() + ": " + proyecto1.getUsuarioProponente().getNIF());
		System.out.println("Estado del "+ proyecto1.getTitulo() + ": " + proyecto1.getEstadoProyecto());
		admin.aprobarProyecto(proyecto1);
		System.out.println("Estado del "+ proyecto1.getTitulo() + ": " + proyecto1.getEstadoProyecto());
		
		
	}
}
