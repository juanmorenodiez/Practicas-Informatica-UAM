package Testers;

import Usuarios.*;
import es.uam.eps.sadp.grants.InvalidIDException;

import java.io.IOException;

import java.io.File;

import Colectivos.Colectivo;
import Proyectos.*;
import Sistemas.*;

/**
 * Tester de todas las clases que prueba como seria la funcionalidad si algunos
 * usuario interactuaran con la aplicacion.
 * 
 * @author Diego Cano, Juan Moreno y Julio Carreras.
 * @version 1.11
 * @since 1.1
 *
 */
public class Main1 {
	public static void main(String[] args) throws InterruptedException, IOException, ClassNotFoundException, InvalidIDException {
		final Sistema sistema;
		Usuario usuario1, usuario2, usuario3, usuario4, usuario5, usuario6,usuario7, usuario8, usuario9, usuario10, usuario11, usuario12, usuario13, usuario14, usuario15, admin;
		Proyecto proyecto1, proyecto2, proyecto3, proyecto4, proyecto5, proyecto6;
		Colectivo colectivo1, colectivo2, colectivo3, colectivo4, colectivo5, colectivo6, colectivo7;
		
		/**
		 * obtenemos una instancia del sistema
		 */
		sistema = Sistema.getInstancia();

		/**
		 * Registramos todos los usuarios(6)
		 */
		usuario1 = sistema.registrarse("JuanMoreno", "11111111", "usuario1");
		usuario2 = sistema.registrarse("JulioCarreras", "22222222", "usuario2");
		usuario3 = sistema.registrarse("DiegoCano", "33333333", "usuario3");
		usuario4 = sistema.registrarse("BadBunny", "44444444", "usuario4");
		usuario5 = sistema.registrarse("Ozuna", "55555555", "usuario5");
		usuario6 = sistema.registrarse("AnuelAA", "66666666", "usuario6");
		usuario7 = sistema.registrarse("DaddyYankee", "77777777", "usuario7");
		usuario8 = sistema.registrarse("JBalvin", "88888888", "usuario8");
		usuario9 = sistema.registrarse("OmarMontes", "99999999", "usuario9");
		usuario10 = sistema.registrarse("NickyJam", "10101010", "usuario10");
		usuario11 = sistema.registrarse("KarolG", "111111111", "usuario11");
		usuario12 = sistema.registrarse("Farruko", "12121212", "usuario12");
		usuario13 = sistema.registrarse("Brytiago", "13131313", "usuario13");
		usuario14 = sistema.registrarse("Darel", "14141414", "usuario14");
		usuario15 = sistema.registrarse("MykeTowers", "15151515", "usuario15");

		/**
		 * obtenemos el administrador del sistema
		 */
		admin = sistema.getAdmin();

		/**
		 * hacemos logIn del administrador para que pueda realizar tareas
		 */
		sistema.logIn("admin", "admin");

		/**
		 * El administrador valida a todos los usuarios del sistema
		 */
		admin.validarUsuario(usuario1);
		admin.validarUsuario(usuario2);
		admin.validarUsuario(usuario3);
		admin.validarUsuario(usuario4);
		admin.validarUsuario(usuario5);
		admin.validarUsuario(usuario6);
		admin.validarUsuario(usuario7);
		admin.validarUsuario(usuario8);
		admin.validarUsuario(usuario9);
		admin.validarUsuario(usuario10);
		admin.validarUsuario(usuario11);
		admin.validarUsuario(usuario12);
		admin.validarUsuario(usuario13);
		admin.validarUsuario(usuario14);
		admin.validarUsuario(usuario15);
		sistema.logOut(admin);

		sistema.logIn("11111111", "usuario1");
		proyecto1 = sistema.crearProyectoInfraestructura(usuario1, "Proyecto I1", "Descripcion del primer proyecto de infraestructura", 1000.00, ".." + File.separator + "Tidea" + File.separator + "src" + File.separator + "Imagenes" + File.separator + "forest.jpg", sistema.getDistritos());
		sistema.logOut(usuario1);
		
		sistema.logIn("22222222", "usuario2");
		proyecto2 = sistema.crearProyectoSocial(usuario2, "Proyecto S1", "Descripcion del primer proyecto social", 2000.00, "Grupo social numero 1", true);
		sistema.logOut(usuario2);
		
		sistema.logIn("33333333", "usuario3");
		proyecto3 = sistema.crearProyectoInfraestructura(usuario3, "Proyecto I2", "Descripcion del segundo proyecto de infraestructura", 1500.00, ".." + File.separator + "Tidea" + File.separator + "src" + File.separator + "Imagenes" + File.separator + "forest.jpg", sistema.getDistritos());
		sistema.logOut(usuario3);
		
		sistema.logIn("44444444", "usuario4");
		proyecto4 = sistema.crearProyectoSocial(usuario4, "Proyecto S2", "Descripcion del segundo proyecto social", 2500.00, "Grupo social numero 2", false);
		sistema.logOut(usuario4);
		
		sistema.logIn("55555555", "usuario5");
		proyecto5 = sistema.crearProyectoInfraestructura(usuario5, "Proyecto I3", "Descripcion del primer proyecto de infraestructura", 3000.00, "../Tidea/src/Imagenes/forest.jpg", sistema.getDistritos());
		sistema.logOut(usuario5);
		
		sistema.logIn("66666666", "usuario6");
		proyecto6 = sistema.crearProyectoSocial(usuario6, "Proyecto S3", "Descripcion del tercer proyecto social", 4000.00, "Grupo social numero 3", true);
		sistema.logOut(usuario6);
		
		sistema.logIn("admin", "admin");
		proyecto1.aprobarProyecto();
		proyecto2.aprobarProyecto();
		proyecto3.aprobarProyecto();
		proyecto4.aprobarProyecto();
		proyecto5.aprobarProyecto();
		proyecto6.aprobarProyecto();
		sistema.logOut(admin);


		sistema.logIn("11111111", "usuario1");
		colectivo1 = usuario1.crearColectivo("Animales");
		sistema.logOut(usuario1);
		
		sistema.logIn("44444444", "usuario4");
		colectivo2 = colectivo1.crearSubColectivo("Reptiles");
		sistema.logOut(usuario4);
		
		sistema.logIn("66666666", "usuario6");
		colectivo3 = colectivo1.crearSubColectivo("Mamiferos");
		sistema.logOut(usuario6);
		
		sistema.logIn("99999999", "usuario9");
		System.out.println(sistema.usuarioLogin());
		colectivo4 = colectivo2.crearSubColectivo("Serpientes");
		sistema.logOut(usuario9);
		
		sistema.logIn("111111111", "usuario11");
		colectivo5 = colectivo2.crearSubColectivo("Lagartos");
		sistema.logOut(usuario11);
		
		sistema.logIn("13131313", "usuario13");
		colectivo6 = colectivo3.crearSubColectivo("Ballenas");
		sistema.logOut(usuario13);
		
		sistema.logIn("88888888", "usuario8");
		colectivo7 = colectivo3.crearSubColectivo("Elefantes");
		sistema.logOut(usuario8);

		sistema.logIn("22222222", "usuario2");
		colectivo1.unirseColectivo();
		sistema.logOut(usuario2);
		sistema.logIn("33333333", "usuario3");
		colectivo1.unirseColectivo();
		sistema.logOut(usuario3);
		
		sistema.logIn("55555555", "usuario5");
		colectivo2.unirseColectivo();
		sistema.logOut(usuario5);
		
		sistema.logIn("77777777", "usuario7");
		colectivo3.unirseColectivo();
		sistema.logOut(usuario7);
		
		sistema.logIn("10101010", "usuario10");
		colectivo4.unirseColectivo();
		sistema.logOut(usuario10);
		
		sistema.logIn("12121212", "usuario12");
		colectivo5.unirseColectivo();
		sistema.logOut(usuario12);
		
		sistema.logIn("14141414", "usuario14");
		colectivo6.unirseColectivo();
		sistema.logOut(usuario14);
		
		sistema.logIn("15151515", "usuario15");
		colectivo7.unirseColectivo();
		sistema.logOut(usuario15);
		
		sistema.logIn("11111111", "usuario1");
		proyecto1.apoyarProyectoRepresentante(colectivo1);
		sistema.logOut(usuario1);
		
		sistema.logIn("44444444", "usuario4");
		proyecto2.apoyarProyectoRepresentante(colectivo2);
		sistema.logOut(usuario4);
		
		sistema.logIn("66666666", "usuario6");
		proyecto3.apoyarProyectoRepresentante(colectivo3);
		sistema.logOut(usuario6);
		
		sistema.logIn("99999999", "usuario9");
		proyecto4.apoyarProyectoRepresentante(colectivo4);
		sistema.logOut(usuario9);
		
		sistema.logIn("111111111", "usuario11");
		proyecto5.apoyarProyectoRepresentante(colectivo5);
		sistema.logOut(usuario11);
		
		sistema.logIn("13131313", "usuario13");
		proyecto6.apoyarProyectoRepresentante(colectivo6);
		sistema.logOut(usuario13);
		
		sistema.logIn("12121212", "usuario12");
		colectivo7.unirseColectivo();
		sistema.logOut(usuario12);
		
		sistema.logIn("88888888", "usuario8");
		proyecto6.apoyarProyectoRepresentante(colectivo7);
		sistema.logOut(usuario8);
		
		sistema.logIn("12121212", "usuario12");
		colectivo7.abandonarColectivo();
		sistema.logOut(usuario12);
		
		
		System.out.println("Proyecto 1: " + proyecto1.getApoyosRecibidos());
		System.out.println("Proyecto 2: " + proyecto2.getApoyosRecibidos());
		System.out.println("Proyecto 3: " + proyecto3.getApoyosRecibidos());
		System.out.println("Proyecto 4: " + proyecto4.getApoyosRecibidos());
		System.out.println("Proyecto 5: " + proyecto5.getApoyosRecibidos());
		System.out.println("Proyecto 6: " + proyecto6.getApoyosRecibidos());
		
		
		
		
		
		
		

		
	}
}
